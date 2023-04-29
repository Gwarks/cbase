#include "tree.h"

GC_BLOCK_START(Node)
  Node* less;
  Node* more;
  Node* data;
GC_BLOCK_CENTER
  char c;
GC_BLOCK_END

GC_BLOCK_START(Tree)
  Node* root;
  GC gc;
GC_BLOCK_CENTER
GC_BLOCK_END

void* tree_new(GC gc)
{
  Tree* t=GC_NEW_BLOCK(gc,Tree);
  t->root=0;
  t->gc=gc;
  return t;
}

void* remove(Node** n,const char* key)
{
  void* data=0;
  while(*n)
  {
    if((*n)->c<*key)
    {
      n=&(*n)->less;
    }else if((*n)->c>*key){
      n=&(*n)->more;
    }else{
      if(*key)
      {
        data=remove(&(*n)->data,key+1);
        if((*n)->data)return data;
      }else{
        data=(*n)->data;
      }
      if((*n)->less)
      {
        if((*n)->more)
        {
          Node** n2=&(*n)->more;
          while((*n2)->less)n=&(*n2)->less;
          (*n)->data=(*n2)->data;
          (*n)->c=(*n2)->c;
          *n2=(*n)->more;
        }else{
          *n=(*n)->less;
        }
      }else{
        *n=(*n)->more;
      }
    }
  }
  return data;
}

void* tree_set(void* root,const char* key,void* data)
{
  Node** n=&((Tree*)root)->root;
  if(!data)return remove(n,key);
  while(*n)
  {
    if((*n)->c<*key)
    {
      n=&(*n)->less;
    }else if((*n)->c>*key){
      n=&(*n)->more;
    }else{
      if(!*key)
      {
        void* old=(*n)->data;
        (*n)->data=data;
        return old;
      }
      key++;
      n=&(*n)->data;
    }
  }
  while(*key)
  {
    *n=GC_NEW_BLOCK(((Tree*)root)->gc,Node);
    (*n)->less=0;
    (*n)->more=0;
    (*n)->c=*key;
    n=&(*n)->data;
    key++;
  }
  *n=GC_NEW_BLOCK(((Tree*)root)->gc,Node);
  (*n)->less=0;
  (*n)->more=0;
  (*n)->c=0;
  (*n)->data=data;
  return 0;
}

void* tree_get(void* root,const char* key)
{
  Node* n=((Tree*)root)->root;
  while(n)
  {
    if(n->c<*key)
    {
      n=n->less;
    }else if(n->c>*key){
      n=n->more;
    }else{
      if(!*key)return n->data;
      key++;
      n=n->data;
    }
  }
  return 0;
}
