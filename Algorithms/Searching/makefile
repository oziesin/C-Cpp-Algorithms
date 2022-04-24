CFLAGS=	-I "./Inc"
CC= gcc

CompileandRun:	All Run


All: main.o Searching.o
	$(CC)  ./Lib/main.o ./Lib/Searching.o -o ./Bin/out

main.o:
	$(CC) $(CFLAGS) -c ./Src/main.c -o ./Lib/main.o

Searching.o:
	$(CC) $(CFLAGS) -c ./Src/Searching.c -o ./lib/Searching.o

clean:
	del lib .o
	del bin .exe

Run:
	./Bin/out.exe