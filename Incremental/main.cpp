/*

Algorytm incremental
do znajdowania otoczki wypuklej punktow 
w przestrzeni trojwymiarowej (3D).

Zalozenie: kazda trojka punktow nie jest wspolliniowa
		   oraz kazda czworka punktow nie jest wspolplaszczyznowa 
		   (w razie potrzeby, uwzglednic to w rownaniu plaszczyzny i wlasciwym algorytmie)!
		   
Dodatkowo, liczba punktow n >= 4.

*/


#include <iostream>
#include <vector>
#include <fstream>

#include "Point.h"
#include "Vector.h"
#include "Edge.h"
#include "Plane.h"
#include "PointGeneration.h"
#include "Voxelization.h"




#define REP(i,a,b) for(int i=a; i<=b; ++i)



const int MAX_N = 300; // maksymalna liczba punktow


int n;
Point P[MAX_N];
std::vector <Plane> Faces; // wygenerowane sciany w czasie algorytmu
std::vector <bool> is_face_in_hull(6, true); // is_face_in_hull[i] - czy i-ta sciana nalezy do otoczki wypuklej?
std::vector <Edge> Edges; // krawedzie otoczki wypuklej


void read_data(){
	
	std::ifstream file_in("in.txt");
	
	file_in >> n;
	
	double x, y, z;
	REP(i,0,n-1){
		file_in >> x >> y >> z;
		P[i].set(x, y, z);
	}
	
	file_in.close();
}


