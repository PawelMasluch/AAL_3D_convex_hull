#include<iostream>
#include<vector>
#include<fstream>
#include "Point.h"


// Przydatne definicje (caly program)
#define REP(i,a,b) for(int i=a; i<=b; ++i)

// Przydatne definicje (punkt, wektor)
#define X t[0]
#define Y t[1]
#define Z t[2]


//const int DIM = 3; // liczba wymiarow punktow

//const double eps = 1e-9; // dokladnosc


// Konstruktor
Point::Point(double x, double y, double z){
	(*this).X = x;
	(*this).Y = y;
	(*this).Z = z;
}


// Destruktor
Point::~Point(){}


// Konstruktor kopiujacy
Point::Point(const Point &other){
	REP(i,0,3-1){
		(*this).t[i] = other.t[i];
	}
}



// Gettery

// Ustawienie i-tej wspolrzednej (i=0,1,2)
double Point::get_ith_coord(int i) const{
	return (*this).t[i];
}


// Pobranie wspolrzednej x
double Point::get_x() const{
	return (*this).X;
}


// Pobranie wspolrzednej y
double Point::get_y() const{
	return (*this).Y;
}


// Pobranie wspolrzednej z
double Point::get_z() const{
	return (*this).Z;
}



// Settery

// Ustawienie i-tej wspolrzednej (i=0,1,2)
void Point::set_ith_coord(int i, double val){
	(*this).t[i] = val;
}


// Ustawienie wspolrzednej x
void Point::set_x(double x){
	(*this).X = x;
}


// Ustawienie wspolrzednej y
void Point::set_y(double y){
	(*this).Y = y;
}


// Ustawienie wspolrzednej z
void Point::set_z(double z){
	(*this).Z = z;
}


// Ustawienie wspolrzednych
void Point::set(double x, double y, double z){
	(*this).X = x;
	(*this).Y = y;
	(*this).Z = z;
}


// Dodawanie punktow
Point Point::operator + (const Point &P) const{
	Point result;
	
	REP(i,0,3-1){
		result.set_ith_coord( i, (*this).get_ith_coord(i) + P.get_ith_coord(i) );
	}
	
	return result;	
}


// Odejmowanie punktow
Point Point::operator - (const Point &P) const{
	Point result;
	
	REP(i,0,3-1){
		result.set_ith_coord( i, (*this).get_ith_coord(i) - P.get_ith_coord(i) );
	}
	
	return result;	
}


// Zapis punktu do pliku
std::ostream& operator << (std::ostream &out, const Point &P){
    out << P.get_x() << " " << P.get_y() << " " << P.get_z() << std::endl;
}
bool operator< (Point const& a, Point const& b) {
	if (a.X < b.X) {
		return true;
	}
	else if (a.X == b.X) {
		if (a.Y < b.Y) {
			return true;
		}
		else if (a.Y == b.Y && a.Z < b.Z) {
			return true;
		}
	}
	return false;
}
