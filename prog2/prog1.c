#include <stdio.h>
#include <GL/glut.h>

#define MAXPOINTS 100		// 記憶する点の数
GLint point[MAXPOINTS][2];	// 座標を記憶する配列
int pointnum = 0;		// 記憶した座標の数
int rubberband = 0;		// ラバーバンドの消去

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

				// 始点ではラバーバンドを書いていないので消さない
				rubberband = 0;
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

void motion(int x, int y){
	static GLint savepoint[2];	// 以前のラバーバンドの端点
	//	論理演算機能 ON
	glEnable(GL_COLOR_LOGIC_OP);
	glLogicOp(GL_INVERT);

	glBegin(GL_LINES);
	if(rubberband){
		glVertex2iv(point[pointnum - 1]);
		glVertex2iv(savepoint);
	}
	//	新しいラバーバンドを書く
	glVertex2iv(point[pointnum - 1]);
	glVertex2i(x, y);
	glEnd();

	glFlush();

	//	論理演算機能 OFF
	glLogicOp(GL_COPY);
	glDisable(GL_COLOR_LOGIC_OP);
	//	今書いたラバーバンドの端点を保存
	savepoint[0] = x;
	savepoint[1] = y;
	//	今書いたラバーバンドは次のタイミングで消す
	rubberband = 1;
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
	glutMotionFunc(motion);
	init();
	glutMainLoop();
	return 0;
}

