// 氏名：有馬海人
// 学籍番号：1710021
// メールアドレス：a1710021@edu.cc.uec.ac.jp
// 作品タイトル：famous time machine

#include <GL/glut.h>

// MacOS : gcc main.c -framework GLUT -framework OpenGL -mmacosx-version-min=10.8

//三角形を描画する関数
void draw_tri(float c_x, float c_y, float l_x, float l_y, float r_x, float r_y){
	glBegin(GL_POLYGON);

	glVertex2d(c_x, c_y);
	glVertex2d(l_x, l_y);
	glVertex2d(r_x, r_y);

	glEnd();
}

//三角形の枠最後の三引数をRGBとしたものを描画する関数
void draw_line_tri(float c_x, float c_y, float l_x, float l_y, float r_x, float r_y, float R, float G, float B){
	glColor3d(R, G, B);

	glBegin(GL_LINES);

	glVertex2d(c_x, c_y);
	glVertex2d(l_x, l_y);

	glVertex2d(l_x, l_y);
	glVertex2d(r_x, r_y);

	glVertex2d(r_x, r_y);
	glVertex2d(c_x, c_y);

	glEnd();
}

//左下の頂点座標を(x,y)として、幅w,高さhの四角形を描画する関数
void draw_sq(float x, float y, float w, float h){
	glBegin(GL_POLYGON);

	glVertex2d(x, y);
	glVertex2d(x+w, y);
	glVertex2d(x+w, y+h);
	glVertex2d(x, y+h);

	glEnd();
}

//左下の頂点座標を(x,y)として、幅w,高さhの四角形の枠最後の三引数をRGBとしたものを描画する関数
void draw_line_sq(float x, float y, float w, float h, float R, float G, float B){
	glColor3d(R, G, B);

	glBegin(GL_LINES);

	glVertex2d(x, y);
	glVertex2d(x+w, y);
	
	glVertex2d(x+w, y);
	glVertex2d(x+w, y+h);

	glVertex2d(x+w, y+h);
	glVertex2d(x, y+h);

	glVertex2d(x, y+h);
	glVertex2d(x, y);

	glEnd();
}

