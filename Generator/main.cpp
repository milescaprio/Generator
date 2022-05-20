#include "includes.h"
unsigned int SEED = 0;
void islandMain(AreaSlice& island);
Mesh cutIsland();

Generator biome(SEED);
Generator elevation(SEED + 1);
Generator rockiness1(SEED + 2);
Generator rockiness2(SEED + 3);
std::normal_distribution<double> normal(0.0, 1.0);
std::uniform_real_distribution<float> uniformSize(50.0, 250.0);
std::uniform_real_distribution<float> uniformDegree(0.0, 360.0);
std::uniform_real_distribution<float> uniform01(0.0, 1.0);
std::uniform_real_distribution<float> uniformShade(0.0, 255.0);

void init(int *argc, char** argv)
{
    biome.generate(WIDTH, HEIGHT);
    elevation.generate(WIDTH, HEIGHT);
    rockiness1.generate(WIDTH, HEIGHT);
    rockiness2.generate(WIDTH, HEIGHT);
    //text = generator::loadTexture();
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Island");
    glClearColor(0, 0.0, 1.0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);   
}

inline shade ubmap(shade val, shade first, shade last) {
    return (val * ((unsigned int)last - (unsigned int)first) / 255 + first); //converts funnily to unsigned int to allow multiplication and division of bigger numbers
}

inline shade moisturered(shade val) {
    return ubmap(val, DEAD_R, LUSH_R);
}

inline shade moisturegreen(shade val) {
    return ubmap(val, DEAD_G, LUSH_G);
}

inline shade moistureblue(shade val) {
    return ubmap(val, DEAD_B, LUSH_B);
}

inline shade waterred(shade val) {
    return ubmap(val, COLD_R, HOT_R);
}

inline shade watergreen(shade val) {
    return ubmap(val, COLD_G, HOT_G);
}

inline shade waterblue(shade val) {
    return ubmap(val, COLD_B, HOT_B);
}

