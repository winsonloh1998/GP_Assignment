#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "Optimus Prime"

float leftArmUpSpeed = 0.0;
int leftArmUpStatus = 0;

float rightArmUpSpeed = 0.0;
int rightArmUpStatus = 0;
LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			PostQuitMessage(0);
		else if (wParam == VK_LEFT)
			glRotatef(1, 0, 1, 0);
		else if (wParam == VK_RIGHT)
			glRotatef(-1, 0, 1, 0);
		else if (wParam == VK_UP)
			glRotatef(-1, 1, 0, 0);
		else if (wParam == VK_DOWN)
			glRotatef(1, 1, 0, 0);
		else if (wParam == 'L')
			leftArmUpStatus = 1;
		else if (wParam == 'R')
			rightArmUpStatus = 1;
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------
void shoePart1() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, -1.9, -0.4);
	glVertex3f(-0.1, -1.9, -0.4);
	glVertex3f(-0.1, -2, -0.4);
	glVertex3f(-0.4, -2, -0.4);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, -2, -0.4);
	glVertex3f(-0.4, -2, -0.2);
	glVertex3f(-0.4, -1.7, -0.3);
	glVertex3f(-0.4, -1.9, -0.4);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, -1.9, -0.4);
	glVertex3f(-0.4, -1.7, -0.3);
	glVertex3f(-0.1, -1.7, -0.3);
	glVertex3f(-0.1, -1.9, -0.4);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -1.9, -0.4);
	glVertex3f(-0.1, -1.7, -0.3);
	glVertex3f(-0.1, -2, -0.2);
	glVertex3f(-0.1, -2, -0.4);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -2, -0.4);
	glVertex3f(-0.4, -2, -0.4);
	glVertex3f(-0.4, -2, -0.2);
	glVertex3f(-0.1, -2, -0.2);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -2, -0.2);
	glVertex3f(-0.4, -2, -0.2);
	glVertex3f(-0.4, -1.7, -0.3);
	glVertex3f(-0.1, -1.7, -0.3);
	glEnd();
}

void shoePart2() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, -1.6, -0.3);
	glVertex3f(-0.1, -1.6, -0.3);
	glVertex3f(-0.1, -1.7, -0.3);
	glVertex3f(-0.4, -1.7, -0.3);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, -1.7, -0.3);
	glVertex3f(-0.4, -2, -0.2);
	glVertex3f(-0.4, -1.9, -0.2);
	glVertex3f(-0.4, -1.6, -0.3);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, -1.6, -0.3);
	glVertex3f(-0.4, -1.9, -0.2);
	glVertex3f(-0.1, -1.9, -0.2);
	glVertex3f(-0.1, -1.6, -0.3);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -1.6, -0.3);
	glVertex3f(-0.1, -1.9, -0.2);
	glVertex3f(-0.1, -2, -0.2);
	glVertex3f(-0.1, -1.7, -0.3);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -1.7, -0.3);
	glVertex3f(-0.4, -1.7, -0.3);
	glVertex3f(-0.4, -2, -0.2);
	glVertex3f(-0.1, -2, -0.2);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -2, -0.2);
	glVertex3f(-0.4, -2, -0.2);
	glVertex3f(-0.4, -1.9, -0.2);
	glVertex3f(-0.1, -1.9, -0.2);
	glEnd();
}

void shoePart3() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, -1.4, -0.26);
	glVertex3f(-0.1, -1.4, -0.26);
	glVertex3f(-0.1, -1.6, -0.3);
	glVertex3f(-0.4, -1.6, -0.3);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, -1.6, -0.3);
	glVertex3f(-0.4, -1.9, -0.2);
	glVertex3f(-0.4, -1.4, -0.2);
	glVertex3f(-0.4, -1.4, -0.26);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, -1.4, -0.26);
	glVertex3f(-0.4, -1.4, -0.2);
	glVertex3f(-0.1, -1.4, -0.2);
	glVertex3f(-0.1, -1.4, -0.26);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -1.4, -0.26);
	glVertex3f(-0.1, -1.4, -0.2);
	glVertex3f(-0.1, -1.9, -0.2);
	glVertex3f(-0.1, -1.6, -0.3);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -1.6, -0.3);
	glVertex3f(-0.4, -1.6, -0.3);
	glVertex3f(-0.4, -1.9, -0.2);
	glVertex3f(-0.1, -1.9, -0.2);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -1.9, -0.2);
	glVertex3f(-0.4, -1.9, -0.2);
	glVertex3f(-0.4, -1.4, -0.2);
	glVertex3f(-0.1, -1.4, -0.2);
	glEnd();
}

void legArmor1() {
	//Front 1
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, -0.75, -0.28);
	glVertex3f(-0.35, -0.75, -0.28);
	glVertex3f(-0.35, -1.4, -0.28);
	glVertex3f(-0.4, -1.4, -0.28);
	glEnd();

	//Front 2
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.35, -0.95, -0.28);
	glVertex3f(-0.15, -0.95, -0.28);
	glVertex3f(-0.15, -1.1, -0.28);
	glVertex3f(-0.35, -1.1, -0.28);
	glEnd();

	//Front 3
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.75, -0.28);
	glVertex3f(-0.1, -0.75, -0.28);
	glVertex3f(-0.1, -1.4, -0.28);
	glVertex3f(-0.15, -1.4, -0.28);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, -1.4, -0.28);
	glVertex3f(-0.4, -1.4, -0.2);
	glVertex3f(-0.4, -0.75, -0.2);
	glVertex3f(-0.4, -0.75, -0.28);
	glEnd();

	//Top 1
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, -0.75, -0.28);
	glVertex3f(-0.4, -0.75, -0.2);
	glVertex3f(-0.35, -0.75, -0.2);
	glVertex3f(-0.35, -0.75, -0.28);
	glEnd();

	//Top 2
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.35, -0.75, -0.28);
	glVertex3f(-0.35, -0.75, -0.2);
	glVertex3f(-0.35, -0.95, -0.2);
	glVertex3f(-0.35, -0.95, -0.28);
	glEnd();

	//Top 3
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.35, -0.95, -0.28);
	glVertex3f(-0.35, -0.95, -0.2);
	glVertex3f(-0.15, -0.95, -0.2);
	glVertex3f(-0.15, -0.95, -0.28);
	glEnd();

	//Top 4
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.95, -0.28);
	glVertex3f(-0.15, -0.95, -0.2);
	glVertex3f(-0.15, -0.75, -0.2);
	glVertex3f(-0.15, -0.75, -0.28);
	glEnd();

	//Top 5
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.75, -0.28);
	glVertex3f(-0.15, -0.75, -0.2);
	glVertex3f(-0.1, -0.75, -0.2);
	glVertex3f(-0.1, -0.75, -0.28);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.75, -0.28);
	glVertex3f(-0.1, -0.75, -0.2);
	glVertex3f(-0.1, -1.4, -0.2);
	glVertex3f(-0.1, -1.4, -0.28);
	glEnd();

	//Bottom 1
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -1.4, -0.28);
	glVertex3f(-0.1, -1.4, -0.2);
	glVertex3f(-0.15, -1.4, -0.2);
	glVertex3f(-0.15, -1.4, -0.28);
	glEnd();

	//Bottom 2
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -1.4, -0.28);
	glVertex3f(-0.15, -1.4, -0.2);
	glVertex3f(-0.15, -1.1, -0.2);
	glVertex3f(-0.15, -1.1, -0.28);
	glEnd();

	//Bottom 3
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -1.1, -0.28);
	glVertex3f(-0.15, -1.1, -0.2);
	glVertex3f(-0.35, -1.1, -0.2);
	glVertex3f(-0.35, -1.1, -0.28);
	glEnd();

	//Bottom 4
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.35, -1.1, -0.28);
	glVertex3f(-0.35, -1.1, -0.2);
	glVertex3f(-0.35, -1.4, -0.2);
	glVertex3f(-0.35, -1.4, -0.28);
	glEnd();

	//Bottom 5
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.35, -1.4, -0.28);
	glVertex3f(-0.4, -1.4, -0.28);
	glVertex3f(-0.4, -1.4, -0.2);
	glVertex3f(-0.35, -1.4, -0.2);
	glEnd();

	//Back 1
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, -0.75, -0.2);
	glVertex3f(-0.35, -0.75, -0.2);
	glVertex3f(-0.35, -1.4, -0.2);
	glVertex3f(-0.4, -1.4, -0.2);
	glEnd();

	//Back 2
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.35, -0.95, -0.2);
	glVertex3f(-0.15, -0.95, -0.2);
	glVertex3f(-0.15, -1.1, -0.2);
	glVertex3f(-0.35, -1.1, -0.2);
	glEnd();

	//Back 3
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.75, -0.2);
	glVertex3f(-0.1, -0.75, -0.2);
	glVertex3f(-0.1, -1.4, -0.2);
	glVertex3f(-0.15, -1.4, -0.2);
	glEnd();

	//Metal Plate 1 
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.35, -1.1, -0.25);
	glVertex3f(-0.15, -1.1, -0.25);
	glVertex3f(-0.15, -1.17, -0.25);
	glVertex3f(-0.35, -1.17, -0.25);
	glEnd();

	//Metal Plate 2
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.35, -1.175, -0.25);
	glVertex3f(-0.15, -1.175, -0.25);
	glVertex3f(-0.15, -1.245, -0.25);
	glVertex3f(-0.35, -1.245, -0.25);
	glEnd();

	//Metal Plate 3
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.35, -1.25, -0.25);
	glVertex3f(-0.15, -1.25, -0.25);
	glVertex3f(-0.15, -1.32, -0.25);
	glVertex3f(-0.35, -1.32, -0.25);
	glEnd();

	//Metal Plate 4
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.35, -1.325, -0.25);
	glVertex3f(-0.15, -1.325, -0.25);
	glVertex3f(-0.15, -1.395, -0.25);
	glVertex3f(-0.35, -1.395, -0.25);
	glEnd();
}

