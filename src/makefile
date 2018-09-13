main.bin: main.o libraryGraphs.o
	gcc main.o libraryGraphs.o -o main.bin
main.o: main.c
	gcc -c main.c
libraryGraphs.o: libraryGraphs.c libraryGraphs.h
	gcc -c libraryGraphs.c
clean:
	rm *.o

