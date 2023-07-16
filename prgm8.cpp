//Develop a menu driven program to animate a flag using Bezier Curve algorithm
#include <GL/glut.h>
#include <GL/glu.h>
#include <Windows.h>
#include <math.h>

GLfloat xa = 10, ya = 50;
int yflag = 1, xflag = 1, aniflag = 1;
void Animate() {
	if (aniflag == 1) {
		if (ya > -50 && yflag == 1)
			ya = ya - 0.1;
		if (ya <= -50 && yflag == 1)
			yflag = 0;
		if (ya < 50 && yflag == 0)
			ya = ya + 0.1;
		if (ya >= 50 && yflag == 0)
			yflag = 1;

		if (xa > -10 && xflag == 1)
			xa = xa - 0.1;
		if (xa <= -10 && xflag == 1)
			xflag = 0;
		if (xa < 10 && xflag == 0)
			xa = xa + 0.1;
		if (xa >= 10 && xflag == 0)
			xflag = 1;
	}
	glutPostRedisplay();
}

void draw() {
	GLfloat x[4], y1[4], y2[4], y3[4];
	GLdouble xt[200], y1t[200], y2t[200], y3t[200], t;
	int i, c;
	glClear(GL_COLOR_BUFFER_BIT);
	x[0] = 100; x[1] = 175+(xa); x[2] = 250+(xa/2); x[3] = 300+(xa/10);
	y1[0] = 450; y1[1] = 450 + ya; y1[2] = 450 - ya; y1[3] = 450 + (ya / 2);
	y2[0] = 400; y2[1] = 400 + ya; y2[2] = 400 - ya; y2[3] = 400 + (ya / 2);
	y3[0] = 350; y3[1] = 350 + ya; y3[2] = 350 - ya; y3[3] = 350 + (ya / 2);

	for (i = 0, t = 0, c = 0; t < 1; i++, t = t + 0.02) {
		xt[i] = pow(1 - t, 3) * x[0] + 3 * t * pow(1 - t, 2) * x[1] + 3 * pow(t, 2) * (1 - t) * x[2] + pow(t, 3) * x[3];
		y1t[i] = pow(1 - t, 3) * y1[0] + 3 * t * pow(1 - t, 2) * y1[1] + 3 * pow(t, 2) * (1 - t) * y1[2] + pow(t, 3) * y1[3];
		y2t[i] = pow(1 - t, 3) * y2[0] + 3 * t * pow(1 - t, 2) * y2[1] + 3 * pow(t, 2) * (1 - t) * y2[2] + pow(t, 3) * y2[3];
		y3t[i] = pow(1 - t, 3) * y3[0] + 3 * t * pow(1 - t, 2) * y3[1] + 3 * pow(t, 2) * (1 - t) * y3[2] + pow(t, 3) * y3[3];
		c++;
	}
	glColor3f(1, 1, 0);
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i < c; i++) {
		glVertex2d(xt[i], y1t[i]);
		glVertex2d(xt[i], y2t[i]);
	}
	glEnd();
	glColor3f(1, 0, 0);
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i < c; i++) {
		glVertex2d(xt[i], y2t[i]);
		glVertex2d(xt[i], y3t[i]);
	}
	glEnd();
	glColor3f(0.8, 0.6, 0.4);
	glRecti(90, 460, 100, 50);
	glutSwapBuffers();
}

void menu(int n) {
	if (n == 1)
		aniflag = 1;
	else if (n == 2)
		aniflag = 0;
	else if (n == 3)
		exit(0);
	glutPostRedisplay();
}

void MyInit()
{
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);

	glutCreateMenu(menu);
	glutAddMenuEntry("Start", 1);
	glutAddMenuEntry("Stop", 2);
	glutAddMenuEntry("Exit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argC, char* argV[])
{
	glutInit(&argC, argV);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Animate Flag");
	MyInit();
	glutDisplayFunc(draw);
	glutIdleFunc(Animate);
	glutMainLoop();
	return 0;
}