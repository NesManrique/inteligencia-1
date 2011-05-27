

all: ideastar

ideastar: aestrella.h aestrella.cpp
	g++ aestrella.cpp aestrella.h -o ida -O3
