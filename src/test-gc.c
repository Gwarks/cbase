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
  gc_sweep();
  x=GC_NEW_BLOCK(Tsx);
  x->a=0;
  x->b=0;
  x=GC_NEW_BLOCK(Tsx);
  x->a=GC_NEW_BLOCK(Tsx);
  x->a->a=GC_NEW_BLOCK(Tsx);
  x->a->b=0;
  x->b=GC_NEW_BLOCK(Tsx);
  x->b->a=x;
  x->b->b=x;
  gc_mark(x);
  x=GC_NEW_BLOCK(Tsx);
  x->a=GC_NEW_BLOCK(Tsx);
  x->b=0;
  gc_mark(x);
  printf("TEST1: %p\n",gc_new(0,0,&test));
  gc_sweep();
  x->a=0;
  gc_mark(x);
  gc_new(0,0,0);
  gc_new(0,4096,0);
  gc_new(0,0,0);
  gc_sweep();
  gc_sweep();
  gc_sweep();
  return 0;
}
