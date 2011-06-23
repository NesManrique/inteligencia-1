// Game of Othello -- Cut from full code
// Universidad Simon Bolivar, 2005.
// Author: Blai Bonet
// Last Revision: 06/01/11
// Modified by: Johann 

#define NDEBUG
#include <stdio.h>
#include <iostream>
#include "assert.h"
#include <time.h>
#include <ext/hash_map>
#include <string.h>

using namespace std;
using namespace __gnu_cxx;

#define MAX(s,t)      ((s)>(t)?(s):(t))
#define MIN(s,t)      ((s)<(t)?(s):(t))
#define MAXVALUE      1000
#define DIM           36
#define N             6
#define LOWERBOUND    'l'
#define UPPERBOUND    'u'
#define EXACT_VALUE   'e'

long nodosVis;


unsigned coll[100000];
const int rows[][7] = { { 4, 5, 6, 7, 8, 9,-1 }, { 4, 5, 6, 7, 8, 9,-1 }, { 4, 5, 6, 7, 8, 9,-1 },
                        { 4, 5, 6, 7, 8, 9,-1 }, { 4, 5, 6, 7, 8, 9,-1 }, { 4, 5, 6, 7, 8, 9,-1 },
                        {10,11,12,13,14,15,-1 }, {10,11,12,13,14,15,-1 }, {10,11,12,13,14,15,-1 },
                        {10,11,12,13,14,15,-1 }, {10,11,12,13,14,15,-1 }, {10,11,12,13,14,15,-1 },
                        {16,17, 0, 1,18,19,-1 }, {16,17, 0, 1,18,19,-1 },
                        {16,17, 0, 1,18,19,-1 }, {16,17, 0, 1,18,19,-1 },
                        {20,21, 2, 3,22,23,-1 }, {20,21, 2, 3,22,23,-1 },
                        {20,21, 2, 3,22,23,-1 }, {20,21, 2, 3,22,23,-1 },
                        {24,25,26,27,28,29,-1 }, {24,25,26,27,28,29,-1 }, {24,25,26,27,28,29,-1 },
                        {24,25,26,27,28,29,-1 }, {24,25,26,27,28,29,-1 }, {24,25,26,27,28,29,-1 },
                        {30,31,32,33,34,35,-1 }, {30,31,32,33,34,35,-1 }, {30,31,32,33,34,35,-1 },
                        {30,31,32,33,34,35,-1 }, {30,31,32,33,34,35,-1 }, {30,31,32,33,34,35,-1 } };
const int cols[][7] = { { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 }, { 6,12, 0, 2,26,32,-1 },
                        { 7,13, 1, 3,27,33,-1 }, { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 },
                        { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 }, { 6,12, 0, 2,26,32,-1 },
                        { 7,13, 1, 3,27,33,-1 }, { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 },
                        { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 },
                        { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 },
                        { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 },
                        { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 },
                        { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 }, { 6,12, 0, 2,26,32,-1 },
                        { 7,13, 1, 3,27,33,-1 }, { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 },
                        { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 }, { 6,12, 0, 2,26,32,-1 },
                        { 7,13, 1, 3,27,33,-1 }, { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 } };
const int dia1[][7] = { { 4,11, 0, 3,28,35,-1 }, { 5,12, 1,22,29,-1,-1 }, { 6,13,18,23,-1,-1,-1 },
                        { 7,14,19,-1,-1,-1,-1 }, { 8,15,-1,-1,-1,-1,-1 }, { 9,-1,-1,-1,-1,-1,-1 },
                        {10,17, 2,27,34,-1,-1 }, { 4,11, 0, 3,28,35,-1 }, { 5,12, 1,22,29,-1,-1 },
                        { 6,13,18,23,-1,-1,-1 }, { 7,14,19,-1,-1,-1,-1 }, { 8,15,-1,-1,-1,-1,-1 },
                        {16,21,26,33,-1,-1,-1 }, {10,17, 2,27,34,-1,-1 },
                        { 6,13,18,23,-1,-1,-1 }, { 7,14,19,-1,-1,-1,-1 },
                        {20,25,32,-1,-1,-1,-1 }, {16,21,26,33,-1,-1,-1 },
                        { 5,12, 1,22,29,-1,-1 }, { 6,13,18,23,-1,-1,-1 },
                        {24,31,-1,-1,-1,-1,-1 }, {20,25,32,-1,-1,-1,-1 }, {16,21,26,33,-1,-1,-1 },
                        {10,17, 2,27,34,-1,-1 }, { 4,11, 0, 3,28,35,-1 }, { 5,12, 1,22,29,-1,-1 },
                        {30,-1,-1,-1,-1,-1,-1 }, {24,31,-1,-1,-1,-1,-1 }, {20,25,32,-1,-1,-1,-1 },
                        {16,21,26,33,-1,-1,-1 }, {10,17, 2,27,34,-1,-1 }, { 4,11, 0, 3,28,35,-1 } };
