#include<iostream>
#include<vector>
#include<fstream>


#ifndef VECTOR_H
#define VECTOR_H


#include "Point.h"


// Wektor 3D: v = [x, y, z]
class Vector{
	
	private:
		double t[3]; // wspolrzedne x, y, z
		
	
	
	public:
		
		// Konstruktor (podajemy wspolrzedne jawnie)
		Vector(double x=0., double y=0., double z=0.);
		
		
		// Konstruktor (podajemy punkt poczatkowy i koncowy)
		Vector(const Point &P_start, const Point &P_end);
		
		
		// Konstruktor (podajemy punkt koncowy; punkt poczatkowy to (0,0,0) )
		Vector(const Point &P_end);
		
		
		// Destruktor
		~Vector();
		
		
		// Konstruktor kopiujacy
		Vector(const Vector &other);
		
		
		
		// Gettery
		
		// Pobranie i-tej wspolrzednej (i=0,1,2)
		double get_ith_coord(int i) const;
		
		
		// Pobranie wspolrzednej x
		double get_x() const;
		
		
		// Pobranie wspolrzednej y
		double get_y() const;
		
		
		// Pobranie wspolrzednej z
		double get_z() const;
		
		
		
		// Settery
		
		// Ustawienie i-tej wspolrzednej (i=0,1,2)
		void set_ith_coord(int i, double val);
		
		
		// Ustawienie wspolrzednej x
		void set_x(double x);
		
		
		// Ustawienie wspolrzednej y
		void set_y(double y);
		
		
		// Ustawienie wspolrzednej z
		void set_z(double z);
		
		
		// Ustawienie wspolrzednych
		void set(double x, double y, double z);
		
		
		
		// Dodawanie wektorow
		Vector operator + (const Vector &a) const;
		
		
		// Odejmowanie wektorow
		Vector operator - (const Vector &a) const;
		
		
		// Iloczyn wektorowy this x b
		Vector operator * (const Vector &b) const;
		
		
		// Iloczyn skalarny this oraz b
		double operator ^ (const Vector &b) const;
		
		
		friend std::ostream& operator << (std::ostream &out, const Vector &v);
			
};

#endif
