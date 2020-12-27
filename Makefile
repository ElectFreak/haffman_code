main: obj/main.o obj/hamming.o obj/matrix.o
	gcc obj/main.o obj/hamming.o obj/matrix.o -o main

obj: 
	mkdir obj;

obj/main.o: src/main.c include/matrix.h include/hamming.h | obj
	gcc -c -I include src/main.c -o obj/main.o

obj/matrix.o: include/matrix.h src/matrix.c | obj
	gcc -c -I include src/matrix.c -o obj/matrix.o

obj/hamming.o: include/hamming.h src/hamming.c include/matrix.h | obj
	gcc -c -I include src/hamming.c -o obj/hamming.o

.PHONY: clean
clean: 
	rm -rf obj main