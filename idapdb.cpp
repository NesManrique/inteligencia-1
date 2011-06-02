#include "staticboard.h"
#include <time.h>
#include <queue>

using namespace std;
typedef struct pattern{
    char pat[7][2];
    char h;
} Pattern;

State board;

const char LU[4][4] = {{0,1,2,3},{4,5,6,7},{8,9,10,11},{12,13,14,15}};

char p11 [16][16][16][16][16][16][8];
char p12 [16][16][16][16][16][16][8];
char p13 [16] = {1,0,1,2,2,1,2,3,3,2,3,4,4,3,4,5};
const char pm1 [15][2] = {{2,0},{0,0},{1,0},{0,1},{0,2},{0,3},{1,1},{0,4},{0,5},{0,6},{1,2},{1,3},{1,4},{1,5},{1,6}};

char p21 [16][16][16][16][16][16][8];
char p22 [16][16][16][16][16][16][8];
char p23 [16] = {1,0,1,2,2,1,2,3,3,2,3,4,4,3,4,5};
const char pm2 [15][2] = {{2,0},{1,0},{1,1},{0,0},{0,1},{1,2},{1,3},{0,2},{0,3},{1,4},{1,5},{0,4},{0,5},{0,6},{1,6}};

long nodosVis;

/*bool operator< (Pattern a, Pattern b){
    if(a.h >= b.h) return true;

    return false;
}
*/

void abstractf(State s, int dir[6][7]){

    int i, j, k;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            k = getPos(s, i, j);
            if(k==0) continue;
            dir[pm1[k-1][0]][pm1[k-1][1]] = LU[i][j];
            dir[pm2[k-1][0]+3][pm2[k-1][1]]= LU[i][j];
           //printf("k %d LU %d\n", k, LU[i][j]);
        }
    }

}

void inipat(State s,const char pm[15][2],Pattern p[2]){

    int i,j;
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            int num = getPos(s,i,j)-1;
            if(pm[num][0]==0) {
            	p[0].pat[pm[num][1]][0]=i;
            	p[0].pat[pm[num][1]][1]=j;
            }
            if(pm[num][0]==1){
            	p[1].pat[pm[num][1]][0]=i;
            	p[1].pat[pm[num][1]][1]=j;
            }
        }
    }

    p[0].h = 0;
    p[1].h = 0;

}

void print(Pattern p){
	for(int i=0;i<7;i++){
		printf("(%d %d)\n",p.pat[i][0],p.pat[i][1]);
	}
	printf("\n");
}
void Exp(Pattern pi,int n,Pattern p[4]){
	int i,t=1;
	memcpy(p[0].pat,pi.pat,sizeof(char)*16);
	memcpy(p[1].pat,pi.pat,sizeof(char)*16);
	memcpy(p[2].pat,pi.pat,sizeof(char)*16);
	memcpy(p[3].pat,pi.pat,sizeof(char)*16);
	p[0].h=120;
	p[1].h=120;
	p[2].h=120;
	p[3].h=120;
	if(p[0].pat[n][0]>0){
		for(i=0; i<n; i++){
			if(p[0].pat[i][0]==p[0].pat[n][0] && p[0].pat[i][1]==p[0].pat[n][1]){
				t=0;
				break;
			}
		}
		if(t){
			p[0].h = pi.h+1;
			p[0].pat[n][0]--;
		}
	}
	t=1;
	if(p[1].pat[n][0]<3){
		for(i=0; i<n; i++){
			if(p[1].pat[i][0]==p[1].pat[n][0] && p[1].pat[i][1]==p[1].pat[n][1]){
				t=0;
				break;
			}
		}
		if(t){
			p[1].h = pi.h+1;
			p[1].pat[n][0]++;
		}
	}
	t=1;
	if(p[2].pat[n][1]<3){
		for(i=0; i<n; i++){
			if(p[2].pat[i][0]==p[2].pat[n][0] && p[2].pat[i][1]==p[2].pat[n][1]){
				t=0;
				break;
			}
		}
		if(t){
			p[2].h = pi.h+1;
			p[2].pat[n][1]++;
		}
	}
	t=1;
	if(p[3].pat[n][1]>0){
		for(i=0; i<n; i++){
			if(p[3].pat[i][0]==p[3].pat[n][0] && p[3].pat[i][1]==p[3].pat[n][1]){
				t=0;
				break;
			}
		}
		if(t){
			p[3].pat[n][1]--;
			p[3].h = pi.h+1;
		}
	}

}

int bfs(Pattern v,char bd[16][16][16][16][16][16][8]){

    queue<Pattern> q;
    q.push(v);
	int i = 0,depth;
    //meter v en las bd;
    while(!q.empty()){
		nodosVis++;
		i++;
        Pattern w = q.front();
		q.pop();
//		if(i>1000000){printf("%ld\n",nodosVis);i=0;}
		depth = w.h;
        for(int j=0;j<7;j++){
            Pattern vecs[4];
            Exp(w,j,vecs);
            for(int i=0; i<4; i++){
            	Pattern v = vecs[i];
//				print(v);
                char value=bd[LU[v.pat[0][0]][v.pat[0][1]]][LU[v.pat[1][0]][v.pat[1][1]]]
                [LU[v.pat[2][0]][v.pat[2][1]]][LU[v.pat[3][0]][v.pat[3][1]]]
                [LU[v.pat[4][0]][v.pat[4][1]]][LU[v.pat[5][0]][v.pat[5][1]]]
                [LU[v.pat[6][0]][v.pat[6][1]]/2];
                if(value==0 || v.h<value){	
                    bd[LU[v.pat[0][0]][v.pat[0][1]]][LU[v.pat[1][0]][v.pat[1][1]]]
                    [LU[v.pat[2][0]][v.pat[2][1]]][LU[v.pat[3][0]][v.pat[3][1]]]
                    [LU[v.pat[4][0]][v.pat[4][1]]][LU[v.pat[5][0]][v.pat[5][1]]]
                    [LU[v.pat[6][0]][v.pat[6][1]]/2]=v.h;
                    q.push(v);
                }
            }
        }
    }
	return depth;
}

