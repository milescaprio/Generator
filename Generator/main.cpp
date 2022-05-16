#include "includes.h"

void islandMain();
void cutIsland();

Generator biome;
Generator elevation;

inline int ubmap(unsigned char val, int first, int last) {
    return (val * (last - first) / 255 + first);
}

float anglerange(float a) { //inefficient but whatever
    while (a < 0) {
        a += 360;
    }
    while (a >= 360) {
        a -= 360;
    }
    /*if (a < 0) {
        return anglerange(a + 360);
    }
    if (a >= 360) {
        return anglerange(a - 360);
    }*/
    return a;
}

float dist(float x1, float y1, float x2, float y2) {
    return sqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));
}

float dist(float x1, float y1, float x2, float y2, float xm, float ym) { //multipliers for the sides, because we are measuring the oval like it's a circle
    return sqrt(((y2 - y1) * ym) * ((y2 - y1) * ym) + ((x2 - x1) * xm) * ((x2 - x1) * xm));
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
    //glutSwapBuffers();
}

void setColor(unsigned char r, unsigned char g, unsigned char b) {
    glColor3ub(r, g, b);
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
    //islandMain();
    cutIsland();
    displayEnd();
}

void islandMain() {
    int t;
    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            t = biome.getpx(r, c);
            setColor(MOISTURERGB(t));
            setPixel(c, HEIGHT - r);
        }
    }
}

void cutIsland() {
    std::default_random_engine generator(111);
    std::normal_distribution<double> distribution(0.0, 1.0);
    float stability = 3.0; //normal turn multiplier, higher makes more quick turns
    float wandering = 6.0; //multiplied by current "turtle radius multiplier" (1.00 is subtracted to get a value surrounding 0) and then added to random turn; lower allows more wandering
    float width = 100.0; //oval width
    float height = 200.0; //oval height
    float step = 2; //pixel step per iteration
    VirtualTurtle t;
    t.setColorFunc(setColor);
    t.setPixelFunc(setPixel);
    t.tp(STARTX, STARTY);
    t.penup();
    t.forward(width);
    t.pendown();
    t.left(90);
    while (t.gety() >= STARTY || t.getx() <= STARTX) { //first three quadrants (last one has a different algoritm to approach the correct spot)
        float rad = dist(STARTX, STARTY, t.getx(), t.gety(), 1/(float)width, 1/(float)height); //"turtle radius multiplier"
        float turn = stability * (distribution(generator) + (rad - 1.00) * wandering);
        t.left(turn);
        if (t.getx() == STARTX || t.gety() == STARTY) { 
            t.forward(step);
            continue;
        }
        float centerDirection = VirtualTurtle::ucAngle(STARTX, STARTY, t.getx(), t.gety());
        if (VirtualTurtle::isAngleGreater(centerDirection, t.getheading())) {
            t.right(turn);
            continue;
        }
        t.forward(step);
    }
    while (t.gety() < STARTY) { //last quadrant (last one has a different algoritm to approach the correct spot) tie-up
        float rad = dist(STARTX, STARTY, t.getx(), t.gety(), 1 / (float)width, 1 / (float)height); //"turtle radius multiplier"
        float ovalturn = stability * (distribution(generator) + (rad - 1.00) * wandering);
        float enddirection = VirtualTurtle::ucAngle(t.getx(), t.gety(), STARTX + width, STARTY);
        float ovalturnmultiplier = ((float)STARTY - (float)t.gety()) / height;
        if (ovalturnmultiplier > 1) {
            ovalturnmultiplier = 1;
        }
        float turn = ovalturnmultiplier * ovalturn + (1 - ovalturnmultiplier) * (enddirection - t.getheading());
        t.left(turn);
        if (t.getx() == STARTX || t.gety() == STARTY) {
            t.forward(step);
            continue;
        }
        float centerDirection = VirtualTurtle::ucAngle(STARTX, STARTY, t.getx(), t.gety());
        if (VirtualTurtle::isAngleGreater(centerDirection, t.getheading())) {
            t.right(turn);
            continue;
        }
        t.forward(step);
        //std::cout << "thinged " << t.getx() << " " << t.gety() << " " << t.getheading() << "\n";
    }
    //std::cout << "ended " << t.getx() << " " << t.gety() << " " << t.getheading() << "\n";
}

int main(int argc, char** argv)
{
    init(&argc, argv);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
