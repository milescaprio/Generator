#pragma once

#include "OpenSimplex.h"

namespace noise {
	double octaveEvalute(const OpenSimplexNoise& noiseGen, double x, double y, int octaves) {
		double out = 0;
		double mult = 1;
		int i;

		for (i = 0; i < octaves; i++) {
			out += noiseGen.Evaluate(x * mult, y * mult) / mult;
			mult *= 0.5;
		}

		return out;
	}
}
