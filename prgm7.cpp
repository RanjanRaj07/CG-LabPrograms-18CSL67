//Design, develop and implement recursively subdivide a tetrahedron to form 3D sierpinski
//gasket.The number of recursive steps is to be specified by the user.
#include <windows.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include<iostream>

int n;

void MyInit() {
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
}

void Triangle(GLfloat A[], GLfloat B[], GLfloat C[]) {
	glBegin(GL_TRIANGLES);
	glVertex3fv(A);
	glVertex3fv(B);
	glVertex3fv(C);
	glEnd();
}

void Tetrahedron(GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat v4[]) {
	glColor3f(1, 1, 1);
	Triangle(v1, v2, v3);
	glColor3f(1,0,0);
	Triangle(v2, v3, v4);
	glColor3f(0, 1, 0);
	Triangle(v1, v2, v4);
	glColor3f(0, 0, 1);
	Triangle(v1, v4, v3); 
}

void Div(GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat v4[],int n) {
	GLfloat v12[3], v23[3], v31[3], v14[3], v24[3], v34[3];

	if (n > 0) {
		v12[0] = (v1[0] + v2[0]) / 2; v12[1] = (v1[1] + v2[1]) / 2; v12[2] = (v1[2] + v2[2]) / 2;
		v23[0] = (v2[0] + v3[0]) / 2; v23[1] = (v2[1] + v3[1]) / 2; v23[2] = (v2[2] + v3[2]) / 2;
		v31[0] = (v3[0] + v1[0]) / 2; v31[1] = (v3[1] + v1[1]) / 2; v31[2] = (v3[2] + v1[2]) / 2;
		v14[0] = (v1[0] + v4[0]) / 2; v14[1] = (v1[1] + v4[1]) / 2; v14[2] = (v1[2] + v4[2]) / 2;
		v24[0] = (v2[0] + v4[0]) / 2; v24[1] = (v2[1] + v4[1]) / 2; v24[2] = (v2[2] + v4[2]) / 2;
		v34[0] = (v3[0] + v4[0]) / 2; v34[1] = (v3[1] + v4[1]) / 2; v34[2] = (v3[2] + v4[2]) / 2;
		Div(v1, v12, v31, v14, n - 1);
		Div(v12, v2, v23, v24, n - 1);
		Div(v31, v23, v3, v34, n - 1);
		Div(v14, v24, v34, v4, n - 1);
	}
	else
		Tetrahedron(v1, v2, v3, v4);
}

void draw() {
	GLfloat p[4][3] = {
		{-0.5,-0.5,0.5},
		{0.5,-0.5,0.5},
		{0.0,0.5,0.5},
		{0.0,0.0,-0.5},
	};
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Div(p[0], p[1], p[2], p[3], n);
	glutSwapBuffers();
}

int main(int argc, char* argv[]) {
	std::cout<<"enter the number of division steps :\t";
	std::cin>>n;
	glutInit(&argc, argv);
	glutInitWindowPosition(75, 50);
	glutInitWindowSize(600, 600);
	MyInit();
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("3D sirepinski gasket");
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}