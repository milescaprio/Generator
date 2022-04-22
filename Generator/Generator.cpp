
#include "includes.h"
#include "OpenSimplex.h"

const int FART_SEED = 100;

namespace generator {
	namespace {
		OpenSimplexNoise* noiseGen;
	}

	void init() {
		noiseGen = new OpenSimplexNoise(FART_SEED);
	}

	int generate() {
		std::cout << noiseGen->Evaluate(10, 10) << std::endl;
		return 0;
	}

	void release() {
		delete noiseGen;
	}
}

