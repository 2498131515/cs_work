#include <GL/glut.h>
#include <iostream>

GLint winWidth = 400, winLength = 400, vWidth = 200, vLength = 200;
void Cothen_Sutherland();
class point {
public:
    int x, y, d1 = 0, d2 = 0, d3 = 0, d4 = 0;
};
point P[2];
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-200, 200, -200, 200);
    glLineWidth(2);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
}
void disPlayFnc() {
    std::cout << "请输入直线的端点：";
    std::cin >> P[0].x >> P[0].y >> P[1].x >> P[1].y;
    for (int i = 0; i < 2; i++) {
        if (P[i].x > vWidth / 2)
            P[i].d4 = 1;
        if (P[i].x < -vWidth / 2)
            P[i].d3 = 1;
        if (P[i].y > vLength / 2)
            P[i].d2 = 1;
        if (P[i].y < -vLength / 2)
            P[i].d1 = 1;
        printf("%d%d%d%d", P[i].d1, P[i].d2, P[i].d3, P[i].d4);
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2i(P[0].x, P[0].y);
    glVertex2i(P[1].x, P[1].y);
    glEnd();
    glFlush();
    Cothen_Sutherland();
}
void Cothen_Sutherland() {
    if ((P[0].d1 | P[1].d1 + P[0].d2 | P[1].d2 + P[0].d3 | P[1].d3 + P[0].d4 | P[1].d4) == 0) {
        glBegin(GL_POLYGON);
        glColor4f(1.0, 0.0, 0.0,0.5);
        glVertex2i(-100, 100);
        glVertex2i(100, 100);
        glVertex2i(100, -100);
        glVertex2i(-100, -100);
        glEnd();
        glBegin(GL_LINES);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2i(P[0].x, P[0].y);
        glVertex2i(P[1].x, P[1].y);
        glEnd();
        glFlush();
        return;
    }
    if ((P[0].d1 & P[1].d1 + P[0].d2 & P[1].d2 + P[0].d3 & P[1].d3 + P[0].d4 & P[1].d4) != 0) {
        glBegin(GL_POLYGON);
        glColor4f(1.0, 0.0, 0.0, 0.5);
        glVertex2i(-100, 100);
        glVertex2i(100, 100);
        glVertex2i(100, -100);
        glVertex2i(-100, -100);
        glEnd();
        glFlush();
        return;
    }
    double k = (double(P[0].y) - P[1].y) / (double(P[0].x) - P[1].x);
    printf("%lf", k);
    double a[4];
    a[0] = k * (-100.0 - P[0].x) + P[0].y;//left
    a[1] = k * (100.0 - P[0].x) + P[0].y;//right
    a[2] = (100.0 - P[0].y)/k + P[0].x;//top
    a[3] = (-100.0 - P[0].y)/k + P[0].x;//bottom
    point newp[2];
    int count = 0;
    if (P[0].d1 + P[0].d2 + P[0].d3 + P[0].d4 == 0) {
        newp[count] = P[0];
        count++;
    }
    else if (P[1].d1 + P[1].d2 + P[1].d3 + P[1].d4 == 0) {
        newp[count] = P[1];
        count++;
    }
    for (int i = 0; i < 4; i++) {
        if (a[i] <= 100 && a[i] >= -100) {
            switch (i)
            {
            case 0:newp[count].x = -100, newp[count].y = a[i]; count++; break;
            case 1:newp[count].x = 100, newp[count].y = a[i]; count++; break;
            case 2:newp[count].x = a[i], newp[count].y = 100; count++; break;
            case 3:newp[count].x = a[i], newp[count].y = -100; count++; break;
            default:
                break;
            }
        }
        if (count > 1)
            break;
        printf("  %d  %d", newp[count].x, newp[count].y);
    }
    glBegin(GL_POLYGON);
    glColor4f(1.0, 0.0, 0.0, 0.5);
    glVertex2i(-100, 100);
    glVertex2i(100, 100);
    glVertex2i(100, -100);
    glVertex2i(-100, -100);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2i(newp[0].x, newp[0].y);
    glVertex2i(newp[1].x, newp[1].y);
    glEnd();
    glFlush();
    return;
}

int main(int argc,char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winLength);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cothen-Sutherland");

    init();
    glutDisplayFunc(disPlayFnc);
    glutMainLoop();
}