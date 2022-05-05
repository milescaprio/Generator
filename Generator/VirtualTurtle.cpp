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