void legArmor2() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.7, -0.2);
	glVertex3f(-0.1, -0.7, -0.2);
	glVertex3f(-0.1, -2, -0.2);
	glVertex3f(-0.15, -2, -0.2);
	glEnd();

	//Left 1
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.7, -0.2);
	glVertex3f(-0.15, -0.7, -0.15);
	glVertex3f(-0.15, -2, -0.15);
	glVertex3f(-0.15, -2, -0.2);
	glEnd();

	//Left 2
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.7, -0.15);
	glVertex3f(-0.15, -0.7, 0.2);
	glVertex3f(-0.15, -1, 0.2);
	glVertex3f(-0.15, -1, -0.15);
	glEnd();

	//Left 3
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -1.5, -0.15);
	glVertex3f(-0.15, -1.5, 0.2);
	glVertex3f(-0.15, -1.6, 0.2);
	glVertex3f(-0.15, -1.6, -0.15);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.7, -0.2);
	glVertex3f(-0.15, -0.7, 0.2);
	glVertex3f(-0.1, -0.7, 0.2);
	glVertex3f(-0.1, -0.7, -0.2);
	glEnd();

	//Right 1
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.7, -0.2);
	glVertex3f(-0.1, -0.7, -0.15);
	glVertex3f(-0.1, -2, -0.15);
	glVertex3f(-0.1, -2, -0.2);
	glEnd();

	//Right 2
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.7, -0.15);
	glVertex3f(-0.1, -0.7, 0.2);
	glVertex3f(-0.1, -1, 0.2);
	glVertex3f(-0.1, -1, -0.15);
	glEnd();

	//Right 3
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -1.5, -0.15);
	glVertex3f(-0.1, -1.5, 0.2);
	glVertex3f(-0.1, -1.6, 0.2);
	glVertex3f(-0.1, -1.6, -0.15);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -2, -0.2);
	glVertex3f(-0.15, -2, 0.2);
	glVertex3f(-0.1, -2, 0.2);
	glVertex3f(-0.1, -2, -0.2);
	glEnd();

	//Back 1
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.7, -0.2);
	glVertex3f(-0.15, -0.7, -0.2);
	glVertex3f(-0.15, -1, -0.2);
	glVertex3f(-0.1, -1, -0.2);
	glEnd();

	//Back 2
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -1, 0.2);
	glVertex3f(-0.15, -1, 0.2);
	glVertex3f(-0.15, -1, -0.15);
	glVertex3f(-0.1, -1, -0.15);
	glEnd();

	//Back 3
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -1, -0.15);
	glVertex3f(-0.15, -1, -0.15);
	glVertex3f(-0.15, -1.5, -0.15);
	glVertex3f(-0.1, -1.5, -0.15);
	glEnd();

	//Back 4
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -1.5, -0.15);
	glVertex3f(-0.15, -1.5, -0.15);
	glVertex3f(-0.15, -1.5, 0.2);
	glVertex3f(-0.1, -1.5, 0.2);
	glEnd();

	//Back 5
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -1.5, 0.2);
	glVertex3f(-0.15, -1.5, 0.2);
	glVertex3f(-0.15, -1.6, 0.2);
	glVertex3f(-0.1, -1.6, 0.2);
	glEnd();

	//Back 6
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -1.6, 0.2);
	glVertex3f(-0.15, -1.6, 0.2);
	glVertex3f(-0.15, -1.6, -0.15);
	glVertex3f(-0.1, -1.6, -0.15);
	glEnd();

	//Back 7
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -1.6, -0.15);
	glVertex3f(-0.15, -1.6, -0.15);
	glVertex3f(-0.15, -2, -0.15);
	glVertex3f(-0.1, -2, -0.15);
	glEnd();

	//Back 8
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -2, -0.15);
	glVertex3f(-0.15, -2, -0.15);
	glVertex3f(-0.15, -2, 0.2);
	glVertex3f(-0.1, -2, 0.2);
	glEnd();
}

void legArmor3() {
	GLUquadricObj *legCylinder = NULL;
	legCylinder = gluNewQuadric();

	glPushMatrix();
	glTranslatef(-0.4, -0.75, 0);
	glRotatef(90, 1, 0, 0);
	gluQuadricDrawStyle(legCylinder, GLU_LINE);
	gluCylinder(legCylinder, 0.05, 0.05, 0.3, 20, 20);
	gluDeleteQuadric(legCylinder);
	glPopMatrix();
}

void legArmor4() {
	//Strap Above
	glBegin(GL_POLYGON);
	glVertex3f(-0.4, -0.99, 0.2);
	glVertex3f(-0.1, -0.99, 0.2);
	glVertex3f(-0.1, -1.01, 0.2);
	glVertex3f(-0.4, -1.01, 0.2);
	glEnd();

	//Strap Below
	glBegin(GL_POLYGON);
	glVertex3f(-0.4, -1.5, 0.2);
	glVertex3f(-0.1, -1.5, 0.2);
	glVertex3f(-0.1, -1.6, 0.2);
	glVertex3f(-0.4, -1.6, 0.2);
	glEnd();
}

void legTyre() {
	//Tyre Above 
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++)
	{
		float degInRad = i * (3.14159 / 180);
		glColor3f(0, 0, 0);
		glVertex3f(-0.45, (sin(degInRad)*(0.15 + 0.05)) - 1.3, (cos(degInRad)*(0.15 - 0.02)) + 0.1);
	}
	glEnd();

	glColor3f(1, 1, 1);
	GLUquadricObj *legTyre1 = NULL;
	legTyre1 = gluNewQuadric();

	glPushMatrix();
	glTranslatef(-0.45, -1.3, 0.1);
	glScalef(1, 1, 0.65);
	glRotatef(90, 0, 1, 0);
	gluQuadricDrawStyle(legTyre1, GLU_LINE);
	gluCylinder(legTyre1, 0.2, 0.2, 0.15, 20, 20);
	gluDeleteQuadric(legTyre1);
	glPopMatrix();


	//Tyre Below 
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++)
	{
		float degInRad = i * (3.14159 / 180);
		glColor3f(0, 0, 0);
		glVertex3f(-0.45, (sin(degInRad)*(0.15 + 0.05)) - 1.75, (cos(degInRad)*(0.15 - 0.02)) + 0.1);
	}
	glEnd();

	glColor3f(1, 1, 1);
	GLUquadricObj *legTyre2 = NULL;
	legTyre2 = gluNewQuadric();

	glPushMatrix();
	glTranslatef(-0.45, -1.75, 0.1);
	glScalef(1, 1, 0.65);
	glRotatef(90, 0, 1, 0);
	gluQuadricDrawStyle(legTyre2, GLU_LINE);
	gluCylinder(legTyre2, 0.2, 0.2, 0.15, 20, 20);
	gluDeleteQuadric(legTyre2);
	glPopMatrix();
}

