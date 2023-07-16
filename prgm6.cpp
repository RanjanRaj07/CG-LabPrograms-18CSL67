/*To draw a simple shaded scene consisting of a tea pot on a table. Define suitably the
position and properties of the light source along with the properties of the surfaces of the
solid object used in the scene.*/

#include <GL/glut.h>
#include <windows.h>
#include <GL/glu.h>

void MyInit() {
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 2, 10);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}
GLfloat T;

void spin() {
	T = T + 0.06;
	if (T > 360)
		T = 0;
	glutPostRedisplay();
} 

void draw() {
	GLfloat pos[] = {1,1,1,1};
	GLfloat col[] = { 0.8,0.8,0.8,1 };

	GLfloat M[] = { 0.95,0.89,0.14,1 };
	GLfloat t[] = {0.8,0.52,0.13 ,0 };
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, col);
	gluLookAt(0,1,3, 0, 0, 0, 0, 1, 0);

	glRotatef(T, 0, 1, 0);
	
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, t); 
	glPushMatrix();
	glScalef(1.1, 0.05, 1.1);
	glutSolidCube(1); 
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.520, -0.5, -0.520);
	glScalef(0.05, 1, 0.05); 
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.520, -0.5, 0.520);
	glScalef(0.05, 1, 0.05);
	glutSolidCube(1); 
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.520, -0.5, 0.520);
	glScalef(0.05, 1, 0.05);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.520, -0.5, -0.520);
	glScalef(0.05, 1, 0.05);
	glutSolidCube(1);
	glPopMatrix();
	glPopAttrib();  

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, M);
	glPushMatrix();
	glTranslatef(0, 0.25, 0);
	glutSolidTeapot(0.25);
	glPopMatrix();
	glPopAttrib(); 
	glutSwapBuffers();
}

int main(int argc,char **argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(75, 50);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Table_and_a_TeaPot");
	MyInit();
	glutDisplayFunc(draw);
	glutIdleFunc(spin);
	glutMainLoop();
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	return 0;
}