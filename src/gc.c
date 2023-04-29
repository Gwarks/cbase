#include "gc.h"
#include <stdlib.h>
#include <string.h>
#ifdef DEBUG
#include <stdio.h>
#endif

struct Block
{
  Block* next;
  Block** center;
  int gen;
  void (*gc)(void*);
};

struct Root
{
  Block* head;
  int gen;
};

GC gc_create()
{
  struct Root* root=malloc(sizeof(struct Root));
  root->head=0;
  root->gen=1;
  return root;
}

void gc_destroy(GC root)
{
  Block* b=root->head;
  Block* n;
  #ifdef DEBUG
  printf("DESTROY START\n");
  #endif  
  while(b)
  {
    #ifdef DEBUG
    printf("destroy %p\n",b);
    #endif
    if(b->gc)b->gc(b+1);
    n=b->next;
    free(b);
    b=n;
  }
  #ifdef DEBUG
  printf("DESTROY END\n");
  #endif
  free(root);
}

void* gc_new(GC root,size_t nptr,size_t nbyte,void (*gc)(void*))
{
  Block* b=malloc(sizeof(Block)+sizeof(Block*)*nptr+nbyte);
  b->next=root->head;
  root->head=b;
  b->center=((Block**)(b+1))+nptr;
  b->gen=0;
  b->gc=gc;
  #ifdef DEBUG
  printf("new %p  %x %x %p\n",b,nptr,nbyte,gc);
  #endif
  return b+1;
}

void gc_mark(GC root,void* ptr)
{
  Block* b=((Block*)ptr)-1;
  if(b->gen==root->gen)return;
  b->gen=root->gen;
  #ifdef DEBUG
  printf("mark %p\n",b);
  #endif
  for(Block** p=(Block**)ptr;p<b->center;p++)
  {
    if(*p)gc_mark(root,*p);
  }
}

void gc_sweep(GC root)
{
  Block* b=root->head;
  Block** lastptr=&root->head;
  #ifdef DEBUG
  printf("GC START\n");
  #endif
  while(b)
  {
    if(b->gen==root->gen)
    {
      lastptr=&b->next;
      b=b->next;
    }else{
      *lastptr=b->next;
      #ifdef DEBUG
      printf("gc %p\n",b);
      #endif
      if(b->gc)b->gc(b+1);
      free(b);
      b=*lastptr;
    }
  }
  #ifdef DEBUG
  printf("GC END\n");
  #endif
  root->gen+=2;
}

char* gc_new_string(GC root,const char* c)
{
  int l=strlen(c)+1;
  char* p=gc_new(root,0,l,0);
  memcpy(p,c,l);
  return p;
}