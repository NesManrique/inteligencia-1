#include "aestrella.h"
using namespace std;

short * lookup[2];

short puzzle::manhattan(State s){

    short i,j,n,r;
    r = 0;
    for(i=0; i<N && i!=s.whitex; i++){
        for(j=0; j<N && j!=s.whitey; j++){
            n = s.tablero[i][j];
            r = r + abs(lookup[n][0]-i + lookup[n][1]-j);
        }
    }

    return r;
}

short puzzle::heuristica(State s){
    return manhattan(s);  
}

char * puzzle::solve(State s){

}
