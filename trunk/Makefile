
all: idaman idapdb

idapdb: staticboard.h idapdb.cpp
	g++ idapdb.cpp staticboard.h -O3 -o idapdb

idaman: idaman.c staticboard.h
	gcc idaman.c staticboard.h -O3 -o idaman

