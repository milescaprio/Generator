
#include "includes.h"

namespace generator {
	namespace {
		OpenSimplexNoise* noiseGen;
	}

	void init() {
		noiseGen = new OpenSimplexNoise();
	}

	int generate() {

	}

	void release() {
		delete noiseGen;
	}
}

