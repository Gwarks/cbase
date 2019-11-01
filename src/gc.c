#include "gc.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Block Block;
struct Block
{
  Block* next;
  Block** center;
  int gen;
  void (*gc)(void*);
};

Block* head=0;
int gen=1;

void* gc_new(size_t nptr,size_t nbyte,void (*gc)(void*))
{
  Block* b=malloc(sizeof(Block)+sizeof(Block*)*nptr+nbyte);
  b->next=head;
  head=b;
  b->center=((Block**)(b+1))+nptr;
  b->gen=0;
  b->gc=gc;
  #ifdef DEBUG
  printf("new %p  %x %x %p\n",b,nptr,nbyte,gc);
  #endif
  return b+1;
}

void gc_mark(void* ptr)
{
  Block* b=((Block*)ptr)-1;
  if(b->gen==gen)return;
  b->gen=gen;
  #ifdef DEBUG
  printf("mark %p\n",b);
  #endif
  for(Block** p=(Block**)ptr;p<b->center;p++)
  {
    if(*p)gc_mark(*p);
  }
}

void gc_sweep()
{
  Block* b=head;
  Block** lastptr=&head;
  #ifdef DEBUG
  printf("GC START\n");
  #endif
  while(b)
  {
    if(b->gen==gen)
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
  gen+=2;
}

char* gc_new_string(const char* c)
{
  int l=strlen(c)+1;
  char* p=gc_new(0,l,0);
  memcpy(p,c,l);
  return p;
}
