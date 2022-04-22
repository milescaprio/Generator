#pragma once

#include "NoiseGenerator.h"

class Generator
{
public:
	explicit Generator(NoiseGenerator generator): generator(generator) {}

	void generate();
	void applyVertices();

private:
	NoiseGenerator generator;
};

