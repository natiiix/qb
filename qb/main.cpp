#include <Windows.h>
#include <GL\freeglut.h>
#include <iostream>
#include "ObjectGL.hpp"
#include <chrono>

static float timePassed = 0.0;
static bool loopFirst = true;
static std::chrono::time_point<std::chrono::steady_clock> loopTime;

float getDeltaTime()
{
	float deltaTime = 0.0;
	std::chrono::time_point<std::chrono::steady_clock> nowTime = std::chrono::steady_clock::now();

	if (loopFirst)
		loopFirst = false;
	else
		deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(nowTime - loopTime).count();

	loopTime = nowTime;

	return deltaTime;
}

void fReshape(const int w, const int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0, (GLdouble)w / (GLdouble)h, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void fDisplay()
{
	float deltaTime = getDeltaTime();
	std::cout << "FPS: " << 1.0f / deltaTime << std::endl;
	timePassed += deltaTime;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				CubeGL cube((float)i - 10.0f, (float)j - 10.0f, (float)-k - 20.0f, 0.3f, 0.3f, 0.3f);
				cube.Rotate(timePassed * 30.0f, timePassed * 15.0f, timePassed * 20.0f);
				cube.Draw();
			}
		}
	}

	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();
}

void fKeyboard(const unsigned char key, const int x, const int y)
{
	std::cout << "DOWN: " << (int)key << ' ' << x << ' ' << y << std::endl;

	if (key == 27)
	{
		glutExit();
		exit(0);
	}
}

void fKeyboardUp(const unsigned char key, const int x, const int y)
{
	std::cout << "UP: " << (int)key << ' ' << x << ' ' << y << std::endl;
}

void fMouse(const int button, const int state, const int x, const int y)
{
	std::cout << "MOUSE: " << button << ' ' << state << ' ' << x << ' ' << y << std::endl;
}

void fMotion(int a, int b)
{
	//std::cout << a << ' ' << b << std::endl;
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("qb");
	
	glutReshapeFunc(fReshape);
	glutDisplayFunc(fDisplay);
	glutKeyboardFunc(fKeyboard);
	glutKeyboardUpFunc(fKeyboardUp);
	glutMouseFunc(fMouse);
	glutMotionFunc(fMotion);
	glutPassiveMotionFunc(fMotion);

	//glutFullScreen();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	GLfloat ambientColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	GLfloat lightColor0[] = { 0.0f, 0.8f, 0.8f, 1.0f };
	GLfloat lightPos0[] = { -10.0, -10.0f, 10.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	GLfloat lightColor1[] = { 1.0f, 0.5f, 0.5f, 1.0f };
	GLfloat lightPos1[] = { 10.0f, 10.0f, 10.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
	glShadeModel(GL_SMOOTH);

	glutMainLoop();
	return -1;
}
