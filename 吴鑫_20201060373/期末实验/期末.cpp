#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>

#define checkImageWidth 64
#define checkImageHeight 64

static GLubyte checkImage[checkImageHeight][checkImageWidth][4];
static GLuint texName;

static GLfloat xrot = 0;
static GLfloat yrot = 0;



//函数功能：绘图
void display(void)
{
	glEnable(GL_LIGHTING);		//启动光源
	glEnable(GL_LIGHT0);		//第一个光源
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);	//删除隐藏的表面
	glEnable(GL_NORMALIZE);		//将阴影向量正则化
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//设置表面材料的属性
	GLfloat mat_ambient[] = { 1.5f,1.5f,1.5f,1.0f };
	GLfloat mat_diffuse[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat mat_specular[] = { 1.0f,1.0f,1.0f,1.0f, };
	GLfloat mat_shininess[] = { 70.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);		//指定环境泛光的强度
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);		//漫反射的强度
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);		//镜面反射的强度
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);	//镜面反射光的会聚强度

	//绘制茶壶纹理图案
	int i, j, c;
	for (i = 0; i < checkImageHeight; i++) {
		for (j = 0; j < checkImageWidth; j++) {
			c = ((((i & 0x5) == 0) ^ ((j & 0x5)) == 0)) * 225;
			checkImage[i][j][0] = (GLubyte)115;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)c;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);	//控制像素存储模式
	glGenTextures(1, &texName);				//用来生成纹理的数量为1
	glBindTexture(GL_TEXTURE_2D, texName);	//绑定纹理
	//纹理滤波，图象从纹理图象空间映射到帧缓冲图象空间
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,
		checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

	//设置光源属性F
	GLfloat light_position[] = { 2.0f, 6.0f, 3.0f, 0.0f };	//光源位置
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMatrixMode(GL_PROJECTION);//后继操作都在投影变换范围内
	glLoadIdentity();			//设置当前矩阵为单位矩阵
	GLfloat h = 1.0;			//窗口的一半高度
	glOrtho(-h * 64 / 48.0, h * 64 / 48.0, -h, h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);	//选择模型观察矩阵
	glLoadIdentity();

	gluLookAt(1, 1.6, 2, 0, 0.2, 0, 0, 1, 0);		//设置观察坐标系


	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotated(-90.0, 0.0, 1.0, 0.0);
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);		//开启纹理
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);//映射方式
	glTranslated(0.0, 0.0, 0.0);
	glRotated(90, 0, 1, 0);
	glutSolidTeapot(0.5);	//绘制茶壶
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);		//关闭纹理
	glPushMatrix();
	glTranslated(0.0, 0.1, 1.);
	glutSolidSphere(0.1, 30, 50);		//绘制球体
	glPopMatrix();
	glFlush();					//绘图结果显示到屏幕上
}


void SpecialKeys(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:		
		xrot += 5.0;
		break;
	case GLUT_KEY_DOWN:		
		xrot -= 5.0;
		break;
	case GLUT_KEY_LEFT:		
		yrot += 5.0;
		break;
	case GLUT_KEY_RIGHT:	
		yrot -= 5.0;
		break;
	default:
		break;
	}
	glutPostRedisplay();		//标记当前窗口需要重新绘制
	glFlush();					//绘图结果显示到屏幕上
}

//函数功能：改变窗口大小
void winReshape(int w, int h)
{
	GLfloat lightPos[] = { -50.f, 50.0f, 100.0f, 1.0f };
	GLfloat nRange = 1.9f;

	if (h == 0)
		h = 1;

	glViewport(0, 0, w, h);		//重新设置屏幕上的窗口大小

	glMatrixMode(GL_PROJECTION);//后继操作都在投影变换范围内
	glLoadIdentity();			//设置当前矩阵为单位矩阵

	//正交投影
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange, nRange);
	else
		glOrtho(-nRange * w / h, nRange * w / h, -nRange, nRange, -nRange, nRange);

	glMatrixMode(GL_MODELVIEW);			//选择模型观察矩阵
	glLoadIdentity();					

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);	
	glutInitWindowSize(700, 500);	
	glutInitWindowPosition(200, 100);	
	glutCreateWindow("final");	

	glutDisplayFunc(display);

	glutReshapeFunc(winReshape);		
	glutSpecialFunc(SpecialKeys);		
	glutMainLoop();						
}