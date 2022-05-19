#include "Mesh.h"

float mapx(float x1, float y1, float x2, float y2, float y) {
	return x1 + (x2 - x1) / (y2 - y1) * (y - y1);
}

float mapy(float x1, float y1, float x2, float y2, float x) {
	return y1 + (y2 - y1) / (x2 - x1) * (x - x1);
}

bool isWithin(float n, float a, float b) {
	return (a <= n && n <= b) || (a >= n && n >= b);
}

void Mesh::rotate(float midx, float midy, float ang) {
	for (size_t i = 0; i < mesh_.size(); i++) {
		Point& p = mesh_[i];
		float r = VirtualTurtle::dist(midx, midy, p.x, p.y);
		float theta = VirtualTurtle::ucAngle(midx, midy, p.x, p.y);
		theta += ang;
		std::cout << p.x << " " << p.y << " " << r << " " << theta << " ";
		p.x = midx + r * cos(theta * PI / 180);
		p.y = midy + r * sin(theta * PI / 180);
		std::cout << p.x << " " << p.y << "\n";
	}
}

bool Mesh::contains(float x, float y) {
	int counter = 0;
	for (size_t i = 1; i < mesh_.size(); i++) {
		if (mesh_[i-1].y <= y && mesh_[i].y >= y) { //is within y range
			if ( x < mapx(mesh_[i - 1].x, mesh_[i - 1].y, mesh_[i].x, mesh_[i].y, y)) { // checks if x is less than mid x
				counter++;
			}
		}
	}
	return counter % 2;
}

AreaSlice Mesh::containment() {
	AreaSlice ret;
	float maxy = -std::numeric_limits<float>::infinity();
	float miny = std::numeric_limits<float>::infinity();
	for (size_t i = 0; i < mesh_.size(); i++) { //grab min/max 
		if (mesh_[i].y > maxy) {
			maxy = mesh_[i].y;
		}
		if (mesh_[i].y < miny) {
			miny = mesh_[i].y;
		}
	}
	/*
	does this function work
	should i include the last pixel?
	should i add 0.5 to the pixels?
	0.5 might center the pixels better
	*/
	std::vector<float> crosspoints;
	for (P y = miny; y <= maxy; y++) { //for each pixel-y in the stack range
		crosspoints = {};
		for (size_t i = 1; i < mesh_.size(); i++) { //for each mesh point
			if (isWithin((float)y + 0.5, mesh_[i - 1].y, mesh_[i].y)) {//if the pixel-y fits in the mesh line
				crosspoints.push_back(mapx(mesh_[i - 1].x, mesh_[i - 1].y, mesh_[i].x, mesh_[i].y, (float)y + 0.5/*Fairer pixel distribution*/));
			}
		}
		std::sort(crosspoints.begin(), crosspoints.end());
		if (crosspoints.size() % 2) {
			throw "Odd number of mesh points";
		}
		for (size_t i = 0; i < crosspoints.size(); i+=2) {
			ret.add(crosspoints[i], crosspoints[i + 1], y);
		}
	}
	return ret;
}