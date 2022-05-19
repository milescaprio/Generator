
#pragma once
#include "includes.h"
class OpenSimplexNoise;
const char THRESHOLD = -24;

class Generator {
private:
	const float scale = 0.6;
	OpenSimplexNoise* noiseGen;
	unsigned char* buff = nullptr;
	size_t w_ = 0;
	size_t h_ = 0;
	void generateGenericHeightmap(size_t w, size_t h);

public:
	Generator();
	Generator(int64_t seed);
	~Generator();

	unsigned char getpx(int r, int c);

	int generate(size_t w, size_t h);
};

/*namespace generator {
	void init();
	void release();

	int generate();
	//GLuint loadTexture();

	unsigned char getpx(int r, int c);
}*/