// 背景の設定
void background(){

	int x;
	int y;
	int w = 1.0;
	int h = 1.0;

	//  左上
	x = -1.0;
	y = +0.0;
	glBegin(GL_POLYGON);
	glColor3d(1.0, 0.0, 0.0); // 赤
	glVertex2d(x, y);
	glColor3d(0.0, 0.0, 0.0); // 白
	glVertex2d(x+w, y);
	glColor3d(1.0, 0.0, 0.0); // 赤
	glVertex2d(x+w, y+h);
	glColor3d(0.0, 0.0, 0.0); // 白
	glVertex2d(x, y+h);
	glEnd();

	// 左下
	x = -1.0;
	y = -1.0;
	glBegin(GL_POLYGON);
	glColor3d(0.0, 0.0, 0.0); // 白
	glVertex2d(x, y);
	glColor3d(0.0, 0.0, 1.0); // 青
	glVertex2d(x+w, y);
	glColor3d(0.0, 0.0, 0.0); // 白
	glVertex2d(x+w, y+h);
	glColor3d(0.0, 0.0, 1.0); // 青
	glVertex2d(x, y+h);
	glEnd();

	// 右下
	x = +0.0;
	y = -1.0;
	glBegin(GL_POLYGON);
	glColor3d(1.0, 1.0, 0.0); // 黄
	glVertex2d(x, y);
	glColor3d(0.0, 0.0, 0.0); // 白
	glVertex2d(x+w, y);
	glColor3d(1.0, 1.0, 0.0); // 黄
	glVertex2d(x+w, y+h);
	glColor3d(0.0, 0.0, 0.0); // 白
	glVertex2d(x, y+h);
	glEnd();

	// 右上
	x = +0.0;
	y = +0.0;
	glBegin(GL_POLYGON);
	glColor3d(0.0, 0.0, 0.0); // 白
	glVertex2d(x, y);
	glColor3d(0.0, 1.0, 0.0); // 緑
	glVertex2d(x+w, y);
	glColor3d(0.0, 0.0, 0.0); // 白
	glVertex2d(x+w, y+h);
	glColor3d(0.0, 1.0, 0.0); // 緑
	glVertex2d(x, y+h);
	glEnd();
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3d(1.0, 0.0, 0.0);
	draw_sq(-0.9, -0.9, 1.8, 1.8);

	// 背景
	background();
	// 本体
	glColor3d(25.0/255.0, 23.0/255.0, 112.0/255.0);
	draw_sq(-0.4, -0.8, 0.8, 1.3);
	draw_line_sq(-0.4, -0.8, 0.8, 1.3, 1.0, 1.0, 0.0);
	//	模様部分
	float distance = 0.05;
	float pattern_w = 0.22;
	float pattern_h = 0.24;
	for(int i = 1; i <= 4; i++){ 
		draw_line_sq(-0.05-pattern_w, 0.4 - (distance + pattern_h) * i, pattern_w, pattern_h, 1.0, 1.0, 0.0);
		draw_line_sq(+0.05, 0.4 - (distance + pattern_h) * i, pattern_w, pattern_h, 1.0, 1.0, 0.0);
		// 窓ガラス部分
		if(i == 1){
			glColor3d(255.0/255.0, 255.0/255.0, 255.0/255.0);
			draw_sq		(-0.05-pattern_w, 0.4 - (distance + pattern_h) * i, pattern_w, pattern_h);
			draw_line_sq	(-0.05-pattern_w, 0.4 - (distance + pattern_h) * i, pattern_w, pattern_h, 128.0/255.0, 128.0/255.0, 128.0/255.0);
			glColor3d(255.0/255.0, 255.0/255.0, 255.0/255.0);
			draw_sq		(+0.05, 0.4 - (distance + pattern_h) * i, pattern_w, pattern_h);
			draw_line_sq	(+0.05, 0.4 - (distance + pattern_h) * i, pattern_w, pattern_h, 128.0/255.0, 128.0/255.0, 128.0/255.0);
		}
		if(i == 2){
			int frame = 0.02;
			glColor3d(192.0/255.0, 192.0/255.0, 192.0/255.0);
			draw_sq		(-0.05-pattern_w+frame, 0.4 - (distance + pattern_h) * i + frame, pattern_w, pattern_h);
			draw_line_sq	(-0.05-pattern_w+frame, 0.4 - (distance + pattern_h) * i + frame, pattern_w, pattern_h, 1.0, 1.0, 1.0);
		}
	}

	// 台座
	glColor3d(25.0/255.0, 23.0/255.0, 112.0/255.0);
	draw_sq(-0.5, -0.9, 1.0, 0.1);
	draw_line_sq(-0.5, -0.9, 1.0, 0.1, 1.0, 1.0, 0.0);

	// 屋根
	// 	一段目
	glColor3d(25.0/255.0, 23.0/255.0, 112.0/255.0);
	draw_sq		(-0.42, 0.4, 0.84, 0.1);
	draw_line_sq	(-0.42, 0.4, 0.84, 0.1, 1.0, 1.0, 0.0);
	// 	二段目
	glColor3d(25.0/255.0, 23.0/255.0, 112.0/255.0);
	draw_sq		(-0.35, 0.5, 0.70, 0.1);
	draw_line_sq	(-0.35, 0.5, 0.70, 0.1, 1.0, 1.0, 0.0);
	// 	二段目
	glColor3d(25.0/255.0, 23.0/255.0, 112.0/255.0);
	draw_sq		(-0.32, 0.6, 0.64, 0.1);
	draw_line_sq	(-0.32, 0.6, 0.64, 0.1, 1.0, 1.0, 0.0);
	//	ランプ部分
	//		台座
	glColor3d(25.0/255.0, 23.0/255.0, 112.0/255.0);
	draw_sq		(-0.05, 0.7, 0.10, 0.050);
	draw_line_sq	(-0.05, 0.7, 0.10, 0.050, 1.0, 1.0, 0.0);
	//		ガラス部分
	glColor3d(255.0/255.0, 255.0/255.0, 224.0/255.0);
	draw_sq		(-0.03, 0.75, 0.06, 0.075);
	draw_line_sq	(-0.03, 0.75, 0.06, 0.075, 1.0, 1.0, 0.0);
	//		屋根
	glColor3d(25.0/255.0, 23.0/255.0, 112.0/255.0);
	draw_tri	(0.0, 0.87, -0.05, 0.825, 0.05, 0.825);
	draw_line_tri	(0.0, 0.87, -0.05, 0.825, 0.05, 0.825, 1.0, 1.0, 0.0);
	// 一段目修飾
	glColor3d(000.0/255.0, 000.0/255.0, 000.0/255.0);
	draw_sq		(-0.25, 0.41, 0.50, 0.07);
	draw_line_sq	(-0.25, 0.41, 0.50, 0.07, 1.0, 1.0, 0.0);
	

	glFlush();
}

void resize(int w, int h){
	glViewport(0,0,w,h);	//ウィンドウ全体をビューポートにする
	glLoadIdentity();	//変換行列の初期化
	glOrtho(-w / 400.0, w / 400.0, -h /400.0, h / 400.0, -1.0, 1.0);	//スクリーン上の表示領域をビューポートの大きさに比例させる
}

void init(void){
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char *argv[]){
	glutInitWindowPosition(400,400);	//300x300のウィンドウを開く
	glutInitWindowSize(400, 400);		//320,240の位置にウィンドウを開く
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	init();
	glutMainLoop();
	return 0;
}

