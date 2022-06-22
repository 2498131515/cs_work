#include <windows.h>
#include <iostream>
#include <gl/glut.h>
#include <gl/GL.h>
#include <math.h>
using namespace std;

void setPixel(int x,int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}
void drawCircle(void) {
    int  r;
    //cout << "请输入点的坐标与半径:" << endl;
    r = 100;
    float d = 1.25 - r;
    int k = r / 1.4;
    int y = r;
    glClear(GL_COLOR_BUFFER_BIT);
    for (int x = 0; x < k; x++) {
        if (d <= 0) {
            d = d + 2 * x + 3;
        }
        else {
            y = y - 1;
            d = d + 2 * (x - y) + 5;
        }
        setPixel(x, y);
        setPixel(y, x);
        setPixel(-x, y);
        setPixel(-x, -y);
        setPixel(x, -y);
        setPixel(y, -x);
        setPixel(-y, -x);
        setPixel(-y, x);
    }
}
void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.9);       // 设置背景色：白色。前三个参数分别代表红绿蓝分量。
    glColor3f(1.0f, 0.0f, 0.0f);          // set the drawing color   
    glPointSize(2.0);                // 点的大小为4*4像素
    glMatrixMode(GL_PROJECTION);     // 
    glLoadIdentity();
    gluOrtho2D(-320.0, 320.0, -240.0, 240.0);// 指定绘图时采用的坐标系统

}


int main(int argc,char** argv)
{
    glutInit(&argc, argv);          // ***对GLUT进行初始化
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ***set display mode，单缓冲/双缓冲，颜色索引模式，深度等
    glutInitWindowSize(640, 480);     // ***设置窗口大小
    glutInitWindowPosition(0, 150); // ***设置窗口位置
    glutCreateWindow("my first attempt"); // ***创建窗口
    glutDisplayFunc(drawCircle);     // 显示事件回调函数
    init();
    glutMainLoop();              // ***启动程序，检测事件并进行处理
}
