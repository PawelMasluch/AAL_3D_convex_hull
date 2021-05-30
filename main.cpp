#include "PointGeneration.h"
#include "Voxelization.h"
#include<iostream>
#include<math.h>



void VoxelizationExample() {
	int count = 2000;
	double size = 20;
	std::set<Point_3D> points = GeneratePointsCube(count, size);
	std::set<Point_3D> pointsVoxelized = Voxelize(points, 1);
	/*
	for (std::set<Point_3D>::iterator it = points.begin(); it != points.end(); ++it) {
		std::cout << it->get_x() << " " << it->get_y() << " " << it->get_z() << "\n";
	}
	std::cout << "***********************************************************\n";
	for (std::set<Point_3D>::iterator it = pointsVoxelized.begin(); it != pointsVoxelized.end(); ++it) {
		std::cout << it->get_x() << " " << it->get_y() << " " << it->get_z() << "\n";
	}
	*/
	std::cout << "Before: " << points.size() << " After: " << pointsVoxelized.size() << "\n";
}

int main() {
	VoxelizationExample();
	return 0;
}