void leg() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, -0.7,-0.2);
	glVertex3f(-0.15, -0.7, -0.2);
	glVertex3f(-0.15, -2, -0.2);
	glVertex3f(-0.4, -2, -0.2);
	glEnd();	

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, -2, -0.2);
	glVertex3f(-0.4, -2, 0.2);
	glVertex3f(-0.4, -0.7, 0.2);
	glVertex3f(-0.4, -0.7, -0.2);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, -0.7, -0.2);
	glVertex3f(-0.4, -0.7, 0.2);
	glVertex3f(-0.15, -0.7, 0.2);
	glVertex3f(-0.15, -0.7, -0.2);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.7, -0.2);
	glVertex3f(-0.15, -0.7, 0.2);
	glVertex3f(-0.15, -2, 0.2);
	glVertex3f(-0.15, -2, -0.2);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -2, -0.2);
	glVertex3f(-0.4, -2, -0.2);
	glVertex3f(-0.4, -2, 0.2);
	glVertex3f(-0.15, -2, 0.2);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -2, 0.2);
	glVertex3f(-0.4, -2, 0.2);
	glVertex3f(-0.4, -0.7, 0.2);
	glVertex3f(-0.15, -0.7, 0.2);
	glEnd();
}

void thighArmor1() {
	//Outer Part - Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.33, 0.1, -0.175);
	glVertex3f(-0.17, 0.1, -0.175);
	glVertex3f(-0.2, -0.4, -0.175);
	glVertex3f(-0.3, -0.4, -0.175);
	glEnd();

	//Outer Part - Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.3, -0.4, -0.175);
	glVertex3f(-0.3, -0.4, -0.15);
	glVertex3f(-0.325, 0.1, -0.15);
	glVertex3f(-0.325, 0.1, -0.175);
	glEnd();

	//Outer Part - Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.325, 0.1, -0.175);
	glVertex3f(-0.325, 0.1, -0.15);
	glVertex3f(-0.175, 0.1, -0.15);
	glVertex3f(-0.175, 0.1, -0.175);
	glEnd();

	//Outer Part - Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.175, 0.1, -0.175);
	glVertex3f(-0.175, 0.1, -0.15);
	glVertex3f(-0.2, -0.4, -0.15);
	glVertex3f(-0.2, -0.4, -0.175);
	glEnd();

	//Outer Part - Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.2, -0.4, -0.175);
	glVertex3f(-0.3, -0.4, -0.175);
	glVertex3f(-0.3, -0.4, -0.15);
	glVertex3f(-0.2, -0.4, -0.15);
	glEnd();

	//Outer Part - Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.2, -0.4, -0.15);
	glVertex3f(-0.3, -0.4, -0.15);
	glVertex3f(-0.33, 0.1, -0.15);
	glVertex3f(-0.17, 0.1, -0.15);
	glEnd();

	//Inner Part 1
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.28, -0.1, -0.175);
	glVertex3f(-0.22, -0.1, -0.175);
	glVertex3f(-0.21, -0.125, -0.175);
	glVertex3f(-0.22, -0.15, -0.175);
	glVertex3f(-0.28, -0.15, -0.175);
	glVertex3f(-0.29, -0.125, -0.175);
	glEnd();

	//Inner Part 2
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.28, -0.2, -0.175);
	glVertex3f(-0.22, -0.2, -0.175);
	glVertex3f(-0.21, -0.225, -0.175);
	glVertex3f(-0.22, -0.25, -0.175);
	glVertex3f(-0.28, -0.25, -0.175);
	glVertex3f(-0.29, -0.225, -0.175);
	glEnd();

}

void thightSmallestTrapezium() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.33, -0.5, -0.175);
	glVertex3f(-0.305, -0.48, -0.175);
	glVertex3f(-0.325, -0.6, -0.175);
	glVertex3f(-0.34, -0.56, -0.175);
	glEnd();

	//Left 
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.34, -0.56, -0.175);
	glVertex3f(-0.34, -0.56, -0.15);
	glVertex3f(-0.33, -0.5, -0.15);
	glVertex3f(-0.33, -0.5, -0.175);
	glEnd();

	//Top 
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.33, -0.5, -0.175);
	glVertex3f(-0.33, -0.5, -0.15);
	glVertex3f(-0.305, -0.48, -0.15);
	glVertex3f(-0.305, -0.48, -0.175);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.305, -0.48, -0.175);
	glVertex3f(-0.305, -0.48, -0.15);
	glVertex3f(-0.325, -0.6, -0.15);
	glVertex3f(-0.325, -0.6, -0.175);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.325, -0.6, -0.175);
	glVertex3f(-0.34, -0.56, -0.175);
	glVertex3f(-0.34, -0.56, -0.15);
	glVertex3f(-0.325, -0.6, -0.15);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.325, -0.6, -0.15);
	glVertex3f(-0.34, -0.56, -0.15);
	glVertex3f(-0.33, -0.5, -0.15);
	glVertex3f(-0.305, -0.48, -0.15);
	glEnd();
}

void thighArmor2() {
	//Biggest Trapezium - Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.28, -0.45, -0.175);
	glVertex3f(-0.22, -0.45, -0.175);
	glVertex3f(-0.17, -0.7, -0.175);
	glVertex3f(-0.33, -0.7, -0.175);
	glEnd();

	//Biggest Trapezium - Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.33, -0.7, -0.175);
	glVertex3f(-0.33, -0.7, -0.15);
	glVertex3f(-0.28, -0.45, -0.15);
	glVertex3f(-0.28, -0.45, -0.175);
	glEnd();

	//Biggest Trapezium - Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.28, -0.45, -0.175);
	glVertex3f(-0.28, -0.45, -0.15);
	glVertex3f(-0.22, -0.45, -0.15);
	glVertex3f(-0.22, -0.45, -0.175);
	glEnd();

	//Biggest Trapezium - Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.22, -0.45, -0.175);
	glVertex3f(-0.22, -0.45, -0.15);
	glVertex3f(-0.17, -0.7, -0.15);
	glVertex3f(-0.17, -0.7, -0.175);
	glEnd();

	//Biggest Trapezium - Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.17, -0.7, -0.175);
	glVertex3f(-0.33, -0.7, -0.175);
	glVertex3f(-0.33, -0.7, -0.15);
	glVertex3f(-0.17, -0.7, -0.15);
	glEnd();

	//Biggest Trapezium - Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.17, -0.7, -0.15);
	glVertex3f(-0.33, -0.7, -0.15);
	glVertex3f(-0.28, -0.45, -0.15);
	glVertex3f(-0.22, -0.45, -0.15);
	glEnd();

	//Smallest Trapezium
	thightSmallestTrapezium();

	//Smallest Trapezium - Another Side
	glPushMatrix();
	glTranslatef(-0.5, 0, -0.35);
	glRotatef(180, 0, 1, 0);
	thightSmallestTrapezium();
	glPopMatrix();
}

void thighInnerHexagon() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.14, -0.4, -0.03);
	glVertex3f(-0.14, -0.4, 0.03);
	glVertex3f(-0.14, -0.425, 0.04);
	glVertex3f(-0.14, -0.45, 0.03);
	glVertex3f(-0.14, -0.45, -0.03);
	glVertex3f(-0.14, -0.425, -0.04);
	glEnd();

	//Left Up
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.14, -0.425, -0.04);
	glVertex3f(-0.15, -0.425, -0.04);
	glVertex3f(-0.15, -0.4, -0.03);
	glVertex3f(-0.14, -0.4, -0.03);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.14, -0.4, -0.03);
	glVertex3f(-0.15, -0.4, -0.03);
	glVertex3f(-0.15, -0.4, 0.03);
	glVertex3f(-0.14, -0.4, 0.03);
	glEnd();

	//Right Up
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.14, -0.4, 0.03);
	glVertex3f(-0.15, -0.4, 0.03);
	glVertex3f(-0.15, -0.425, 0.04);
	glVertex3f(-0.14, -0.425, 0.04);
	glEnd();

	//Right Down
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.14, -0.425, 0.04);
	glVertex3f(-0.15, -0.425, 0.04);
	glVertex3f(-0.15, -0.45, 0.03);
	glVertex3f(-0.14, -0.45, 0.03);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.14, -0.45, 0.03);
	glVertex3f(-0.15, -0.45, 0.03);
	glVertex3f(-0.15, -0.45, -0.03);
	glVertex3f(-0.14, -0.45, -0.03);
	glEnd();

	//Left Down
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.14, -0.45, -0.03);
	glVertex3f(-0.15, -0.45, -0.03);
	glVertex3f(-0.15, -0.425, -0.04);
	glVertex3f(-0.14, -0.425, -0.04);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.425, -0.04);
	glVertex3f(-0.15, -0.4, -0.03);
	glVertex3f(-0.15, -0.4, 0.03);
	glVertex3f(-0.15, -0.425, 0.04);
	glVertex3f(-0.15, -0.45, 0.03);
	glVertex3f(-0.15, -0.45, -0.03);
	glEnd();
}

