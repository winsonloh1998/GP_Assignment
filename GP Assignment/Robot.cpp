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
	
	glTranslatef(-0.45, -0.75, 0);
	glRotatef(90, 1, 0, 0);
	gluQuadricDrawStyle(legCylinder, GLU_FILL);
	gluCylinder(legCylinder, 0.08, 0.08, 0.3, 20, 20);
	gluDeleteQuadric(legCylinder);
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
	glVertex3f(-0.35, 0.32, -0.35);
	glVertex3f(-0.2, 0.32, -0.35);
	glVertex3f(-0.2, 0.22, -0.35);
	glEnd();
}

void buttDesign() {
	//Rectangle
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, 0.3, -0.35);
	glVertex3f(0.15, 0.3, -0.35);
	glVertex3f(0.15, 0, -0.35);
	glVertex3f(-0.15, 0, -0.35);
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
	glTranslatef(0, 0, -0.7);
	glRotatef(180, 0, 1, 0);
	buttTriangle();

	glPushMatrix();
	glTranslatef(-0.01, -0.15, 0);
	glScalef(0.9, 0.9, 1);
	buttTriangle();
	glPopMatrix();

	glPopMatrix();
}

void butt() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 0.4, -0.35);
	glVertex3f(0.4, 0.4, -0.35);
	glVertex3f(0.4, 0.1, -0.35);
	glVertex3f(0.075, -0.2, -0.35);
	glVertex3f(-0.075, -0.2, -0.35);
	glVertex3f(-0.4, 0.1, -0.35);
	glEnd();

	//Left Below
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 0.1, -0.35);
	glVertex3f(-0.4, 0.1, 0.35);
	glVertex3f(-0.075, -0.2, 0.35);
	glVertex3f(-0.075, -0.2, -0.35);
	glEnd();

	//Left Above
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 0.1, -0.35);
	glVertex3f(-0.4, 0.1, 0.35);
	glVertex3f(-0.4, 0.4, 0.35);
	glVertex3f(-0.4, 0.4, -0.35);
	glEnd();

	//Top 
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 0.4, -0.35);
	glVertex3f(-0.4, 0.4, 0.35);
	glVertex3f(0.4, 0.4, 0.35);
	glVertex3f(0.4, 0.4, -0.35);
	glEnd();

	//Right Above
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.4, 0.4, -0.35);
	glVertex3f(0.4, 0.4, 0.35);
	glVertex3f(0.4, 0.1, 0.35);
	glVertex3f(0.4, 0.1, -0.35);
	glEnd();

	//Right Below
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.4, 0.1, -0.35);
	glVertex3f(0.4, 0.1, 0.35);
	glVertex3f(0.075, -0.2, 0.35);
	glVertex3f(0.075, -0.2, -0.35);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.075, -0.2, -0.35);
	glVertex3f(0.075, -0.2, 0.35);
	glVertex3f(-0.075, -0.2, 0.35);
	glVertex3f(-0.075, -0.2, -0.35);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 0.4, 0.35);
	glVertex3f(0.4, 0.4, 0.35);
	glVertex3f(0.4, 0.1, 0.35);
	glVertex3f(0.075, -0.2, 0.35);
	glVertex3f(-0.075, -0.2, 0.35);
	glVertex3f(-0.4, 0.1, 0.35);
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

void head() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, 1.9, -0.05);
	glVertex3f(0.15, 1.9, -0.05);
	glVertex3f(0.15, 1.5, -0.05);
	glVertex3f(-0.15, 1.5, -0.05);
	glEnd();

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
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.15, 1.5, 0.25);
	glVertex3f(-0.15, 1.5, 0.25);
	glVertex3f(-0.15, 1.9, 0.25);
	glVertex3f(0.15, 1.9, 0.25);
	glEnd();
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
	glVertex3f(-0.45, 0.75, -0.05);
	glVertex3f(-0.7, 0.75, -0.05);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.7, 0.75, -0.05);
	glVertex3f(-0.7, 0.75, 0.25);
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
	glVertex3f(-0.45, 0.75, 0.25);
	glVertex3f(-0.45, 0.75, -0.05);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.45, 0.75, -0.05);
	glVertex3f(-0.7, 0.75, -0.05);
	glVertex3f(-0.7, 0.75, 0.25);
	glVertex3f(-0.45, 0.75, 0.25);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.45, 0.75, 0.25);
	glVertex3f(-0.7, 0.75, 0.25);
	glVertex3f(-0.7, 1.55, 0.25);
	glVertex3f(-0.45, 1.55, 0.25);
	glEnd();
}

void lowerArm() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.68, 0.75, -0.05);
	glVertex3f(-0.47, 0.75, -0.05);
	glVertex3f(-0.47, 0.1, -0.05);
	glVertex3f(-0.68, 0.1, -0.05);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.68, 0.1, -0.05);
	glVertex3f(-0.68, 0.1, 0.25);
	glVertex3f(-0.68, 0.75, 0.25);
	glVertex3f(-0.68, 0.75, -0.05);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.68, 0.75, -0.05);
	glVertex3f(-0.68, 0.75, 0.25);
	glVertex3f(-0.47, 0.75, 0.25);
	glVertex3f(-0.47, 0.75, -0.05);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.47, 0.75, -0.05);
	glVertex3f(-0.47, 0.75, 0.25);
	glVertex3f(-0.47, 0.1, 0.25);
	glVertex3f(-0.47, 0.1, -0.05);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.47, 0.1, -0.05);
	glVertex3f(-0.68, 0.1, -0.05);
	glVertex3f(-0.68, 0.1, 0.25);
	glVertex3f(-0.47, 0.1, 0.25);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.47, 0.1, 0.25);
	glVertex3f(-0.68, 0.1, 0.25);
	glVertex3f(-0.68, 0.75, 0.25);
	glVertex3f(-0.47, 0.75, 0.25);
	glEnd();
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
	thigh();
	upperArmJoint();
	upperArm();

	/* Move the Left Arm Up & Down */
	glPushMatrix();
	glTranslatef(0, 0.75, 0.15);
	glRotatef(leftArmUpSpeed, 1, 0, 0);
	glTranslatef(0, -0.75, -0.15);
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
	glPopMatrix();

	/* Translate Leg Armor 2 To The Right Part */
	glPushMatrix();
	glTranslatef(0.25, 0, 0);
	legArmor2();
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
	
		glPushMatrix();
		glTranslatef(0, 0.75, 0.15);
		glRotatef(-rightArmUpSpeed, 1, 0, 0);
		glTranslatef(0, -0.75, -0.15);
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