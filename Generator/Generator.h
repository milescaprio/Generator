
#pragma once
#include "includes.h"

const int SEED = 100;
const int WIDTH = 256;
const int HEIGHT = 256;

const char THRESHOLD = -24;

namespace generator {
	void init();
	void release();

	int generate();
	//GLuint loadTexture();

	unsigned char getpx(int r, int c);
}