void thighArmor3() {
	//Center Strap
	thighInnerHexagon();

	//Upper Strap
	glPushMatrix();
	glTranslatef(0, 0.075, 0);
	thighInnerHexagon();
	glPopMatrix();

	//Lower Strap
	glPushMatrix();
	glTranslatef(0, -0.075, 0);
	thighInnerHexagon();
	glPopMatrix();
}

void thighArmor4() {
	//Outer Area
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.3, -0.15, 0.15);
	glVertex3f(-0.2, -0.15, 0.15);
	glVertex3f(-0.15, -0.7, 0.15);
	glVertex3f(-0.35, -0.7, 0.15);
	glEnd();

	//Inner Area
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.28, -0.35, 0.15);
	glVertex3f(-0.22, -0.35, 0.15);
	glVertex3f(-0.15, -0.7, 0.15);
	glVertex3f(-0.35, -0.7, 0.15);
	glEnd();
}

void thigh() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.35, 0.1, -0.15);
	glVertex3f(-0.15, 0.1, -0.15);
	glVertex3f(-0.15, -0.7, -0.15);
	glVertex3f(-0.35, -0.7, -0.15);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.35, -0.7, -0.15);
	glVertex3f(-0.35, -0.7, 0.15);
	glVertex3f(-0.35, 0.1, 0.15);
	glVertex3f(-0.35, 0.1, -0.15);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.35, 0.1, -0.15);
	glVertex3f(-0.35, 0.1, 0.15);
	glVertex3f(-0.15, 0.1, 0.15);
	glVertex3f(-0.15, 0.1, -0.15);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, 0.1, -0.15);
	glVertex3f(-0.15, 0.1, 0.15);
	glVertex3f(-0.15, -0.7, 0.15);
	glVertex3f(-0.15, -0.7, -0.15);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.7, -0.15);
	glVertex3f(-0.35, -0.7, -0.15);
	glVertex3f(-0.35, -0.7, 0.15);
	glVertex3f(-0.15, -0.7, 0.15);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.7, 0.15);
	glVertex3f(-0.35, -0.7, 0.15);
	glVertex3f(-0.35, 0.1, 0.15);
	glVertex3f(-0.15, 0.1, 0.15);
	glEnd();
}

void buttTriangle() {
	//Triangle
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.35, 0.32, -0.3);
	glVertex3f(-0.2, 0.32, -0.3);
	glVertex3f(-0.2, 0.22, -0.3);
	glEnd();
}

void buttDesign() {
	//Rectangle
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, 0.3, -0.3);
	glVertex3f(0.15, 0.3, -0.3);
	glVertex3f(0.15, 0, -0.3);
	glVertex3f(-0.15, 0, -0.3);
	glEnd();

	//Left Part Triangle in Butt Area
	buttTriangle();

	glPushMatrix();
	glTranslatef(-0.01, -0.15, 0);
	glScalef(0.9, 0.9, 1);
	buttTriangle();
	glPopMatrix();

	
	//Right Part Triangle in Butt Area
	glPushMatrix();
	glTranslatef(0, 0, -0.6);
	glRotatef(180, 0, 1, 0);
	buttTriangle();

	glPushMatrix();
	glTranslatef(-0.01, -0.15, 0);
	glScalef(0.9, 0.9, 1);
	buttTriangle();
	glPopMatrix();

	glPopMatrix();
}

void buttArmor1() {

	glColor3f(0, 0, 1);
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.13, -0.1, -0.305);
	glVertex3f(0.13, -0.1, -0.305);
	glVertex3f(0.1, -0.3, -0.25);
	glVertex3f(-0.1, -0.3, -0.25);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.3, -0.25);
	glVertex3f(-0.1, -0.3, 0.3);
	glVertex3f(-0.13, -0.1, 0.4);
	glVertex3f(-0.13, -0.1, -0.305);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.13, -0.1, -0.305);
	glVertex3f(-0.13, -0.1, 0.4);
	glVertex3f(0.13, -0.1, 0.4);
	glVertex3f(0.13, -0.1, -0.305);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.13, -0.1, -0.305);
	glVertex3f(0.13, -0.1, 0.4);
	glVertex3f(0.1, -0.3, 0.3);
	glVertex3f(0.1, -0.3, -0.25);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.1, -0.3, -0.25);
	glVertex3f(-0.1, -0.3, -0.25);
	glVertex3f(-0.1, -0.3, 0.3);
	glVertex3f(0.1, -0.3, 0.3);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.1, -0.3, 0.3);
	glVertex3f(-0.1, -0.3, 0.3);
	glVertex3f(-0.13, -0.1, 0.4);
	glVertex3f(0.13, -0.1, 0.4);
	glEnd();

	glColor3f(1, 1, 1);
}

void buttArmor2() {
	glColor3f(0, 0, 1);
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.13, 0.2, 0.4);
	glVertex3f(-0.13, 0.3, 0.3);
	glVertex3f(-0.13, -0.3, 0.3);
	glVertex3f(-0.13, -0.1, 0.4);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.13, -0.1, 0.4);
	glVertex3f(0.13, -0.1, 0.4);
	glVertex3f(0.13, 0.2, 0.4);
	glVertex3f(-0.13, 0.2, 0.4);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.13, 0.2, 0.4);
	glVertex3f(0.13, 0.2, 0.4);
	glVertex3f(0.13, 0.3, 0.3);
	glVertex3f(-0.13, 0.3, 0.3);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.13, 0.3, 0.3);
	glVertex3f(0.13, 0.3, 0.3);
	glVertex3f(0.13, -0.3, 0.3);
	glVertex3f(-0.13, -0.3, 0.3);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.13, -0.3, 0.3);
	glVertex3f(-0.13, -0.1, 0.4);
	glVertex3f(0.13, -0.1, 0.4);
	glVertex3f(0.13, -0.3, 0.3);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.13, -0.3, 0.3);
	glVertex3f(0.13, -0.1, 0.4);
	glVertex3f(0.13, 0.2, 0.4);
	glVertex3f(0.13, 0.3, 0.3);
	glEnd();

	glColor3f(1, 1, 1);
}

void butt() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 0.4, -0.3);
	glVertex3f(0.4, 0.4, -0.3);
	glVertex3f(0.4, 0.1, -0.3);
	glVertex3f(0.13, -0.15, -0.3);
	glVertex3f(-0.13, -0.15, -0.3);
	glVertex3f(-0.4, 0.1, -0.3);
	glEnd();

	//Left Below
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 0.1, -0.3);
	glVertex3f(-0.4, 0.1, 0.3);
	glVertex3f(-0.13, -0.15, 0.3);
	glVertex3f(-0.13, -0.15, -0.3);
	glEnd();

	//Left Above
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 0.1, -0.3);
	glVertex3f(-0.4, 0.1, 0.3);
	glVertex3f(-0.4, 0.4, 0.3);
	glVertex3f(-0.4, 0.4, -0.3);
	glEnd();

	//Top 
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 0.4, -0.3);
	glVertex3f(-0.4, 0.4, 0.3);
	glVertex3f(0.4, 0.4, 0.3);
	glVertex3f(0.4, 0.4, -0.3);
	glEnd();

	//Right Above
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.4, 0.4, -0.3);
	glVertex3f(0.4, 0.4, 0.3);
	glVertex3f(0.4, 0.1, 0.3);
	glVertex3f(0.4, 0.1, -0.3);
	glEnd();

	//Right Below
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.4, 0.1, -0.3);
	glVertex3f(0.4, 0.1, 0.3);
	glVertex3f(0.13, -0.15, 0.3);
	glVertex3f(0.13, -0.15, -0.3);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.13, -0.15, -0.3);
	glVertex3f(0.13, -0.15, 0.3);
	glVertex3f(-0.13, -0.15, 0.3);
	glVertex3f(-0.13, -0.15, -0.3);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 0.4, 0.3);
	glVertex3f(0.4, 0.4, 0.3);
	glVertex3f(0.4, 0.1, 0.3);
	glVertex3f(0.13, -0.15, 0.3);
	glVertex3f(-0.13, -0.15, 0.3);
	glVertex3f(-0.4, 0.1, 0.3);
	glEnd();
	
	//Butt is Designed
	buttDesign();
}

