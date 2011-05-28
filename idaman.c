#include <stdio.h>
#include "staticboard.h"
#include <time.h>

short lookup[16][2] = {{0,0},{0,1},{0,2},{0,3},{1,0},{1,1},{1,2},{1,3},{2,0},{2,1},{2,2},{2,3},{3,0},{3,1},{3,2},{3,3}};

State board;
long nodosVis;

void expU(){
	short wx,wy,h;
	wx=getWhiteX(board);
	wy=getWhiteY(board);
	h=getH(board);
	if(lookup[getPos(board,wx-1,wy)][0] < wx){
		setH(&board,h+1);
	}else{
		setH(&board,h-1);
	}
	moveU(&board);
}

void expD(){
	short wx,wy,h;
	wx=getWhiteX(board);
	wy=getWhiteY(board);
	h=getH(board);
	if(lookup[getPos(board,wx+1,wy)][0] > wx){
		setH(&board,h+1);
	}else{
		setH(&board,h-1);
	}
	moveD(&board);
}
void expL(){
	short wx,wy,h;
	wx=getWhiteX(board);
	wy=getWhiteY(board);
	h=getH(board);
	if(lookup[getPos(board,wx,wy-1)][1] < wy){
		setH(&board,h+1);
	}else{
		setH(&board,h-1);
	}
	moveL(&board);
}
void expR(){
	short wx,wy,h;
	wx=getWhiteX(board);
	wy=getWhiteY(board);
	h=getH(board);
	if(lookup[getPos(board,wx,wy+1)][1] > wy){
		setH(&board,h+1);
	}else{
		setH(&board,h-1);
	}
	moveR(&board);
}

short heuristica(State s){

    short i,j,r,n;
    r = 0;
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            n = getPos(s,i,j);
			if(n==0)continue;
            r = r + abs(lookup[n][0]-i) + abs(lookup[n][1]-j);
        }
    }
    return r;
}

char dirs[4]={'d','l','r','u'};
int dfs(int sc, int cl, char* ok, char dir){
	nodosVis++;
    short cm = sc + getH(board);
    if(cm > cl) return cm;
    if(isGoal(board)){
		*ok = 1;
		return sc;
	}
    
    int ncl = 32767;
    short i=0;
    int ret;
	short wx,wy;
	wx = getWhiteX(board);
	wy = getWhiteY(board);
    for(i=0;i<4;i++){
		State succ;
		//moviendo
		switch(i){
			case 0:
				if(wx <= 0 || dir==dirs[i]) continue;
				expU(board);
				break;
			case 1:
				if(wy >= 3 || dir==dirs[i]) continue;
				expR(board);
				break;
			case 2:
				if(wy <=0 || dir==dirs[i]) continue;
				expL(board);
				break;
			case 3:
				if(wx >= 3 || dir==dirs[i]) continue;
				expD(board);
				break;
		}
		//imprimir(succ);
        ret = dfs(sc+1, cl, ok,dirs[3-i]);
        if(*ok) return ret;
        if(ncl > ret) ncl = ret;
		//regresando el movimiento
		switch(i){
			case 0:
				expD(board);
				break;
			case 1:
				expL(board);
				break;
			case 2:
				expR(board);
				break;
			case 3:
				expU(board);
				break;
		}
	} 
	return ncl;
}


int solve(State s){
    
    int cl = getH(board);
    char ok = 0;
    while(1){
		printf("%d ",cl);
        int ret = dfs(0,cl,&ok,'i');
        if(ok) return ret;
		if(ret>3000) return -1;
        cl = ret;
    }
}

int main(){
	int pasos;
	clock_t begin,end;
	while(1){
	board = sboard();
	nodosVis=0;
	imprimir(board);
	begin=clock();
	pasos=solve(board);
	end=clock();
	printf("%d %d %f\n",nodosVis,pasos,((double)end-begin)/CLOCKS_PER_SEC);
	}

}
