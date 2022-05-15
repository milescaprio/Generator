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

// aa < ab
bool isAngleGreater(float aa, float ab) {
    float ad = anglerange(aa - ab);
    if (ad < 180) {
        return true;
    }
    return false;
}

bool isAngleLess(float aa, float ab) {
    float ad = anglerange(aa - ab);
    if (ad > 180) {
        return true;
    }
    return false;
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
    bool hasDipped = false; //it goes down then back up again
    while (t.gety() <= STARTY || hasDipped == false) {
        float rad = sqrt(((t.gety() - STARTY) / (float)height) * ((t.gety() - STARTY) / (float)height) + ((t.getx() - STARTX) / (float)width) * ((t.getx() - STARTX) / (float)width)); //"turtle radius multiplier"
        float turn = stability * (distribution(generator) + (rad - 1.00) * wandering);
        t.left(turn);
        if (t.getx() == STARTX || t.gety() == STARTY) { 
            t.forward(step);
            continue;
        }
        float centerDirection = atan((float)(t.gety() - STARTY) / (float)(t.getx() - STARTX)) * (180.0 / PI);
        if (centerDirection < 0) {
            centerDirection += 180;
        }
        /*                             + 90 because that's the direction of the turtle at the beginning, - because the ange thing starts facing inwards*/
        std::cout << centerDirection << "___" << t.getheading() << "___" << t.getx() << "___" << t.gety() << "\n";
        if ((t.gety() > STARTY ? isAngleGreater : isAngleLess)(centerDirection, t.getheading())) {
            t.right(turn);
            std::cout << "\n";
            continue;
        }
        t.forward(step);
        if (t.gety() < STARTY) {
            hasDipped = true; //could be more efficient by stopping this check once it's true, with a second while loop after, but thatd be bad code. And this is a bad comment.
        }
    }
}

int main(int argc, char** argv)
{
    init(&argc, argv);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
