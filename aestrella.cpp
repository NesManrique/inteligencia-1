#include "aestrella.h"
using namespace std;

short lookup[16][2] = {{0,0},{0,1},{0,2},{0,3},{1,0},{1,1},{1,2},{1,3},{2,0},{2,1},{2,2},{2,3},{3,0},{3,1},{3,2},{3,3}};

//expansiones

State expU(State s){
    short i, n, c = 0;
    unsigned short t, wx, wy;
    wx = s.white & 0xf0;
    wx >>= 4;
    wy = s.white & 0xf;
	State temp;
	temp.h=255;
	if(wx != 0 && s.lastmove!='d'){
		memcpy(temp.tablero, s.tablero, 8);
		t = temp.tablero[wx-1] & masks[wy];
		temp.tablero[wx-1] &= ~(masks[wy]);
		temp.tablero[wx] |= t;
		if(lookup[t >> ((3-wy) << 2)][0] < wx){
			temp.h = s.h+1;
		}else{
			temp.h = s.h-1;
		}
		temp.lastmove = 'u';
		temp.white = s.white-0x10;
		i++;
	}
	return temp;
}

State expD(State s){
	short i, n, c = 0;
	unsigned short t, wx, wy;
	wx = s.white & 0xf0;
	wx >>= 4;
	wy = s.white & 0xf;
	State temp;
	temp.h=255;
	if(wx != 3 && s.lastmove!='u'){
		memcpy(temp.tablero, s.tablero, 8);
		t = temp.tablero[wx+1] & masks[wy];
		temp.tablero[wx+1] &= ~(masks[wy]);
		temp.tablero[wx] |= t;
		if(lookup[t>>((3-wy)<<2)][0] > wx){
			temp.h = s.h+1;
		}else{
			temp.h = s.h-1;
		}
		temp.lastmove = 'd';
		temp.white = s.white+0x10;
		i++;
	}
	return temp;
}

State expL(State s){
	short i, n, c = 0;
	unsigned short t, wx, wy;
	wx = s.white & 0xf0;
	wx >>= 4;
	wy = s.white & 0xf;
	State temp;
	temp.h=255;
	if(wy != 0 && s.lastmove!='r'){
		memcpy(temp.tablero, s.tablero, 8);
		t = temp.tablero[wx] & masks[wy-1];
		t >>= 4;
		temp.tablero[wx] &= ~(masks[wy-1]);
		temp.tablero[wx] |= t;
		if(lookup[t>>((3-wy)<<2)][1] < wy){
			temp.h = s.h+1;
		}else{
			temp.h = s.h-1;
		}
		temp.lastmove='l';
		temp.white = s.white-0x01;
		i++;
	}
	return temp;
}

