#pragma once
#pragma inline_recursion(on)

typedef int P;
typedef unsigned char shade;

#include <GL/glut.h>
#include <iostream>
#include <random>
#include "Generator.h"
#include "Mesh.h"
#include "Pixels.h"
#include "AreaSlice.h"
#include "VirtualTurtle.h"

#define PI 3.14159265

#define STARTX 400
#define STARTY 400
#define WIDTH 750
#define HEIGHT 750
#define TOL 3.0

#define DEAD_R 198
#define DEAD_G 171
#define DEAD_B 114
#define LUSH_R 51
#define LUSH_G 68
#define LUSH_B 51
#define COLD_R 18
#define COLD_G 8
#define COLD_B 175
#define HOT_R 100
#define HOT_G 200
#define HOT_B 190