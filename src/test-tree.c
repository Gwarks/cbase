#include "tree.h"
#include "gc.h"
#include <stdio.h>

int main()
{
  gc_sweep();
  void* t=tree_new();
  tree_set(t,"abc",gc_new_string("Hallo"));
  gc_mark(t);
  gc_sweep();
  tree_set(t,"a",gc_new_string("Welt"));
  gc_mark(t);
  gc_sweep();
  tree_set(t,"acab",gc_new_string("!"));
  gc_mark(t);
  gc_sweep();
  tree_set(t,"A",gc_new_string(" "));
  gc_mark(t);
  gc_sweep();
  printf("%s\n",tree_get(t,"abc"));
  printf("%s%s%s%s\n",tree_get(t,"abc"),tree_get(t,"A"),tree_get(t,"a"),tree_get(t,"acab"));
  tree_set(t,"a",gc_new_string("du"));
  gc_mark(t);
  gc_sweep();
  printf("%s%s%s%s\n",tree_get(t,"abc"),tree_get(t,"A"),tree_get(t,"a"),tree_get(t,"acab"));
  gc_sweep();
  gc_sweep();
  return 0;
}
