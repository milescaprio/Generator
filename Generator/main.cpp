#include "includes.h"

void islandMain();

GLuint text;

void init(int *argc, char** argv)
{
    generator::init();
    generator::generate();
    text = generator::loadTexture();

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
    glutInit(argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Island");
}

void setPixel(GLint x, GLint y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void setColor(float r, float g, float b) {
    glColor3f(r, g, b);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, text);
    glutSolidCube(1.0);
    glutSwapBuffers();
}

void islandMain() {
    setColor(255.0, 0.0, 0.0);
    setPixel(100, 100);
}

int main(int argc, char** argv)
{
    init(&argc, argv);
    glutDisplayFunc(display);
    glutMainLoop();

    generator::release();
    return 0;
}