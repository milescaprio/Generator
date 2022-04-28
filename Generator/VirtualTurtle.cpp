#include "VirtualTurtle.h"
#include <cmath>

void VirtualTurtle::forward(float length) {	
	float x1 = x_;
	float y1 = y_;
	x_ += length * cos(angle_);
	y_ += length * sin(angle_);
	if (!pendown_) {
		return;
	}
	graphicsint bigger1;
	graphicsint bigger;
	graphicsint smaller1;
	graphicsint smaller;
	if (x_ - x1 > y_ - y1) {
		bigger1 = x1;
		bigger = x_;
		smaller1 = y1;
		smaller = y_;
	}
	else {
		bigger1 = y1;
		bigger = y_;
		smaller1 = x1;
		smaller = x_;
	}
	float ratio = ((float)smaller - (float)smaller1) / ((float)bigger - (float)bigger1);
	color_(r_, g_, b_);
	for (graphicsint i = bigger1; i <= bigger; i++) {
		pixel_(i, smaller1 + (graphicsint)(ratio * (i - bigger1)));
	}
}

void VirtualTurtle::left(float angle) {
	angle_ += angle;
}

void VirtualTurtle::right(float angle) {
	angle -= angle;
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
	y_ = x;
	if (!pendown_) {
		return;
	}
	graphicsint bigger1;
	graphicsint bigger;
	graphicsint smaller1;
	graphicsint smaller;
	if (x_ - x1 > y_ - y1) {
		bigger1 = x1;
		bigger = x_;
		smaller1 = y1;
		smaller = y_;
	}
	else {
		bigger1 = y1;
		bigger = y_;
		smaller1 = x1;
		smaller = x_;
	}
	float ratio = ((float)smaller - (float)smaller1) / ((float)bigger - (float)bigger1);
	color_(r_, g_, b_);
	for (graphicsint i = bigger1; i <= bigger; i++) {
		pixel_(i, smaller1 + (graphicsint)(ratio * (i - bigger1)));
	}
}

