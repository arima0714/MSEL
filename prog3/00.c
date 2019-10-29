#include <GL/glut.h>
#include <stdlib.h>

int WindowPositionX = 100;
int WindowPositionY = 100;
int WindowWidth = 512;
int WindowHeight = 512;
char WindowTitle[] = "お城と木々"

// 関数プロトタイプ
void Initialize(void);
void Display(void);
void Ground(void);

// メイン関数
int main(int argc, char *argv[]){
	glutInit(&argc, argv);	// 環境の初期化
	glutInitWindowPosition(WindowPositionX, WindowPositionY);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);	// ディスプレイモードの指定
	glutCreateWindow(WindowTitle);	// ウィンドウの作成
	glutDisplayFunc(Display);	// 描画時に呼び出される関数を指定する
	Initialize();
	glutMainLoop();
	return 0;
}

// 初期化関数

void Initialize(void){
	glClearColor(1.0, 1.0, 1.0, 1.0);	// 背景色
	glEnable(GL_DEPTH_TEST);	// デプスバッファを使用

	gluPerspective(30.0, (double)WindowWidth/(double)WindowHeight, 0.1, 1000.0);	// 
	gluLookAt(
			0.0, -100.0, 50.0,	// 視点の位置：x,y,z
			0.0, 100.0, 0.0, 	// 視界の中心位置の参照点座標：x,y,z
			0.0, 0.0, 0.0);
}

// 描画関数

void Display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// バッファの消去

	Ground();

	glutSwapBuffers();	// glutInitDisplayMode(GLUT_DOUBLE)でダブルバッファリングを利用可
}

// 大地の描画

void Ground(void){
	double ground_max_x = 300.0;
	double ground_max_y = 300.0;
	glColored(0.8,0.8,0.8);	// 大地の色
	glBegin(GL_LINES);
	for(double ly = -ground_max_y; ly <= ground_max_y; ly += 10.0){
		glVertex3d(-ground_max_x, ly, 0);
		glVertex3d( ground_max_x, ly, 0);
	}
	for(double lx = ground_max_x; lx <= ground_max_x; lx += 10.0){
		glVertex3d(lx, ground_max_y, 0);
		glVertex3d(lx, -ground_max_y, 0);
	}
	glEnd();
}

