//Develop a menu driven program to fill the polygon using scan line algorithm
#include <windows.h>
#include <GL/glut.h>
#include <GL/glu.h>

int LE[500], RE[500];
int edgeFill = 0, fillFlag = 0;

void menu(int id) {
	if (id == 1)
		edgeFill = 1;
	else if (id == 2)
		edgeFill = 0;
	else if (id == 3)
		exit(0);
	fillFlag = 1;
	glutPostRedisplay();
}
void MyInit() {
	glClearColor(0, 0, 0, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0,500);
	glMatrixMode(GL_MODELVIEW);

	glutCreateMenu(menu);
	glutAddMenuEntry("with edge", 1);
	glutAddMenuEntry("without edge", 2);
	glutAddMenuEntry("exit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);   
}

void Intersection(GLint x1, GLint y1, GLint x2, GLint y2) {
	float x, M;
	int t, y;
	if (y1 > y2) {
		t = x1;
		x1 = x2;
		x2 = t;
		t = y1;
		y1 = y2;
		y2 = t; 
	}
	if ((y2 - y1) == 0)
		M = x2 - x1;
	else
		M = (x2 - x1) / (y2 - y1);
	x = x1;
	for (y = y1; y < y2; y++) {
		if (x < LE[y])
			LE[y] = x;
		if (x > RE[y])
			RE[y] = x;

		x = x + M;
	}
}

void draw() {
	GLint p1[2] = { 125,250 }, p2[2] = { 250,125 }, p3[2] = { 375,250 }, p4[2] = { 250,375 };
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 1);
	for (int i = 0; i < 500; i++) {
		LE[i] = 500;
		RE[i] = 0;
	}
	if (edgeFill == 1) {
		glBegin(GL_LINE_LOOP);
		glVertex2iv(p1);
		glVertex2iv(p2);
		glVertex2iv(p3);
		glVertex2iv(p4);
		glEnd();

	}
	Intersection(p1[0], p1[1], p2[0], p2[1]);
	Intersection(p2[0], p2[1], p3[0], p3[1]);
	Intersection(p3[0], p3[1], p4[0], p4[1]);
	Intersection(p4[0], p4[1], p1[0], p1[1]);
	if(fillFlag==1){
	for (int y = 0; y < 500; y++) {
		for (int x = LE[y]; x <RE[y]; x++) {
			glBegin(GL_POINTS);
			glVertex2i(x, y);
			glEnd();
			glFlush(); 
		}
	}
	}
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitWindowPosition(75, 50);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("2D Scan Line fill"); 
	MyInit(); 
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}