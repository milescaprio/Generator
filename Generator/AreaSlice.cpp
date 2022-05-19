#include "AreaSlice.h"
Pixels AreaSlice::pixels() {
	Pixels pixels;
	for (size_t i = 0; i < stack_.size(); i++) {
		for (P j = stack_[i].x1 + 0.5; j <= stack_[i].x2 + 0.5;  j++) {
		                                  /*implicitly casted, add 0.5 to make rounding fairer, TODO maybe make rounding fairer in other places*/  
			pixels.add(j, stack_[i].y);
		}
	}
	return pixels;
}