const int dia2[][7] = { { 4,-1,-1,-1,-1,-1,-1 }, { 5,10,-1,-1,-1,-1,-1 }, { 6,11,16,-1,-1,-1,-1 },
                        { 7,12,17,20,-1,-1,-1 }, { 8,13, 0,21,24,-1,-1 }, { 9,14, 1, 2,25,30,-1 },
                        { 5,10,-1,-1,-1,-1,-1 }, { 6,11,16,-1,-1,-1,-1 }, { 7,12,17,20,-1,-1,-1 },
                        { 8,13, 0,21,24,-1,-1 }, { 9,14, 1, 2,25,30,-1 }, {15,18, 3,26,31,-1,-1 },
                        { 6,11,16,-1,-1,-1,-1 }, { 7,12,17,20,-1,-1,-1 },
                        {15,18, 3,26,31,-1,-1 }, {19,22,27,32,-1,-1,-1 },
                        { 7,12,17,20,-1,-1,-1 }, { 8,13, 0,21,24,-1,-1 },
                        {19,22,27,32,-1,-1,-1 }, {23,28,33,-1,-1,-1,-1 },
                        { 8,13, 0,21,24,-1,-1 }, { 9,14, 1, 2,25,30,-1 }, {15,18, 3,26,31,-1,-1 },
                        {19,22,27,32,-1,-1,-1 }, {23,28,33,-1,-1,-1,-1 }, {29,34,-1,-1,-1,-1,-1 },
                        { 9,14, 1, 2,25,30,-1 }, {15,18, 3,26,31,-1,-1 }, {19,22,27,32,-1,-1,-1 },
                        {23,28,33,-1,-1,-1,-1 }, {29,34,-1,-1,-1,-1,-1 }, {35,-1,-1,-1,-1,-1,-1 } };

// moves on the principal variation
static int PV[] = { 12, 21, 26, 13, 22, 18,  7,  6,  5, 27, 33, 23, 17, 11, 19, 15,
                    14, 31, 20, 32, 30, 10, 25, 24, 34, 28, 16,  4, 29, 35, 36,  8, 9 };

class state_t {
  protected:
    unsigned char t_; 
    unsigned free_;
    unsigned pos_;
  public:
    explicit state_t(unsigned char t = 6) : t_(t), free_(0), pos_(0) { }

    unsigned char t() const { return t_; }
    unsigned free() const { return free_; }
    unsigned pos() const { return pos_; }

    bool operator==(const state_t s) const{;
        return (t_ == s.t() && pos_ == s.pos() && free_ == s.free());
    }

    bool is_color(bool color, int pos) const {
        if( color )
            return pos < 4 ? t_&(1<<pos) : pos_&(1<<pos-4);
        else
            return !(pos < 4 ? t_&(1<<pos) : pos_&(1<<pos-4));
    }
    bool is_black(int pos) const { return is_color(true, pos); }
    bool is_white(int pos) const { return is_color(false, pos); }
    bool is_free(int pos) const { return pos < 4 ? false : !(free_&(1<<pos-4)); }
    bool is_full() const { return ~free_ == 0; }

    int value() const;
    bool terminal() const;
    bool outflank(bool color, int pos) const;
    bool is_black_move(int pos) const { return (pos == DIM) || outflank(true, pos); }
    bool is_white_move(int pos) const { return (pos == DIM) || outflank(false, pos); }

    void set_color(bool color, int pos);
    state_t move(bool color, int pos) const;
    state_t black_move(int pos) { return move(true, pos); }
    state_t white_move(int pos) { return move(false, pos); }

    bool operator<(const state_t &s) const {
        return (free_ < s.free_) || ((free_ == s.free_) && (pos_ < s.pos_));
    }
    void print(ostream &os, int depth) const;
    void print_bits(ostream &os) const;
};

