#include <stdio.h>
#include <stdlib.h>
#include <queue>
using namespace std;

template <short N> class puzzle{    

    struct State{
        short tablero[N][N];
        short whitex;
        short whitey;
        short cost;
        short steps;
        char * sol;
    };

    State ini;

    puzzle puzzle(short [][] t){
        
        short i,j;
        for(i=0; i<N; i++){
            for(j=0; i<N; i++){
                
            }
        }
    }

    /* Funcion que calcula la heuristica */
    short heuristica(State s);

    /* Funcion que expande un estado */
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


    /* Chequea si se llego al goal*/
    bool isGoal(State s);

    /* Algoritmo a estrella =) */
    char * solve(State s);

    /* mas nada.. (por ahora) */
}
