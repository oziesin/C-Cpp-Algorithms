CFLAGS=	-I "./Inc"
CC= gcc
CCX= g++

gcc: output Run			# to build & run for C language
g++: outputX Run		# to build & run for C++ language


output: main.o Stack.o
	$(CC)  ./Lib/main.o ./Lib/Stack.o -o ./Bin/out
outputX: mainX.o StackX.o
	$(CCX)  ./Lib/main.o ./Lib/Stack.o -o ./Bin/out

main.o:
	$(CC)  $(CFLAGS) -c ./Src/main.c -o ./Lib/main.o
mainX.o:
	$(CCX)  $(CFLAGS) -c ./Src/main.cpp -o ./Lib/main.o

Stack.o:
	$(CC) $(CFLAGS) -c ./Src/Stack.c -o ./lib/Stack.o
StackX.o:
	$(CCX) $(CFLAGS) -c ./Src/Stack.c -o ./lib/Stack.o

clean:
	del lib .o
	del bin .exe

Run:
	./Bin/out.exe