inline int state_t::value() const {
    int v = 0;
    for( int pos = 0; pos < DIM; ++pos ) {
        if( !is_free(pos) )
            v += is_black(pos) ? -1 : 1;
    }
    assert( (-36 <= v) && (v <= 36) );
    return 36+v;
}

inline bool state_t::terminal() const {
    if( is_full() ) return true;
    for( unsigned b = 0; b < DIM; ++b )
        if( is_black_move(b) || is_white_move(b) )
            return false;
    return true;
}

bool state_t::outflank(bool color, int pos) const {
    if( !is_free(pos) ) return false;

    const int *p = 0;

    // check rows
    const int *r = rows[pos-4];
    while( *r != pos ) ++r;
    if( *(r+1) != -1 ) {
        for( p = r+1; (*p != -1) && !is_free(*p) && (color^is_black(*p)); ++p );
        if( (p > r+1) && (*p != -1) && !is_free(*p) ) return true;
    }
    if( r != rows[pos-4] ) {
        for( p = r-1; (p >= rows[pos-4]) && !is_free(*p) && (color^is_black(*p)); --p );
        if( (p < r-1) && (p >= rows[pos-4]) && !is_free(*p) ) return true;
    }

    // check cols
    const int *c = cols[pos-4];
    while( *c != pos ) ++c;
    if( *(c+1) != -1 ) {
        for( p = c+1; (*p != -1) && !is_free(*p) && (color^is_black(*p)); ++p );
        if( (p > c+1) && (*p != -1) && !is_free(*p) ) return true;
    }
    if( c != cols[pos-4] ) {
        for( p = c-1; (p >= cols[pos-4]) && !is_free(*p) && (color^is_black(*p)); --p );
        if( (p < c-1) && (p >= cols[pos-4]) && !is_free(*p) ) return true;
    }

    // check diag1
    const int *d1 = dia1[pos-4];
    while( *d1 != pos ) ++d1;
    if( *(d1+1) != -1 ) {
        for( p = d1+1; (*p != -1) && !is_free(*p) && (color^is_black(*p)); ++p );
        if( (p > d1+1) && (*p != -1) && !is_free(*p) ) return true;
    }
    if( d1 != dia1[pos-4] ) {
        for( p = d1-1; (p >= dia1[pos-4]) && !is_free(*p) && (color^is_black(*p)); --p );
        if( (p < d1-1) && (p >= dia1[pos-4]) && !is_free(*p) ) return true;
    }

    // check diag2
    const int *d2 = dia2[pos-4];
    while( *d2 != pos ) ++d2;
    if( *(d2+1) != -1 ) {
        for( p = d2+1; (*p != -1) && !is_free(*p) && (color^is_black(*p)); ++p );
        if( (p > d2+1) && (*p != -1) && !is_free(*p) ) return true;
    }
    if( d2 != dia2[pos-4] ) {
        for( p = d2-1; (p >= dia2[pos-4]) && !is_free(*p) && (color^is_black(*p)); --p );
        if( (p < d2-1) && (p >= dia2[pos-4]) && !is_free(*p) ) return true;
    }

    return false;
}

inline void state_t::set_color(bool color, int pos) {
    if( color ) {
        if( pos < 4 ) {
            t_ |= (1<<pos);
        } else {
            free_ |= (1<<pos-4);
            pos_ |= (1<<pos-4);
        }
    } else {
        if( pos < 4 ) {
            t_ &= ~(1<<pos);
        } else {
            free_ |= (1<<pos-4);
            pos_ &= ~(1<<pos-4);
        }
    }
}

