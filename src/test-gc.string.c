#include "gc.h"
#include <stdio.h>

int main()
{
  gc_sweep();
  char * c=gc_new_string("Hallo Welt!");
  gc_mark(c);
  gc_sweep();
  printf("%s\n",c);
  gc_sweep();
  gc_sweep();
}
