#ifndef PLANE_H
#define PLANE_H


#include "Point.h"


// Przydatne definicje (plaszczyzna)
#define A t[0]
#define B t[1]
#define C t[2]
#define D t[3]




// Plaszczyzna w 3D: Ax + By + Cz + D = 0
class Plane{
	
	private:
		double t[3+1]; // A, B, C, D
		Point P[3]; // 3 punkty tworzace plaszczyzne
		
		int edge_number[3]; // numery krawedzi
		
		
		// Sprawdzamy, czy liczbe zmiennoprzecinkowa
		// mozemy uznac za zero
		static bool is_zero(double a);
		
			
	public:
		
		// Konstruktor
		Plane();
		
		
		// Destruktor
		~Plane();
		
		
		// Konstruktor kopiujacy
		Plane(const Plane &other);
		
		
		
		// Gettery
		
		// Pobranie i-tego identyfikatora krawedzi (i=0,1,2)
		int get_ith_edge_number(int i) const;
		
		
		// Pobranie i-tego punktu (i=0,1,2)
		Point get_ith_point(int i) const;
		
		
		// Pobranie i-tego wspolczynnika (i=0,1,2,3)
		double get_ith_coeff(int i) const;
		
		
		// Pobranie wspolczynnika A
		double get_A() const;
		
		
		// Pobranie wspolczynnika B
		double get_B() const;
		
		
		// Pobranie wspolczynnika C
		double get_C() const;
		
		
		// Pobranie wspolczynnika D
		double get_D() const;
		
		
		
		// Settery
		
		// Ustawienie i-tego identyfikatora krawedzi (i=0,1,2)
		void set_ith_edge_number(int i, int val);
		
		
		// Ustawienie i-tego punktu (i=0,1,2)
		void set_ith_point(int i, const Point &P);
		
		
		// Ustawienie i-tego wspolczynnika (i=0,1,2,3)
		void set_ith_coeff(int i, double val);
		
		
		// Ustawienie wspolczynnika A
		void set_A(double val);
		
		
		// Ustawienie wspolczynnika B
		void set_B(double val);
		
		
		// Ustawienie wspolczynnika C
		void set_C(double val);
		
		
		// Ustawienie wspolczynnika D
		void set_D(double val);
		
		
		
		// Tworzymy plaszczyzne z 3 niewspolliniowych (!) punktow
		static Plane create_plane(const Point &P1, const Point &P2, const Point &P3);
		
		
		// Zwracamy identyfikator strony punktu P wzgledem plaszczyzny pi:
		//	-1 - punkt P lezy po jednej stronie plaszczyzny pi
		//	0 - punkt P lezy na plaszczyznie pi
		//	1 - punkt P lezy po drugiej stronie plaszczyzny pi
		static int side(const Plane &pi, const Point &P);
		
		
		// Objetosc (ze znakiem) czworoscianu (podstawa pi, wierzcholek P)
		static double V(const Plane &pi, const Point &P);
		
		
		friend std::ostream& operator << (std::ostream &out, const Plane &pi);
		
};

#endif
