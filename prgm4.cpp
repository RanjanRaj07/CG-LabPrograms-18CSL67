//Draw a color cube and allow the user to move the camera suitably to experiment with perspective viewing.
#include<windows.h>
#include<GL/glu.h>
#include<GL/glut.h>

GLdouble cx=0, cy=0, cz=3;

void MyInit() {
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 2, 10); 
	glMatrixMode(GL_MODELVIEW);
}

void square(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[]) {
	glBegin(GL_POLYGON);
	glVertex3fv(A);
	glVertex3fv(B);
	glVertex3fv(C);
	glVertex3fv(D);
	glEnd();
}

void cube(GLfloat v0[], GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat v4[], GLfloat v5[], GLfloat v6[], GLfloat v7[]) {
	glColor3f(1, 0, 0);
	square(v0, v1, v2, v3);
	glColor3f(0, 1, 0);
	square(v4, v5, v6, v7);
	glColor3f(0, 0, 1);
	square(v1, v5, v6, v2);
	glColor3f(1, 1, 0);
	square(v0, v4, v7, v3);
	glColor3f(1, 0, 1);
	square(v3, v2, v6, v7);
	glColor3f(0, 1, 1);
	square(v1, v5, v4, v0);
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat v[8][3] = {
		{-0.5,0.5,0.5},
		{0.5,0.5,0.5},
		{0.5,-0.5,0.5},
		{-0.5,-0.5,0.5},
		{-0.5,0.5,-0.5},
		{0.5,0.5,-0.5},
		{0.5,-0.5,-0.5},
		{-0.5,-0.5,-0.5}
	};

	glLoadIdentity();
	gluLookAt(cx, cy, cz, 0, 0, 0, 0, 1, 0);

	cube(v[0], v[1], v[2], v[3], v[4], v[5], v[6], v[7]);

	glutSwapBuffers();
}

void key(unsigned char ch, int x, int y) {
	switch (ch) {
	case 'x': cx = cx - 0.5; break;
	case 'X': cx = cx + 0.5; break;

	case 'y': cy = cy - 0.5; break;
	case 'Y': cy = cy + 0.5; break;

	case 'z': cz = cz - 0.5; break;
	case 'Z': cz = cz + 0.5; break;
	}
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowPosition(75, 50);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("perspective viewing");
	MyInit();
	glutDisplayFunc(draw);
	glutKeyboardUpFunc(key);
	glutMainLoop();
	return 0;
}