void sixpack() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.3, 0.8, -0.25);
	glVertex3f(0.3, 0.8, -0.25);
	glVertex3f(0.3, 0.4, -0.25);
	glVertex3f(-0.3, 0.4, -0.25);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.3, 0.4, -0.25);
	glVertex3f(-0.3, 0.4, 0.25);
	glVertex3f(-0.3, 0.8, 0.25);
	glVertex3f(-0.3, 0.8, -0.25);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.3, 0.8, -0.25);
	glVertex3f(-0.3, 0.8, 0.25);
	glVertex3f(0.3, 0.8, 0.25);
	glVertex3f(0.3, 0.8, -0.25);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.3, 0.8, -0.25);
	glVertex3f(0.3, 0.8, 0.25);
	glVertex3f(0.3, 0.4, 0.25);
	glVertex3f(0.3, 0.4, -0.25);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.3, 0.4, -0.25);
	glVertex3f(-0.3, 0.4, -0.25);
	glVertex3f(-0.3, 0.4, 0.25);
	glVertex3f(0.3, 0.4, 0.25);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.3, 0.4, 0.25);
	glVertex3f(-0.3, 0.4, 0.25);
	glVertex3f(-0.3, 0.8, 0.25);
	glVertex3f(0.3, 0.8, 0.25);
	glEnd();
}

void chest() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 1.5, -0.45);
	glVertex3f(0.4, 1.5, -0.45);
	glVertex3f(0.4, 0.8, -0.45);
	glVertex3f(-0.4, 0.8, -0.45);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 0.8, -0.45);
	glVertex3f(-0.4, 0.8, 0.45);
	glVertex3f(-0.4, 1.5, 0.45);
	glVertex3f(-0.4, 1.5, -0.45);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 1.5, -0.45);
	glVertex3f(-0.4, 1.5, 0.45);
	glVertex3f(0.4, 1.5, 0.45);
	glVertex3f(0.4, 1.5, -0.45);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.4, 1.5, -0.45);
	glVertex3f(0.4, 1.5, 0.45);
	glVertex3f(0.4, 0.8, 0.45);
	glVertex3f(0.4, 0.8, -0.45);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.4, 0.8, -0.45);
	glVertex3f(-0.4, 0.8, -0.45);
	glVertex3f(-0.4, 0.8, 0.45);
	glVertex3f(0.4, 0.8, 0.45);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.4, 0.8, 0.45);
	glVertex3f(-0.4, 0.8, 0.45);
	glVertex3f(-0.4, 1.5, 0.45);
	glVertex3f(0.4, 1.5, 0.45);
	glEnd();
}
void head()
{
	//head x=-0.15/0.15 y=1.5/1.9 z=-0.05/0.25
	//lefteye x=-0.12/-0.03 y=1.7/1.75 z=-0.05
	//righteye x=0.03/0.12 y=1.7/1.725 z=-0.05
	//mouth x=-0.15/0.15 y=1.5/1.65 z=-0.05/-0.07

	//head dxxx
	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 1.9, -0.05);
	glVertex3f(0.05, 1.9, -0.05);
	glVertex3f(0.05, 2.05, -0.0);
	glVertex3f(0.00, 2.1, -0.0);
	glVertex3f(-0.05, 2.05, -0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 1.9, -0.07);
	glVertex3f(0.05, 1.9, -0.07);
	glVertex3f(0.05, 2.05, -0.02);
	glVertex3f(0.00, 2.1, -0.02);
	glVertex3f(-0.05, 2.05, -0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 1.9, -0.07);
	glVertex3f(-0.05, 1.9, -0.05);
	glVertex3f(-0.05, 2.05, -0.0);
	glVertex3f(0.0, 2.1, -0.0);
	glVertex3f(0.0, 2.1, -0.02);
	glVertex3f(-0.05, 2.05, -0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.05, 1.9, -0.07);
	glVertex3f(0.05, 1.9, -0.05);
	glVertex3f(0.05, 2.05, -0.0);
	glVertex3f(0.0, 2.1, -0.0);
	glVertex3f(0.0, 2.1, -0.02);
	glVertex3f(0.05, 2.05, -0.02);
	glEnd();




	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 2.0, -0.00);
	glVertex3f(0.05, 2.0, -0.00);
	glVertex3f(0.05, 2.0, 0.25);
	glVertex3f(-0.05, 2.0, 0.25);

	glEnd();

	//upper-part helmet
	glBegin(GL_POLYGON);
	glVertex3f(-0.15, 1.9, -0.05);
	glVertex3f(-0.14, 1.91, -0.05);
	glVertex3f(-0.13, 1.92, -0.04);
	glVertex3f(-0.12, 1.93, -0.03);
	glVertex3f(-0.11, 1.94, -0.02);
	glVertex3f(-0.10, 1.95, -0.01);
	glVertex3f(-0.05, 2, 0);
	glVertex3f(0.05, 2.0, 0.0);
	glVertex3f(0.10, 1.95, 0.0);
	glVertex3f(0.11, 1.94, -0.01);
	glVertex3f(0.12, 1.93, -0.02);
	glVertex3f(0.13, 1.92, -0.03);
	glVertex3f(0.14, 1.91, -0.04);
	glVertex3f(0.14, 1.91, -0.05);
	glVertex3f(0.15, 1.9, -0.06);
	glEnd();
	
	
	glColor3f(1, 0, 0);
	//left-upper-part-helmet
	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 2.0, 0.27);
	glVertex3f(-0.06, 1.97, 0.27);
	glVertex3f(-0.07, 1.95, 0.27);
	glVertex3f(-0.15, 1.9, 0.25);
	glVertex3f(-0.15, 1.88, 0.10);
	glVertex3f(-0.15, 1.9, -0.05);
	glVertex3f(-0.15, 1.9, -0.05);
	glVertex3f(-0.15, 1.9, -0.05);
	glVertex3f(-0.14, 1.91, -0.05);
	glVertex3f(-0.13, 1.92, -0.04);
	glVertex3f(-0.12, 1.93, -0.03);
	glVertex3f(-0.11, 1.94, -0.02);
	glVertex3f(-0.10, 1.95, -0.01);
	glVertex3f(-0.05, 2, 0);

	glEnd();

	glBegin(GL_POLYGON);

	glVertex3f(-0.15, 1.9, 0.25);
	glVertex3f(-0.15, 1.8, 0.25);
	glVertex3f(-0.15, 1.88, 0.10);


	glEnd();
	

	/*
	//right upper-part helmet
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.10, 2.0, 0.25);
	glVertex3f(0.17, 1.8, 0.25);
	glVertex3f(0.17, 1.88, 0.10);
	glVertex3f(0.17, 1.9, -0.05);
	glVertex3f(0.17, 1.9, -0.05);
	glVertex3f(0.15, 1.9, -0.05);
	glVertex3f(0.14, 1.91, -0.05);
	glVertex3f(0.13, 1.92, -0.04);
	glVertex3f(0.12, 1.93, -0.03);
	glVertex3f(0.11, 1.94, -0.02);
	glVertex3f(0.10, 1.95, -0.01);
	glVertex3f(0.05, 2, 0);
	glEnd();*/
	glBegin(GL_POLYGON);
	glVertex3f(0.05, 2.0, 0.27);
	glVertex3f(0.06, 1.97, 0.27);
	glVertex3f(0.07, 1.95, 0.27);
	glVertex3f(0.15, 1.9, 0.25);
	glVertex3f(0.15, 1.8, 0.25);
	glVertex3f(0.15, 1.88, 0.10);
	glVertex3f(0.15, 1.9, -0.05);
	glVertex3f(0.15, 1.9, -0.05);
	glVertex3f(0.15, 1.9, -0.05);
	glVertex3f(0.14, 1.91, -0.05);
	glVertex3f(0.13, 1.92, -0.04);
	glVertex3f(0.12, 1.93, -0.03);
	glVertex3f(0.11, 1.94, -0.02);
	glVertex3f(0.10, 1.95, -0.01);
	glVertex3f(0.05, 2, 0);

	glEnd();




	glColor3f(1, 1, 1);
	//top part helmet
	glBegin(GL_POLYGON);
	glVertex3f(-0.15, 1.88, -0.07);
	glVertex3f(-0.15, 1.9, -0.07);
	glVertex3f(0.15, 1.9, -0.07);
	glVertex3f(0.15, 1.88, -0.07);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.15, 1.88, -0.05);
	glVertex3f(-0.15, 1.9, -0.05);
	glVertex3f(0.15, 1.9, -0.05);
	glVertex3f(0.15, 1.88, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.15, 1.88, -0.05);
	glVertex3f(-0.15, 1.9, -0.05);
	glVertex3f(-0.15, 1.9, -0.07);
	glVertex3f(-0.15, 1.88, -0.07);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.15, 1.88, -0.05);
	glVertex3f(0.15, 1.9, -0.05);
	glVertex3f(0.15, 1.9, -0.07);
	glVertex3f(0.15, 1.88, -0.07);
	glEnd();
	//top
	glBegin(GL_POLYGON);
	glVertex3f(-0.15, 1.9, -0.05);
	glVertex3f(-0.15, 1.9, -0.07);
	glVertex3f(-0.15, 1.9, -0.07);
	glVertex3f(-0.15, 1.9, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-0.15, 1.88, -0.05);
	glVertex3f(-0.15, 1.88, -0.07);
	glVertex3f(-0.15, 1.88, -0.07);
	glVertex3f(-0.15, 1.88, -0.05);
	glEnd();

	//back-part helmet
	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(0.15, 1.5, 0.25);
	glVertex3f(0.15, 1.9, 0.25);
	glVertex3f(0.07, 1.95, 0.27);
	glVertex3f(0.06, 1.97, 0.27);
	glVertex3f(0.05, 2.0, 0.27);
	glVertex3f(0.0, 2.0, 0.27);
	glVertex3f(-0.05, 2.0, 0.27);
	glVertex3f(-0.06, 1.97, 0.27);
	glVertex3f(-0.07, 1.95, 0.27);
	glVertex3f(-0.15, 1.9, 0.25);
	glVertex3f(-0.15, 1.5, 0.25);
	glEnd();
	glColor3f(1, 1, 1);
	//============================
	//right upper-part helmet

	//top
	glBegin(GL_POLYGON);
	glVertex3f(0.15, 1.9, -0.05);
	glVertex3f(0.15, 1.88, 0.10);
	glVertex3f(0.15, 1.8, 0.25);
	glVertex3f(0.17, 1.8, 0.25);
	glVertex3f(0.17, 1.88, 0.10);
	glVertex3f(0.17, 1.9, -0.05);
	glEnd();
	//left

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(0.17, 1.7, -0.05);
	glVertex3f(0.17, 1.7, 0.25);
	glVertex3f(0.17, 1.8, 0.25);
	glVertex3f(0.17, 1.88, 0.10);
	glVertex3f(0.17, 1.9, -0.05);
	glEnd();

	//right
	glBegin(GL_POLYGON);
	glVertex3f(0.15, 1.7, -0.05);
	glVertex3f(0.15, 1.7, 0.25);
	glVertex3f(0.15, 1.8, 0.25);
	glVertex3f(0.15, 1.88, 0.10);
	glVertex3f(0.15, 1.9, -0.05);
	glEnd();
	//front
	glBegin(GL_POLYGON);
	glVertex3f(0.15, 1.7, -0.05);
	glVertex3f(0.17, 1.7, -0.05);
	glVertex3f(0.17, 1.9, -0.05);
	glVertex3f(0.15, 1.9, -0.05);
	glEnd();
	//back
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(0.15, 1.7, 0.25);
	glVertex3f(0.17, 1.7, 0.25);
	glVertex3f(0.17, 1.8, 0.25);
	glVertex3f(0.15, 1.8, 0.25);
	glEnd();
	//============================
