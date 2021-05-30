/*

Algorytm naiwny do znajdowania
otoczki wypuklej punktow
w przestrzeni trojwymiarowej (3D).

Zalozenie: kazda trojka punktow nie jest wspolliniowa
		   oraz kazda czworka punktow nie jest wspolplaszczyznowa
		   (w razie potrzeby, uwzglednic to w rownaniu plaszczyzny i wlasciwym algorytmie)!

*/

#include<iostream>
#include<vector>
#include<fstream>


using namespace std;


const int DIM = 3; // liczba wymiarow punktow

const double eps = 1e-9; // dokladnosc


// Przydatne definicje (caly program)
#define REP(i,a,b) for(int i=a; i<=b; ++i)


// Przydatne definicje (punkt, wektor)
#define X t[0]
#define Y t[1]
#define Z t[2]




// Punkt 3D: A(x,y,z)
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
	double get_x() {
		return (*this).X;
	}


	// Pobranie wspolrzednej y
	double get_y() {
		return (*this).Y;
	}


	// Pobranie wspolrzednej z
	double get_z() {
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


	friend ofstream& operator << (ofstream& out, Point_3D& P) {
		out << P.X << " " << P.Y << " " << P.Z << endl;
	}
};




// Wektor 3D: v = [x, y, z]
class Vector_3D {

private:
	int t[DIM];



public:

	// Konstruktor (podajemy wspolrzedne jawnie)
	Vector_3D(double x = 0., double y = 0., double z = 0.) {
		(*this).X = x;
		(*this).Y = y;
		(*this).Z = z;
	}


	// Konstruktor (podajemy punkt poczatkowy i koncowy)
	Vector_3D(Point_3D& P_start, Point_3D& P_end) {

		Point_3D P = P_end - P_start;

		REP(i, 0, DIM - 1) {
			(*this).t[i] = P.get_ith_coord(i);
		}
	}


	// Konstruktor (podajemy punkt koncowy; punkt poczatkowy to (0,0,0) )
	Vector_3D(Point_3D& P_end) {

		Point_3D P_start(0., 0., 0.);
		/*Point_3D P = P_end - P_start;

		REP(i,0,DIM-1){
			(*this).t[i] = P.get_ith_coord(i);
		}*/
		Vector_3D(P_start, P_end);
	}


	// Destruktor
	~Vector_3D() {}



	// Gettery

	// Ustawienie i-tej wspolrzednej (i=0,1,2)
	double get_ith_coord(int i) {
		return (*this).t[i];
	}


	// Pobranie wspolrzednej x
	double get_x() {
		return (*this).X;
	}


	// Pobranie wspolrzednej y
	double get_y() {
		return (*this).Y;
	}


	// Pobranie wspolrzednej z
	double get_z() {
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



	// Dodawanie wektorow
	Vector_3D operator + (Vector_3D& a) {
		Vector_3D result;

		REP(i, 0, DIM - 1) {
			result.set_ith_coord(i, (*this).get_ith_coord(i) + a.get_ith_coord(i));
		}

		return result;
	}


	// Odejmowanie wektorow
	Vector_3D operator - (Vector_3D& a) {
		Vector_3D result;

		REP(i, 0, DIM - 1) {
			result.set_ith_coord(i, (*this).get_ith_coord(i) - a.get_ith_coord(i));
		}

		return result;
	}


	// Iloczyn wektorowy this x b
	Vector_3D operator * /*cross_product*/(/*Vector_3D &a,*/ Vector_3D b) {
		double x = (*this).get_y() * b.get_z() - (*this).get_z() * b.get_y();
		double y = (*this).get_z() * b.get_x() - (*this).get_x() * b.get_z();
		double z = (*this).get_x() * b.get_y() - (*this).get_y() * b.get_x();

		Vector_3D result(x, y, z);

		return result;
	}

};




// Przydatne definicje (plaszczyzna)
#define A t[0]
#define B t[1]
#define C t[2]
#define D t[3]




// Plaszczyzna w 3D: Ax + By + Cz + D = 0
class Plane {

private:
	double t[DIM + 1];
	Point_3D P[DIM];


	// Sprawdzamy, czy liczbe zmiennoprzecinkowa
	// mozemy uznac za zero
	static bool is_zero(double a) {
		return a < eps&& a>-eps; // |a| < eps
	}


public:

	// Konstruktor
	Plane() {

		REP(i, 0, DIM) {
			(*this).t[i] = 0.;
		}

		REP(i, 0, DIM - 1) {
			P[i].set(0., 0., 0.);
		}
	}


	// Destruktor
	~Plane() {}



	// Gettery

