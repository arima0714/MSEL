#include <stdlib.h>
#include <GL/glut.h>

void house(GLfloat *body, GLfloat *roof){
	glPushMatrix();

	// 本体(居住部)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, body);	
	glutSolidCube(1.0);

	// 屋根
	glPushMatrix();
	glTranslated(0.0, 0.50, 0.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glRotated(180.0, 0.0, 1.0, 0.0);
	glRotated(45.0, 0.0, 0.0, 1.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, roof);	
	glutSolidCone(00.90, 00.90, 4, 4);
	glPopMatrix();

	glPopMatrix();
}

void tree(GLfloat *body_color, GLfloat *leavs){
	glPushMatrix();
	// 木の幹
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, body_color);	
	glutSolidCube(1.0);
	glTranslated(0.0, 1.0, 0.0);
	glutSolidCube(1.0);
	// 木の葉
	glPushMatrix();
	glTranslated(0.0, 0.70, 0.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glRotated(180.0, 0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, leavs);
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

void car(GLfloat *body, GLfloat *tire){

	GLUquadricObj *tire_body;
	GLUquadricObj *tire_cap1;
	GLUquadricObj *tire_cap2;
	tire_body = gluNewQuadric();
	tire_cap1 = gluNewQuadric();
	tire_cap2 = gluNewQuadric();
	float tire_rad = 0.25;
	float tire_height = 1.2;

	glPushMatrix();

	glPushMatrix();
	// 本体(居住部)
//	glTranslated(0.0, 0.20, 0.0);
//	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, body);	
//	glutSolidCube(1.0);
//	glPopMatrix();

	// タイヤ
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, tire);
	//	タイヤふた１
	glPushMatrix();
	glTranslated(5.0, 5.00, 5.0);
	gluDisk(tire_cap1, 0, tire_rad, 20, 20);
	glPopMatrix();
	//	タイヤ本体
	gluCylinder(tire_body, tire_rad, tire_rad, tire_height, 20.0, 20.0);
	//	タイヤふた２
	glPushMatrix();
	gluDisk(tire_cap2, 0, tire_rad, 20, 20);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
}

