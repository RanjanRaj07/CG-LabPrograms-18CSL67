//Create and rotate a triangle about the origin and a fixed point.
#include <GL/glut.h>
#include <Windows.h>
#include <iostream>

using namespace std;
GLint x, y,translate_x,translate_y;
GLfloat r_angle;
int where_to_rotate = 0;

void myInit() {
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-800, 800, -800, 800);
	glMatrixMode(GL_MODELVIEW);
}

void setPixel(GLint x, GLint y) {
	glPointSize(5);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void drawTriangle(GLint x, GLint y) {
	glColor3f(0, 1, 0); 
	glBegin(GL_TRIANGLES);
	glVertex2i(x, y);
	glVertex2i(x + 300, y);
	glVertex2i(x + 400, x + 400);
	glEnd();
	glFlush();
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glColor3f(1, 0, 0);
	setPixel(0, 0);

	if (where_to_rotate == 1) {
		translate_x = 0;
		translate_y = 0;
		r_angle += 0.8;
	}

	if (where_to_rotate == 2) {
		translate_x = x;
		translate_y = y;
		r_angle += 0.8;
		glColor3f(0, 0, 1);
		setPixel(x, y);
	}

	glTranslatef(translate_x, translate_y, 0);
	glRotatef(r_angle, 0, 0, 1);
	glTranslatef(-translate_x, -translate_y, 0);

	drawTriangle(x, y);
	glutPostRedisplay();
	glutSwapBuffers();
}
void Rotate(int id) {
	if (id == 1)
		where_to_rotate = 1;
	else if (id == 2)
		where_to_rotate = 2;
	else
		where_to_rotate = 3;
	display();
}
void main(int argc, char* argv[]) {
	cout << "enter the fixed point for rotation" << endl;
	cin >> x >> y;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("triangle rotation");
	myInit(); 
	glutDisplayFunc(display);
	glutCreateMenu(Rotate);
	glutAddMenuEntry("rotate about origin", 1);
	glutAddMenuEntry("rotate about fixedpoint", 2);
	glutAddMenuEntry("stop rotation", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON); 
	glutMainLoop();
}