//left upper-part helmet
//top
	glBegin(GL_POLYGON);
	glVertex3f(-0.15, 1.9, -0.05);
	glVertex3f(-0.15, 1.88, 0.10);
	glVertex3f(-0.15, 1.8, 0.25);
	glVertex3f(-0.17, 1.8, 0.25);
	glVertex3f(-0.17, 1.88, 0.10);
	glVertex3f(-0.17, 1.9, -0.05);
	glEnd();
	//left

	glColor3f(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.17, 1.7, -0.05);
	glVertex3f(-0.17, 1.7, 0.25);
	glVertex3f(-0.17, 1.8, 0.25);
	glVertex3f(-0.17, 1.88, 0.10);
	glVertex3f(-0.17, 1.9, -0.05);
	glEnd();

	//right
	glBegin(GL_POLYGON);
	glVertex3f(-0.15, 1.7, -0.05);
	glVertex3f(-0.15, 1.7, 0.25);
	glVertex3f(-0.15, 1.8, 0.25);
	glVertex3f(-0.15, 1.88, 0.10);
	glVertex3f(-0.15, 1.9, -0.05);
	glEnd();
	//front
	glBegin(GL_POLYGON);
	glVertex3f(-0.15, 1.7, -0.05);
	glVertex3f(-0.17, 1.7, -0.05);
	glVertex3f(-0.17, 1.9, -0.05);
	glVertex3f(-0.15, 1.9, -0.05);
	glEnd();
	//back
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(-0.15, 1.7, 0.25);
	glVertex3f(-0.17, 1.7, 0.25);
	glVertex3f(-0.17, 1.8, 0.25);
	glVertex3f(-0.15, 1.8, 0.25);
	glEnd();
	//=====================================================================
		//left-bottom-part helmet 


	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	glPushMatrix();
	glTranslatef(-0.19, 1.7, 0.1);
	glRotatef(90, 0, 1, 0);
	gluQuadricDrawStyle(sphere, GLU_FILL);


	gluSphere(sphere, 0.05, 50, 50);


	gluDeleteQuadric(sphere);
	glPopMatrix();

	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	glPushMatrix();
	glTranslatef(-0.19, 1.7, 0.1);
	glRotatef(-90, 1, 0, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.03, 0.0, 0.3, 40, 40);





	gluDeleteQuadric(cylinder);
	glPopMatrix();

	//front
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex3f(-0.15, 1.7, -0.05);
	glVertex3f(-0.15, 1.65, -0.1);
	glVertex3f(-0.15, 1.55, -0.1);
	glVertex3f(-0.15, 1.5, -0.05);
	glVertex3f(-0.17, 1.5, -0.05);
	glVertex3f(-0.17, 1.55, -0.1);
	glVertex3f(-0.17, 1.65, -0.1);
	glVertex3f(-0.17, 1.7, -0.05);
	glEnd();
	//left


	glBegin(GL_POLYGON);
	glColor3f(1, 1, 0);
	glVertex3f(-0.17, 1.5, -0.05);
	glVertex3f(-0.17, 1.55, -0.1);
	glVertex3f(-0.17, 1.65, -0.1);
	glVertex3f(-0.17, 1.7, -0.05);
	glVertex3f(-0.17, 1.7, 0.25);
	glVertex3f(-0.17, 1.5, 0.25);
	glEnd();
	//right
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 0);
	glVertex3f(-0.15, 1.5, -0.05);
	glVertex3f(-0.15, 1.55, -0.1);
	glVertex3f(-0.15, 1.65, -0.1);
	glVertex3f(-0.15, 1.7, -0.05);
	glVertex3f(-0.15, 1.7, 0.25);
	glVertex3f(-0.15, 1.5, 0.25);
	glEnd();
	//back
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 0);
	glVertex3f(-0.15, 1.7, 0.25);
	glVertex3f(-0.17, 1.7, 0.25);
	glVertex3f(-0.17, 1.5, 0.25);
	glVertex3f(-0.15, 1.5, 0.25);
	glEnd();

	//bottom
	glBegin(GL_POLYGON);
	glVertex3f(-0.15, 1.5, -0.05);
	glVertex3f(-0.17, 1.5, -0.05);
	glVertex3f(-0.17, 1.7, 0.25);
	glVertex3f(-0.15, 1.7, 0.25);
	glEnd();
	glColor3f(1, 1, 1);
	//====================================================================
	//right bottom part helmet

	sphere = gluNewQuadric();
	glPushMatrix();
	glTranslatef(0.19, 1.7, 0.1);
	glRotatef(90, 0, 1, 0);
	gluQuadricDrawStyle(sphere, GLU_FILL);


	gluSphere(sphere, 0.05, 50, 50);


	gluDeleteQuadric(sphere);
	glPopMatrix();


	cylinder = gluNewQuadric();
	glPushMatrix();
	glTranslatef(0.19, 1.7, 0.1);
	glRotatef(-90, 1, 0, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluCylinder(cylinder, 0.03, 0.0, 0.3, 40, 40);





	gluDeleteQuadric(cylinder);
	glPopMatrix();

	//front
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex3f(0.15, 1.7, -0.05);
	glVertex3f(0.15, 1.65, -0.1);
	glVertex3f(0.15, 1.55, -0.1);
	glVertex3f(0.15, 1.5, -0.05);
	glVertex3f(0.17, 1.5, -0.05);
	glVertex3f(0.17, 1.55, -0.1);
	glVertex3f(0.17, 1.65, -0.1);
	glVertex3f(0.17, 1.7, -0.05);
	glEnd();
	//left


	glBegin(GL_POLYGON);
	glColor3f(1, 1, 0);
	glVertex3f(0.17, 1.5, -0.05);
	glVertex3f(0.17, 1.55, -0.1);
	glVertex3f(0.17, 1.65, -0.1);
	glVertex3f(0.17, 1.7, -0.05);
	glVertex3f(0.17, 1.7, 0.25);
	glVertex3f(0.17, 1.5, 0.25);
	glEnd();
	//right
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 0);
	glVertex3f(0.15, 1.5, -0.05);
	glVertex3f(0.15, 1.55, -0.1);
	glVertex3f(0.15, 1.65, -0.1);
	glVertex3f(0.15, 1.7, -0.05);
	glVertex3f(0.15, 1.7, 0.25);
	glVertex3f(0.15, 1.5, 0.25);
	glEnd();
	//back
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 0);
	glVertex3f(0.15, 1.7, 0.25);
	glVertex3f(0.17, 1.7, 0.25);
	glVertex3f(0.17, 1.5, 0.25);
	glVertex3f(0.15, 1.5, 0.25);
	glEnd();

	//bottom
	glBegin(GL_POLYGON);
	glVertex3f(0.15, 1.5, -0.05);
	glVertex3f(0.17, 1.5, -0.05);
	glVertex3f(0.17, 1.7, 0.25);
	glVertex3f(0.15, 1.7, 0.25);
	glEnd();
	glColor3f(1, 1, 1);
	//====================================================================

		//left eye
	glBegin(GL_POLYGON);
	glVertex3f(-0.10, 1.7, -0.051);
	glVertex3f(-0.12, 1.725, -0.051);
	glVertex3f(-0.10, 1.75, -0.051);
	glVertex3f(-0.05, 1.75, -0.051);
	glVertex3f(-0.03, 1.725, -0.051);
	glVertex3f(-0.05, 1.7, -0.051);
	glEnd();
	//right eye
	glBegin(GL_POLYGON);
	glVertex3f(0.10, 1.7, -0.051);
	glVertex3f(0.12, 1.725, -0.051);
	glVertex3f(0.10, 1.75, -0.051);
	glVertex3f(0.05, 1.75, -0.051);
	glVertex3f(0.03, 1.725, -0.051);
	glVertex3f(0.05, 1.7, -0.051);
	glEnd();
	//mouth
	glBegin(GL_QUADS);
	glVertex3f(-0.15, 1.5, -0.05);
	glVertex3f(-0.15, 1.65, -0.05);
	glVertex3f(0.0, 1.65, -0.07);
	glVertex3f(0.0, 1.5, -0.07);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(0.15, 1.5, -0.05);
	glVertex3f(0.15, 1.65, -0.05);
	glVertex3f(0.0, 1.65, -0.07);
	glVertex3f(0.0, 1.5, -0.07);
	glEnd();

	//nose
	glBegin(GL_QUADS);
	glVertex3f(0.01, 1.65, -0.051);
	glVertex3f(0.01, 1.725, -0.051);
	glVertex3f(-0.01, 1.725, -0.051);
	glVertex3f(-0.01, 1.65, -0.051);
	glEnd();



	//Front
	glColor3f(0, 1, 0);
	glBegin(GL_QUADS);
	glVertex3f(-0.15, 1.9, -0.05);
	glVertex3f(0.15, 1.9, -0.05);
	glVertex3f(0.15, 1.5, -0.05);
	glVertex3f(-0.15, 1.5, -0.05);
	glEnd();
	glColor3f(1, 1, 1);
	/*
	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, 1.5, -0.05);
	glVertex3f(-0.15, 1.5, 0.25);
	glVertex3f(-0.15, 1.9, 0.25);
	glVertex3f(-0.15, 1.9, -0.05);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, 1.9, -0.05);
	glVertex3f(-0.15, 1.9, 0.25);
	glVertex3f(0.15, 1.9, 0.25);
	glVertex3f(0.15, 1.9, -0.05);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.15, 1.9, -0.05);
	glVertex3f(0.15, 1.9, 0.25);
	glVertex3f(0.15, 1.5, 0.25);
	glVertex3f(0.15, 1.5, -0.05);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.15, 1.5, -0.05);
	glVertex3f(-0.15, 1.5, -0.05);
	glVertex3f(-0.15, 1.5, 0.25);
	glVertex3f(0.15, 1.5, 0.25);
	glEnd();

	//Back
	glColor3f(0, 0, 1);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.15, 1.5, 0.25);
	glVertex3f(-0.15, 1.5, 0.25);
	glVertex3f(-0.15, 1.9, 0.25);
	glVertex3f(0.15, 1.9, 0.25);
	glEnd();
	glColor3f(1, 1, 1);*/
}
void upperArmJoint() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.45, 1.4, 0);
	glVertex3f(-0.4, 1.4, 0);
	glVertex3f(-0.4, 1.15, 0);
	glVertex3f(-0.45, 1.15, 0);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.45, 1.15, 0);
	glVertex3f(-0.45, 1.15, 0.1);
	glVertex3f(-0.45, 1.4, 0.1);
	glVertex3f(-0.45, 1.4, 0);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.45, 1.4, 0);
	glVertex3f(-0.45, 1.4, 0.1);
	glVertex3f(-0.4, 1.4, 0.1);
	glVertex3f(-0.4, 1.4, 0);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 1.4, 0);
	glVertex3f(-0.4, 1.4, 0.1);
	glVertex3f(-0.4, 1.15, 0.1);
	glVertex3f(-0.4, 1.15, 0);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 1.15, 0);
	glVertex3f(-0.45, 1.15, 0);
	glVertex3f(-0.45, 1.15, 0.1);
	glVertex3f(-0.4, 1.15, 0.1);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 1.15, 0.1);
	glVertex3f(-0.45, 1.15, 0.1);
	glVertex3f(-0.45, 1.4, 0.1);
	glVertex3f(-0.4, 1.4, 0.1);
	glEnd();
}