inline shade elevationmoistureshade(shade val, shade elevation) {
    if (elevation > 127) {
        return 255 - ((unsigned int)(255 - val) * (127 - (elevation - 127)) / 128);
    }
    else {
        return ((unsigned int)(val) * (elevation) / 128);
    }
}
inline shade elevationwatershade(shade val, shade elevation) {
    return ((unsigned int)(val) * elevation / 255);
}
void setPixel(GLint x, GLint y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void setColor(unsigned char r, unsigned char g, unsigned char b) {
    glColor3ub(r, g, b);
}

void islandPixel(GLint r, GLint c) {
    const int seg = 16;
    shade b = biome.getpx(r, c);
    shade e = elevation.getpx(r, c);
    /*
    unsigned char red = elevationmoistureshade(moisturered(b), e / seg * seg);
    unsigned char green = elevationmoistureshade(moisturegreen(b), e / seg * seg);
    unsigned char blue = elevationmoistureshade(moistureblue(b), e / seg * seg);
    */
    unsigned char red = moisturered(b);
    unsigned char green = moisturegreen(b);
    unsigned char blue = moistureblue(b);
    setColor(red, green, blue);
    setPixel(c, HEIGHT - r);
}

void seaPixel(GLint r, GLint c) {
    const int seg = 16;
    shade b = biome.getpx(r, c);
    shade e = elevation.getpx(r, c);
    unsigned char red = elevationwatershade(waterred(b), e / seg * seg);
    unsigned char green = elevationwatershade(watergreen(b), e / seg * seg);
    unsigned char blue = elevationwatershade(waterblue(b), e / seg * seg);
    setColor(red, green, blue);
    setPixel(c, HEIGHT - r);
}

void rock(GLint r, GLint c, std::default_random_engine& generator) {
    if (uniform01(generator) < 0.18 && 
        uniformShade(generator) < rockiness1.getpx(r, c) && uniformShade(generator) < rockiness1.getpx(r, c) && uniformShade(generator) < rockiness1.getpx(r, c) &&
        uniformShade(generator) < rockiness2.getpx(r, c) && uniformShade(generator) < rockiness2.getpx(r, c) && uniformShade(generator) < rockiness2.getpx(r, c)) {
        shade s = 127 + normal(generator)*2;
        setColor(s, s, s);
        if (uniform01(generator) > 0.5) {
            setPixel(c, HEIGHT - r);
            setPixel(c, HEIGHT - r + 1);
            setPixel(c + 1, HEIGHT - r);
            setPixel(c + 1, HEIGHT - r + 1);
        }
        else {
            setPixel(c, HEIGHT - r + 1);
            setPixel(c, HEIGHT - r + 2);
            setPixel(c + 1, HEIGHT - r);
            setPixel(c + 1, HEIGHT - r + 1);
            setPixel(c + 1, HEIGHT - r + 2);
            setPixel(c + 1, HEIGHT - r + 3);
            setPixel(c + 2, HEIGHT - r);
            setPixel(c + 2, HEIGHT - r + 1);
            setPixel(c + 2, HEIGHT - r + 2);
            setPixel(c + 2, HEIGHT - r + 3);
            setPixel(c + 3, HEIGHT - r + 1);
            setPixel(c + 3, HEIGHT - r + 2);
        }
    }
}

void snow(GLint r, GLint c, std::default_random_engine& generator) {
    if (uniformShade(generator) < elevation.getpx(r, c) && 200 < elevation.getpx(r, c) &&
        uniformShade(generator) < biome.getpx(r, c) && 145 < biome.getpx(r, c)) {
        /*uniformShade(generator) < elevation.getpx(r, c) && uniformShade(generator) < elevation.getpx(r, c) && uniformShade(generator) < elevation.getpx(r, c) &&
        uniformShade(generator) < biome.getpx(r, c) && uniformShade(generator) < biome.getpx(r, c) && uniformShade(generator) < biome.getpx(r, c) {*/
        setColor(236, 255, 253);
        setPixel(c, HEIGHT - r);
    }
}

void tree(GLint r, GLint c, std::default_random_engine& generator) {
    if (uniform01(generator) < 0.05 &&
        uniformShade(generator) < biome.getpx(r, c) && 180 < biome.getpx(r, c)) {
        /*uniformShade(generator) < elevation.getpx(r, c) && uniformShade(generator) < elevation.getpx(r, c) && uniformShade(generator) < elevation.getpx(r, c) &&
        uniformShade(generator) < biome.getpx(r, c) && uniformShade(generator) < biome.getpx(r, c) && uniformShade(generator) < biome.getpx(r, c) {*/
        setColor(105, 122, 80);
        setPixel(c, HEIGHT - r);
        setPixel(c + 1, HEIGHT - r);
        setPixel(c + 1, HEIGHT - r + 1);
        setPixel(c + 2, HEIGHT - r);
        setPixel(c + 2, HEIGHT - r + 1);
        setPixel(c + 2, HEIGHT - r + 2);
        setPixel(c + 3, HEIGHT - r);
        setPixel(c + 3, HEIGHT - r + 1);
        setPixel(c + 4, HEIGHT - r);
    }
}

void inline displayStart() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(1.0);
}

void inline displayEnd() {
    glutSwapBuffers();
}

void display()
{
    displayStart();
    Mesh m = cutIsland();

    AreaSlice a = m.containment();
    /*for (Pixel p = a.readPixel(); p.x != -1; p = a.readPixel()) {
        setColor(251, 145, 155);
        setPixel(p.y, HEIGHT - p.x);
    }*/
    //Pixels island = a.pixels(); //very memory consuming, better off with an iterator instead of a full cache
    islandMain(a);
    displayEnd();
}

void onMouseButton(int button, int state, int, int)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        SEED++;
    }
#ifdef REDOMAPS
    biome.changeSeed(SEED);
    elevation.changeSeed(SEED + 1);
    rockiness1.changeSeed(SEED + 2);
    rockiness2.changeSeed(SEED + 3);
    biome.generate(WIDTH, HEIGHT);
    elevation.generate(WIDTH, HEIGHT);
    rockiness1.generate(WIDTH, HEIGHT);
    rockiness2.generate(WIDTH, HEIGHT);
#endif
}

