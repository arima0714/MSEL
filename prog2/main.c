#include <GL/glut.h>

GLdouble vertex[][3] = {
	{ 000.0, 000.0, 000.0},
	{ 001.0, 000.0, 000.0},
	{ 001.0, 001.0, 000.0},
	{ 000.0, 001.0, 000.0},
	{ 000.0, 000.0, 001.0},
	{ 001.0, 000.0, 001.0},
	{ 001.0, 001.0, 001.0},
	{ 000.0, 001.0, 001.0},
};

int face[][4] = {
	{ 0, 1, 2, 3 },
	{ 1, 5, 6, 2 },
	{ 5, 4, 7, 6 },
	{ 4, 0, 3, 7 },
	{ 4, 5, 1, 0 },
	{ 3, 2, 6, 7 },
};

GLdouble normal[][3] = {
	{ 0.0, 0.0,-1.0 },
	{ 1.0, 0.0, 0.0 },
	{ 0.0, 0.0, 1.0 },
	{-1.0, 0.0, 0.0 },
	{ 0.0,-1.0, 0.0 },
	{ 0.0, 1.0, 0.0 },
};

// Z軸上斜め上の最初の光源(GL_LIGHT0)
GLfloat light0pos[] = { 0.0, 3.0, 5.0, 1.0 };
// X軸上斜め上の二つ目の光源(GL_LIGHT1)
GLfloat light1pos[] = { 5.0, 3.0, 0.0, 1.0 };

// 物体の色配列群
GLfloat blue[] = {0.2, 0.2, 0.8, 1.0 };
GLfloat black[] = {000.0/255.0, 000.0/255.0, 000.0/255.0, 1.0};
// forestgreen : 木の葉
GLfloat forestgreen[] = {34.0/255.0, 139.0/255.0, 34.0/255.0, 1.0};
GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
// peru : 木の幹,
GLfloat peru[] = {205.0/255.0, 133.0/255.0, 65.0/255.0, 1.0};
GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
GLfloat white[] = {001.0/255.0, 001.0/255.0, 001.0/255.0, 1.0};

void cube(void){
	int i;
	int j;

	glBegin(GL_QUADS);
	for(j = 0; j < 6; ++j){
		glNormal3dv(normal[j]);
		for(i = 0; i < 4; ++i){
			glVertex3dv(vertex[face[j][i]]);
		}
	}
	glEnd();
}

GLdouble color[][3] = {
	{ 001.0, 000.0, 000.0}, // 赤
	{ 000.0, 001.0, 000.0}, // 緑
	{ 000.0, 000.0, 001.0}, // 青
	{ 001.0, 001.0, 000.0}, // 黄
	{ 001.0, 000.0, 001.0}, // マゼンタ
	{ 000.0, 001.0, 001.0}, // シアン
};

int edge[][2] = {
	{ 0, 1 },
	{ 1, 2 },
	{ 2, 3 },
	{ 3, 0 },
	{ 4, 5 },
	{ 5, 6 },
	{ 6, 7 },
	{ 7, 4 },
	{ 0, 4 },
	{ 1, 5 },
	{ 2, 6 },
	{ 3, 7 },
};

void idle(void){
	glutPostRedisplay();
}

void tree(void){
	glPushMatrix();
	// 木の幹
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, peru);	
	glutSolidCube(1.0);
	glTranslated(0.0, 1.0, 0.0);
	glutSolidCube(1.0);
	// 木の葉
	glPushMatrix();
	glTranslated(0.0, 0.70, 0.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glRotated(180.0, 0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, forestgreen);
	glutSolidCone(1.5, 2.0, 64.0, 64.0);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.0, 1.70, 0.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glRotated(180.0, 0.0, 1.0, 0.0);
	glutSolidCone(1.0, 3.0, 64.0, 64.0);
	glPopMatrix();
	glPopMatrix();
}
	

void display(void){
	int i;
	int j;
	static int r = 0;	// 回転角

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// 視点位置と視線方向
	gluLookAt(15.0, 20.0, 25.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// 光源の位置設定
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
	glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
	
	// モデルビュー変換行列の保存
	glPushMatrix();

	// 図形の描画
	tree();

	// 二つ目の図形の描画
	glTranslated(1.0, 1.0, 1.0);
	glRotated((double)(2 * r), 0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
	glutSolidCube(1.0);

	// モデルビュー変換行列の復帰
	glPopMatrix();

	glutSwapBuffers();

	// 一周回ったら回転角を0に戻す
	if(++r >= 360) r = 0;
}

void resize(int w, int h){
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
	// モデルビュー変換行列の設定
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void mouse(int button, int state, int x, int y){
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){
				// アニメーション開始
				glutIdleFunc(idle);
			}
			else{
				// アニメーション停止
				glutIdleFunc(0);
			}
			break;
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN){
				// コマ送りを実施
				glutPostRedisplay();
			}
			break;
		default:
			break;
	}
}
				
void keyboard(unsigned char key, int x, int y){
	switch (key){
		case 'q':
		case 'Q':
		case '\033':	// '\033'はESCのASCIIコード
			exit(0);
		default:
			break;
	}
}

void init(void){
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);
}

int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	init();
	glutMainLoop();
	return 0;
}

