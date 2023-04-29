#ifndef _GC_H_
#define _GC_H_

#include <stddef.h>

#define GC_BLOCK_START(x) typedef struct x x;struct x{
#define GC_BLOCK_CENTER char _gc_block_center[0];
#define GC_BLOCK_END };

#define GC_NEW_BLOCK(c,x) (x*)gc_new(c,offsetof(x,_gc_block_center)/sizeof(void*),sizeof(x)-offsetof(x,_gc_block_center),0)
#define GC_NEW_BLOCK_GC(c,x,y) (x*)gc_new(c,offsetof(x,_gc_block_center)/sizeof(void*),sizeof(x)-offsetof(x,_gc_block_center),(void (*)(void*))y)

typedef struct Block Block;
typedef struct Root* GC;

GC gc_create();
void gc_destroy(GC);
void* gc_new(GC,size_t,size_t,void (*)(void*));
void gc_mark(GC,void*);
void gc_sweep(GC);

char* gc_new_string(GC,const char*);

#endif
