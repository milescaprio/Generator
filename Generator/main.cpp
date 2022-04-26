#include "includes.h"

void islandMain();

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
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Island");
    //glClearColor(0, 0.0, 1.0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);   
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

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(2.0);
    /*glColor3ub(255, 0, 255);
    glBegin(GL_POINTS);
    glVertex2i(10, 10);
    glEnd();*/
    /*glBindTexture(GL_TEXTURE_2D, text);
    glutSolidCube(1.0);*/
    islandMain();
    glutSwapBuffers();
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

int main(int argc, char** argv)
{
    init(&argc, argv);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}