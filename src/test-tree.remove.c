#include "tree.h"
#include "gc.h"
#include <stdio.h>

void test(char* c)
{
  printf("=%c\n",*c);
}

void set(void* t,const char* key,char c)
{
  char* p=gc_new(0,1,(void (*)(void*))&test);
  *p=c;
  tree_set(t,key,p);
}

void del(void* t,const char* key)
{
  tree_set(t,key,0);
  gc_mark(t);
  gc_sweep();
}

int main()
{
  gc_sweep();
  void* t=tree_new();
  set(t,"abc",'3');
  set(t,"aa",'2');
  set(t,"b",'1');
  set(t,"ab",'0');
  set(t,"",'x');
  set(t,"a",'A');
  gc_mark(t);
  gc_sweep();
  del(t,"aa");
  del(t,"ab");
  del(t,"abc");
  del(t,"b");
  gc_sweep();
  return 0;
}
