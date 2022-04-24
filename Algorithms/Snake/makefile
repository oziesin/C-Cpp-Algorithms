CFLAGS=	-I "./Inc"
CCX= g++


g++: All Run		# to build & run for C++ language

All: main.o Snake.o Feed.o Area.o
	$(CCX)  ./Lib/main.o ./Lib/Snake.o ./Lib/Feed.o ./Lib/Area.o -o ./Bin/out


main.o:
	$(CCX)  $(CFLAGS) -c ./Src/main.cpp -o ./Lib/main.o

Snake.o:
	$(CCX) $(CFLAGS) -c ./Src/Snake.cpp -o ./lib/Snake.o

Feed.o:
	$(CCX) $(CFLAGS) -c ./Src/Feed.cpp -o ./lib/Feed.o

Area.o:
	$(CCX) $(CFLAGS) -c ./Src/Area.cpp -o ./lib/Area.o

clean:
	del lib .o
	del bin .exe

Run:
	./Bin/out.exe