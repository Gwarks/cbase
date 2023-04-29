#include "gc.h"
#include <stdio.h>

GC_BLOCK_START(Tsx)
  Tsx* a;
  Tsx* b;
GC_BLOCK_CENTER
  int i;
GC_BLOCK_END

void test(void* p)
{
  printf("TEST2: %p\n",p);
}

int main()
{
  Tsx* x;
  GC gc=gc_create();
  gc_sweep(gc);
  x=GC_NEW_BLOCK(gc,Tsx);
  x->a=0;
  x->b=0;
  x=GC_NEW_BLOCK(gc,Tsx);
  x->a=GC_NEW_BLOCK(gc,Tsx);
  x->a->a=GC_NEW_BLOCK(gc,Tsx);
  x->a->b=0;
  x->b=GC_NEW_BLOCK(gc,Tsx);
  x->b->a=x;
  x->b->b=x;
  gc_mark(gc,x);
  x=GC_NEW_BLOCK(gc,Tsx);
  x->a=GC_NEW_BLOCK(gc,Tsx);
  x->b=0;
  gc_mark(gc,x);
  printf("TEST1: %p\n",gc_new(gc,0,0,&test));
  gc_sweep(gc);
  x->a=0;
  gc_mark(gc,x);
  gc_new(gc,0,0,0);
  gc_new(gc,0,4096,0);
  gc_new(gc,0,0,0);
  gc_sweep(gc);
  gc_sweep(gc);
  gc_sweep(gc);
  gc_new(gc,0,256,0);
  gc_destroy(gc);
  return 0;
}
