FileManager.o : FileManager.cpp FileManager.h
	g++ -c fpermissive FileManager.cpp

mycat.o : mycat.cpp
	g++ -c fpermissive mycat.cpp

mycat : mycat.o FileManager.o
	g++ -o mycat mycat.o FileManager.o

mycp.o : mycp.cpp
	g++ -c -fpermissive mycp.cpp

mycp : mycp.o FileManager,o
	g++ -o mycp mycp.o FileManager.o

mydiff.o : mydiff.cpp
	g++ -c -fpermissive mydiff.cpp

mydiff : mydiff.o FileManager.o
	g++ -o mydiff mydiff.o FileManager.o

myls.o : myls.cpp
	g++ -c -fpermissive myls.cpp

myls : mylas.o FileManager.o
	g++ myls myls.o FileManager.o

mymv.o : mymv.coo
	g++ -c -fpermissive mymv.cpp

mymv : mymv.o FileManager.o
	g++ -o mymv mymv.o FileManager.o

myrm.o : myrm.cpp
	g++ -c -fpermissive myrm.cpp

myrm : myrm.o FileManager.o
	g++ -o myrm myrm.o FileManager.o

mystat.o : mystat.cpp
	g++ -o -fpermissive mystat.cpp

mystat : mystat.o FileManager.o
	g++ -o mystat mystat.o FileManager.o

clean :
	rm *.o

all: mycat mydiff mycp myrm mystat mymv myls