void expU(){
    int dir[6][7];
	moveU(&board);
    abstractf(board, dir);
    setH(&board, heuristica2(dir));
}

void expD(){
	int dir[6][7];
	moveD(&board);
    abstractf(board, dir);
    setH(&board, heuristica2(dir));
}
void expL(){
	int dir[6][7];
	moveL(&board);
    abstractf(board, dir);
    setH(&board, heuristica2(dir));
}
void expR(){
	int dir[6][7];
	moveR(&board);
    abstractf(board, dir);
    setH(&board, heuristica2(dir));
}

short heuristica2(int dir[6][7]){

    char v11, v12, w21, w22, h1, h2;
    v11 = p11[dir[0][0]][dir[0][1]][dir[0][2]][dir[0][3]][dir[0][4]][dir[0][5]][dir[0][6]];
    v12 = p12[dir[1][0]][dir[1][1]][dir[1][2]][dir[1][3]][dir[1][4]][dir[1][5]][dir[1][6]];
    h1 = v11+v12+p13[dir[2][0]];

    w21 = p21[dir[3][0]][dir[3][1]][dir[3][2]][dir[3][3]][dir[3][4]][dir[3][5]][dir[3][6]];
    w22 = p22[dir[4][0]][dir[4][1]][dir[4][2]][dir[4][3]][dir[4][4]][dir[4][5]][dir[4][6]];
    h2 = w21+w22+p13[dir[5][0]];

    if(h1<=h2) return h2;

    return h1;

}

char dirs[4]={'d','l','r','u'};
int dfs(int sc, int cl, char* ok, char dir){
	nodosVis++;
    short curnth = getH(board);
    short cm = sc + curnth;
    if(cm > cl) return cm;
    if(curnth == 0){
		*ok = 1;
		return sc;
	}

    int ncl = 32767;
    short i;

    int ret;
	short wx,wy;
	wx = getWhiteX(board);
	wy = getWhiteY(board);
    char t;
    for(i=0;i<4;i++){
        if(dir == dirs[i]) continue;
		//moviendo
		switch(i){
			case 0:
				if(wx <= 0) continue;
				expU();
                t = 'u';
				break;
			case 1:
				if(wy >= 3) continue;
				expR();
                t = 'r';
				break;
			case 2:
				if(wy <= 0) continue;
				expL();
                t = 'l';
				break;
			case 3:
				if(wx >= 3) continue;
				expD();
                t = 'd';
				break;
		}
		//imprimir(succ);
        ret = dfs(sc+1, cl, ok, t);
        if(*ok) return ret;
        if(ncl > ret) ncl = ret;
		//regresando el movimiento
		switch(i){
			case 0:
				expD();
				break;
			case 1:
				expL();
				break;
			case 2:
				expR();
				break;
			case 3:
				expU();
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

	memset(p11, 0, 16*16*16*16*16*16*8);
	memset(p12, 0, 16*16*16*16*16*16*8);
	memset(p13, 0, 16);
	memset(p21, 0, 16*16*16*16*16*16*8);
	memset(p22, 0, 16*16*16*16*16*16*8);
	memset(p23, 0, 16);
	int prof;
	clock_t begin,end;
    int arr[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int dir[6][7];
	board = sboard2(arr);
	imprimir(board);
	Pattern p1[2],p2[2];
	inipat(	board,pm1,p1);
    //printf("hola\n");

	//p11
	nodosVis=0;
	print(p1[0]);
	begin=clock();
	prof = bfs(p1[0], p11);
	end=clock();
	printf("vis %ld prof %d time %f\n\n",nodosVis,prof,((double)(end-begin))/CLOCKS_PER_SEC);

	//p12
	nodosVis=0;
	print(p1[1]);
	begin=clock();
	prof = bfs(p1[1], p12);
	end=clock();
	printf("vis %ld prof %d time %f\n\n",nodosVis,prof,((double)(end-begin))/CLOCKS_PER_SEC);

	inipat(	board,pm2,p2);
	//p21
	nodosVis=0;
	print(p2[0]);
	begin=clock();
	prof = bfs(p2[0], p21);
	end=clock();
	printf("vis %ld prof %d time %f\n\n",nodosVis,prof,((double)(end-begin))/CLOCKS_PER_SEC);

	//p22
	nodosVis=0;
	print(p2[1]);
	begin=clock();
	prof = bfs(p2[1], p22);
	end=clock();
	printf("vis %ld prof %d time %f\n\n",nodosVis,prof,((double)(end-begin))/CLOCKS_PER_SEC);

    //algo de la bd1
    //printf("p11 2 15 6 4 3 9 11 %d\n",p11[2][15][6][4][3][9][11]);

    while(1){

        board = sboard();
        if(board.h == -1) break;
        abstractf(board, dir);
        setH(&board, heuristica2(dir));
	    nodosVis=0;
	    imprimir(board);
	    begin=clock();
	    prof=solve(board);
	    end=clock();
	    printf("%ld %d %f\n\n",nodosVis,prof,((double)(end-begin))/CLOCKS_PER_SEC);

    }
   
    return 0; 
}
