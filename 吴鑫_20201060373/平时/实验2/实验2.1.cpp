#include <iostream>

using namespace std;
void init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 400, 0, 400);
}
void setPixel(int x, int y) {
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(3.0);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}
int Round(float x) {
	return (int)(x + 0.5);
}
void ldda() {
	glClear(GL_COLOR_BUFFER_BIT);
	int x0, y0;
	float k ;
	float x1,y1;
	cout << "请输入x，y及斜率k：" << endl;
	cin >> x0 >> y0 >> k;
	x1 = x0;
	y1 = y0;
		if (k <= 1) {
		for (int x = x0,y = y0; x < 400; x++) {
			setPixel(x,Round(y1) );
			y1 = y1 + k;
		}
	}
	else {
		for (int x = x0, y = y0; y < 480; y++) {
			setPixel(Round(x1),y);
			x1 = x1+1/k;
		}
	}
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("ldda");
	init();
	glutDisplayFunc(ldda);
	glutMainLoop();
}