state_t state_t::move(bool color, int pos) const {
    state_t s(*this);
    if( pos == DIM ) return s;

    assert(outflank(color, pos));
    s.set_color(color, pos);

    // process rows
    const int *p = 0;
    const int *r = rows[pos-4];
    while( *r != pos ) ++r;
    if( *(r+1) != -1 ) {
        for( p = r+1; (*p != -1) && !is_free(*p) && (color^is_black(*p)); ++p );
        if( (p > r+1) && (*p != -1) && !is_free(*p) )
            for( const int *q = r+1; q < p; ++q ) s.set_color(color, *q);
    }
    if( r != rows[pos-4] ) {
        for( p = r-1; (p >= rows[pos-4]) && !is_free(*p) && (color^is_black(*p)); --p );
        if( (p < r-1) && (p >= rows[pos-4]) && !is_free(*p) )
            for( const int *q = r-1; q > p; --q ) s.set_color(color, *q);
    }

    // process columns
    const int *c = cols[pos-4];
    while( *c != pos ) ++c;
    if( *(c+1) != -1 ) {
        for( p = c+1; (*p != -1) && !is_free(*p) && (color^is_black(*p)); ++p );
        if( (p > c+1) && (*p != -1) && !is_free(*p) )
            for( const int *q = c+1; q < p; ++q ) s.set_color(color, *q);
    }
    if( c != cols[pos-4] ) {
        for( p = c-1; (p >= cols[pos-4]) && !is_free(*p) && (color^is_black(*p)); --p );
        if( (p < c-1) && (p >= cols[pos-4]) && !is_free(*p) )
            for( const int *q = c-1; q > p; --q ) s.set_color(color, *q);
    }

    // process diagonal 1
    const int *d1 = dia1[pos-4];
    while( *d1 != pos ) ++d1;
    if( *(d1+1) != -1 ) {
        for( p = d1+1; (*p != -1) && !is_free(*p) && (color^is_black(*p)); ++p );
        if( (p > d1+1) && (*p != -1) && !is_free(*p) )
            for( const int *q = d1+1; q < p; ++q ) s.set_color(color, *q);
    }
    if( d1 != dia1[pos-4] ) {
        for( p = d1-1; (p >= dia1[pos-4]) && !is_free(*p) && (color^is_black(*p)); --p );
        if( (p < d1-1) && (p >= dia1[pos-4]) && !is_free(*p) )
            for( const int *q = d1-1; q > p; --q ) s.set_color(color, *q);
    }

    // process diagonal 2
    const int *d2 = dia2[pos-4];
    while( *d2 != pos ) ++d2;
    if( *(d2+1) != -1 ) {
        for( p = d2+1; (*p != -1) && !is_free(*p) && (color^is_black(*p)); ++p );
        if( (p > d2+1) && (*p != -1) && !is_free(*p) )
            for( const int *q = d2+1; q < p; ++q ) s.set_color(color, *q);
    }
    if( d2 != dia2[pos-4] ) {
        for( p = d2-1; (p >= dia2[pos-4]) && !is_free(*p) && (color^is_black(*p)); --p );
        if( (p < d2-1) && (p >= dia2[pos-4]) && !is_free(*p) )
            for( const int *q = d2-1; q > p; --q ) s.set_color(color, *q);
    }

    return s;
}

void state_t::print(ostream &os, int depth) const {
    os << "+";
    for( int j = 0; j < N; ++j ) os << "-";
    os << "+" << endl;

    int pos = 4;
    for( int i = 0; i < N; ++i ) {
        os << "|";
        for( int j = 0; j < N; ++j ) {
            if( ((i != 2) && (i != 3)) || ((j != 2) && (j != 3)) ) {
                os << (is_free(pos) ? ' ' : (is_black(pos) ? '&' : 'O'));
                ++pos;
            } else {
                assert(((i == 2) || (i == 3)) && ((j == 2) || (j == 3)));
                int p = ((i-2)<<1) + (j-2);
                os << (is_free(p) ? ' ' : (is_black(p) ? '&' : 'O'));
            }
        }
        os << "|" << endl;
    }

    os << "+";
    for( int j = 0; j < N; ++j ) os << "-";
    os << "+" << endl;
}

void state_t::print_bits(ostream &os) const {
    for( int i = 3; i >= 0; --i )
        os << (t_ & (1<<i) ? '1' : '0');
    os << ":";
    for( int i = 31; i >= 0; --i )
        os << (pos_ & (1<<i) ? '1' : '0');
    os << ":";
    for( int i = 31; i >= 0; --i )
        os << (free_ & (1<<i) ? '1' : '0');
}


/*struct hashst{
    size_t operator()(state_t s){
    }
};*/

namespace __gnu_cxx {
  template<> class hash<state_t> {
    public:
      size_t operator()(const state_t &s) const { return( s.pos() ^ s.free()) + s.t();}
  };
};

typedef struct info{
    unsigned int value;
    char type;
    unsigned char depth;
} info;

hash_map<state_t,info > hashstate;

