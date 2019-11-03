all: out out/gc.o out/test-gc out/test-gc.string out/test-tree out/test-tree.remove

lib: out/gc.a

clean:
	rm -R out

out/gc.o: src/gc.c
	gcc -c -o out/gc.o src/gc.c

out/tree.o: src/tree.c
	gcc -c -o out/tree.o src/tree.c

out/gc.a: out/gc.o out/tree.o
	ar rcs out/gc.a out/gc.o out/tree.o

out/gc_debug.o: src/gc.c
	gcc -D DEBUG= -c -o out/gc_debug.o src/gc.c

out/tree_debug.o: src/tree.c
	gcc -D DEBUG= -c -o out/tree_debug.o src/tree.c

out/gc_debug.a: out/gc_debug.o out/tree_debug.o
	ar rcs out/gc_debug.a out/gc_debug.o out/tree_debug.o

out/test-gc: src/test-gc.c out/gc_debug.a
	gcc -o out/test-gc src/test-gc.c out/gc_debug.a

out/test-gc.string: src/test-gc.string.c out/gc_debug.a
	gcc -o out/test-gc.string src/test-gc.string.c out/gc_debug.a

out/test-tree: src/test-tree.c out/gc_debug.a
	gcc -o out/test-tree src/test-tree.c out/gc_debug.a

out/test-tree.remove: src/test-tree.remove.c out/gc_debug.a
	gcc -o out/test-tree.remove src/test-tree.remove.c out/gc_debug.a

out:
	mkdir out
