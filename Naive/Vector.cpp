#include<iostream>
#include<vector>
#include<fstream>
#include "Point.h"
#include "Vector.h"


// Przydatne definicje (caly program)
#define REP(i,a,b) for(int i=a; i<=b; ++i)

// Przydatne definicje (punkt, wektor)
#define X t[0]
#define Y t[1]
#define Z t[2]


// Konstruktor (podajemy wspolrzedne jawnie)
Vector::Vector(double x, double y, double z){
	(*this).X = x;
	(*this).Y = y;
	(*this).Z = z;
}


// Konstruktor (podajemy punkt poczatkowy i koncowy)
Vector::Vector(const Point &P_start, const Point &P_end){
	
	Point P = P_end - P_start;
	
	REP(i,0,3-1){
		(*this).t[i] = P.get_ith_coord(i);
	}
}


// Konstruktor (podajemy punkt koncowy; punkt poczatkowy to (0,0,0) )
Vector::Vector(const Point &P_end){
	
	REP(i,0,3-1){
		(*this).t[i] = P_end.get_ith_coord(i);
	}
}


// Destruktor
Vector::~Vector(){}


// Konstruktor kopiujacy
Vector::Vector(const Vector &other){
	REP(i,0,3-1){
		(*this).t[i] = other.t[i];
	}
}



// Gettery

// Ustawienie i-tej wspolrzednej (i=0,1,2)
double Vector::get_ith_coord(int i) const{
	return (*this).t[i];
}


// Pobranie wspolrzednej x
double Vector::get_x() const{
	return (*this).X;
}


// Pobranie wspolrzednej y
double Vector::get_y() const{
	return (*this).Y;
}


// Pobranie wspolrzednej z
double Vector::get_z() const{
	return (*this).Z;
}



// Settery

// Ustawienie i-tej wspolrzednej (i=0,1,2)
void Vector::set_ith_coord(int i, double val){
	(*this).t[i] = val;
}


// Ustawienie wspolrzednej x
void Vector::set_x(double x){
	(*this).X = x;
}


// Ustawienie wspolrzednej y
void Vector::set_y(double y){
	(*this).Y = y;
}


// Ustawienie wspolrzednej z
void Vector::set_z(double z){
	(*this).Z = z;
}


// Ustawienie wspolrzednych
void Vector::set(double x, double y, double z){
	(*this).X = x;
	(*this).Y = y;
	(*this).Z = z;
}



// Dodawanie wektorow
Vector Vector::operator + (const Vector &a) const{
	Vector result;
	
	REP(i,0,3-1){
		result.set_ith_coord( i, (*this).get_ith_coord(i) + a.get_ith_coord(i) );
	}
	
	return result;
}


// Odejmowanie wektorow
Vector Vector::operator - (const Vector &a) const{
	Vector result;
	
	REP(i,0,3-1){
		result.set_ith_coord( i, (*this).get_ith_coord(i) - a.get_ith_coord(i) );
	}
	
	return result;	
}


// Iloczyn wektorowy this x b
Vector Vector::operator * (const Vector &b) const{
	double x = (*this).get_y()*b.get_z() - (*this).get_z()*b.get_y();
	double y = -( (*this).get_x()*b.get_z() - (*this).get_z()*b.get_x() );
	double z = (*this).get_x()*b.get_y() - (*this).get_y()*b.get_x();
	
	Vector result(x,y,z);
	
	return result;
}


// Iloczyn skalarny this oraz b
double Vector::operator ^ (const Vector &b) const{
	double sum = 0.;
	
	REP(i,0,3-1){
		sum += (*this).t[i] * b.t[i];
	}
	
	return sum;
}


std::ostream& operator << (std::ostream &out, const Vector &v){
    out << v.X << " " << v.Y << " " << v.Z << std::endl;
}
