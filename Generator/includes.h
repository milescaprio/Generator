#pragma once
#pragma inline_recursion(on)

#include <GL/glut.h>
#include <iostream>
#include <random>
#include "Generator.h"
#include "Mesh.h"
#include "VirtualTurtle.h"

#define PI 3.14159265

#define STARTX 500
#define STARTY 500
#define SEED 100
#define WIDTH 1000
#define HEIGHT 1000

#define DEAD_R 198
#define DEAD_G 171
#define DEAD_B 114
#define LUSH_R 51
#define LUSH_G 68
#define LUSH_B 51
#define MOISTURERGB(val) ubmap((val), DEAD_R, LUSH_R), ubmap((val), DEAD_G, LUSH_G), ubmap((val), DEAD_B, LUSH_B)
/*\/   Opposite of moisture, just reversed map   \/*/
#define DROUGHTRGB(val) ubmap((val), LUSH_R, DEAD_R), ubmap((val), LUSH_G, DEAD_G), ubmap((val), LUSH_B, DEAD_B)