#include <GL/glut.h>

//左下の頂点座標を(x,y)として、幅w,高さhの四角形を描画する関数
void draw_sq(float x, float y, float w, float h){
	glBegin(GL_POLYGON);

	glVertex2d(x, y);
	glVertex2d(x+w, y);
	glVertex2d(x+w, y+h);
	glVertex2d(x, y+h);

	glEnd();
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3d(1.0, 0.0, 0.0);
	draw_sq(-0.9, -0.9, 1.8, 1.8);
	glFlush();
}

void resize(int w, int h){
	glViewport(0,0,w,h);	//ウィンドウ全体をビューポートにする
	glLoadIdentity();	//変換行列の初期化
	glOrtho(-w / 200.0, w / 200.0, -h /200.0, h / 200.0, -1.0, 1.0);	//スクリーン上の表示領域をビューポートの大きさに比例させる
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
	init();
	glutMainLoop();
	return 0;
}

