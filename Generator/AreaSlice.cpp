#include "AreaSlice.h"
Pixels AreaSlice::pixels() {
	Pixels pixels;
	for (size_t i = 0; i < stack_.size(); i++) {
		for (P j = stack_[i].x1; j <= stack_[i].x2; j++) {
			pixels.add(j, stack_[i].y);
		}
	}
	return pixels;
}

Pixel AreaSlice::readPixel() {
	if (nextstack_ >= stack_.size()) {
		nextstack_ = 0;
		return Pixel(-1, -1);
	}
	Pixel ret(stack_[nextstack_].x1 + nextpixel_, stack_[nextstack_].y);
	nextpixel_ += 1;
	if (nextpixel_ > stack_[nextstack_].x2 - stack_[nextstack_].x1) {
		nextpixel_ = 0;
		nextstack_++;
	}
	return ret;
}