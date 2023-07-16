//Draw a colour cube and spin it using OpenGL transformation matrices.
#include<windows.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>

GLfloat d = 0;
int a = 1;

void MyInit()
{
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
}

void Spin()
{
    d = d + 0.05;
    if (d > 360)
        d = 0;
    glutPostRedisplay();
}

void Face(GLfloat A[], GLfloat B[], GLfloat C[], GLfloat D[])
{
   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
    glVertex3fv(A);
    glVertex3fv(B);
    glVertex3fv(C);
    glVertex3fv(D);
    glEnd();
}

void Cube(GLfloat V0[], GLfloat V1[], GLfloat V2[], GLfloat V3[], GLfloat V4[], GLfloat V5[], GLfloat V6[], GLfloat V7[])
{
    glColor3f(0, 1, 0);
    Face(V4, V5, V6, V7); //Back
    glColor3f(1, 0, 0);
    Face(V0, V1, V2, V3); //Front
    glColor3f(0, 0, 1);
    Face(V0, V4, V7, V3); //Left
    glColor3f(1, 1, 0);
    Face(V1, V5, V6, V2); //Right
    glColor3f(1, 0, 1);
    Face(V2, V6, V7, V3); //Bot
    glColor3f(0, 1, 1);
    Face(V0, V1, V5, V4); //Top
}

void Draw()
{
    GLfloat V[8][3] = {
                            {-0.5, 0.5, 0.5},
                            { 0.5, 0.5, 0.5},
                            { 0.5,-0.5, 0.5},
                            {-0.5,-0.5, 0.5},
                            {-0.5, 0.5,-0.5},
                            { 0.5, 0.5,-0.5},
                            { 0.5,-0.5,-0.5},
                            {-0.5,-0.5,-0.5},
    };
    GLfloat rV[8][3], r;
    int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    r = d * 3.14 / 180;

    if (a == 1)
    {
        for (i = 0; i < 8; i++)
        {
            rV[i][0] = V[i][0];
            rV[i][1] = V[i][1] * cos(r) - V[i][2] * sin(r);
            rV[i][2] = V[i][1] * sin(r) + V[i][2] * cos(r);
        }
    }

    if (a == 2)
    {
        for (i = 0; i < 8; i++)
        {
            rV[i][0] = V[i][2] * sin(r) + V[i][0] * cos(r);
            rV[i][1] = V[i][1];
            rV[i][2] = V[i][2] * cos(r) - V[i][0] * sin(r);
        }
    }

    if (a == 3)
    {
        for (i = 0; i < 8; i++)
        {
            rV[i][0] = V[i][0] * cos(r) - V[i][1] * sin(r);
            rV[i][1] = V[i][0] * sin(r) + V[i][1] * cos(r);
            rV[i][2] = V[i][2];
        }
    }
    if (a == 4)
        exit(0);

    Cube(rV[0], rV[1], rV[2], rV[3], rV[4], rV[5], rV[6], rV[7]);

    glutSwapBuffers();
}


void rotate_menu(int option) {
    if (option == 1)
        a = 1;
    if (option == 2)
        a = 2;
    if (option == 3)
        a = 3;
    if (option == 4)
        a = 4;
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(50, 150);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Cube Spin with Matrices");
    MyInit();
    glutDisplayFunc(Draw);
    glutIdleFunc(Spin);
    glutCreateMenu(rotate_menu);
    glutAddMenuEntry("axis = x", 1);
    glutAddMenuEntry("axis = y", 2);
    glutAddMenuEntry("axis = z", 3);
    glutAddMenuEntry("stop", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;
}