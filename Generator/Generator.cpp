
#include "Generator.h"
#include "NoiseUtil.h"

#include <iostream>
#include <chrono>

static inline unsigned char clampc(double a) {
	unsigned char b;
	if (a > 255) {
		b = 255;
	} else if (a < 0) {
		b = 0;
	} else {
		b = (unsigned char)a;
	}
	return b;
}

namespace generator {
	namespace {
		OpenSimplexNoise* noiseGen;
		unsigned char* buff;
	}

	void init() {
		noiseGen = new OpenSimplexNoise();
	}

	static void generateGenericHeightmap() {
		buff = new unsigned char[WIDTH * HEIGHT];
		int r, c;
		double out;

		for (r = 0; r < HEIGHT; r++) {
			for (c = 0; c < WIDTH; c++) {
				out = noise::octaveEvalute(*noiseGen, c, r, 8) + 127; // 0 to 254
				buff[r * WIDTH + c] = clampc(out);
			}
		}
	}

	unsigned char getpx(int r, int c) {
		return buff[r * WIDTH + c];
	}

	int generate() {
		generateGenericHeightmap();
		std::cout << "Finished!!!" << std::endl;
		return 0;
	}


	void release() {
		delete noiseGen;
		delete buff;
	}
}

