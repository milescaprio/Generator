#include "VirtualTurtle.h"
#include <cmath>
#define PI 3.14159265

void VirtualTurtle::forward(float length) {	
	float x1 = x_;
	float y1 = y_;
	x_ += length * cos(angle_*PI/180);
	y_ += length * sin(angle_*PI/180);
	if (!pendown_) {
		return;
	}

	if ((int)angle_ % 90 == 0) {
		graphicsint bigger1;
		graphicsint bigger;
		bool xthing;
		if (abs(x_ - x1) > abs(y_ - y1)) {
			bigger1 = x1 < x_ ? x1 : x_;
			bigger = x1 < x_ ? x_ : x1;
			xthing = true;
		}
		else {
			bigger1 = y1 < y_ ? y1 : y_;
			bigger = y1 < y_ ? y_ : y1;
			xthing = false;
		}
		color_(r_, g_, b_);
		for (graphicsint i = bigger1; i <= (graphicsint)bigger; i += 1) {
			pixel_(xthing ? i : x_, xthing ? y_ : i);
		}
		return;
	}


	float bigger1;
	float bigger;
	float smaller1;
	float smaller;
	bool xthing;
	if (abs(x_ - x1) > abs(y_ - y1)) {
		bigger1 = x1 < x_ ? x1 : x_;
		bigger = x1 < x_ ? x_ : x1;
		smaller1 = x1 < x_ ? y1 : y_;
		smaller = x1 < x_ ? y_ : y1;
		xthing = true;
	}
	else {
		bigger1 = y1 < y_ ? y1 : y_;
		bigger = y1 < y_ ? y_ : y1;
		smaller1 = y1 < y_ ? x1 : x_;
		smaller = y1 < y_ ? x_ : x1;
		xthing = false;
	}
	float ratio = (smaller - smaller1) / (bigger - bigger1);
	color_(r_, g_, b_);
	for (graphicsint i = bigger1; i <= bigger; i += 1) { //consider optimizing the repetitive float cast
		auto debugvar = (graphicsint)(ratio * (i - bigger1));
		pixel_(xthing ? i : smaller1 + (graphicsint)(ratio * (i - bigger1)), xthing ? smaller1 + (graphicsint)(ratio * (i - bigger1)) : i);
	}
}

void VirtualTurtle::left(float angle) {
	angle_ += angle;
}

void VirtualTurtle::right(float angle) {
	angle_ -= angle;
}

void VirtualTurtle::tp(float x, float y) {
	x_ = x;
	y_ = y;
}

void VirtualTurtle::move(float x, float y)
{
	float x1 = x_;
	float y1 = y_;
	x_ = x;
	y_ = y;
	if (!pendown_) {
		return;
	}

	if (x1 == x_ || y1 == y_) {
		graphicsint bigger1;
		graphicsint bigger;
		bool xthing;
		if (abs(x_ - x1) > abs(y_ - y1)) {
			bigger1 = x1 < x_ ? x1 : x_;
			bigger = x1 < x_ ? x_ : x1;
			xthing = true;
		}
		else {
			bigger1 = y1 < y_ ? y1 : y_;
			bigger = y1 < y_ ? y_ : y1;
			xthing = false;
		}
		color_(r_, g_, b_);
		for (graphicsint i = bigger1; i <= (graphicsint)bigger; i += 1) {
			pixel_(xthing ? i : x_, xthing ? y_ : i);
		}
		return;
	}

	float bigger1;
	float bigger;
	float smaller1;
	float smaller;
	bool xthing;
	if (abs(x_ - x1) > abs(y_ - y1)) {
		bigger1 = x1 < x_ ? x1 : x_;
		bigger = x1 < x_ ? x_ : x1;
		smaller1 = x1 < x_ ? y1 : y_;
		smaller = x1 < x_ ? y_ : y1;
		xthing = true;
	}
	else {
		bigger1 = y1 < y_ ? y1 : y_;
		bigger = y1 < y_ ? y_ : y1;
		smaller1 = y1 < y_ ? x1 : x_;
		smaller = y1 < y_ ? x_ : x1;
		xthing = false;
	}
	float ratio = (smaller - smaller1) / (bigger - bigger1);
	color_(r_, g_, b_);
	for (graphicsint i = bigger1; i <= bigger; i += 1) { //consider optimizing the repetitive float cast
		auto debugvar = (graphicsint)(ratio * (i - bigger1));
		pixel_(xthing ? i : smaller1 + (graphicsint)(ratio * (i - bigger1)), xthing ? smaller1 + (graphicsint)(ratio * (i - bigger1)) : i);
	}
}

float VirtualTurtle::anglerange(float a) { //inefficient but whatever
	while (a < 0) {
		a += 360;
	}
	while (a >= 360) {
		a -= 360;
	}
	return a;
}
// aa < ab
bool VirtualTurtle::isAngleGreater(float aa, float ab) {
	float ad = anglerange(aa - ab);
	if (ad < 180) {
		return true;
	}
	return false;
}

bool VirtualTurtle::isAngleLess(float aa, float ab) {
	float ad = anglerange(aa - ab);
	if (ad > 180) {
		return true;
	}
	return false;
}

float VirtualTurtle::ucAngle(float x1, float y1, float x2, float y2) { //unit-circle format angle, undefined behavior for expected outputs of 0, 90, 180, and 270, as they aren't distinguishable inputs
	float ret = atan((y2 - y1) / (x2 - x1)) * (180.0 / PI);
	if (ret < 0) {
		ret += 180;
	}
	if (y2 < y1) {
		ret += 180;
	}
	return ret;
}

float VirtualTurtle::dist(float x1, float y1, float x2, float y2) {
	return sqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));
}

float VirtualTurtle::dist(float x1, float y1, float x2, float y2, float xm, float ym) { //multipliers for the sides, because we are measuring the oval like it's a circle
	return sqrt(((y2 - y1) * ym) * ((y2 - y1) * ym) + ((x2 - x1) * xm) * ((x2 - x1) * xm));
}

void VirtualTurtle::updateMesh(Mesh& m) {
	m.add(x_, y_);
}

void VirtualTurtle::followMesh(Mesh& m) {
	for (int i = 0; i < m.count(); i++) {
		move(m.point(i).x, m.point(i).y);
	}
}