// Wlasciwy algorytm
void compute(){
	
	Edge e01, e02, e03, e12, e13, e23;
	
	
	
	
	// Inicjacja otoczki wypuklej z pierwszych 4 punktow
	
	// Krawedzie
	
	// e01
	e01.set_ith_point_number(0, 0);
	e01.set_ith_point_number(1, 1);
	
	e01.set_ith_face_number(0, 0);
	e01.set_ith_face_number(1, 1);
	
	// e02
	e02.set_ith_point_number(0, 0);
	e02.set_ith_point_number(1, 2);
	
	e02.set_ith_face_number(0, 0);
	e02.set_ith_face_number(1, 2);
	
	// e03
	e03.set_ith_point_number(0, 0);
	e03.set_ith_point_number(1, 3);
	
	e03.set_ith_face_number(0, 1);
	e03.set_ith_face_number(1, 2);
	
	// e12
	e12.set_ith_point_number(0, 1);
	e12.set_ith_point_number(1, 2);
	
	e12.set_ith_face_number(0, 0);
	e12.set_ith_face_number(1, 3);
	
	// e13
	e13.set_ith_point_number(0, 1);
	e13.set_ith_point_number(1, 3);
	
	e13.set_ith_face_number(0, 1);
	e13.set_ith_face_number(1, 3);
	
	// e23
	e23.set_ith_point_number(0, 2);
	e23.set_ith_point_number(1, 3);
	
	e23.set_ith_face_number(0, 2);
	e23.set_ith_face_number(1, 3);
	
	
	
	Edges.push_back(e01); // e0
	Edges.push_back(e02); // e1
	Edges.push_back(e03); // e2
	Edges.push_back(e12); // e3
	Edges.push_back(e13); // e4
	Edges.push_back(e23); // e5
	
	
	
	
	Plane pi;
	
	// Sciany
	pi = Plane::create_plane( P[0], P[1], P[2] );
	pi.set_ith_edge_number(0, 0); // e01 = e0
	pi.set_ith_edge_number(1, 1); // e02 = e1
	pi.set_ith_edge_number(2, 3); // e12 = e3
	Faces.push_back( pi ); // pi0
	
	pi = Plane::create_plane( P[0], P[1], P[3] );
	pi.set_ith_edge_number(0, 0); // e01 = e0
	pi.set_ith_edge_number(1, 2); // e03 = e2
	pi.set_ith_edge_number(2, 4); // e13 = e4
	Faces.push_back( pi ); // pi1
	
	pi = Plane::create_plane( P[0], P[2], P[3] );
	pi.set_ith_edge_number(0, 1); // e02 = e1
	pi.set_ith_edge_number(1, 2); // e03 = e2
	pi.set_ith_edge_number(2, 5); // e23 = e5
	Faces.push_back( pi ); // pi2
	
	pi = Plane::create_plane( P[1], P[2], P[3] );
	pi.set_ith_edge_number(0, 3); // e12 = e3
	pi.set_ith_edge_number(1, 4); // e13 = e4
	pi.set_ith_edge_number(2, 5); // e23 = e5
	Faces.push_back( pi ); // pi3
	
	
	//std::ofstream abc("out2.txt");
	/*
	std::cout << "\nPoczatkowe sciany:\n";
	REP(x,0,3){
		std::cout << Faces[x] << std::endl << std::endl;
	}
	//abc.close();
	std::cout << std::endl;
	*/
	
	
	int edge_counter = 6; // numer kolejnej (do dodania) krawedzi
	int face_counter = 4; // numer kolejnej (do dodania) sciany
	Edge e;
	
	
	// Dla kazdego nastepnego punktu wyznaczymy nowe przyblizenie otoczki wypuklej
	REP(i,4,n-1){
		
		//std::cout << "Punkt nr " << i << std::endl;
		
		
		
		int visible_faces = 0; // liczba widocznych scian z perspektywy punktu P[i]
		
		int noFaces = Faces.size(); // liczba scian aktualnego przyblizenia otoczki wypuklej
		
		//std::cout << noFaces << std::endl;
		
		std::vector <bool> visible(noFaces, false); // visible[j] - czy j-ta sciana widoczna z aktualnego punktu P[i]?
		
		
		// Dla kazdej sciany w aktualnym przyblizeniu otoczki
		REP(j,0,noFaces-1){
			
			if( is_face_in_hull[j] == true ){
				double Volume = Plane::V( Faces[j], P[i] );
				
				//std::cout << "\n\nSciana nr " << j << ":\n" << Faces[j] << P[i] << Volume << std::endl;
				
				if( Volume < 0. ){
					++visible_faces;
					visible[j] = true;
					
					//std::cout << "sciana nr " << j << " jest widoczna" << std::endl;
		
					
				}
				else{
					//std::cout << "sciana nr " << j << " nie jest widoczna" << std::endl;
				}
			}
		}
		
		//std::cout << std::endl;
		
		if( visible_faces > 0 ){ // jesli istnieja widoczne sciany z perspektywy punktu P[i]
			int noEdges = Edges.size();
			
			// kazda krawedz
			REP(j,0,noEdges-1){
				int face0 = Edges[j].get_ith_face_number(0);
				int face1 = Edges[j].get_ith_face_number(1);
				
				//std::cout << face0 << " " << face1 << ": ";
				
				if(   (face0 > -1 && visible[face0] == true && face1 > -1 && visible[face1] == false  &&  is_face_in_hull[face0] == true  &&  is_face_in_hull[face1] == true  )   ||   (face0 > -1 && visible[face0] == false && face1 > -1 && visible[face1] == true && is_face_in_hull[face0] == true  &&  is_face_in_hull[face1] == true)   ){
					
					// Usuwanie sciany
					if(face0 > -1 && visible[face0] == true && face1 > -1 && visible[face1] == false  &&  is_face_in_hull[face0] == true  &&  is_face_in_hull[face1] == true){
						is_face_in_hull[face0] = false;
						
						//std::cout << "Usuniecie sciany nr " << face0 << ":\n";
						//std::cout << Faces[face0] << std::endl;
						
						//std::cout << "trafienie\n";
						
					}
					else{
						is_face_in_hull[face1] = false;
						
						//std::cout << "Usuniecie sciany nr " << face1 << ":\n";
						//std::cout << Faces[face1] << std::endl;
						
						//std::cout << "nietrafienie\n";
					}
					
					
					
					
					
					Edge e1,e2;
					
					
					
					
					/* Dodanie nowej sciany do otoczki */
					
					// Krawedzie
	
					// Edges[j]
					REP(k,0,2-1){
						if( Edges[j].get_ith_face_number(k) > -1 && visible[Edges[j].get_ith_face_number(k)] == true  &&  is_face_in_hull[ Edges[j].get_ith_face_number(k) ] == true ){
							Edges[j].set_ith_face_number(k, face_counter);
							break;
						}
					}
					
					// e1
					e1.set_ith_point_number( 0, Edges[j].get_ith_point_number(0) );
					e1.set_ith_point_number(1, i); // P[i]
					
					REP(k,0,2-1){
						if( e1.get_ith_face_number(k) == -1 ){
							e1.set_ith_face_number(k, face_counter);
							break;
						}
					}
					
					// e2
					e2.set_ith_point_number( 0, Edges[j].get_ith_point_number(1) );
					e2.set_ith_point_number(1, i); // P[i]
					
					REP(k,0,2-1){
						if( e2.get_ith_face_number(k) == -1 ){
							e2.set_ith_face_number(k, face_counter);
							break;
						}
					}
					
					
					Edges.push_back( e1 ); // edge_counter
					Edges.push_back( e2 ); // edge_counter + 1
					
					
					
					// Sciana
					pi = Plane::create_plane( P[ Edges[j].get_ith_point_number(0) ], P[ Edges[j].get_ith_point_number(1) ], P[i] );
					pi.set_ith_edge_number(0, j); // Edges[j]
					pi.set_ith_edge_number(1, edge_counter); // e1
					pi.set_ith_edge_number(2, edge_counter+1); // e2
					Faces.push_back( pi ); //
					is_face_in_hull.push_back(true); // wlasnie stworzona sciana jest w otoczce wypuklej 
					
					++face_counter;
				}
			}
		}
		
		
		
		// Kontrolne sprawdzenie
		/*
		std::cout << "\n\nPo analizie punktu nr " << i << ":\n";
		REP(j,0,Faces.size()-1){
			if( is_face_in_hull[j] == true ){
				std::cout << Faces[j] << std::endl;
			}
		}
		std::cout << std::endl;
		*/
		
		
		// Czyszczenie
		visible.clear();
	}	
}


