CFLAGS=	-I "./Inc"
CC= gcc
CCX= g++

gcc: output Run			# to build & run for C language
g++: outputX Run		# to build & run for C++ language


output: main.o CircularBuffer.o
	$(CC)  ./Lib/main.o ./Lib/CircularBuffer.o -o ./Bin/out
outputX: mainX.o CircularBufferX.o
	$(CCX)  ./Lib/main.o ./Lib/CircularBuffer.o -o ./Bin/out

main.o:
	$(CC)  $(CFLAGS) -c ./Src/main.c -o ./Lib/main.o
mainX.o:
	$(CCX)  $(CFLAGS) -c ./Src/main.cpp -o ./Lib/main.o

CircularBuffer.o:
	$(CC) $(CFLAGS) -c ./Src/CircularBuffer.c -o ./lib/CircularBuffer.o
CircularBufferX.o:
	$(CCX) $(CFLAGS) -c ./Src/CircularBuffer.c -o ./lib/CircularBuffer.o

clean:
	del lib .o
	del bin .exe

Run:
	./Bin/out.exe