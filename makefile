all: out out/test-gc out/test-gc.string out/test-tree out/test-tree.remove

clean:
	rm -R out

out/test-gc: src/test-gc.c src/gc.c
	gcc -D DEBUG= -o out/test-gc src/test-gc.c src/gc.c

out/test-gc.string: src/test-gc.string.c src/gc.c
	gcc -D DEBUG= -o out/test-gc.string src/test-gc.string.c src/gc.c

out/test-tree: src/test-tree.c src/tree.c src/gc.c
	gcc -D DEBUG= -o out/test-tree src/test-tree.c src/tree.c src/gc.c

out/test-tree.remove: src/test-tree.remove.c src/tree.c src/gc.c
	gcc -D DEBUG= -o out/test-tree.remove src/test-tree.remove.c src/tree.c src/gc.c

out:
	mkdir out
