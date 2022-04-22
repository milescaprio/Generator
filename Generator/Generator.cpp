
#include "includes.h"
#include "NoiseUtil.h"

const int SEED = 100;
const int WIDTH = 256;
const int HEIGHT = 256;

const char THRESHOLD = -24;

#include <iostream>
#include <chrono>

static inline char clampc(double a) {
	char b;
	if (a > 127.0) {
		b = 127;
	} else if (a < -127.0) {
		b = -127;
	} else {
		b = (char)a;
	}
	return b;
}

namespace generator {
	namespace {
		OpenSimplexNoise* noiseGen;
		char* buff;
	}

	void init() {
		noiseGen = new OpenSimplexNoise();
	}

	static void generateGenericHeightmap() {
		buff = new char[WIDTH * HEIGHT];
		int i, j;
		double out;

		for (i = 0; i < WIDTH; i++) {
			for (j = 0; j < HEIGHT; j++) {
				out = noise::octaveEvalute(*noiseGen, i, j, 8); // -127 to 127
				buff[i * j] = clampc(out);
			}
		}
	}

	int generate() {
		return 0;
	}

	void release() {
		delete noiseGen;
		delete buff;
	}
}

