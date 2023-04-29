#include "gc.h"
#include <stdio.h>

int main()
{
  GC gc=gc_create();
  gc_sweep(gc);
  char * c=gc_new_string(gc,"Hallo Welt!");
  gc_mark(gc,c);
  gc_sweep(gc);
  printf("%s\n",c);
  gc_sweep(gc);
  gc_sweep(gc);
  gc_destroy(gc);
}
