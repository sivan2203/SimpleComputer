bin/prog: build/main.o lib/libmyTerm.a lib/libmybigChars.a bin
	gcc build/main.o -L./lib -lmyTerm -L./lib -lmybigChars -o bin/prog

build/main.o: src/main.c src/myTerm.h src/bigChars.h build
	gcc -Wall -Werror -c src/main.c -o build/main.o 

lib/libmyTerm.a: build/myTerm.o lib
	ar rc lib/libmyTerm.a build/myTerm.o

build/myTerm.o: src/myTerm.c src/myTerm.h build
	gcc -Wall -Werror -c src/myTerm.c -o build/myTerm.o 

lib/libmybigChars.a: build/bigChars.o build/myTerm.o lib
	ar rc lib/libmybigChars.a build/bigChars.o build/myTerm.o

build/bigChars.o: src/bigChars.c src/bigChars.h src/myTerm.h build
	gcc -Wall -Werror -c src/bigChars.c -o build/bigChars.o 

build: 
	mkdir build

bin:
	mkdir bin

lib:
	mkdir lib

clean: 
	rm -rf bin build lib *.bin

.PHONY: all clean 