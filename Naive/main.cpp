/*

Algorytm naiwny 
do znajdowania otoczki wypuklej punktow 
w przestrzeni trojwymiarowej (3D).

Zalozenie: kazda trojka punktow nie jest wspolliniowa
		   oraz kazda czworka punktow nie jest wspolplaszczyznowa 
		   (w razie potrzeby, uwzglednic to w rownaniu plaszczyzny i wlasciwym algorytmie)!

Liczba punktow n >= 4.

*/


#include<iostream>
#include<vector>
#include<fstream>

#include "Point.h"
#include "Vector.h"
#include "Plane.h"


using namespace std;


// Przydatne definicje (caly program)
#define REP(i,a,b) for(int i=a; i<=b; ++i)


const int MAX_N = 300; // maksymalna liczba punktow


int n;
Point P[MAX_N];
vector <Plane> convex_hull;


void read_data(){
	
	ifstream file_in("in.txt");
	
	file_in >> n;
	
	double x, y, z;
	REP(i,0,n-1){
		file_in >> x >> y >> z;
		P[i].set(x, y, z);
	}
	
	file_in.close();
}


void compute(){
	
	Plane pi;
	
	int side1 = 0, side2 = 0;
	
	// Kazda trojka punktow
	REP(i,0,n-1){
		REP(j,i+1,n-1){
			REP(k,j+1,n-1){
				
				pi = Plane::create_plane( P[i], P[j], P[k] );
				
				REP(l,0,n-1){
					if( l != i  &&  l != j  &&  l != k ){
						
						if( Plane::side(pi, P[l]) == -1 ){
							++side1;
						}
						else{
							if( Plane::side(pi, P[l]) == 1 ){
								++side2;
							}
						}
					}
				}
				
				//cout << i << " " << j << " " << k << ": side1 = " << side1 << ", side2 = " << side2 << endl;
				
				if( (side1 == 0 && side2 > 0)  ||  (side1 > 0 && side2 == 0) ){
					convex_hull.push_back(pi);
				}
				
				side1 = side2 = 0;
			}
		}
	}
	
}


void save_result(){
	
	ofstream file_out("out.txt");
	
	int m = convex_hull.size(); // liczba scian otoczki wypuklej
	file_out << m << endl;
	
	REP(i,0,m-1){
		file_out << convex_hull[i] << endl;
	}
	
	file_out.close();
}


int main(int argc, char** argv){
	
	read_data();
	compute();
	save_result();
	
	return 0;
}


/*

Testy:



Test #1:

In:
4
10 0 0
0 0 0
0 10 0
0 0 10 


Out:
4
10 0 0 
0 0 0 
0 10 0 

10 0 0 
0 0 0 
0 0 10 

10 0 0 
0 10 0 
0 0 10 

0 0 0 
0 10 0 
0 0 10 




Test #2:

In:
7
10 0 0
0 0 0
0 10 0
0 0 10
1 1 1
0.5 0.5 0.5
2 2 2


Out:
4
10 0 0 
0 0 0 
0 10 0 

10 0 0 
0 0 0 
0 0 10 

10 0 0 
0 10 0 
0 0 10 

0 0 0 
0 10 0 
0 0 10 




*/
