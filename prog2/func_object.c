#include <stdlib.h>
#include <GL/glut.h>

void house(GLfloat *body, GLfloat *roof){
	glPushMatrix();

	// 本体(居住部)
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, body);	
	glutSolidCube(1.0);

	// 屋根
	glPushMatrix();
	glTranslated(0.0, 0.70, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, roof);	
	glutSolidCone(00.50, 01.00, 5, 5);
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