	// Pobranie i-tego punktu (i=0,1,2)
	Point_3D get_ith_point(int i) {
		return (*this).P[i];
	}


	// Pobranie i-tego wspolczynnika (i=0,1,2,3)
	double get_ith_coord(int i) {
		return (*this).t[i];
	}


	// Pobranie wspolczynnika A
	double get_A() {
		return (*this).A;
	}


	// Pobranie wspolczynnika B
	double get_B() {
		return (*this).B;
	}


	// Pobranie wspolczynnika C
	double get_C() {
		return (*this).C;
	}


	// Pobranie wspolczynnika D
	double get_D() {
		return (*this).D;
	}



	// Settery

	// Ustawienie i-tego punktu (i=0,1,2)
	void set_ith_point(int i, Point_3D& P) {
		(*this).P[i] = P;
	}


	// Ustawienie i-tego wspolczynnika (i=0,1,2,3)
	double set_ith_coord(int i, double val) {
		(*this).t[i] = val;
	}


	// Ustawienie wspolczynnika A
	double set_A(double val) {
		(*this).A = val;
	}


	// Ustawienie wspolczynnika B
	double set_B(double val) {
		(*this).B = val;
	}


	// Ustawienie wspolczynnika C
	double set_C(double val) {
		(*this).C = val;
	}


	// Ustawienie wspolczynnika D
	double set_D(double val) {
		(*this).D = val;
	}



	// Tworzymy plaszczyzne z 3 niewspolliniowych (!) punktow
	Plane create_plane(Point_3D& P1, Point_3D& P2, Point_3D& P3) {

		Vector_3D a(P1), b(P2), c(P3);
		Vector_3D n = (b - a) * (c - a); // wektor wspolczynnikow A,B,C plaszczyzny (odpowiednio) i normalny zarazem

		Plane result;

		result.set_ith_point(0, P1);
		result.set_ith_point(1, P2);
		result.set_ith_point(2, P3);


		REP(i, 0, DIM - 1) {
			result.set_ith_coord(i, n.get_ith_coord(i));
		}

		result.set_D(-((*this).A * P1.get_x() + (*this).B * P1.get_y() + (*this).C * P1.get_z()));

		(*this) = result;

		return *this;
	}


	/* Zwracamy identyfikator strony punktu P wzgledem plaszczyzny pi:
		-1 - punkt P lezy po jednej stronie plaszczyzny pi
		0 - punkt P lezy na plaszczyznie pi
		1 - punkt P lezy po drugiej stronie plaszczyzny pi
	*/
	static int side(Plane& pi, Point_3D& P) {
		double sum = 0.;

		REP(i, 0, DIM - 1) {
			sum += pi.get_ith_coord(i) * P.get_ith_coord(i);
		}
		sum += pi.get_D();

		if (is_zero(sum)) {
			return 0;
		}

		if (sum < 0.) {
			return -1;
		}

		return 1;
	}


	friend ofstream& operator << (ofstream& out, Plane& pi) {

		REP(i, 0, DIM - 1) {
			REP(j, 0, DIM - 1) {
				out << pi.get_ith_point(i).get_ith_coord(j) << " ";
			}
			out << endl;
		}
	}

};




const int MAX_N = 300; // maksymalna liczba punktow


int n;
Point_3D P[MAX_N];
vector <Plane> convex_hull;


void read_data() {

	ifstream file_in("in.txt");

	file_in >> n;

	double x, y, z;
	REP(i, 0, n - 1) {
		file_in >> x >> y >> z;
		P[i].set(x, y, z);
	}

	file_in.close();
}


void compute() {

	Plane pi;

	int side1 = 0, side2 = 0;

	// Kazda trojka punktow
	REP(i, 0, n - 1) {
		REP(j, i + 1, n - 1) {
			REP(k, j + 1, n - 1) {

				pi.create_plane(P[i], P[j], P[k]);

				REP(l, 0, n - 1) {
					if (l != i && l != j && l != k) {

						if (Plane::side(pi, P[l]) == -1) {
							++side1;
						}
						else {
							if (Plane::side(pi, P[l]) == 1) {
								++side2;
							}
						}
					}
				}

				if (side1 == 0 || side2 == 0) {
					convex_hull.push_back(pi);
				}

				side1 = side2 = 0;
			}
		}
	}

}


void save_result() {

	ofstream file_out("out.txt");

	int m = convex_hull.size(); // liczba scian otoczki wypuklej
	file_out << m << endl;

	REP(i, 0, m - 1) {
		file_out << convex_hull[i] << endl;
	}

	file_out.close();
}


void solve() {

	read_data();
	compute();
	save_result();
}


int main() {

	solve();
	return 0;
}