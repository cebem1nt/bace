CC = clang
CFLAGS = -Wall -Wextra
SRCS = bace/da.h bace/misc.h bace/span.h

bake: $(SRCS)
	mkdir -p build
	python baker.py $(SRCS) -o build/bace.h

test: bake test.c
	$(CC) $(CFLAGS) test.c -I build -o build/test
	./build/test

clean:
	rm -rf build/