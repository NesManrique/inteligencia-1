#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

const short masks[4] = {0xf000, 0x0f00, 0x00f0, 0x000f};

struct State{
    unsigned short tablero [4];
    unsigned char white;
    unsigned char steps;
    unsigned char h;
};

/* Imprimir tablero y costo */
void imprimir(State s){
    printf("tablero %x\n",s.tablero[0]);
    printf("        %x\n",s.tablero[1]);
    printf("        %x\n",s.tablero[2]);
    printf("        %x\n",s.tablero[3]);
    printf("pasos %d\n",s.steps);
    printf("heuristica %d\n",s.h);
    printf("blanco %x\n\n", s.white);
}

class puzzle{    

    public:

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
        ini.steps =0; 
        ini.h=heuristica(ini);
    }

    /* Funcion que calcula la heuristica */
    short heuristica(State s);

    /* Funcion que expande un estado */
    void expandir(State s, State * neighbors);

    /* Chequea si se llego al goal*/
    static bool isGoal(State s){

        if( s.tablero[0] == 0x0123 && s.tablero[1] == 0x4567 &&
                s.tablero[2] == 0x89ab && s.tablero[3] == 0xcdef){
            return true;
        }

        return false;
    }

    /* Algoritmo a estrella =) */
    int solve(State s);

   
    /* mas nada.. (por ahora)*/


};
