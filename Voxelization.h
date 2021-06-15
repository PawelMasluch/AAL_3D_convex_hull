#include "Point.h"

#ifndef ICLUDED_VOXELIZATION
#define ICLUDED_VOXELIZATION

std::set<Point_3D> Voxelize(std::set<Point_3D> points, double voxelSize) {
	std::set<Point_3D> result;
	for (std::set<Point_3D>::iterator it = points.begin(); it != points.end(); ++it) {
		double x = it->get_x();
		double y = it->get_y();
		double z = it->get_z();
		Point_3D point(voxelSize * floor(x / voxelSize) + voxelSize/2, voxelSize * floor(y / voxelSize) + voxelSize / 2, voxelSize * floor(z / voxelSize) + voxelSize / 2);
		result.insert(point);
	}
	return result;
}
#endif