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
#include<chrono>

#include "Point.h"
#include "Vector.h"
#include "Plane.h"
#include "../PointGeneration.h"
#include "../Voxelization.h"


using namespace std;


// Przydatne definicje (caly program)
#define REP(i,a,b) for(int i=a; i<=b; ++i)


const int MAX_N = 350; // maksymalna liczba punktow


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


void compute(Point* P, int n){
	
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
	string test_data_ball;
	string test_data_square;
	string test_data_sphere;
	ofstream file_ball_points_naive("ball_points_naive.txt");
	for (int i = 0; i < 10; i++) {
		long long mean_time;
		int n = i * 30;
		for (int k = 0; i < 5; i++) {	
			Point P[MAX_N];
			std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
			vector<Point> vextor = GeneratePointsBall(n, 10.0);
			set<Point> set = Voxelize(vector, 1.0);
			int j = 0;
			for (std::set<Point>::iterator it = points.begin(); it != points.end(); ++it) {
				P[j] = *it;
				j++;
			}
			compute(P, n);
			std::chrono::duration<float, std::micro> elapsed = std::chrono::high_resolution_clock::now() - start;
			mean_time += elapsed
		}
		mean_time /= 5;
		file_ball_points_naive << n << " " << mean_time << endl;
	}
	file_ball_points_naive.close();

	ofstream file_sphere_points_naive("sphere_points_naive.txt");
	for (int i = 0; i < 10; i++) {
		long long mean_time;
		int n = i * 30;
		for (int k = 0; i < 5; i++) {
			Point P[MAX_N];
			std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
			vector<Point> vextor = GeneratePointsSphere(n, 10.0);
			set<Point> set = Voxelize(vector, 1.0);
			int j = 0;
			for (std::set<Point>::iterator it = points.begin(); it != points.end(); ++it) {
				P[j] = *it;
				j++;
			}
			compute(P, n);
			std::chrono::duration<float, std::micro> elapsed = std::chrono::high_resolution_clock::now() - start;
			mean_time += elapsed
		}
		mean_time /= 5;
		file_sphere_points_naive << n << " " << mean_time << endl;
	}
	file_sphere_points_naive.close();

	ofstream file_cube_points_naive("cube_points_naive.txt");
	for (int i = 0; i < 10; i++) {
		long long mean_time;
		int n = i * 30;
		for (int k = 0; i < 5; i++) {
			Point P[MAX_N];
			std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
			vector<Point> vextor = GeneratePointsCube(n, 10.0);
			set<Point> set = Voxelize(vector, 1.0);
			int j = 0;
			for (std::set<Point>::iterator it = points.begin(); it != points.end(); ++it) {
				P[j] = *it;
				j++;
			}
			compute(P, n);
			std::chrono::duration<float, std::micro> elapsed = std::chrono::high_resolution_clock::now() - start;
			mean_time += elapsed
		}
		mean_time /= 5;
		file_cube_points_naive << n << " " << mean_time << endl;
	}
	file_cube_points_naive.close();





	ofstream file_ball_size_naive("ball_size_naive.txt");
	for (int i = 0; i < 10; i++) {
		long long mean_time;
		int n = 100;
		for (int k = 0; i < 5; i++) {
			Point P[MAX_N];
			std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
			vector<Point> vextor = GeneratePointsBall(n, 10.0);
			set<Point> set = Voxelize(vector, 0.3*n);
			int j = 0;
			for (std::set<Point>::iterator it = points.begin(); it != points.end(); ++it) {
				P[j] = *it;
				j++;
			}
			compute(P, n);
			std::chrono::duration<float, std::micro> elapsed = std::chrono::high_resolution_clock::now() - start;
			mean_time += elapsed
		}
		mean_time /= 5;
		file_ball_size_naive << n << " " << mean_time << endl;
	}
	file_ball_size_naive.close();

	ofstream file_sphere_size_naive("sphere_size_naive.txt");
	for (int i = 0; i < 10; i++) {
		long long mean_time;
		int n = 100;
		for (int k = 0; i < 5; i++) {
			Point P[MAX_N];
			std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
			vector<Point> vextor = GeneratePointsSphere(n, 10.0);
			set<Point> set = Voxelize(vector, 0.3 * n);
			int j = 0;
			for (std::set<Point>::iterator it = points.begin(); it != points.end(); ++it) {
				P[j] = *it;
				j++;
			}
			compute(P, n);
			std::chrono::duration<float, std::micro> elapsed = std::chrono::high_resolution_clock::now() - start;
			mean_time += elapsed
		}
		mean_time /= 5;
		file_sphere_size_naive << n << " " << mean_time << endl;
	}
	file_sphere_size_naive.close();

	ofstream file_cube_size_naive("cube_size_naive.txt");
	for (int i = 0; i < 10; i++) {
		long long mean_time;
		int n = 100;
		for (int k = 0; i < 5; i++) {
			Point P[MAX_N];
			std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
			vector<Point> vextor = GeneratePointsCube(n, 10.0);
			set<Point> set = Voxelize(vector, 0.3 * n);
			int j = 0;
			for (std::set<Point>::iterator it = points.begin(); it != points.end(); ++it) {
				P[j] = *it;
				j++;
			}
			compute(P, n);
			std::chrono::duration<float, std::micro> elapsed = std::chrono::high_resolution_clock::now() - start;
			mean_time += elapsed
		}
		mean_time /= 5;
		file_cube_size_naive << n << " " << mean_time << endl;
	}
	file_cube_size_naive.close();



	
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
