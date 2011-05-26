#include "aestrella.h"
using namespace std;

short lookup[16][2] = {{0,0},{0,1},{0,2},{0,3},{1,0},{1,1},{1,2},{1,3},{2,0},{2,1},{2,2},{2,3},{3,0},{3,1},{3,2},{3,3}};

short manhattan(State s){

    unsigned short i,j,r;
    unsigned int n;
    r = 0;
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            n = s.tablero[i] & masks[j];
            n >>= ((3-j)<<2);
            r = r + abs(lookup[n][0]-i) + abs(lookup[n][1]-j);
            printf("r %d\n",r);
        }
    }
    return r;
}

short puzzle::heuristica(State s){
    return manhattan(s);  
}

int main(){
    
    int arr[16] = {0,1,3,6,2,5,7,8,9,10,11,13,12,14,15,4};
    puzzle p(arr, 0,0);
    
    return 0;
}
