#ifndef _TREE_H_
#define _TREE_H_
#include "gc.h"

void* tree_new(GC);
void* tree_set(void*,const char*,void*);
void* tree_get(void*,const char*);

#endif