unsigned alphaBeta2(state_t s, unsigned d, unsigned a, unsigned b, bool t){
	nodosVis++;
    //coll[h(s)%100000] = coll[h(s)%100000]+1;
    hash_map<state_t,info>::iterator it= hashstate.find(s);
    
    if(! (it==hashstate.end()) && ((*it).second).depth >= d ){
        info as = (*it).second;
        if(as.type == EXACT_VALUE) return as.value;
        if(as.type==LOWERBOUND && as.value > a) a = as.value;
        else if(as.type==UPPERBOUND && as.value < b) b = as.value;
        if( a>= b) return as.value;
    }

	if(d == 0 || s.terminal()){
        unsigned v=s.value();
        info as;
        as.depth=d;
        as.value=v;
        if(v<=a) as.type=LOWERBOUND;
        else if(v>=b) as.type=UPPERBOUND;
        else as.type=EXACT_VALUE;
        hashstate[s]=as;
        return v;
    }

	unsigned value;
	bool canMove = false;
	if(t){
        unsigned beta = b;
		for(int i=0;i<DIM;i++){
			if(s.outflank(true,i)){
				canMove=true;
				state_t sucesor = s.black_move(i);
				b = MIN(b, alphaBeta2(sucesor, d-1, a, b,false));
				if(a>=b) break;
			}
		}
		if(!canMove){
			b=MIN(b,alphaBeta2(s, d-1, a, b,false));
		}
   
        info as;
        as.depth=d;
        as.value=b;
        if(b<=a) as.type=LOWERBOUND;
        else if(b>=beta) as.type=UPPERBOUND;
        else as.type=EXACT_VALUE;
        hashstate[s]=as; 
		return b;
	}else{
        unsigned alpha =a;
		for(int i=0;i<DIM;i++){
			if(s.outflank(false,i)){
				canMove=true;
				state_t sucesor = s.white_move(i);
				a = MAX(a, alphaBeta2(sucesor, d-1, a, b,true));
				if(a>=b) break;
			}
		}
		if(!canMove){
			a=MAX(a,alphaBeta2(s, d-1, a, b,true));
		}

        info as;
        as.depth=d;
        as.value=a;
        if(a<=alpha) as.type=LOWERBOUND;
        else if(a>=b) as.type=UPPERBOUND;
        else as.type=EXACT_VALUE;
        hashstate[s]=as;
		return a;
	}
}

int alphaBeta(state_t s, unsigned char d, int a, int b, bool t){
	nodosVis++;
    hash_map<state_t,info>::iterator it= hashstate.find(s);
    int oa=a;

   /* if(!(it==hashstate.end()) && ((*it).second).depth >= d){
        info af = (*it).second;
        if(af.type == EXACT_VALUE) // stored value is exact
            return af.value;
        if(af.type == LOWERBOUND && af.value > a)  
            a = af.value;           // update lowerbound alpha if needed
        else if(af.type == UPPERBOUND && af.value < b)
            b = af.value;            // update upperbound beta if needed
        if(a >= b)
            return af.value;            // if lowerbound surpasses upperbound
    }
*/
	if(d == 0 || s.terminal()){
 //       info as;
        int value = s.value();
 /*       as.value = value;
        as.depth = d;
        if(value <= a){           // a lowerbound value
            as.type = LOWERBOUND;
        }else if(value >= b){         // an upperbound value
            as.type = UPPERBOUND;
        }else{                           // a true minimax value
            as.type = EXACT_VALUE;
        }
        //hashstate.erase(it);
        hashstate[s] = as;

*/        return value;
    }

	bool canMove = false;
	int value;
    //int best = -MAXVALUE-1;
	for(int i=0;i<DIM;i++){
		if(s.outflank(t,i)){
			canMove=true;
			state_t sucesor = s.move(t,i);
			a = MAX(a, -alphaBeta(sucesor, d-1, -b, -a,!t));
            //a = MAX(a, best);
			if(a>=b) break;
		}
	}
	if(!canMove){
		a = MAX(a,-alphaBeta(s, d-1, -b, -a,!t));
        //a = MAX(a, best);
	}
/*
    info y;
    y.value = a;
    y.depth = d;
    if(a <= oa){           // a lowerbound value
        y.type = LOWERBOUND;
    }else if(best >= b){         // an upperbound value
        y.type = UPPERBOUND;
    }else{                           // a true minimax value
        y.type = EXACT_VALUE;
    }
    //hashstate.erase(it);
    hashstate[s] = y;
*/
	return a;
}

int alphaBet(state_t s, unsigned char d, int a, int b, bool t){
	nodosVis++;
	if(d == 0 || s.terminal()) return s.value();
	bool canMove = false;
	int value;
	for(int i=0;i<DIM;i++){
		if(s.outflank(t,i)){
			canMove=true;
			state_t sucesor = s.move(t,i);
			a = MAX(a, -alphaBeta(sucesor, d-1, -b, -a,!t));
			if(a>=b) break;
		}
	}
	if(!canMove){
		a=MAX(a,-alphaBeta(s, d-1, -b, -a,!t));
	}
	return a;
}