void save_result(){
	
	std::ofstream file_out("out.txt"); // plik wyjsciowy
	
	int m = Faces.size(); // liczba scian (nie wszystkie naleza do otoczki)
	int no_hull_faces = 0; // liczba scian otoczki
	
	
	// Wyznaczenie liczby scian otoczki
	REP(i,0,m-1){
		if( is_face_in_hull[i] == true ){
			++no_hull_faces;
		}
	}
	file_out << no_hull_faces << std::endl;
	
	
	// Wypisanie scian otoczki
	REP(i,0,m-1){
		if( is_face_in_hull[i] == true ){
			file_out << Faces[i] << std::endl;
		}
	}
	
	file_out.close(); // zamykamy plik wyjsciowy
}


/*
void compute1(){
	/*
	Point P1(0,0,0);
	Point P2(1,0,0);
	Point P3(0,1,0);
	Point DD(0,0,1);
	
	Plane pi = Plane::create_plane(P3,P2,P1);
	
	double Vol = Plane::V(pi, DD);
	
	std::cout << Vol << std::endl;
	
	
	Point P1(0,0,0);
	Point P2(0,10,0);
	Point P3(0,0,10);
	Point DD(2,2,2);
	
	Plane pi = Plane::create_plane(P3,P2,P1);
	
	double Vol = Plane::V(pi, DD);
	
	std::cout << Vol << std::endl;
}
*/


