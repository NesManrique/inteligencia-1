#include <stdio.h>
#include <stdlib.h>
#include <queue>
using namespace std;

const short masks[4] = {0xf000, 0x0f00, 0x00f0, 0x000f};

struct State{
    unsigned short tablero [4];
    char white;
    short cost;
};

class puzzle{    

    State ini;

    public:

    puzzle(int t[], int whitex, int whitey){
       
        unsigned short i,j,k,l;
        for(i=0, l=0; i<4; i++){
            k =0;
            for(j=0; j<4; j++){
                k <<= 4;
                k |= t[l++];
            }
            ini.tablero[i] = k;
        }
        
        k =0;
        k |= whitex;
        k <<= 4;
        k |= whitey;
        ini.white = k;
        ini.cost = heuristica(ini);
        printf("tablero %x\n",ini.tablero[0]);
        printf("tablero %x\n",ini.tablero[1]);
        printf("tablero %x\n",ini.tablero[2]);
        printf("tablero %x\n",ini.tablero[3]);
        printf("costo %d\n",ini.cost);
    }

    /* Funcion que calcula la heuristica */
    short heuristica(State s);
};

    /* Funcion que expande un estado 
    void expandir(State s, State * neighbors){

        short i, j,n, c = 0;
        for(n=0;n<4;n++){
            State <N> temp;
            for(i=0; i<N; i++){
                for(j=0; j<N; j++){
                    temp.tablero[i][j] = s.tablero[i][j];
                }
            }
            switch(n){
                case 0:
                    if(s.whitex != 0){
                        temp.tablero[s.whitex][s.whitey] = temp.tablero[s.whitex - 1][s.whitey];
                        temp.tablero[s.whitex - 1][s.whitey] = 0;
                        temp.sol = (char *)malloc(strlength(s.sol)+1);
                        sprintf(temp.sol, "%s%c", s.sol, 'u');
                    }
                    break;
                case 1:
                    if(s.whitex != N-1){
                        temp.tablero[s.whitex][s.whitey] = temp.tablero[s.whitex + 1][s.whitey];
                        temp.tablero[s.whitex + 1][s.whitey] = 0;
                        temp.sol = (char *)malloc(strlength(s.sol)+1);
                        sprintf(temp.sol, "%s%c", s.sol, 'd');
                    }
                    break;
                case 2:
                    if(s.whitey != 0){
                        temp.tablero[s.whitex][s.whitey] = temp.tablero[s.whitex][s.whitey - 1];
                        temp.tablero[s.whitex][s.whitey - 1] = 0;
                        temp.sol = (char *)malloc(strlength(s.sol)+1);
                        sprintf(temp.sol, "%s%c", s.sol, 'l');
                    }
                    break;
                case 3:
                    if(s.whitey != N-1){
                        temp.tablero[s.whitex][s.whitey] = temp.tablero[s.whitex][s.whitey + 1];
                        temp.tablero[s.whitex][s.whitey + 1] = 0;
                        temp.sol = (char *)malloc(strlength(s.sol)+1);
                        sprintf(temp.sol, "%s%c", s.sol, 'r');
                    }
                    break;
            }
            temp.whitex = s.whitex - 1;
            temp.whitey = s.whitey;
            temp.steps = s.steps+1;
            temp.cost = heuristica(temp)+temp.steps;
            neighbors[n]=temp;
        }

    }


    * Chequea si se llego al goal*
    bool isGoal(State s);

    * Algoritmo a estrella =) *
    char * solve(State s);

    * mas nada.. (por ahora) */

