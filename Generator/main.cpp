#include <GL/glut.h>
#include<iostream>

void islandMain();

void init(int *argc, char** argv)
{
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
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(1.0);
    islandMain();
    glFlush();
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
    return 0;
}