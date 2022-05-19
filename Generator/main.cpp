#include "includes.h"

void islandMain(Pixels& island);
Mesh cutIsland(unsigned int seed);

Generator biome;
Generator elevation;
Generator rockiness;

inline int ubmap(unsigned char val, int first, int last) {
    return (val * (last - first) / 255 + first);
}

void init(int *argc, char** argv)
{
    biome.generate(WIDTH, HEIGHT);
    elevation.generate(WIDTH, HEIGHT);
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
    int t = biome.getpx(r, c);
    setColor(MOISTURERGB(t));
    setPixel(c, HEIGHT - r);
}

void seaPixel(GLint r, GLint c) {
    int t = 0;
    setColor(MOISTURERGB(t));
    setPixel(c, HEIGHT - r);
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
    /*glColor3ub(255, 0, 255);
    glBegin(GL_POINTS);
    glVertex2i(10, 10);
    glEnd();*/
    /*glBindTexture(GL_TEXTURE_2D, text);
    glutSolidCube(1.0);*/
    Mesh m = cutIsland(SEED);
    AreaSlice a = m.containment();
    Pixels island = a.pixels();
    islandMain(island);
    displayEnd();
}

void islandMain(Pixels& points) {
    int t;
    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            seaPixel(r,c);
        }
    }
    for (int i = 0; i < points.count(); i++) {
        islandPixel(HEIGHT - points.pixel(i).y, points.pixel(i).x);
    }
}

Mesh cutIsland(unsigned int seed) {
    std::default_random_engine generator(seed);
    std::normal_distribution<double> normal(0.0, 1.0);
    std::uniform_real_distribution<float> uniformSize(50.0, 250.0);
    std::uniform_real_distribution<float> uniformDegree(0.0, 360.0);
    float stability = 3.0; //normal turn multiplier, higher makes more quick turns
    float wandering = 6.0; //multiplied by current "turtle radius multiplier" (1.00 is subtracted to get a value surrounding 0) and then added to random turn; lower allows more wandering
    float width = uniformSize(generator); //oval width
    float height = uniformSize(generator); //oval height
    float step = 2.0; //pixel step per iteration
    VirtualTurtle t;
    Mesh m;
    t.setColorFunc(setColor);
    t.setPixelFunc(setPixel);
    t.tp(STARTX, STARTY);
    t.penup();
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
    glutMainLoop();
    return 0;
}
