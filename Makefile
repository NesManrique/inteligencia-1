

all: ideastar ida

ideastar: aestrella.h aestrella.cpp
	g++ aestrella.cpp aestrella.h -o idas -O3

ida: idaman.c staticboard.h
	gcc idaman.c staticboard -O3 -o ida

