all: lib test

lib: out out/lib.a

test: out out/test-gc out/test-gc.string out/test-tree out/test-tree.remove

clean:
	rm -Rf out

out/%.o: src/%.c
	gcc -c -o $@ $?

out/lib.a: out/gc.o out/tree.o
	ar rcs $@ $?

out/%_debug.o: src/%.c
	gcc -D DEBUG= -c -o $@ $?

out/debug.a: out/gc_debug.o out/tree_debug.o
	ar rcs $@ $?

out/test-%: src/test-%.c out/debug.a
	gcc -o $@ $?

out:
	mkdir out
