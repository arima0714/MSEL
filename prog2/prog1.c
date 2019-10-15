#include <stdio.h>
#include <GL/glut.h>

#define MAXPOINTS 100
GLint point[MAXPOINTS][2];
int pointnum = 0;

void display(void){
	int i;

	glClear(GL_COLOR_BUFFER_BIT);
	if(pointnum > 1){
		glColor3d(0.0, 0.0, 0.0);
		glBegin(GL_LINES);
		for( i = 0; i < pointnum; ++i){
			glVertex2iv(point[i]);
		}
		glEnd();
	}
	glFlush();
}

void resize(int w, int h){
	glViewport(0,0,w,h);	//ウィンドウ全体をビューポートにする
	glLoadIdentity();	//変換行列の初期化
	glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);
}

void mouse(int button, int state, int x, int y){
	switch(button){
		case GLUT_LEFT_BUTTON:
			point[pointnum][0] = x;
			point[pointnum][1] = y;
			if(state == GLUT_UP){
				glColor3d(0.0, 0.0, 0.0);
				glBegin(GL_LINES);
				glVertex2iv(point[pointnum - 1]);	// ひとつ前は押した位置
				glVertex2iv(point[pointnum]);		// 今の位置は話した位置
				glEnd();
				glFlush();
			}
			else{
			}
			if(pointnum < MAXPOINTS - 1) ++pointnum;
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		default:
			break;
	}

}

void init(void){
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char *argv[]){
	glutInitWindowPosition(100,100);	//300x300のウィンドウを開く
	glutInitWindowSize(320, 240);		//320,240の位置にウィンドウを開く
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	init();
	glutMainLoop();
	return 0;
}

