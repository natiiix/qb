#include <Windows.h>
#include <GL\freeglut.h>
#include <iostream>

void fReshape(const int w, const int h)
{
	glViewport(0, 0, w, h);
}

void fDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	glTranslatef(0.0f, 0.0f, -5.0f);

	glBegin(GL_QUADS);

	glColor3f(0.5f, 0.0f, 0.0f);

	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);

	glColor3f(0.0, 0.5, 0.0);

	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, -1.0);

	glColor3f(0.0, 0.0, 0.5);

	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, 1.0, 1.0);
	glVertex3f(1.0, 1.0, -1.0);

	glColor3f(0.5f, 0.0f, 0.0f);

	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);

	glColor3f(0.0, 0.5, 0.0);

	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, -1.0);

	glColor3f(0.0, 0.0, 0.5);

	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(-1.0, -1.0, 1.0);
	glVertex3f(-1.0, 1.0, 1.0);
	glVertex3f(-1.0, 1.0, -1.0);

	glEnd();

	glPopMatrix();
	glutSwapBuffers();
}

void fKeyboard(const unsigned char key, const int x, const int y)
{
	std::cout << "DOWN: " << (int)key << ' ' << x << ' ' << y << std::endl;
}

void fKeyboardUp(const unsigned char key, const int x, const int y)
{
	std::cout << "UP: " << (int)key << ' ' << x << ' ' << y << std::endl;
}

void fMouse(const int button, const int state, const int x, const int y)
{
	std::cout << "MOUSE: " << button << ' ' << state << ' ' << x << ' ' << y << std::endl;
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("qb");
	
	glutReshapeFunc(fReshape);
	glutDisplayFunc(fDisplay);
	glutKeyboardFunc(fKeyboard);
	glutKeyboardUpFunc(fKeyboardUp);
	glutMouseFunc(fMouse);

	glutFullScreen();

	gluPerspective(45.0, 800.0f / 600.0f, 0.1, 50.0);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

	glutMainLoop();
	return -1;
}
