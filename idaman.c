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

short hU(){
	short wx,wy,h;
	wx=getWhiteX(board);
	wy=getWhiteY(board);
	h=getH(board);
	if(lookup[getPos(board,wx-1,wy)][0] < wx){
	    return h+1;
	}else{
		return h-1;
	}
}

short hD(){
	short wx,wy,h;
	wx=getWhiteX(board);
	wy=getWhiteY(board);
	h=getH(board);
	if(lookup[getPos(board,wx+1,wy)][0] > wx){
	    return h+1;
	}else{
		return h-1;
	}
}

short hL(){
	short wx,wy,h;
	wx=getWhiteX(board);
	wy=getWhiteY(board);
	h=getH(board);
	if(lookup[getPos(board,wx,wy-1)][1] < wy){
        return h+1;
	}else{
		return h-1;
	}
}
short hR(){
	short wx,wy,h;
	wx=getWhiteX(board);
	wy=getWhiteY(board);
	h=getH(board);
	if(lookup[getPos(board,wx,wy+1)][1] > wy){
		return h+1;
	}else{
		return h-1;
	}
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
    short curnth = getH(board);
    short cm = sc + curnth;
    if(cm > cl) return cm;
    if(isGoal(board)){
		*ok = 1;
		return sc;
	}
    
    int ncl = 32767;
    int ret;
    short i, j;
    short ord[4] = {0,1,2,3}; 
    short hord[4] = {200, 200, 200, 200};
	short wx,wy,d;
	wx = getWhiteX(board);
	wy = getWhiteY(board);

    if(wx <= 0) hord[0] = hD();
	if(wy >= 3) hord[1] = hL();
	if(wy <= 0) hord[2] = hR();
	if(wx >= 3) hord[3] = hU();

    for(i=0, j=3; i>=j;){
        if(hord[i]>curnth){
            short temp = hord[i];
            hord[i] = hord[j];
            hord[j] = temp;
            temp = ord[i];
            ord[i] = ord[j];
            ord[j] = temp;
            j--;
        }else{
            i++;
        }
    }

    for(i=0;i<4;i++){
        d = ord[i];
		State succ;
		//moviendo
		switch(d){
			case 0:
				if(wx <= 0 || dir==dirs[d]) continue;
				expU(board);
				break;
			case 1:
				if(wy >= 3 || dir==dirs[d]) continue;
				expR(board);
				break;
			case 2:
				if(wy <=0 || dir==dirs[d]) continue;
				expL(board);
				break;
			case 3:
				if(wx >= 3 || dir==dirs[d]) continue;
				expD(board);
				break;
		}
		//imprimir(succ);
        ret = dfs(sc+1, cl, ok,dirs[3-d]);
        if(*ok) return ret;
        if(ncl > ret){ 
            ncl = ret;
        }    
		//regresando el movimiento
		switch(d){
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
	    printf("%ld %d %f\n\n",nodosVis,pasos,((double)(end-begin))/CLOCKS_PER_SEC);
	}

}
