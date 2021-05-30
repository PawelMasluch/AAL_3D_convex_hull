#include <vector>
#include <iostream>
#include <random>
#include <math.h>   
#include <set>
#include "Point.h"

#ifndef ICLUDED_POINT_GENEARTION
#define ICLUDED_POINT_GENEARTION



std::set<Point_3D> GeneratePointsCube(int count, double size) {
	std::set<Point_3D> result;
	std::uniform_real_distribution<double> uniform(0, size);
	std::default_random_engine re;
	for (int i = 0; i < count; i++) {
		result.insert(Point_3D(uniform(re), uniform(re), uniform(re)));
	}
	return result;
}

std::set<Point_3D> GeneratePointsBall(int count, double size) {
	std::set<Point_3D> result;
	std::uniform_real_distribution<double> uniform(-size, size);
	std::default_random_engine re;
	for (int i = 0; i < count;) {
		double x = uniform(re);
		double y = uniform(re);
		double z = uniform(re);
		if (std::pow(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2), 0.5) < size) {
			result.insert(Point_3D(x, y, z));
			i++;
		}
	}
	return result;
}

std::set<Point_3D> GeneratePointsSphere(int count, double size) {
	double pi = 3.141592;
	std::set<Point_3D> result;
	std::uniform_real_distribution<double> radiusDistribution(size, size*1.05);
	std::uniform_real_distribution<double> inclinationDistribution(0, pi);
	std::uniform_real_distribution<double> azimuthDistribution(0, 2*pi);
	std::default_random_engine re;
	for (int i = 0; i < count; i++) {
		double r = radiusDistribution(re);
		double inclination = inclinationDistribution(re);
		double azimuth = azimuthDistribution(re);
		result.insert(Point_3D(r * std::cos(azimuth) * std::sin(inclination), r * std::sin(azimuth) * std::sin(inclination), r * std::cos(inclination)));
	}
	return result;
}

#endif