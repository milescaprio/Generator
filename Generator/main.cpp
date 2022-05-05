#include "includes.h"

void islandMain();
void cutIsland();

Generator biome;
Generator elevation;

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
    std::default_random_engine generator;
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
    t.forward(width);
    t.pendown();
    t.left(90);
    /*for (int i = 0; i < 12; i++) {
        t.left(30);
        t.forward(100);
    }*/
    /*for (int i = 90; i > 85; --i) {
        t.left(i);
        t.forward(i);
    }*/
    
    while (t.gety() >= 0 or t.getx() <= 0)
    /*for (int i = 0; i < 5; i++)*/ { //we will make three quarters oval until we have better while stopper
        float rad = sqrt(((t.gety() - STARTY) / height) * ((t.gety() - STARTY) / height) + ((t.getx() - STARTX) / width) * ((t.getx() - STARTX) / width)); //"turtle radius multiplier"
        t.left(stability * (distribution(generator) + (rad - 1.00) * wandering));
        //std::cout << rad << "___" << t.getheading() << "\n";
        t.forward(step);
    }
    /*for (int i = 0; i < 100; i++) {
        std::cout << distribution(generator) << "\n";
    }*/
}

int main(int argc, char** argv)
{
    init(&argc, argv);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