void upperArm() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.7, 1.55, -0.05);
	glVertex3f(-0.45, 1.55, -0.05);
	glVertex3f(-0.45, 1.1, -0.05);
	glVertex3f(-0.7, 1.1, -0.05);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.7, 1.1, -0.05);
	glVertex3f(-0.7, 1.1, 0.25);
	glVertex3f(-0.7, 1.55, 0.25);
	glVertex3f(-0.7, 1.55, -0.05);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.7, 1.55, -0.05);
	glVertex3f(-0.7, 1.55, 0.25);
	glVertex3f(-0.45, 1.55, 0.25);
	glVertex3f(-0.45, 1.55, -0.05);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.45, 1.55, -0.05);
	glVertex3f(-0.45, 1.55, 0.25);
	glVertex3f(-0.45, 1.1, 0.25);
	glVertex3f(-0.45, 1.1, -0.05);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.45, 1.1, -0.05);
	glVertex3f(-0.7, 1.1, -0.05);
	glVertex3f(-0.7, 1.1, 0.25);
	glVertex3f(-0.45, 1.1, 0.25);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.45, 1.1, 0.25);
	glVertex3f(-0.7, 1.1, 0.25);
	glVertex3f(-0.7, 1.55, 0.25);
	glVertex3f(-0.45, 1.55, 0.25);
	glEnd();
}

void armMuscle1() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.7, 1.1, -0.025);
	glVertex3f(-0.46, 1.1, -0.025);
	glVertex3f(-0.46, 0.95, -0.025);
	glVertex3f(-0.7, 0.95, -0.025);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.7, 0.95, -0.025);
	glVertex3f(-0.7, 0.95, 0.225);
	glVertex3f(-0.7, 1.1, 0.225);
	glVertex3f(-0.7, 1.1, -0.025);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.7, 1.1, -0.025);
	glVertex3f(-0.7, 1.1, 0.225);
	glVertex3f(-0.46, 1.1, 0.225);
	glVertex3f(-0.46, 1.1, -0.025);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.46, 1.1, -0.025);
	glVertex3f(-0.46, 1.1, 0.225);
	glVertex3f(-0.46, 0.95, 0.225);
	glVertex3f(-0.46, 0.95, -0.025);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.46, 0.95, -0.025);
	glVertex3f(-0.7, 0.95, -0.025);
	glVertex3f(-0.7, 0.95, 0.225);
	glVertex3f(-0.46, 0.95, 0.225);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.46, 0.95, 0.225);
	glVertex3f(-0.7, 0.95, 0.225);
	glVertex3f(-0.7, 1.1, 0.225);
	glVertex3f(-0.46, 1.1, 0.225);
	glEnd();
}

