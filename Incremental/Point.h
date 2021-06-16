#include<iostream>
#include<vector>
#include<fstream>


#ifndef POINT_H
#define POINT_H


// Przydatne definicje (caly program)
#define REP(i,a,b) for(int i=a; i<=b; ++i)


// Przydatne definicje (punkt, wektor)
#define X t[0]
#define Y t[1]
#define Z t[2]


// Punkt 3D: P(x,y,z)
class Point{
	
	private:
		double t[3]; // wspolrzedne x, y, z
		
		
	
	public:
		
		// Konstruktor
		Point(double x=0., double y=0., double z=0.);
		
		
		// Destruktor
		~Point();
		
		
		// Konstruktor kopiujacy
		Point(const Point &other);
		
		
		
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
		
		
		// Dodawanie punktow
		Point operator + (const Point &P) const;
		
		
		// Odejmowanie punktow
		Point operator - (const Point &P) const;
		
		
		// Zapis punktu do pliku
		friend std::ostream& operator << (std::ostream &out, const Point &P);
		friend bool operator< (Point const& a, Point const& b);
};

#endif
