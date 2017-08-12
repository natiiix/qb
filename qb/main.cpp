#include <Windows.h>
#include <GL\freeglut.h>
#include <iostream>
#include "ObjectGL.hpp"
#include <chrono>
#define _USE_MATH_DEFINES
#include <math.h>

static float timePassed = 0.0;
static bool loopFirst = true;
static std::chrono::time_point<std::chrono::steady_clock> loopTime;

static bool keyW = false;
static bool keyS = false;
static bool keyA = false;
static bool keyD = false;
static bool keySpace = false;
static bool keyLCtrl = false;

static float posX = 0.0f;
static float posY = 0.0f;
static float posZ = 0.0f;

static float rotX = 0.0f;
static float rotY = 0.0f;

static int windowWidth = 800;
static int windowHeight = 600;

void resetMousePos(void)
{
	glutWarpPointer(windowWidth / 2, windowHeight / 2);
}

float clampAngleDeg(const float angle)
{
	float clamped = angle;

	while (clamped < 0.0f)
	{
		clamped += 360.0f;
	}

	while (clamped >= 360.0f)
	{
		clamped -= 360.0f;
	}

	return clamped;
}

float degToRad(const float angle)
{
	return angle * (float)M_PI / 180.0f;
}

unsigned char ignoreModifiers(const unsigned char ascii)
{
	int modifiers = glutGetModifiers();

	if (modifiers & GLUT_ACTIVE_CTRL &&
		ascii >= 1 && ascii <= 26)
	{
		return ascii - 1 + 'a';
	}

	if (modifiers & GLUT_ACTIVE_SHIFT &&
		ascii >= 'A' && ascii <= 'Z')
	{
		return ascii | 0x20;
	}

	return ascii;
}

float getDeltaTime(void)
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
	windowWidth = w;
	windowHeight = h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0, (GLdouble)w / (GLdouble)h, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void fDisplay(void)
{
	float deltaTime = getDeltaTime();
	//std::cout << "FPS: " << 1.0f / deltaTime << std::endl;
	timePassed += deltaTime;

	const float movementFactor = deltaTime * 10.0f;

	if (keyW != keyS)
	{
		const float direction = keyW ? -1.0f : 1.0f;

		posX += movementFactor * direction * -sin(degToRad(rotY));
		posZ += movementFactor * direction * cos(degToRad(rotY));
	}

	if (keyA != keyD)
	{
		const float direction = keyA ? -1.0f : 1.0f;

		posX += movementFactor * direction * cos(degToRad(rotY));
		posZ += movementFactor * direction * sin(degToRad(rotY));
	}

	if (keySpace != keyLCtrl)
	{
		const float direction = keySpace ? 1.0f : -1.0f;

		posY += movementFactor * direction;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	glRotatef(rotX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotY, 0.0f, 1.0f, 0.0f);
	glTranslatef(-posX, -posY - 10.0f, -posZ - 20.0f);

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			CubeGL cube((float)i - 20.0f, 0.0f, (float)-j, 1.0f, 1.0f, 1.0f);
			//cube.Rotate(timePassed * 30.0f, timePassed * 15.0f, timePassed * 20.0f);
			cube.Draw();
		}
	}

	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();
}

void setKeyState(const unsigned char key, const bool state)
{
	unsigned char keyNoMod = ignoreModifiers(key);

	switch (keyNoMod)
	{
	case 27:
		glutExit();
		exit(0);
		break;

	case 'w':
		keyW = state;
		break;

	case 's':
		keyS = state;
		break;

	case 'a':
		keyA = state;
		break;

	case 'd':
		keyD = state;
		break;

	case ' ':
		keySpace = state;
		break;

	default:
		break;
	}
}

void fKeyboard(const unsigned char key, const int x, const int y)
{
	std::cout << "DOWN: " << (int)key << ' ' << x << ' ' << y << std::endl;
	setKeyState(key, true);
}

void fKeyboardUp(const unsigned char key, const int x, const int y)
{
	std::cout << "UP: " << (int)key << ' ' << x << ' ' << y << std::endl;
	setKeyState(key, false);
}

void fSpecial(const int key, const int x, const int y)
{
	std::cout << "SPECIAL DOWN: " << key << ' ' << x << ' ' << y << std::endl;

	if (key == GLUT_KEY_CTRL_L)
	{
		keyLCtrl = true;
	}
}

void fSpecialUp(const int key, const int x, const int y)
{
	std::cout << "SPECIAL UP: " << key << ' ' << x << ' ' << y << std::endl;

	if (key == GLUT_KEY_CTRL_L)
	{
		keyLCtrl = false;
	}
}

void fMouse(const int button, const int state, const int x, const int y)
{
	std::cout << "MOUSE: " << button << ' ' << state << ' ' << x << ' ' << y << std::endl;
}

void fMotion(int x, int y)
{
	//std::cout << x << ' ' << y << std::endl;

	int windowWidthHalf = windowWidth / 2;
	int windowHeightHalf = windowHeight / 2;

	int xOffset = x - windowWidthHalf;
	int yOffset = y - windowHeightHalf;

	if (xOffset || yOffset)
	{
		rotX = clampAngleDeg(rotX + (yOffset * 0.1f));
		rotY = clampAngleDeg(rotY + (xOffset * 0.1f));

		resetMousePos();
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("qb");
		
	glutReshapeFunc(fReshape);
	glutDisplayFunc(fDisplay);
	glutKeyboardFunc(fKeyboard);
	glutKeyboardUpFunc(fKeyboardUp);
	glutSpecialFunc(fSpecial);
	glutSpecialUpFunc(fSpecialUp);
	glutIgnoreKeyRepeat(true);
	glutMouseFunc(fMouse);
	glutMotionFunc(fMotion);
	glutPassiveMotionFunc(fMotion);

	//glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE);
	resetMousePos();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat ambientColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	GLfloat lightColor0[] = { 0.0f, 0.8f, 1.0f, 1.0f };
	GLfloat lightPos0[] = { 0.0f, 100000.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
	glShadeModel(GL_SMOOTH);

	glutMainLoop();
	return -1;
}
