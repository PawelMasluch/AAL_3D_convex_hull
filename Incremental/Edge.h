#ifndef EDGE_H
#define EDGE_H


#define REP(i,a,b) for(int i=a; i<=b; ++i)


class Edge{
	
	private:
		int point_number[2]; // numery punktow krancowych (oczywiscie, krawedz ma 2 konce)
		int face_number[2]; // numery scian skojarzonych z krawedzia (oczywiscie, krawedz ma 2 skojarzone sciany)
	
	
	public:
		
		// Konstruktor
		Edge();
		
		
		// Destruktor
		~Edge();
		
		
		// Konstruktor kopiujacy
		Edge(const Edge &other);
		
		
		
		// Gettery
		
		// Pobranie identyfikatora i-tego konca krawedzi (i=0,1) 
		int get_ith_point_number(int i) const;
		
		
		// Pobranie identyfikatora i-tej sciany (i=0,1) 
		int get_ith_face_number(int i) const;
		
		
		
		// Settery 
		
		// Ustawienie identyfikatora i-tego kranca krawedzi (i=0,1) 
		void set_ith_point_number(int i, int val);
		
		
		// Ustawienie identyfikatora i-tej sciany (i=0,1) 
		void set_ith_face_number(int i, int val);
};

#endif
