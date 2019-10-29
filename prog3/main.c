#include <stdlib.h>
#include <GL/glut.h>
#include "func_object.h"

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

double camera_ex = 1.0;
double camera_ez = 1.0;	// 視点の位置
double camera_r = 0.0; 	// 視点の向き

int car_x = -4.0;

void timer(int value){
	// 車のx座標を増加
	car_x += 0.01;

	if(car_x >= 5.0){
		car_x = -4.0;
	}

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

	for(int k = -3; k < 4; k += 4){
		// 木
		glPushMatrix();
		glTranslated(k, 0.0, -3.0);
		tree(peru, forestgreen);
		glPopMatrix();
	}

	// 家
	glPushMatrix();
	glTranslated(0.0, 0.0, 3.0);
	house(peru, red);
	glPopMatrix();
	
	// 車
	glPushMatrix();
	glTranslated(0.0, 0.0, 0.0);
	car(white, black);
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

	// 視点の移動
	glRotated(camera_r, 0.0, 1.0, 0.0);
	glTranslated(camera_ex, 0.0, camera_ez);

	// 光源の位置を設定
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

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
	gluLookAt(10.0, 12.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// モデルビュー変換行列の指定
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key , int x , int y){
	//if (key == '\033' || key == 'q'){
	//	exit(0);
	//}
	switch(key){
		case 'x':
			camera_ex += 1;
			break;
		case 'z':
			camera_ez += 1;
			break;
		case 'r':
			camera_r += 10;
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

