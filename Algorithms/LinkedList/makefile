CFLAGS=	-I "./Inc"
CC= gcc
CCX= g++


g++: outputX Run		# to build & run for C++ language
gcc: output Run			# to build & run for C language

output: main.o LinkedList.o
	$(CC)  ./Lib/main.o ./Lib/LinkedList.o -o ./Bin/out
outputX: LinkedListX.o mainX.o
	$(CCX)  ./Lib/main.o ./Lib/LinkedList.o -o ./Bin/out

main.o:
	$(CC)  $(CFLAGS) -c ./Src/main.c -o ./Lib/main.o
mainX.o:
	$(CCX)  $(CFLAGS) -c ./Src/main.cpp -o ./Lib/main.o

LinkedList.o:
	$(CC) $(CFLAGS) -c ./Src/LinkedList.c -o ./lib/LinkedList.o
LinkedListX.o:
	$(CCX) $(CFLAGS) -c ./Src/LinkedList.c -o ./lib/LinkedList.o

clean:
	del lib .o
	del bin .exe

Run:
	./Bin/out.exe