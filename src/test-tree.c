#include "tree.h"
#include "gc.h"
#include <stdio.h>

int main()
{
  GC gc=gc_create();
  gc_sweep(gc);
  void* t=tree_new(gc);
  tree_set(t,"abc",gc_new_string(gc,"Hallo"));
  gc_mark(gc,t);
  gc_sweep(gc);
  tree_set(t,"a",gc_new_string(gc,"Welt"));
  gc_mark(gc,t);
  gc_sweep(gc);
  tree_set(t,"acab",gc_new_string(gc,"!"));
  gc_mark(gc,t);
  gc_sweep(gc);
  tree_set(t,"A",gc_new_string(gc," "));
  gc_mark(gc,t);
  gc_sweep(gc);
  printf("%s\n",tree_get(t,"abc"));
  printf("%s%s%s%s\n",tree_get(t,"abc"),tree_get(t,"A"),tree_get(t,"a"),tree_get(t,"acab"));
  tree_set(t,"a",gc_new_string(gc,"du"));
  gc_mark(gc,t);
  gc_sweep(gc);
  printf("%s%s%s%s\n",tree_get(t,"abc"),tree_get(t,"A"),tree_get(t,"a"),tree_get(t,"acab"));
  gc_sweep(gc);
  gc_sweep(gc);
  gc_destroy(gc);
  return 0;
}
