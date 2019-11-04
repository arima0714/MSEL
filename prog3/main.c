#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "func_object.h"

#define PI 3.141592

// 物体の色配列群
GLfloat blue[] = {0.2, 0.2, 0.8, 1.0 };
GLfloat black[] = {000.0/255.0, 000.0/255.0, 000.0/255.0, 1.0};
// forestgreen : 木の葉
GLfloat forestgreen[] = {34.0/255.0, 139.0/255.0, 34.0/255.0, 1.0};
GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
// peru : 木の幹,
GLfloat peru[] = {205.0/255.0, 133.0/255.0, 65.0/255.0, 1.0};
GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
GLfloat white[] = {255.0/255.0, 255.0/255.0, 255.0/255.0, 1.0};
GLfloat mediumvioletred[] = {199.0/255.0, 21.0/255.0, 133.0/255.0, 1.0};
GLfloat cornflowerblue[] = {100.0/255.0, 149.0/255.0, 237.0/255.0, 1.0};
GLfloat firebrick[] = {178.0/255.0, 34.0/255.0, 34.0/255.0, 1.0};
GLfloat darkolivegreen[] = {85.0/255.0, 107.0/255.0, 47.0/255.0, 1.0};
GLfloat olive[] = {128.0/255.0, 100.0/255.0, 0.0/255.0, 1.0};

double theta = 0.0;
double tau = 0.0;
double circle_r = 10.0;

double camera_ex;
double camera_ey;
double camera_ez;	// 視点の位置

int car_x = -4.0;

void timer(int value){
	// 車のx座標を増加
	car_x += 0.001;

	glutPostRedisplay();

	glutTimerFunc(100, timer, 0);
}

void scene(void){
	static GLfloat yellow[] = {0.8, 0.8, 0.2, 1.0};
	static GLfloat ground[][4] = {
		{0.6, 0.6, 0.6, 1.0},
		{0.3, 0.3, 0.3, 1.0}
	};

	int i;
	int j;

	// 木
	glPushMatrix();
	glTranslated(-3, 0.0, -3.0);
	tree(peru, darkolivegreen);
	glPopMatrix();

	// 木
	glPushMatrix();
	glTranslated(0, 0.0, -3.0);
	tree(peru, olive);
	glPopMatrix();

	// 木
	glPushMatrix();
	glTranslated(3, 0.0, -3.0);
	tree(peru, forestgreen);
	glPopMatrix();

	// 家
	glPushMatrix();
	glTranslated(-4, 0.0, 3.0);
	house(peru, yellow);
	glPopMatrix();

	// 家
	glPushMatrix();
	glTranslated(-2, 0.0, 3.0);
	house(peru, mediumvioletred);
	glPopMatrix();

	// 家
	glPushMatrix();
	glTranslated(0, 0.0, 3.0);
	house(peru, firebrick);
	glPopMatrix();

	// 家
	glPushMatrix();
	glTranslated(2, 0.0, 3.0);
	house(peru, red);
	glPopMatrix();

	// 家
	glPushMatrix();
	glTranslated(4, 0.0, 3.0);
	house(peru, cornflowerblue);
	glPopMatrix();
	
	// 車
	glPushMatrix();
	glTranslated(4.0 + car_x, 0.0, 0.0);
	car(blue, black);
	glPopMatrix();

	// 車
	glPushMatrix();
	glTranslated(car_x, 0.0, 0.0);
	car(white, black);
	glPopMatrix();

	glBegin(GL_QUADS);
	glNormal3d(0.0, 1.0, 0.0);
	for(j = -5; j < 5; j++){
		for(i = -5; i < 5; i++){
			glMaterialfv(GL_FRONT, GL_DIFFUSE, ground[(i+j) & 1]);
			glVertex3d((GLdouble)i, -0.5, (GLdouble)j);
			glVertex3d((GLdouble)i, -0.5, (GLdouble)(j+1));
			glVertex3d((GLdouble)(i + 1), -0.5, (GLdouble)(j+1));
			glVertex3d((GLdouble)(i + 1), -0.5, (GLdouble)j);
		}
	}
	glEnd();
}

void Display(void){
	static GLfloat lightpos[] = {3.0, 4.0, 5.0, 1.0};

	// 画面クリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// モデルビュー変換行列の初期化
	glLoadIdentity();

	// 光源の位置を設定
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	gluLookAt(camera_ex, camera_ey, camera_ez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// シーンの描画
	scene();

	glFlush();
}

void resize(int w, int h){
	// ウィンドウ全体をビューポートにする
	glViewport(0, 0, w, h);

	// 透視変換行列の指定
	glMatrixMode(GL_PROJECTION);

	// 透視変換行列の初期化
	glLoadIdentity();
	gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);

	// モデルビュー変換行列の指定
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key , int x , int y){
	//if (key == '\033' || key == 'q'){
	//	exit(0);
	//}
	switch(key){
		case 'x':
			camera_ex = circle_r * cos(theta * PI / 180.0);
			break;
		case 'y':
			camera_ey = circle_r * sin(theta * PI / 180.0);
			break;
		case 'z':
			camera_ez = circle_r * sin(theta * PI / 180.0);
			break;
		case '\033':
			exit(0);
			break;
		case 'q':
			exit(0);
			break;
		default:
			break;
	}
}

void init(void){
	// 初期設定
	glClearColor(1.0,1.0,1.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//
	camera_ex = circle_r * cos(theta * PI / 180.0);
 	camera_ey = circle_r * sin(theta * PI / 180.0);
 	camera_ez = circle_r * cos(theta * PI / 180.0);
}

int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(Display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	init();
	glutTimerFunc(100, timer, 0);
	glutMainLoop();
	return 0;
}

