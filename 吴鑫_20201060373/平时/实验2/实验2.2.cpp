#include <iostream>
#include <GL/glut.h>
#include <cstdio>
using namespace std;

void setPixel(int x, int y) {
    glPointSize(2);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}
void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}
void bresenham(int x0,int x1,int y0,int y1) {
    glClear(GL_COLOR_BUFFER_BIT);
    int b = x1 - x0;
    int a = -(y1 - y0);
    int cx = (b >= 0 ? 1 : (b = -b, -1));
    int cy = (a <= 0 ? 1 : (a = -a, -1));
    int x = x0, y = y0;
    setPixel(x0, y0);
    if (-a <= b) {
        int  d = 2 * a + b;
        while (x != x1) {
            if (d < 0) {
                d += 2 * a + 2 * b;
                y += cy;
            }
            else {
                d += 2 * a;
            }
            x += cx;
            setPixel(x, y);
        }
        return;
    }
    else {
        int d = 2 * b + a;
        while (y != y1) {
            if (d < 0) {
                d += 2 * b;
            }
            else {
                d += 2 * (a + b);
                x += cx;
            }
            y += cy;
            setPixel(x, y);
        }
        return ;
    }
}
void callbresen(void) {
    int x0 = 0, x1 = 100, y0 = 0, y1 = 90;
    glClear(GL_COLOR_BUFFER_BIT);
    bresenham(x0, x1, y0, y1);
    glFlush();
}
int main(int argc,char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 300);
    glutCreateWindow("An example of bresenham");
    init();
    glutDisplayFunc(callbresen);
    glutMainLoop();
    return 0;
}