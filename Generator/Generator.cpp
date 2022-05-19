
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

void Generator::generateGenericHeightmap(size_t w, size_t h) {
	w_ = w;
	h_ = h;
	if (buff) {
		delete buff;
	}
	buff = new unsigned char[w_ * h_];
	int r, c;
	double out;

	for (r = 0; r < h_; r++) {
		for (c = 0; c < w_; c++) {
			out = noise::octaveEvalute(*noiseGen, c * scale, r * scale, 8) + 127; // 0 to 254
			buff[r * w_ + c] = clampc(out);
		}
	}
}

Generator::Generator() {
	noiseGen = new OpenSimplexNoise();
}
Generator::Generator(int64_t seed) {
	noiseGen = new OpenSimplexNoise(seed);
}
Generator::~Generator() {
	delete noiseGen;
	delete buff;
}

unsigned char Generator::getpx(int r, int c) {
	return buff[r * w_ + c];
}

int Generator::generate(size_t w, size_t h) {
	generateGenericHeightmap(w, h);
	return 0;
}

