#include<iostream>
#include<vector>
#include<fstream>

#include "Point.h"
#include "Vector.h"
#include "Plane.h"


#define REP(i,a,b) for(int i=a; i<=b; ++i)


// Przydatne definicje (plaszczyzna)
#define A t[0]
#define B t[1]
#define C t[2]
#define D t[3]




// Sprawdzamy, czy liczbe zmiennoprzecinkowa
// mozemy uznac za zero
bool Plane::is_zero(double a){
	const double eps = 1e-9; 
	return a < eps && a>-eps; // |a| < eps
}


// Konstruktor
Plane::Plane(){
	
	REP(i,0,3){
		(*this).t[i] = 0.;
	}
	
	REP(i,0,3-1){
		(*this).P[i].set(0., 0., 0.);
		
		(*this).edge_number[i] = -1; // UNDEF
	}
}


// Destruktor
Plane::~Plane(){}


// Konstruktor kopiujacy
Plane::Plane(const Plane &other){
	REP(i,0,3){
		(*this).t[i] = other.t[i];
	}
	
	REP(i,0,3-1){
		(*this).P[i] = other.P[i];
		(*this).edge_number[i] = other.edge_number[i];
	}
}



// Gettery

// Pobranie i-tego identyfikatora krawedzi (i=0,1,2)
int Plane::get_ith_edge_number(int i) const{
	return (*this).edge_number[i];
}


// Pobranie i-tego punktu (i=0,1,2)
Point Plane::get_ith_point(int i) const{
	return (*this).P[i];
}


// Pobranie i-tego wspolczynnika (i=0,1,2,3)
double Plane::get_ith_coeff(int i) const{
	return (*this).t[i];
}


// Pobranie wspolczynnika A
double Plane::get_A() const{
	return (*this).A;
}


// Pobranie wspolczynnika B
double Plane::get_B() const{
	return (*this).B;
}


// Pobranie wspolczynnika C
double Plane::get_C() const{
	return (*this).C;
}


// Pobranie wspolczynnika D
double Plane::get_D() const{
	return (*this).D;
}



// Settery

// Ustawienie i-tego identyfikatora krawedzi (i=0,1,2)
void Plane::set_ith_edge_number(int i, int val){
	(*this).edge_number[i] = val;
}


// Ustawienie i-tego punktu (i=0,1,2)
void Plane::set_ith_point(int i, const Point &P){
	(*this).P[i] = P;
}


// Ustawienie i-tego wspolczynnika (i=0,1,2,3)
void Plane::set_ith_coeff(int i, double val){
	(*this).t[i] = val;
}


// Ustawienie wspolczynnika A
void Plane::set_A(double val){
	(*this).A = val;
}


// Ustawienie wspolczynnika B
void Plane::set_B(double val){
	(*this).B = val;
}


// Ustawienie wspolczynnika C
void Plane::set_C(double val){
	(*this).C = val;
}


// Ustawienie wspolczynnika D
void Plane::set_D(double val){
	(*this).D = val;
}



// Tworzymy plaszczyzne z 3 niewspolliniowych (!) punktow
Plane Plane::create_plane(const Point &P1, const Point &P2, const Point &P3){
	
	Plane result;
	result.set_ith_point(0, P1);
	
	
	Vector P1P2(P1, P2), P1P3(P1, P3);
	
	Vector tmp = P1P2 * P1P3;
	
	const double eps = 1e-9;
	
	if( tmp.get_ith_coord(0) > eps || tmp.get_ith_coord(1) > eps || tmp.get_ith_coord(2) > eps ){
		result.set_ith_point(1, P2);
		result.set_ith_point(2, P3);
	}
	else{
		result.set_ith_point(1, P3);
		result.set_ith_point(2, P2);
	}
	
	
	
	
	Vector a( result.get_ith_point(0) ), b( result.get_ith_point(1) ), c( result.get_ith_point(2) );
	
	/*REP(i,0,DIM-1){
		cout << c.get_ith_coord(i) << " ";
	}
	cout << endl;
	*/
	
	Vector n = (b - a) * (c - a); // wektor wspolczynnikow A,B,C plaszczyzny (odpowiednio) i normalny zarazem
	
	/*REP(i,0,DIM-1){
		cout << n.get_ith_coord(i) << " ";
	}
	cout << endl;
	*/
	
	//Plane result;
	
	/*result.set_ith_point(0, P1);
	result.set_ith_point(1, P2);
	result.set_ith_point(2, P3);
	*/
	
	REP(i,0,3-1){
		result.set_ith_coeff( i, n.get_ith_coord(i) );
	}
	
	result.set_D(  -( result.A * P1.get_x()  +  result.B * P1.get_y()  +  result.C * P1.get_z() )  );
	
	//(*this) = result;
	
	//return *this;
	
	return result;
}


// Zwracamy identyfikator strony punktu P wzgledem plaszczyzny pi:
//	-1 - punkt P lezy po jednej stronie plaszczyzny pi
//	0 - punkt P lezy na plaszczyznie pi
//	1 - punkt P lezy po drugiej stronie plaszczyzny pi
int Plane::side(const Plane &pi, const Point &P){
	double sum = 0.;
	
	REP(i,0,3-1){
		//cout << pi.get_ith_coeff(i) << " " << P.get_ith_coord(i) << " ";
		sum  +=  pi.get_ith_coeff(i) * P.get_ith_coord(i);
	}
	sum += pi.get_D();
	
	//cout << sum << endl;
	
	if( is_zero(sum) ){
		return 0;
	}
	
	if( sum < 0. ){
		return -1; 
	}
	
	return 1;
}


// Objetosc (ze znakiem) czworoscianu (podstawa pi, wierzcholek P)
double Plane::V(const Plane &pi, const Point &P){
	Vector AB( pi.get_ith_point(0), pi.get_ith_point(1) );
	Vector AC( pi.get_ith_point(0), pi.get_ith_point(2) );
	Vector AP( pi.get_ith_point(0), P );
	
	//std::cout << "AB: " << AB << std::endl << "AC: " << AC << std::endl << "AP: " << AP << std::endl;
	
	//std::cout << (AB*AC) << std::endl;
	
	return 1./6. * ( AP ^ (AB * AC) );
}


std::ostream& operator << (std::ostream &out, const Plane &pi){
	
	REP(i,0,3-1){
		REP(j,0,3-1){
			out << pi.get_ith_point(i).get_ith_coord(j) << " ";
		}
		out << std::endl;
	}
}