int main(int argc, char** argv){

	std::ofstream file_ball_points_incremental("ball_points_incremental.txt");
	for (int i = 1; i <= 11; i++) {
		long long mean_time;
		int n = i * 200;
		for (int k = 0; k < 5; k++) {
			Point P[MAX_N];
			std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
			std::vector<Point> vector = GeneratePointsBall(n, 10.0);
			std::set<Point> set = Voxelize(vector, 1.0);
			int j = 0;
			for (std::set<Point>::iterator it = set.begin(); it != set.end(); ++it) {
				P[j] = *it;
				j++;
			}
			compute(P, n);
			std::chrono::duration<float, std::micro> elapsed = std::chrono::high_resolution_clock::now() - start;
			mean_time += elapsed.count();
		}
		mean_time /= 5;
		file_ball_points_incremental << n << " " << mean_time << std::endl;
	}
	file_ball_points_incremental.close();

	std::ofstream file_sphere_points_incremental("sphere_points_incremental.txt");
	for (int i = 1; i <= 11; i++) {
		long long mean_time;
		int n = i * 200;
		for (int k = 0; k < 5; k++) {
			Point P[MAX_N];
			std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
			std::vector<Point> vector = GeneratePointsSphere(n, 10.0);
			std::set<Point> set = Voxelize(vector, 1.0);
			int j = 0;
			for (std::set<Point>::iterator it = set.begin(); it != set.end(); ++it) {
				P[j] = *it;
				j++;
			}
			compute(P, n);
			std::chrono::duration<float, std::micro> elapsed = std::chrono::high_resolution_clock::now() - start;
			mean_time += elapsed.count();
		}
		mean_time /= 5;
		file_sphere_points_incremental << n << " " << mean_time << std::endl;
	}
	file_sphere_points_incremental.close();

	std::ofstream file_cube_points_incremental("cube_points_incremental.txt");
	for (int i = 1; i <= 11; i++) {
		long long mean_time;
		int n = i * 200;
		for (int k = 0; k < 5; k++) {
			Point P[MAX_N];
			std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
			std::vector<Point> vector = GeneratePointsCube(n, 10.0);
			std::set<Point> set = Voxelize(vector, 1.0);
			int j = 0;
			for (std::set<Point>::iterator it = set.begin(); it != set.end(); ++it) {
				P[j] = *it;
				j++;
			}
			compute(P, n);
			std::chrono::duration<float, std::micro> elapsed = std::chrono::high_resolution_clock::now() - start;
			mean_time += elapsed.count();
		}
		mean_time /= 5;
		file_cube_points_incremental << n << " " << mean_time << std::endl;
	}
	file_cube_points_incremental.close();





	std::ofstream file_ball_size_incremental("ball_size_incremental.txt");
	for (int i = 1; i <= 11; i++) {
		long long mean_time;
		int n = 1000;
		for (int k = 0; k < 5; k++) {
			Point P[MAX_N];
			std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
			std::vector<Point> vector = GeneratePointsBall(n, 10.0);
			std::set<Point> set = Voxelize(vector, 0.3 * i);
			int j = 0;
			for (std::set<Point>::iterator it = set.begin(); it != set.end(); ++it) {
				P[j] = *it;
				j++;
			}
			compute(P, n);
			std::chrono::duration<float, std::micro> elapsed = std::chrono::high_resolution_clock::now() - start;
			mean_time += elapsed.count();
		}
		mean_time /= 5;
		file_ball_size_incremental << 0.3 * i << " " << mean_time << std::endl;
	}
	file_ball_size_incremental.close();

	std::ofstream file_sphere_size_incremental("sphere_size_incremental.txt");
	for (int i = 1; i <= 11; i++) {
		long long mean_time;
		int n = 1000;
		for (int k = 0; k < 5; k++) {
			Point P[MAX_N];
			std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
			std::vector<Point> vector = GeneratePointsSphere(n, 10.0);
			std::set<Point> set = Voxelize(vector, 0.3 * i);
			int j = 0;
			for (std::set<Point>::iterator it = set.begin(); it != set.end(); ++it) {
				P[j] = *it;
				j++;
			}
			compute(P, n);
			std::chrono::duration<float, std::micro> elapsed = std::chrono::high_resolution_clock::now() - start;
			mean_time += elapsed.count();
		}
		mean_time /= 5;
		file_sphere_size_incremental << 0.3 * i << " " << mean_time << std::endl;
	}
	file_sphere_size_incremental.close();

	std::ofstream file_cube_size_incremental("cube_size_incremental.txt");
	for (int i = 1; i <= 11; i++) {
		long long mean_time;
		int n = 1000;
		for (int k = 0; k < 5; k++) {
			Point P[MAX_N];
			std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
			std::vector<Point> vector = GeneratePointsCube(n, 10.0);
			std::set<Point> set = Voxelize(vector, 0.3 * i);
			int j = 0;
			for (std::set<Point>::iterator it = set.begin(); it != set.end(); ++it) {
				P[j] = *it;
				j++;
			}
			compute(P, n);
			std::chrono::duration<float, std::micro> elapsed = std::chrono::high_resolution_clock::now() - start;
			mean_time += elapsed.count();
		}
		mean_time /= 5;
		file_cube_size_incremental << 0.3 * i << " " << mean_time << std::endl;
	}
	file_cube_size_incremental.close();

	return 0;
}