State expR(State s){
	short i, n, c = 0;
	unsigned short t, wx, wy;
	wx = s.white & 0xf0;
	wx >>= 4;
	wy = s.white & 0xf;
	State temp;
	temp.h=255;
	if(wy != 3 && s.lastmove!='l'){
		memcpy(temp.tablero, s.tablero, 8);
		t = temp.tablero[wx] & masks[wy + 1];
		t <<= 4;
		temp.tablero[wx] &= ~(masks[wy + 1]);
		temp.tablero[wx] |= t;
		if(lookup[t>>((3-wy)<<2)][1] > wy){
			temp.h = s.h+1;
		}else{
			temp.h = s.h-1;
		}
		temp.lastmove='r';
		temp.white = s.white+0x01;
		i++;
//	imprimir(temp);
	}
//	imprimir(temp);
//	printf("AAAAAAAAA\n");
	return temp;
}
/* Funcion que expande un estado 
int expandir(State s, State * neighbors){

    short i, n, c = 0;
    unsigned short t, wx, wy;
    wx = s.white & 0xf0;
    wx >>= 4;
    wy = s.white & 0xf;
    for(n=0, i=0 ; n<4; n++){
        switch(n){
            case 0:
                if(wx != 0 && s.lastmove!='d'){
                    State temp;
                    memcpy(temp.tablero, s.tablero, 8);
                    t = temp.tablero[wx-1] & masks[wy];
                    temp.tablero[wx-1] &= ~(masks[wy]);
                    temp.tablero[wx] |= t;
                    if(lookup[t >> ((3-wy) << 2)][0] < wx){
                        temp.h = s.h+1;
                    }else{
                        temp.h = s.h-1;
                    }
					temp.lastmove = 'u';
                    temp.white = s.white-0x10;
                    neighbors[i]=temp;
                    i++;
                }
                break;
            case 1:
                if(wy != 0 && s.lastmove!='r'){
                    State temp;
                    memcpy(temp.tablero, s.tablero, 8);
                    t = temp.tablero[wx] & masks[wy-1];
                    t >>= 4;
                    temp.tablero[wx] &= ~(masks[wy-1]);
                    temp.tablero[wx] |= t;
                    if(lookup[t>>((4-wy)<<2)][1] < wy){
                        temp.h = s.h+1;
                    }else{
                        temp.h = s.h-1;
                    }
	                temp.lastmove='l';
                    temp.white = s.white-0x01;
                    neighbors[i]=temp;
                    i++;
                }
                break;
            case 2:
                if(wx != 3 && s.lastmove='u'){
                    State temp;
                    memcpy(temp.tablero, s.tablero, 8);
                    t = temp.tablero[wx+1] & masks[wy];
                    temp.tablero[wx+1] &= ~(masks[wy]);
                    temp.tablero[wx] |= t;
                    if(lookup[t>>((3-wy)<<2)][0] > wx){
                        temp.h = s.h+1;
                    }else{
                        temp.h = s.h-1;
                    }
                    temp.lastmove = 'd';
                    temp.white = s.white+0x10;
                    neighbors[i]=temp;
                    i++;
                }
                break;
            case 3:
                if(wy != 3 && s.lastmove='l'){
                    State temp;
                    memcpy(temp.tablero, s.tablero, 8);
                    t = temp.tablero[wx] & masks[wy + 1];
                    t <<= 4;
                    temp.tablero[wx] &= ~(masks[wy + 1]);
                    temp.tablero[wx] |= t;
                    if(lookup[t>>((2-wy)<<2)][1] > wy){
                        temp.h = s.h+1;
                    }else{
                        temp.h = s.h-1;
                    }
					temp.lastmove='r';
                    temp.white = s.white+0x01;
                    neighbors[i]=temp;
                    i++;
                }
                break;
        }
    }
    return i;
}
*/


short manhattan(State s){

    unsigned short i,j,r;
    unsigned int n;
    r = 0;
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            n = s.tablero[i] & masks[j];
            n >>= ((3-j)<<2);
            r = r + abs(lookup[n][0]-i) + abs(lookup[n][1]-j);
        }
    }
    return r;
}

short puzzle::heuristica(State s){
    return manhattan(s);  
}

int dfs(short sc, State s, int cl, bool &ok){
    short cm = sc + s.h;
    if(cm > cl) return cm;
    if(puzzle::isGoal(s)){
		ok = true ;
		return sc;
	}
    
    int ncl = 32767;

    short i=0;
    int ret;
    for(i=0;i<4;i++){
		State succ;
		switch(i){
			case 0:
				succ=expU(s);
				break;
			case 1:
				succ=expR(s);
				break;
			case 2:
				succ=expD(s);
				break;
			case 3:
				succ=expL(s);
				break;
		}
		if (succ.h==255){
		//	imprimir(succ);
			continue;
		}
		//imprimir(succ);
        ret = dfs(sc+1, succ, cl, ok);
        if(ok) return ret;
        if(ncl > ret) ncl = ret;
	} 
	return ncl;
	
	/*    State succ[4];

    int hijos = expandir(s,succ);
    short i=0;
    int ret;
//	printf("hijos %d\n",hijos);
    for(i=0;i<hijos;i++){
//		imprimir(succ[i]);
        ret = dfs(sc+1, succ[i], cl, ok);
        if(ok) return ret;
        if(ncl > ret) ncl = ret;
    } 
    return ncl;*/
}

int puzzle::solve(State s){
    
    int cl = s.h;
    bool ok = false;
    while(1){
		printf("cl %d %d\n",cl,ok);
        int ret = dfs(0,s,cl,ok);
        if(ok) return ret;
		if(ret>3000) return -1;
        cl = ret;
    }
}


int main(){
    
    int arr[16] = {15,2,5,7,13,8,3,6,11,4,0,1,14,9,12,10};
 //   int hijos, i;
    puzzle p(arr, 2,1);
    printf("tablero inicial\n");
    imprimir(p.ini);
/*    State n[4];
    hijos = expandir(p.ini, n);
    printf("hay %d hijos\n",hijos);
*    for(i=0; i<hijos; i++){
        imprimir(n[i]);
    }
*/
   // cout << puzzle::isGoal(p.ini);

    printf("solve %d\n", p.solve(p.ini));
    
    return 0;
}