int alphaBetaTT(state_t s, unsigned char depth, int alpha, int beta, bool t){

    int value;
    nodosVis++;
    hash_map<state_t,info>::iterator it= hashstate.find(s);
   // printf("%u ",depth);
/*
    if(!(it==hashstate.end()) && ((*it).second).depth >= depth){

        if(((*it).second).type == EXACT_VALUE) // stored value is exact
            return ((*it).second).value;
        if(((*it).second).type == LOWERBOUND && ((*it).second).value > alpha)  
            alpha = ((*it).second).value;           // update lowerbound alpha if needed
        else if(((*it).second).type == UPPERBOUND && ((*it).second).value < beta)
            beta = ((*it).second).value;            // update upperbound beta if needed
        if(alpha >= beta)
            return ((*it).second).value;            // if lowerbound surpasses upperbound
    }
*/
    if(depth == 0 || s.terminal()){
     //   s.print(cout,0);
       //  printf("%u ",depth);

        value = s.value();
/*        info as;
        as.value = value;
        as.depth = depth;
        if(value <= alpha){           // a lowerbound value
            as.type = LOWERBOUND;
        }else if(value >= beta){         // an upperbound value
            as.type = UPPERBOUND;
        }else{                           // a true minimax value
            as.type = EXACT_VALUE;
        }
        hashstate.erase(it);
        hashstate[s] = as;
  */      //s.print(cout, 0);
        //printf("value %d %c a:%d  b:%d \n", value, as.type,alpha,beta);
        return value;
    }

 //   int best = -MAXVALUE-1;
    bool canMove = false;    

    for(int i=0;i<DIM;i++){
	    if(s.outflank(t,i)){
			canMove=true;
			state_t sucesor = s.move(t, i);
			value = -alphaBetaTT(sucesor, depth-1, -beta, -alpha, !t);
        //printf("value %d a:%d  b:%d d:%d\n", value, alpha,beta,depth);

   //         if(value > best) 
     //           best = value;
            if(value > alpha)
                alpha = value;
            if(alpha >= beta)
                break;
		}
    }

    if(!canMove){
        value = -alphaBetaTT(s, depth-1, -beta, -alpha, !t);
//        if(value > best) 
//            best = value;
        if(value > alpha)
            alpha = value;
    }

/*    info y;
    y.value = best;
    y.depth = depth;
    if(best <= alpha){           // a lowerbound value
        y.type = LOWERBOUND;
    }else if(best >= beta){         // an upperbound value
        y.type = UPPERBOUND;
    }else{                           // a true minimax value
        y.type = EXACT_VALUE;
    }
    hashstate.erase(it);
    hashstate[s] = y;
*/    return alpha;
}

int mtd(state_t s, int f, bool t){

    int LB = -MAXVALUE;
    int UB = MAXVALUE;
    int g = f;
    int beta;
    while(LB<UB){

        if(g == LB) beta = g+1;
        else beta = g;

        g = alphaBeta2(s, 255, beta-1, beta, t);

        if(g<beta) UB = g;
        else LB = g;
    }

    return g;
}

int main(){
	clock_t begin,end;
    memset(coll, 0, 100000*sizeof(int));

	while(1){	
		int value,n;
		bool turn;
        hashstate.clear();
        
		//avanzar jugadas
		scanf("%d",&n);
        cerr << n;
		if(n==-1) break;
		state_t ini;
		for(int i=0;i<n;i++){
			if(i%2==0){
				ini = ini.black_move(PV[i]);
			}else{
				ini = ini.white_move(PV[i]);
			}
		}
 //       ini.print(cout,0);
		turn =(n%2==0);
		nodosVis=0;
		begin = clock();
        //if(turn) value=alphaBeta2(ini,255,0,MAXVALUE,turn);
        //else value=alphaBeta2(ini,255,0,MAXVALUE,turn);
        if(turn) value=mtd(ini,35,turn);
        else value=mtd(ini,35,turn);
		end = clock();
		printf("Jugada del PV: %d, Valor=%d, Nodos Visitados = %ld, tiempo tomado = %.2lf\n",
				n,value,nodosVis,((double) (end-begin))/CLOCKS_PER_SEC);
	}
	return 0;
}
