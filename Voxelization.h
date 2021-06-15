#include "Point.h"

#ifndef ICLUDED_VOXELIZATION
#define ICLUDED_VOXELIZATION

std::set<Point> Voxelize(std::vector<Point> points, double voxelSize) {
	std::set<Point> result;
	for (std::vector<Point>::iterator it = points.begin(); it != points.end(); ++it) {
		double x = it->get_x();
		double y = it->get_y();
		double z = it->get_z();
		Point point(voxelSize * floor(x / voxelSize) + voxelSize/2, voxelSize * floor(y / voxelSize) + voxelSize / 2, voxelSize * floor(z / voxelSize) + voxelSize / 2);
		result.insert(point);
	}
	return result;
}
#endif