#include <stdio.h>
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

double theta = 	225.0;
double tau = 0.0;
double circle_r = 25.0;

double cam_point_x = 5.0;
double cam_point_y = 5.0;
double cam_point_z = 5.0;	// カメラの注視点の座標

double camera_ex = 10.0;
double camera_ey = 2.0;
double camera_ez = 10.0;	// 視点の位置

int car_x = -4.0;

void set_xyz(void){
	//	camera_ex = circle_r * cos(theta * PI / 180.0) * cos(tau * PI / 180.0);
	//	camera_ez = circle_r * sin(theta * PI / 180.0) * cos(tau * PI / 180.0);
 	//	camera_ey = circle_r * sin(tau * PI / 180.0);

	cam_point_x  = circle_r * cos(theta * PI / 180.0) * cos(tau * PI / 180.0);
	cam_point_z  = circle_r * sin(theta * PI / 180.0) * cos(tau * PI / 180.0);

	cam_point_y = circle_r * sin(tau * PI / 180.0);
}

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
	gluLookAt(camera_ex, camera_ey, camera_ez, cam_point_x, cam_point_y, cam_point_z, 0.0, 1.0, 0.0);

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
	double diff_x = camera_ex - cam_point_x;
	double diff_z = camera_ez - cam_point_z;
	double c_r = pow(pow(diff_x , 2) + pow(diff_z , 2), 0.5) ;
	double cos_t = diff_x / c_r;
	double sin_t = diff_z / c_r;

	switch(key){
		case 's':
			camera_ex += cos_t;
			camera_ez += sin_t;;
			set_xyz();
			break;
		case 'w':
			camera_ex -= cos_t;
			camera_ez -= sin_t;
			set_xyz();
			break;
		case 'd':
			camera_ex += sin_t;
			camera_ez -= cos_t;
			break;
		case 'a':
			camera_ex -= sin_t;
			camera_ez += cos_t;
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

void sp_keyboard(int key , int x , int y){
	switch(key){
		case GLUT_KEY_LEFT:
			theta -= 3;
			set_xyz();
			break;
		case GLUT_KEY_RIGHT:
			theta += 3;
			set_xyz();
			break;
		case GLUT_KEY_UP:
			tau += 3;
			set_xyz();
			break;
		case GLUT_KEY_DOWN:
			tau -= 3;
			set_xyz();
			break;
		default:
			break;
	}
}

void init(void){
	// 初期設定
	set_xyz();
	glClearColor(1.0,1.0,1.0,1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(Display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(sp_keyboard);
	init();
	glutTimerFunc(100, timer, 0);
	glutMainLoop();
	return 0;
}

