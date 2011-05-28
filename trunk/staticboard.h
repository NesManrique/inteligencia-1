#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <iostream>
//using namespace std;

const short masks[4] = {0xf000, 0x0f00, 0x00f0, 0x000f};

typedef struct estado{
    unsigned short tablero [4][4];
    unsigned short white [2];
    unsigned short h;
} State;

/* Funcion que calcula la heuristica */
short heuristica(State s);

/* Constructor */
State sboard(){

    State board;
	int i,j,n;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			scanf("%d",&n);
			board.tablero[i][j]=n;
			if(n==0){
				board.white[0]=i;
				board.white[1]=j;
			}
		}
	}
  
	/* scanf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
			&board.tablero[0][0], &board.tablero[0][1], &board.tablero[0][2], &board.tablero[0][3],
			&board.tablero[1][0], &board.tablero[1][1], &board.tablero[1][2], &board.tablero[1][3],
			&board.tablero[2][0], &board.tablero[2][1], &board.tablero[2][2], &board.tablero[2][3],
			&board.tablero[3][0], &board.tablero[3][1], &board.tablero[3][2], &board.tablero[3][3]);
    printf("Escribe la posicion del blanco < 0 1 > :\n");
    scanf("%d %d", &board.white[0], &board.white[1]);
*/
    board.h = heuristica(board);

    return board;
}

unsigned short getPos(State s, short x, short y){
    return s.tablero[x][y];
}

void setPos(State * s, short x, short y, unsigned short n){
    s->tablero[x][y] = n;
}

unsigned short getWhiteX(State s){
    return s.white[0];
}

void setWhiteX(State *s, unsigned short x){
    s->white[0] = x;	
}

unsigned short getWhiteY(State s){
    return s.white[1];
}

void setWhiteY(State *s, unsigned short y){
    s->white[1] = y;	
}

unsigned short getH(State s){
	return s.h;
}

void setH(State * s, unsigned short h){
	s->h = h;
}

/* Movimiento hacia arriba */
void moveU(State *s){
	unsigned short wx, wy, n;
	wx = getWhiteX(*s);
	wy = getWhiteY(*s);
	n = getPos(*s, wx-1, wy);
	setPos(s, wx, wy, n);
	setPos(s, wx-1, wy, 0);
	setWhiteX(s, wx-1);
	setWhiteY(s, wy);
}

/* Movimiento hacia abajo */
void moveD(State *s){
	unsigned short wx, wy, n;
	wx = getWhiteX(*s);
	wy = getWhiteY(*s);
	n = getPos(*s, wx+1, wy);
	setPos(s, wx, wy, n);
	setPos(s, wx+1, wy, 0);
	setWhiteX(s, wx+1);
	setWhiteY(s, wy);
}

/* Movimiento hacia la derecha */
void moveR(State *s){
	unsigned short wx, wy, n;
	wx = getWhiteX(*s);
	wy = getWhiteY(*s);
	n = getPos(*s, wx, wy+1);
	setPos(s, wx, wy, n);
	setPos(s, wx, wy+1, 0);
	setWhiteX(s, wx);
	setWhiteY(s, wy+1);
}

/* Movimiento hacia la izquierda */
void moveL(State *s){
	unsigned short wx, wy, n;
	wx = getWhiteX(*s);
	wy = getWhiteY(*s);
	n = getPos(*s, wx, wy-1);
	setPos(s, wx, wy, n);
	setPos(s, wx, wy-1, 0);
	setWhiteX(s, wx);
	setWhiteY(s, wy-1);
}

/* Imprimir tablero y costo */
void imprimir(State s){

    short i,j;
    printf("Tablero \n");
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            printf("%d ", s.tablero[i][j]);
        }
        printf("\n");
    }
    printf("heuristica %d\n",s.h);
    printf("blanco %d %d\n\n", s.white[0], s.white[1]);
}



/* Chequea si se llego al goal*/
int isGoal(State s){

	int i,n,j;
	n=0;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			if(getPos(s,i,j)!=n)return 0;
			n++;
		}
	}
    return 1;
}

/* Algoritmo a estrella =) */
int solve(State s);
  
