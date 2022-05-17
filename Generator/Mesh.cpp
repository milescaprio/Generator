#include "Mesh.h"
void Mesh::rotate(float midx, float midy, float ang) {
	for (int i = 0; i < mesh_.size(); i++) {
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