#include "tree.h"
#include "gc.h"
#include <stdio.h>

GC gc;

void test(char* c)
{
  printf("=%c\n",*c);
}

void set(void* t,const char* key,char c)
{
  char* p=gc_new(gc,0,1,(void (*)(void*))&test);
  *p=c;
  tree_set(t,key,p);
}

void del(void* t,const char* key)
{
  tree_set(t,key,0);
  gc_mark(gc,t);
  gc_sweep(gc);
}

int main()
{
  gc=gc_create();
  gc_sweep(gc);
  void* t=tree_new(gc);
  set(t,"abc",'3');
  set(t,"aa",'2');
  set(t,"b",'1');
  set(t,"ab",'0');
  set(t,"",'x');
  set(t,"a",'A');
  gc_mark(gc,t);
  gc_sweep(gc);
  del(t,"aa");
  del(t,"ab");
  del(t,"abc");
  del(t,"b");
  gc_sweep(gc);
  gc_destroy(gc);
  return 0;
}
