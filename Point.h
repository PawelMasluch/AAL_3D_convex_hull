#ifndef ICLUDED_POINT
#define ICLUDED_POINT


#define DIM 3
#define X t[0]
#define Y t[1]
#define Z t[2]
#define REP(i,a,b) for(int i=a; i<=b; ++i)
class Point_3D {

private:
	double t[DIM];



public:

	// Konstruktor
	Point_3D(double x = 0., double y = 0., double z = 0.) {
		(*this).X = x;
		(*this).Y = y;
		(*this).Z = z;
	}


	// Destruktor
	~Point_3D() {}



	// Gettery

	// Ustawienie i-tej wspolrzednej (i=0,1,2)
	double get_ith_coord(int i) {
		return (*this).t[i];
	}


	// Pobranie wspolrzednej x
	double get_x() const {
		return (*this).X;
	}


	// Pobranie wspolrzednej y
	double get_y() const {
		return (*this).Y;
	}


	// Pobranie wspolrzednej z
	double get_z() const {
		return (*this).Z;
	}



	// Settery

	// Ustawienie i-tej wspolrzednej (i=0,1,2)
	void set_ith_coord(int i, double val) {
		(*this).t[i] = val;
	}


	// Ustawienie wspolrzednej x
	void set_x(double x) {
		(*this).X = x;
	}


	// Ustawienie wspolrzednej y
	void set_y(double y) {
		(*this).Y = y;
	}


	// Ustawienie wspolrzednej z
	void set_z(double z) {
		(*this).Z = z;
	}


	// Ustawienie wspolrzednych
	void set(double x, double y, double z) {
		(*this).X = x;
		(*this).Y = y;
		(*this).Z = z;
	}


	// Dodawanie punktow
	Point_3D operator + (Point_3D& P) {
		Point_3D result;

		REP(i, 0, DIM - 1) {
			result.set_ith_coord(i, (*this).get_ith_coord(i) + P.get_ith_coord(i));
		}

		return result;
	}


	// Odejmowanie punktow
	Point_3D operator - (Point_3D& P) {
		Point_3D result;
		REP(i, 0, DIM - 1) {
			result.set_ith_coord(i, (*this).get_ith_coord(i) - P.get_ith_coord(i));
		}

		return result;
	}

	friend bool operator< (Point_3D const& a, Point_3D const& b) {
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

};

#endif