void armMuscle2() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.7, 0.95, -0.025);
	glVertex3f(-0.46, 0.95, -0.025);
	glVertex3f(-0.46, 0.8, -0.025);
	glVertex3f(-0.7, 0.8, -0.025);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.7, 0.8, -0.025);
	glVertex3f(-0.7, 0.8, 0.225);
	glVertex3f(-0.7, 0.95, 0.225);
	glVertex3f(-0.7, 0.95, -0.025);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.7, 0.95, -0.025);
	glVertex3f(-0.7, 0.95, 0.225);
	glVertex3f(-0.46, 0.95, 0.225);
	glVertex3f(-0.46, 0.95, -0.025);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.46, 0.95, -0.025);
	glVertex3f(-0.46, 0.95, 0.225);
	glVertex3f(-0.46, 0.8, 0.225);
	glVertex3f(-0.46, 0.8, -0.025);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.46, 0.8, -0.025);
	glVertex3f(-0.7, 0.8, -0.025);
	glVertex3f(-0.7, 0.8, 0.225);
	glVertex3f(-0.46, 0.8, 0.225);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.46, 0.8, 0.225);
	glVertex3f(-0.7, 0.8, 0.225);
	glVertex3f(-0.7, 0.95, 0.225);
	glVertex3f(-0.46, 0.95, 0.225);
	glEnd();
}

void muscleLowerArmJoint() {
	/*
	GLUquadricObj *joint = NULL;
	joint = gluNewQuadric();

	glPushMatrix();
	glScalef(1, 1, 0.8);
	glTranslatef(-0.7, 0.75, 0.125);
	glRotatef(90, 0, 1, 0);
	gluQuadricDrawStyle(joint, GLU_LINE);
	gluCylinder(joint, 0.125, 0.125, 0.24, 20, 20);
	gluDeleteQuadric(joint);
	glPopMatrix();
	*/

	GLUquadricObj *joint = NULL;
	joint = gluNewQuadric();

	glPushMatrix();
	glScalef(1, 1, 0.75);
	glTranslatef(-0.58, 0.75, 0.125);
	gluQuadricDrawStyle(joint, GLU_LINE);
	gluSphere(joint, 0.125, 30, 30);
	gluDeleteQuadric(joint);
	glPopMatrix();
}

void lowerArm() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.71, 0.7, -0.025);
	glVertex3f(-0.45, 0.7, -0.025);
	glVertex3f(-0.45, 0.1, -0.025);
	glVertex3f(-0.71, 0.1, -0.025);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.71, 0.1, -0.025);
	glVertex3f(-0.71, 0.1, 0.225);
	glVertex3f(-0.71, 0.7, 0.225);
	glVertex3f(-0.71, 0.7, -0.025);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.71, 0.7, -0.025);
	glVertex3f(-0.71, 0.7, 0.225);
	glVertex3f(-0.45, 0.7, 0.225);
	glVertex3f(-0.45, 0.7, -0.025);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.45, 0.7, -0.025);
	glVertex3f(-0.45, 0.7, 0.225);
	glVertex3f(-0.45, 0.1, 0.225);
	glVertex3f(-0.45, 0.1, -0.025);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.45, 0.1, -0.025);
	glVertex3f(-0.71, 0.1, -0.025);
	glVertex3f(-0.71, 0.1, 0.225);
	glVertex3f(-0.45, 0.1, 0.225);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.45, 0.1, 0.225);
	glVertex3f(-0.71, 0.1, 0.225);
	glVertex3f(-0.71, 0.7, 0.225);
	glVertex3f(-0.45, 0.7, 0.225);
	glEnd();
}

void armAntenna() {
	GLUquadricObj *bottomAntenna = NULL;
	bottomAntenna = gluNewQuadric();

	glPushMatrix();
	glScalef(1, 1, 0.8);
	glTranslatef(-0.725, 1.4, 0);
	glRotatef(90, 1, 0, 0);
	gluQuadricDrawStyle(bottomAntenna, GLU_LINE);
	gluCylinder(bottomAntenna, 0.02, 0.02, 0.4, 20, 20);
	gluDeleteQuadric(bottomAntenna);
	glPopMatrix();
}

void hand() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.68, 0.1, 0.05);
	glVertex3f(-0.47, 0.1, 0.05);
	glVertex3f(-0.47, -0.1, 0.05);
	glVertex3f(-0.68, -0.1, 0.05);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.68, -0.1, 0.05);
	glVertex3f(-0.68, -0.1, 0.15);
	glVertex3f(-0.68, 0.1, 0.15);
	glVertex3f(-0.68, 0.1, 0.05);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.68, 0.1, 0.05);
	glVertex3f(-0.68, 0.1, 0.15);
	glVertex3f(-0.47, 0.1, 0.15);
	glVertex3f(-0.47, 0.1, 0.05);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.47, 0.1, 0.05);
	glVertex3f(-0.47, 0.1, 0.15);
	glVertex3f(-0.47, -0.1, 0.15);
	glVertex3f(-0.47, -0.1, 0.05);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.47, -0.1, 0.05);
	glVertex3f(-0.68, -0.1, 0.05);
	glVertex3f(-0.68, -0.1, 0.15);
	glVertex3f(-0.47, -0.1, 0.15);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.47, -0.1, 0.15);
	glVertex3f(-0.68, -0.1, 0.15);
	glVertex3f(-0.68, 0.1, 0.15);
	glVertex3f(-0.47, 0.1, 0.15);
	glEnd();
}

void optimusPrime()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.53, 0.81, 0.92, 0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	/////////////////////////////////// ONE AND ONLY ONE /////////////////////////////////////
	butt();
	buttArmor1();
	buttArmor2();
	sixpack();
	chest();
	head();

	/////////////////////////////// LEFT PART FROM SCREEN VIEW ///////////////////////////////
	leg();
	shoePart1();
	shoePart2();
	shoePart3();
	legArmor1();
	legArmor2();
	legArmor3();
	legArmor4();
	legTyre();
	thigh();
	thighArmor1();
	thighArmor2();
	thighArmor3();
	thighArmor4();
	upperArmJoint();
	upperArm();
	armMuscle1();
	armMuscle2();
	muscleLowerArmJoint();
	armAntenna();

	/* Move the Left Arm Up & Down */
	glPushMatrix();
	glTranslatef(0, 0.65, 0.15);
	glRotatef(leftArmUpSpeed, 1, 0, 0);
	glTranslatef(0, -0.65, -0.15);
	lowerArm();
	hand();
	glPopMatrix();

	/////////////////////////////// RIGHT PART FROM SCREEN VIEW ///////////////////////////////
	/* Translate Shoe To The Right Part*/
	glPushMatrix();
	glTranslatef(0.5, 0, 0);
	shoePart1();
	shoePart2();
	shoePart3();
	legArmor1();
	legArmor4();
	thighArmor1();
	thighArmor2();
	thighArmor4();
	glPopMatrix();

	/* Translate Leg Armor 2 To The Right Part */
	glPushMatrix();
	glTranslatef(0.25, 0, 0);
	legArmor2();
	glPopMatrix();

	/* Translate Thigh Armor 3 To The Right Part */
	glPushMatrix();
	glTranslatef(0.29, 0, 0);
	thighArmor3();
	glPopMatrix();

	/* Rotate 180 To Duplicate Another Part */
	glPushMatrix();
	glRotatef(180, 0, 1, 0);

	leg();
	legArmor3();
	thigh();

	/* Due to not symmetric, translate it to make it symmetric */
	glPushMatrix();
	glTranslatef(0, 0, -0.1);
	upperArmJoint();
	glPopMatrix();

	/* Due to not symmetric, translate it to make it symmetric */
	glPushMatrix();
	glTranslatef(0, 0, -0.2);
	upperArm();
	armMuscle1();
	armMuscle2();
	legTyre();
	muscleLowerArmJoint();
	

		glPushMatrix();
		glTranslatef(0, 0.65, 0.15);
		glRotatef(-rightArmUpSpeed, 1, 0, 0);
		glTranslatef(0, -0.65, -0.15);
		lowerArm();
		hand();
		glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1200, 700,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	
	glScalef(0.4, 0.4, 0.4);
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (leftArmUpStatus == 1) {
			leftArmUpSpeed += 0.01;

			if (leftArmUpSpeed >= 90) {
				leftArmUpSpeed = 90;
				leftArmUpStatus = 0;
			}
		}

		if (rightArmUpStatus == 1) {
			rightArmUpSpeed += 0.01;

			if (rightArmUpSpeed >= 90) {
				rightArmUpSpeed = 90;
				rightArmUpStatus = 0;
			}
		}



		optimusPrime();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------