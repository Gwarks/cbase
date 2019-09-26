#ifndef _GC_H_
#define _GC_H_

#include <stddef.h>

#define GC_BLOCK_START(x) typedef struct x x;struct x{
#define GC_BLOCK_CENTER char _gc_block_center[0];
#define GC_BLOCK_END };

#define GC_NEW_BLOCK(x) (x*)gc_new(offsetof(x,_gc_block_center)/sizeof(void*),sizeof(x)-offsetof(x,_gc_block_center),0)

void* gc_new(size_t,size_t,void (*)(void*));
void gc_mark(void*);
void gc_sweep();

char* gc_new_string(const char*);

#endif
