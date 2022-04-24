CFLAGS=	-I "./Inc"
CC= gcc

CompileandRun:	All Run


All: main.o Sorting.o
	$(CC) ./Lib/main.o ./Lib/Sorting.o -o ./Bin/out

main.o:
	$(CC) $(CFLAGS) -c ./Src/main.c -o ./Lib/main.o

Sorting.o:
	$(CC) $(CFLAGS) -c ./Src/Sorting.c -o ./lib/Sorting.o

clean:
	del Lib *.o
	del Bin *.exe

Run:
	./Bin/out.exe