void islandMain(AreaSlice& island) {
    std::default_random_engine generator(SEED);
    int t;
    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            seaPixel(r,c);
        }
    }
    for (Pixel p = island.readPixel(); p.x != -1; p = island.readPixel()) {
        islandPixel(HEIGHT - p.y, p.x); //does pass as r, c, might be incorrectly converting from x y? might also be offsetting range by one when subtracting from a size value? maybe I shouldn't convert? Oh well, I can't remember at this point..
    }
    for (Pixel p = island.readPixel(); p.x != -1; p = island.readPixel()) {
        rock(HEIGHT - p.y, p.x, generator);
        snow(HEIGHT - p.y, p.x, generator);
        tree(HEIGHT - p.y, p.x, generator);
    }
}

Mesh cutIsland() {
    std::default_random_engine generator(SEED);
    float stability = 4.0; //normal turn multiplier, higher makes more quick turns
    float wandering = 4.0; //multiplied by current "turtle radius multiplier" (1.00 is subtracted to get a value surrounding 0) and then added to random turn; lower allows more wandering
    float width = uniformSize(generator); //oval width
    float height = uniformSize(generator); //oval height
    float step = 2.0; //pixel step per iteration
    VirtualTurtle t;
    Mesh m;
    t.setColorFunc(setColor);
    t.setPixelFunc(setPixel);
    t.tp(STARTX, STARTY);
    t.pendown();
    t.forward(width);
    t.left(90);
    t.updateMesh(m); //equivalent to m.add(t.getx(),t.gety())
    while (t.gety() >= STARTY || t.getx() <= STARTX) { //first three quadrants (last one has a different algoritm to approach the correct spot)
        float rad = VirtualTurtle::dist(STARTX, STARTY, t.getx(), t.gety(), 1/(float)width, 1/(float)height); //"turtle radius multiplier"
        float turn = stability * (normal(generator) + (rad - 1.00) * wandering);
        t.left(turn);
        if (t.getx() == STARTX || t.gety() == STARTY) { 
            t.forward(step);
            t.updateMesh(m);
            continue;
        }
        float centerDirection = VirtualTurtle::ucAngle(STARTX, STARTY, t.getx(), t.gety());
        if (VirtualTurtle::isAngleGreater(centerDirection, t.getheading())) {
            t.right(turn);
            continue;
        }
        t.forward(step);
        t.updateMesh(m);
    }
    while (t.gety() < STARTY) { //last quadrant (last one has a different algoritm to approach the correct spot) tie-up
        float rad = VirtualTurtle::dist(STARTX, STARTY, t.getx(), t.gety(), 1 / width, 1 / height); //"turtle radius multiplier"
        float ovalturn = stability * (normal(generator) + (rad - 1.00) * wandering);
        float enddirection = VirtualTurtle::ucAngle(t.getx(), t.gety(), STARTX + width, STARTY);
        float ovalturnmultiplier = ((float)STARTY - (float)t.gety()) / height;
        float endturn = VirtualTurtle::signedanglerange(enddirection - t.getheading());
        if (ovalturnmultiplier > 1.0) {
            ovalturnmultiplier = 1.0;
        }
        float turn = ovalturnmultiplier * ovalturn + (1 - ovalturnmultiplier) * endturn;
        t.left(turn);
        if (t.getx() == STARTX || t.gety() == STARTY) {
            t.forward(step);
            t.updateMesh(m);
            continue;
        }
        float centerDirection = VirtualTurtle::ucAngle(STARTX, STARTY, t.getx(), t.gety());
        if (VirtualTurtle::isAngleGreater(centerDirection, t.getheading())) {
            t.right(turn);
            continue;
        }
        t.forward(step);
        t.updateMesh(m);
    }
    if (abs(m.point(m.count() - 1).x - m.point(0).x) > TOL || abs(m.point(m.count() - 1).y - m.point(0).y) > TOL) {
        throw "Code Mesh Generation Error";
    }
    m.pop();
    m.add(m.point(0)); //update last point to be the same as last
    m.rotate(STARTX, STARTY, uniformDegree(generator));
    return m;
}

int main(int argc, char** argv)
{
    init(&argc, argv);
    glutDisplayFunc(display);
    glutMouseFunc(onMouseButton);
    glutMainLoop();
    return 0;
}
