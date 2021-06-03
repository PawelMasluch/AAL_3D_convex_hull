#include "Edge.h"


#define REP(i,a,b) for(int i=a; i<=b; ++i)


// Konstruktor
Edge::Edge(){
	REP(i,0,2-1){
		(*this).point_number[i] = (*this).face_number[i] = -1; // UNDEF
	}
}


// Destruktor
Edge::~Edge() {}


// Konstruktor kopiujacy
Edge::Edge(const Edge &other){
	REP(i,0,2-1){
		(*this).point_number[i] = other.point_number[i];
		(*this).face_number[i] = other.face_number[i];
		
	}
}



// Gettery

// Pobranie identyfikatora i-tego konca krawedzi (i=0,1) 
int Edge::get_ith_point_number(int i) const{
	return (*this).point_number[i];
}


// Pobranie identyfikatora i-tej sciany (i=0,1) 
int Edge::get_ith_face_number(int i) const{
	return (*this).face_number[i];
}



// Settery 

// Ustawienie identyfikatora i-tego kranca krawedzi (i=0,1) 
void Edge::set_ith_point_number(int i, int val){
	(*this).point_number[i] = val;
}


// Ustawienie identyfikatora i-tej sciany (i=0,1) 
void Edge::set_ith_face_number(int i, int val){
	(*this).face_number[i] = val;
}
