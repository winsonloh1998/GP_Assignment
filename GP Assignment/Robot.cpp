#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")
#pragma warning(disable:4305)

#define WINDOW_TITLE "Optimus Prime"

float leftArmUpSpeed = 0.0;
int leftArmUpStatus = 0;
float x = 0.0, y = 0.0, z = 0.0;
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
		else if (wParam == 'W')
			y += 0.1;
		else if (wParam == 'S')
			y -= 0.1;
		else if (wParam == 'A')
			x += 0.1;
		else if (wParam == 'D')
			x -= 0.1;
		else if (wParam == 'Q')
			z += 0.1;
		else if (wParam == 'E')
			z -= 0.1;
		break;

	case WM_MOUSEWHEEL:
		if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
			//mouse wheel scrolled up
			glScalef(1.1, 1.1, 1.1);
		else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0)
			//mouse wheel scrolled down
			glScalef(0.9, 0.9, 0.9);
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
	GLUquadricObj* legCylinder = NULL;
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
		glVertex3f(-0.45, (sin(degInRad) * (0.15 + 0.05)) - 1.3, (cos(degInRad) * (0.15 - 0.02)) + 0.1);
	}
	glEnd();

	glColor3f(1, 1, 1);
	GLUquadricObj* legTyre1 = NULL;
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
		glVertex3f(-0.45, (sin(degInRad) * (0.15 + 0.05)) - 1.75, (cos(degInRad) * (0.15 - 0.02)) + 0.1);
	}
	glEnd();

	glColor3f(1, 1, 1);
	GLUquadricObj* legTyre2 = NULL;
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
	glVertex3f(-0.4, -0.7, -0.2);
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
	glBegin(GL_POLYGON);
	glVertex3f(-0.13, 0.2, 0.4);
	glVertex3f(-0.13, 0.35, 0.3);
	glVertex3f(-0.13, -0.3, 0.3);
	glVertex3f(-0.13, -0.1, 0.4);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glVertex3f(-0.13, -0.1, 0.4);
	glVertex3f(0.13, -0.1, 0.4);
	glVertex3f(0.13, 0.2, 0.4);
	glVertex3f(-0.13, 0.2, 0.4);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glVertex3f(-0.13, 0.2, 0.4);
	glVertex3f(0.13, 0.2, 0.4);
	glVertex3f(0.13, 0.35, 0.3);
	glVertex3f(-0.13, 0.35, 0.3);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glVertex3f(-0.13, 0.35, 0.3);
	glVertex3f(0.13, 0.35, 0.3);
	glVertex3f(0.13, -0.3, 0.3);
	glVertex3f(-0.13, -0.3, 0.3);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glVertex3f(-0.13, -0.3, 0.3);
	glVertex3f(-0.13, -0.1, 0.4);
	glVertex3f(0.13, -0.1, 0.4);
	glVertex3f(0.13, -0.3, 0.3);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glVertex3f(0.13, -0.3, 0.3);
	glVertex3f(0.13, -0.1, 0.4);
	glVertex3f(0.13, 0.2, 0.4);
	glVertex3f(0.13, 0.35, 0.3);
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

void sixPackBlader() {
	//1st Blade
	glBegin(GL_POLYGON);
	glVertex3f(-0.225, 0.95, -0.255);
	glVertex3f(-0.01, 0.95, -0.255);
	glVertex3f(-0.01, 0.89, -0.265);
	glVertex3f(-0.225, 0.89, -0.265);
	glEnd();

	//2nd Blade
	glBegin(GL_POLYGON);
	glVertex3f(-0.225, 0.88, -0.255);
	glVertex3f(-0.01, 0.88, -0.255);
	glVertex3f(-0.01, 0.82, -0.265);
	glVertex3f(-0.225, 0.82, -0.265);
	glEnd();

	//3rd Blade
	glBegin(GL_POLYGON);
	glVertex3f(-0.225, 0.81, -0.255);
	glVertex3f(-0.01, 0.81, -0.255);
	glVertex3f(-0.01, 0.75, -0.265);
	glVertex3f(-0.225, 0.75, -0.265);
	glEnd();

	//4th Blade
	glBegin(GL_POLYGON);
	glVertex3f(-0.225, 0.74, -0.255);
	glVertex3f(-0.01, 0.74, -0.255);
	glVertex3f(-0.01, 0.68, -0.265);
	glVertex3f(-0.225, 0.68, -0.265);
	glEnd();

	//5th Blade
	glBegin(GL_POLYGON);
	glVertex3f(-0.225, 0.67, -0.255);
	glVertex3f(-0.01, 0.67, -0.255);
	glVertex3f(-0.01, 0.61, -0.265);
	glVertex3f(-0.225, 0.61, -0.265);
	glEnd();

	//6th Blade
	glBegin(GL_POLYGON);
	glVertex3f(-0.225, 0.60, -0.255);
	glVertex3f(-0.01, 0.60, -0.255);
	glVertex3f(-0.01, 0.54, -0.265);
	glVertex3f(-0.225, 0.54, -0.265);
	glEnd();

	//7th Blade
	glBegin(GL_POLYGON);
	glVertex3f(-0.225, 0.53, -0.255);
	glVertex3f(-0.01, 0.53, -0.255);
	glVertex3f(-0.01, 0.47, -0.265);
	glVertex3f(-0.225, 0.47, -0.265);
	glEnd();

	//8th Blade
	glBegin(GL_POLYGON);
	glVertex3f(-0.225, 0.46, -0.255);
	glVertex3f(-0.01, 0.46, -0.255);
	glVertex3f(-0.01, 0.4, -0.265);
	glVertex3f(-0.225, 0.4, -0.265);
	glEnd();
}

void sixPackArmor1() {
	glColor3f(0.8, 0.8, 0.8);
	//Front 1
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, 1, -0.275);
	glVertex3f(-0.225, 1, -0.275);
	glVertex3f(-0.225, 0.4, -0.275);
	glVertex3f(-0.25, 0.4, -0.275);
	glEnd();

	//Front 2
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, 1, -0.275);
	glVertex3f(0.25, 1, -0.275);
	glVertex3f(0.25, 0.95, -0.275);
	glVertex3f(-0.25, 0.95, -0.275);
	glEnd();

	//Front 3
	glBegin(GL_POLYGON);
	glVertex3f(0.225, 1, -0.275);
	glVertex3f(0.25, 1, -0.275);
	glVertex3f(0.25, 0.4, -0.275);
	glVertex3f(0.225, 0.4, -0.275);
	glEnd();

	//Front 4
	glBegin(GL_POLYGON);
	glVertex3f(-0.225, 1, -0.275);
	glVertex3f(-0.225, 1, -0.251);
	glVertex3f(-0.225, 0.4, -0.251);
	glVertex3f(-0.225, 0.4, -0.275);
	glEnd();

	//Front 5
	glBegin(GL_POLYGON);
	glVertex3f(-0.225, 1, -0.275);
	glVertex3f(-0.225, 1, -0.251);
	glVertex3f(0.225, 0.95, -0.251);
	glVertex3f(0.225, 0.95, -0.275);
	glEnd();

	//Front 6
	glBegin(GL_POLYGON);
	glVertex3f(0.225, 1, -0.275);
	glVertex3f(0.225, 1, -0.251);
	glVertex3f(0.225, 0.4, -0.251);
	glVertex3f(0.225, 0.4, -0.275);
	glEnd();

	//Front 7
	glBegin(GL_POLYGON);
	glVertex3f(-0.01, 1, -0.27);
	glVertex3f(0.01, 1, -0.251);
	glVertex3f(0.01, 0.4, -0.251);
	glVertex3f(-0.01, 0.4, -0.27);
	glEnd();

	//Front 8
	glBegin(GL_POLYGON);
	glVertex3f(-0.01, 1, -0.27);
	glVertex3f(-0.01, 1, -0.251);
	glVertex3f(-0.01, 0.4, -0.251);
	glVertex3f(-0.01, 0.4, -0.27);
	glEnd();

	//Front 9
	glBegin(GL_POLYGON);
	glVertex3f(0.01, 1, -0.27);
	glVertex3f(0.01, 1, -0.251);
	glVertex3f(0.01, 0.4, -0.251);
	glVertex3f(0.01, 0.4, -0.27);
	glEnd();

	glColor3f(1, 0, 0);

	//Left Six-Pack Blader
	sixPackBlader();

	//Right Six-Pack Blader
	glPushMatrix();
	glTranslatef(0.235, 0, 0);
	sixPackBlader();
	glPopMatrix();

	glColor3f(1, 1, 1);
	//Left
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, 0.4, -0.275);
	glVertex3f(-0.25, 0.4, -0.251);
	glVertex3f(-0.25, 1, -0.251);
	glVertex3f(-0.25, 1, -0.275);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, 1, -0.275);
	glVertex3f(-0.25, 1, -0.251);
	glVertex3f(0.25, 1, -0.251);
	glVertex3f(0.25, 1, -0.275);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 1, -0.275);
	glVertex3f(0.25, 1, -0.251);
	glVertex3f(0.25, 0.4, -0.251);
	glVertex3f(0.25, 0.4, -0.275);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 0.4, -0.275);
	glVertex3f(-0.25, 0.4, -0.275);
	glVertex3f(-0.25, 0.4, -0.251);
	glVertex3f(0.25, 0.4, -0.251);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 0.4, -0.25);
	glVertex3f(-0.25, 0.4, -0.25);
	glVertex3f(-0.25, 1, -0.251);
	glVertex3f(0.25, 1, -0.251);
	glEnd();
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

void chestMirrorFrameSide() {

	glColor3f(1, 0, 0);

	//Frame Side 1 - Front
	glBegin(GL_POLYGON);
	glVertex3f(-0.4, 1.4, -0.35);
	glVertex3f(-0.35, 1.35, -0.35);
	glVertex3f(-0.35, 1.05, -0.35);
	glVertex3f(-0.4, 1.0, -0.35);
	glEnd();

	//Frame Side 1 - Left
	glBegin(GL_POLYGON);
	glVertex3f(-0.4, 1.0, -0.35);
	glVertex3f(-0.4, 1.0, -0.25);
	glVertex3f(-0.4, 1.4, -0.25);
	glVertex3f(-0.4, 1.4, -0.35);
	glEnd();

	//Frame Side 1 - Top
	glBegin(GL_POLYGON);
	glVertex3f(-0.4, 1.4, -0.35);
	glVertex3f(-0.4, 1.4, -0.25);
	glVertex3f(-0.35, 1.35, -0.25);
	glVertex3f(-0.35, 1.35, -0.35);
	glEnd();

	//Frame Side 1 - Right
	glBegin(GL_POLYGON);
	glVertex3f(-0.35, 1.35, -0.35);
	glVertex3f(-0.35, 1.35, -0.25);
	glVertex3f(-0.35, 1.05, -0.25);
	glVertex3f(-0.35, 1.05, -0.35);
	glEnd();

	//Frame Side 1 - Bottom
	glBegin(GL_POLYGON);
	glVertex3f(-0.35, 1.05, -0.35);
	glVertex3f(-0.4, 1.0, -0.35);
	glVertex3f(-0.4, 1.0, -0.25);
	glVertex3f(-0.35, 1.05, -0.25);
	glEnd();

	//Frame Side 1 - Back
	glBegin(GL_POLYGON);
	glVertex3f(-0.35, 1.05, -0.25);
	glVertex3f(-0.4, 1.0, -0.25);
	glVertex3f(-0.4, 1.4, -0.25);
	glVertex3f(-0.35, 1.35, -0.25);
	glEnd();

	//////////////////////////////////////// Frame Side 2 ////////////////////////////////////////////
	//Frame Side 2 - Front
	glBegin(GL_POLYGON);
	glVertex3f(-0.4, 1.4, -0.35);
	glVertex3f(0, 1.4, -0.35);
	glVertex3f(-0.05, 1.35, -0.35);
	glVertex3f(-0.35, 1.35, -0.35);
	glEnd();

	//Frame Side 2 - Left
	glBegin(GL_POLYGON);
	glVertex3f(-0.35, 1.35, -0.35);
	glVertex3f(-0.35, 1.35, -0.25);
	glVertex3f(-0.4, 1.4, -0.25);
	glVertex3f(-0.4, 1.4, -0.35);
	glEnd();

	//Frame Side 2 - Top
	glBegin(GL_POLYGON);
	glVertex3f(-0.4, 1.4, -0.35);
	glVertex3f(-0.4, 1.4, -0.25);
	glVertex3f(0, 1.4, -0.25);
	glVertex3f(0, 1.4, -0.35);
	glEnd();

	//Frame Side 2 - Right
	glBegin(GL_POLYGON);
	glVertex3f(0, 1.4, -0.35);
	glVertex3f(0, 1.4, -0.25);
	glVertex3f(-0.05, 1.35, -0.25);
	glVertex3f(-0.05, 1.35, -0.35);
	glEnd();

	//Frame Side 2 - Bottom
	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 1.35, -0.35);
	glVertex3f(-0.35, 1.35, -0.35);
	glVertex3f(-0.35, 1.35, -0.25);
	glVertex3f(-0.05, 1.35, -0.25);
	glEnd();

	//Frame Side 2 - Back
	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 1.35, -0.25);
	glVertex3f(-0.35, 1.35, -0.25);
	glVertex3f(-0.4, 1.4, -0.25);
	glVertex3f(0, 1.4, -0.25);
	glEnd();

	//////////////////////////////////////// Frame Side 3 ////////////////////////////////////////////
	//Frame Side 3 - Front
	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 1.35, -0.35);
	glVertex3f(0.0, 1.4, -0.35);
	glVertex3f(0.0, 1.0, -0.35);
	glVertex3f(-0.05, 1.05, -0.35);
	glEnd();

	//Frame Side 3 - Left
	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 1.05, -0.35);
	glVertex3f(-0.05, 1.05, -0.25);
	glVertex3f(-0.05, 1.35, -0.25);
	glVertex3f(-0.05, 1.35, -0.35);
	glEnd();

	//Frame Side 3 - Top
	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 1.35, -0.35);
	glVertex3f(-0.05, 1.35, -0.25);
	glVertex3f(0.0, 1.4, -0.25);
	glVertex3f(0.0, 1.4, -0.35);
	glEnd();

	//Frame Side 3 - Right
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 1.4, -0.35);
	glVertex3f(0.0, 1.4, -0.25);
	glVertex3f(0.0, 1.0, -0.25);
	glVertex3f(0.0, 1.0, -0.35);
	glEnd();

	//Frame Side 3 - Bottom
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 1.0, -0.35);
	glVertex3f(-0.05, 1.05, -0.35);
	glVertex3f(-0.05, 1.05, -0.25);
	glVertex3f(0.0, 1.0, -0.25);
	glEnd();

	//Frame Side 3 - Back
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 1.0, -0.25);
	glVertex3f(-0.05, 1.05, -0.25);
	glVertex3f(-0.05, 1.35, -0.25);
	glVertex3f(0.0, 1.4, -0.25);
	glEnd();

	//////////////////////////////////////// Frame Side 4 ////////////////////////////////////////////

	//Frame Side 4 - Front
	glBegin(GL_POLYGON);
	glVertex3f(-0.35, 1.05, -0.35);
	glVertex3f(-0.05, 1.05, -0.35);
	glVertex3f(0.0, 1.0, -0.35);
	glVertex3f(-0.4, 1.0, -0.35);
	glEnd();

	//Frame Side 4 - Left
	glBegin(GL_POLYGON);
	glVertex3f(-0.4, 1.0, -0.35);
	glVertex3f(-0.4, 1.0, -0.25);
	glVertex3f(-0.35, 1.05, -0.25);
	glVertex3f(-0.35, 1.05, -0.35);
	glEnd();

	//Frame Side 4 - Top
	glBegin(GL_POLYGON);
	glVertex3f(-0.35, 1.05, -0.35);
	glVertex3f(-0.35, 1.05, -0.25);
	glVertex3f(-0.05, 1.05, -0.25);
	glVertex3f(-0.05, 1.05, -0.35);
	glEnd();

	//Frame Side 4 - Right
	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 1.05, -0.35);
	glVertex3f(-0.05, 1.05, -0.25);
	glVertex3f(0.0, 1.0, -0.25);
	glVertex3f(0.0, 1.0, -0.35);
	glEnd();

	//Frame Side 4 - Bottom
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 1.0, -0.35);
	glVertex3f(-0.4, 1.0, -0.35);
	glVertex3f(-0.4, 1.0, -0.25);
	glVertex3f(0.0, 1.0, -0.25);
	glEnd();

	//Frame Side 4 - Back
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 1.0, -0.25);
	glVertex3f(-0.4, 1.0, -0.25);
	glVertex3f(-0.35, 1.05, -0.25);
	glVertex3f(-0.05, 1.05, -0.25);
	glEnd();

	glColor3f(1, 1, 1);
}

void chestMirror() {
	glColor3f(0.53, 0.81, 0.92);

	//Front
	glBegin(GL_POLYGON);
	glVertex3f(-0.35, 1.35, -0.31);
	glVertex3f(-0.05, 1.35, -0.31);
	glVertex3f(-0.05, 1.05, -0.31);
	glVertex3f(-0.35, 1.05, -0.31);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glVertex3f(-0.35, 1.05, -0.31);
	glVertex3f(-0.35, 1.05, -0.29);
	glVertex3f(-0.35, 1.35, -0.29);
	glVertex3f(-0.35, 1.35, -0.31);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glVertex3f(-0.35, 1.35, -0.31);
	glVertex3f(-0.35, 1.35, -0.29);
	glVertex3f(-0.05, 1.35, -0.29);
	glVertex3f(-0.05, 1.35, -0.31);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 1.35, -0.31);
	glVertex3f(-0.05, 1.35, -0.29);
	glVertex3f(-0.05, 1.05, -0.29);
	glVertex3f(-0.05, 1.05, -0.31);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 1.05, -0.31);
	glVertex3f(-0.35, 1.05, -0.31);
	glVertex3f(-0.35, 1.05, -0.29);
	glVertex3f(-0.05, 1.05, -0.29);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glVertex3f(-0.05, 1.05, -0.29);
	glVertex3f(-0.35, 1.05, -0.29);
	glVertex3f(-0.35, 1.35, -0.29);
	glVertex3f(-0.05, 1.35, -0.29);
	glEnd();

	glColor3f(1, 1, 1);
}

void chestMirrorFrame() {
	//Center Line
	glBegin(GL_POLYGON);
	glVertex3f(0, 1.4, -0.35);
	glVertex3f(0, 1.4, -0.25);
	glVertex3f(0, 1.0, -0.25);
	glVertex3f(0, 1.0, -0.35);
	glEnd();

	//Left Frame
	chestMirrorFrameSide();
	chestMirror();

	//Right Frame
	glPushMatrix();
	glTranslatef(0.4, 0, 0);
	chestMirrorFrameSide();
	chestMirror();
	glPopMatrix();
}

void chestArmor1() {
	/*
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 1.4, -0.3);
	glVertex3f(0.4, 1.4, -0.3);
	glVertex3f(0.4, 1.0, -0.3);
	glVertex3f(-0.4, 1.0, -0.3);
	glEnd();
	*/

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 1.0, -0.35);
	glVertex3f(-0.4, 1.0, -0.25);
	glVertex3f(-0.4, 1.5, -0.25);
	glVertex3f(-0.4, 1.4, -0.35);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 1.4, -0.35);
	glVertex3f(-0.4, 1.5, -0.25);
	glVertex3f(0.4, 1.5, -0.25);
	glVertex3f(0.4, 1.4, -0.35);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.4, 1.4, -0.35);
	glVertex3f(0.4, 1.5, -0.25);
	glVertex3f(0.4, 1.0, -0.25);
	glVertex3f(0.4, 1.0, -0.35);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.4, 1.0, -0.35);
	glVertex3f(-0.4, 1.0, -0.35);
	glVertex3f(-0.4, 1.0, -0.25);
	glVertex3f(0.4, 1.0, -0.25);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.4, 1.0, -0.25);
	glVertex3f(-0.4, 1.0, -0.25);
	glVertex3f(-0.4, 1.5, -0.25);
	glVertex3f(0.4, 1.5, -0.25);
	glEnd();
}

void chestArmor2() {
	GLUquadricObj* upperChestCylinder1 = NULL;
	upperChestCylinder1 = gluNewQuadric();

	glPushMatrix();
	glTranslatef(-0.35, 1.5, -0.275);
	gluQuadricDrawStyle(upperChestCylinder1, GLU_LINE);
	gluCylinder(upperChestCylinder1, 0.02, 0.02, 0.05, 20, 20);
	gluDeleteQuadric(upperChestCylinder1);
	glPopMatrix();

	GLUquadricObj* upperChestCylinder2 = NULL;
	upperChestCylinder2 = gluNewQuadric();

	glPushMatrix();
	glTranslatef(-0.3, 1.5, -0.275);
	gluQuadricDrawStyle(upperChestCylinder2, GLU_LINE);
	gluCylinder(upperChestCylinder2, 0.02, 0.02, 0.05, 20, 20);
	gluDeleteQuadric(upperChestCylinder2);
	glPopMatrix();

	GLUquadricObj* upperChestCylinder3 = NULL;
	upperChestCylinder3 = gluNewQuadric();

	glPushMatrix();
	glTranslatef(0.3, 1.5, -0.275);
	gluQuadricDrawStyle(upperChestCylinder3, GLU_LINE);
	gluCylinder(upperChestCylinder3, 0.02, 0.02, 0.05, 20, 20);
	gluDeleteQuadric(upperChestCylinder3);
	glPopMatrix();

	GLUquadricObj* upperChestCylinder4 = NULL;
	upperChestCylinder4 = gluNewQuadric();

	glPushMatrix();
	glTranslatef(0.35, 1.5, -0.275);
	gluQuadricDrawStyle(upperChestCylinder4, GLU_LINE);
	gluCylinder(upperChestCylinder4, 0.02, 0.02, 0.05, 20, 20);
	gluDeleteQuadric(upperChestCylinder4);
	glPopMatrix();
}

void chest() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 1.5, -0.25);
	glVertex3f(0.4, 1.5, -0.25);
	glVertex3f(0.4, 1, -0.25);
	glVertex3f(-0.4, 1, -0.25);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 1, -0.25);
	glVertex3f(-0.4, 1, 0.35);
	glVertex3f(-0.4, 1.5, 0.35);
	glVertex3f(-0.4, 1.5, -0.25);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 1.5, -0.25);
	glVertex3f(-0.4, 1.5, 0.35);
	glVertex3f(0.4, 1.5, 0.35);
	glVertex3f(0.4, 1.5, -0.25);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.4, 1.5, -0.25);
	glVertex3f(0.4, 1.5, 0.35);
	glVertex3f(0.4, 1, 0.35);
	glVertex3f(0.4, 1, -0.25);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.4, 1, -0.25);
	glVertex3f(-0.4, 1, -0.25);
	glVertex3f(-0.4, 1, 0.35);
	glVertex3f(0.4, 1, 0.35);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.4, 1, 0.35);
	glVertex3f(-0.4, 1, 0.35);
	glVertex3f(-0.4, 1.5, 0.35);
	glVertex3f(0.4, 1.5, 0.35);
	glEnd();
}

void middleChest() {
	//Left Front
	glBegin(GL_POLYGON);
	glVertex3f(-0.4, 1, -0.35);
	glVertex3f(-0.25, 1, -0.35);
	glVertex3f(-0.27, 0.8, -0.3);
	glVertex3f(-0.35, 0.8, -0.3);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glVertex3f(-0.35, 0.8, -0.3);
	glVertex3f(-0.35, 0.8, 0.3);
	glVertex3f(-0.4, 1, 0.35);
	glVertex3f(-0.4, 1, -0.35);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glVertex3f(-0.4, 1, -0.35);
	glVertex3f(-0.4, 1, 0.35);
	glVertex3f(0.4, 1, 0.35);
	glVertex3f(0.4, 1, -0.35);
	glVertex3f(0.25, 1, -0.35);
	glVertex3f(0.25, 1, -0.25);
	glVertex3f(-0.25, 1, -0.25);
	glVertex3f(-0.25, 1, -0.35);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glVertex3f(0.4, 1, -0.35);
	glVertex3f(0.4, 1, 0.35);
	glVertex3f(0.35, 0.8, 0.3);
	glVertex3f(0.35, 0.8, -0.3);
	glEnd();


	//Right Front
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 1, -0.35);
	glVertex3f(0.4, 1, -0.35);
	glVertex3f(0.35, 0.8, -0.3);
	glVertex3f(0.27, 0.8, -0.3);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glVertex3f(0.35, 0.8, -0.3);
	glVertex3f(0.27, 0.8, -0.3);
	glVertex3f(0.27, 0.8, -0.25);
	glVertex3f(-0.27, 0.8, -0.25);
	glVertex3f(-0.27, 0.8, -0.3);
	glVertex3f(-0.35, 0.8, -0.3);
	glVertex3f(-0.35, 0.8, 0.3);
	glVertex3f(0.35, 0.8, 0.3);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glVertex3f(0.35, 0.8, 0.3);
	glVertex3f(-0.35, 0.8, 0.3);
	glVertex3f(-0.4, 1, 0.35);
	glVertex3f(0.4, 1, 0.35);
	glEnd();

	glColor3f(0, 1, 0);
	//Internal 1
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, 1, -0.35);
	glVertex3f(-0.25, 1, -0.25);
	glVertex3f(-0.27, 0.8, -0.25);
	glVertex3f(-0.27, 0.8, -0.3);
	glEnd();

	//Internal 2
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, 1, -0.25);
	glVertex3f(0.25, 1, -0.25);
	glVertex3f(0.27, 0.8, -0.25);
	glVertex3f(-0.27, 0.8, -0.25);
	glEnd();

	//Internal 3
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 1, -0.35);
	glVertex3f(0.25, 1, -0.25);
	glVertex3f(0.27, 0.8, -0.25);
	glVertex3f(0.27, 0.8, -0.3);
	glEnd();
	glColor3f(1, 1, 1);
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

	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.68, 0.8, -0.01);
	glVertex3f(-0.47, 0.8, -0.01);
	glVertex3f(-0.47, 0.7, -0.01);
	glVertex3f(-0.68, 0.7, -0.01);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.68, 0.7, -0.01);
	glVertex3f(-0.68, 0.7, 0.21);
	glVertex3f(-0.68, 0.8, 0.21);
	glVertex3f(-0.68, 0.8, -0.01);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.68, 0.8, -0.01);
	glVertex3f(-0.68, 0.8, 0.21);
	glVertex3f(-0.47, 0.8, 0.21);
	glVertex3f(-0.47, 0.8, -0.01);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.47, 0.8, -0.01);
	glVertex3f(-0.47, 0.8, 0.21);
	glVertex3f(-0.47, 0.7, 0.21);
	glVertex3f(-0.47, 0.7, -0.01);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.47, 0.7, -0.01);
	glVertex3f(-0.68, 0.7, -0.01);
	glVertex3f(-0.68, 0.7, 0.21);
	glVertex3f(-0.47, 0.7, 0.21);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.47, 0.7, 0.21);
	glVertex3f(-0.68, 0.7, 0.21);
	glVertex3f(-0.68, 0.8, 0.21);
	glVertex3f(-0.47, 0.8, 0.21);
	glEnd();

}

void lowerArmArmor1() {
	glColor3f(1, 0, 0);

	//Lower Arm Shield (Front) - 1
	glBegin(GL_POLYGON);
	glVertex3f(-0.71, 0.5, -0.025);
	glVertex3f(-0.45, 0.5, -0.025);
	glVertex3f(-0.45, 0.1, -0.025);
	glVertex3f(-0.71, 0.1, -0.025);
	glEnd();

	//Lower Arm Shield (Left) - 1
	glBegin(GL_POLYGON);
	glVertex3f(-0.71, 0.1, -0.025);
	glVertex3f(-0.71, 0.1, -0.01);
	glVertex3f(-0.71, 0.5, -0.01);
	glVertex3f(-0.71, 0.5, -0.025);
	glEnd();

	//Lower Arm Shield (Right) - 1
	glBegin(GL_POLYGON);
	glVertex3f(-0.45, 0.5, -0.025);
	glVertex3f(-0.45, 0.5, -0.01);
	glVertex3f(-0.45, 0.1, -0.01);
	glVertex3f(-0.45, 0.1, -0.025);
	glEnd();

	//Lower Arm Shield (Bottom) - 1
	glBegin(GL_POLYGON);
	glVertex3f(-0.45, 0.1, -0.025);
	glVertex3f(-0.71, 0.1, -0.025);
	glVertex3f(-0.71, 0.1, -0.01);
	glVertex3f(-0.45, 0.1, -0.01);
	glEnd();

	////////////////////////////////////////////////////////////////////////////

	//Lower Arm Shield (Front) - 2
	glBegin(GL_POLYGON);
	glVertex3f(-0.71, 0.65, -0.025);
	glVertex3f(-0.63, 0.65, -0.025);
	glVertex3f(-0.63, 0.1, -0.025);
	glVertex3f(-0.71, 0.1, -0.025);
	glEnd();

	//Lower Arm Shield (Left) - 2
	glBegin(GL_POLYGON);
	glVertex3f(-0.71, 0.1, -0.025);
	glVertex3f(-0.71, 0.1, -0.01);
	glVertex3f(-0.71, 0.7, -0.01);
	glVertex3f(-0.71, 0.65, -0.025);
	glEnd();

	//Lower Arm Shield (Top) - 2
	glBegin(GL_POLYGON);
	glVertex3f(-0.71, 0.65, -0.025);
	glVertex3f(-0.71, 0.7, -0.01);
	glVertex3f(-0.63, 0.7, -0.01);
	glVertex3f(-0.63, 0.65, -0.025);
	glEnd();

	//Lower Arm Shield (Right) - 2
	glBegin(GL_POLYGON);
	glVertex3f(-0.63, 0.65, -0.025);
	glVertex3f(-0.63, 0.7, -0.01);
	glVertex3f(-0.63, 0.1, -0.01);
	glVertex3f(-0.63, 0.1, -0.025);
	glEnd();

	//Lower Arm Shield (Bottom) - 2
	glBegin(GL_POLYGON);
	glVertex3f(-0.63, 0.1, -0.025);
	glVertex3f(-0.71, 0.1, -0.025);
	glVertex3f(-0.71, 0.1, -0.01);
	glVertex3f(-0.63, 0.1, -0.01);
	glEnd();

	//Lower Arm Shield (Back) - 2
	glBegin(GL_POLYGON);
	glVertex3f(-0.63, 0.1, -0.01);
	glVertex3f(-0.71, 0.1, -0.01);
	glVertex3f(-0.71, 0.7, -0.01);
	glVertex3f(-0.63, 0.7, -0.01);
	glEnd();

	////////////////////////////////////////////////////////////////////////////

	//Lower Arm Shield (Front) - 3
	glBegin(GL_POLYGON);
	glVertex3f(-0.53, 0.65, -0.025);
	glVertex3f(-0.45, 0.65, -0.025);
	glVertex3f(-0.45, 0.1, -0.025);
	glVertex3f(-0.53, 0.1, -0.025);
	glEnd();

	//Lower Arm Shield (Left) - 3
	glBegin(GL_POLYGON);
	glVertex3f(-0.53, 0.1, -0.025);
	glVertex3f(-0.53, 0.1, -0.01);
	glVertex3f(-0.53, 0.7, -0.01);
	glVertex3f(-0.53, 0.65, -0.025);
	glEnd();

	//Lower Arm Shield (Top) - 3
	glBegin(GL_POLYGON);
	glVertex3f(-0.53, 0.65, -0.025);
	glVertex3f(-0.53, 0.7, -0.01);
	glVertex3f(-0.45, 0.7, -0.01);
	glVertex3f(-0.45, 0.65, -0.025);
	glEnd();

	//Lower Arm Shield (Right) - 3
	glBegin(GL_POLYGON);
	glVertex3f(-0.45, 0.65, -0.025);
	glVertex3f(-0.45, 0.7, -0.01);
	glVertex3f(-0.45, 0.1, -0.01);
	glVertex3f(-0.45, 0.1, -0.025);
	glEnd();

	//Lower Arm Shield (Bottom) - 3
	glBegin(GL_POLYGON);
	glVertex3f(-0.45, 0.1, -0.025);
	glVertex3f(-0.53, 0.1, -0.025);
	glVertex3f(-0.53, 0.1, -0.01);
	glVertex3f(-0.45, 0.1, -0.01);
	glEnd();

	//Lower Arm Shield (Back) - 3
	glBegin(GL_POLYGON);
	glVertex3f(-0.45, 0.1, -0.01);
	glVertex3f(-0.53, 0.1, -0.01);
	glVertex3f(-0.53, 0.7, -0.01);
	glVertex3f(-0.45, 0.7, -0.01);
	glEnd();

	glColor3f(1, 1, 1);
}

void lowerArmArmor2() {
	//Upper Rectangular
	glBegin(GL_POLYGON);
	glVertex3f(-0.63, 0.34, -0.0255);
	glVertex3f(-0.53, 0.34, -0.0255);
	glVertex3f(-0.53, 0.315, -0.0255);
	glVertex3f(-0.63, 0.315, -0.0255);
	glEnd();

	//Lower Rectangular
	glBegin(GL_POLYGON);
	glVertex3f(-0.63, 0.3, -0.0255);
	glVertex3f(-0.53, 0.3, -0.0255);
	glVertex3f(-0.53, 0.275, -0.0255);
	glVertex3f(-0.63, 0.275, -0.0255);
	glEnd();

	//Triangle
	glBegin(GL_POLYGON);
	glVertex3f(-0.61, 0.25, -0.0255);
	glVertex3f(-0.55, 0.25, -0.0255);
	glVertex3f(-0.58, 0.2, -0.0255);
	glEnd();
}

void lowerArm() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.71, 0.7, -0.01);
	glVertex3f(-0.45, 0.7, -0.01);
	glVertex3f(-0.45, 0.1, -0.01);
	glVertex3f(-0.71, 0.1, -0.01);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.71, 0.1, -0.01);
	glVertex3f(-0.71, 0.1, 0.225);
	glVertex3f(-0.71, 0.7, 0.225);
	glVertex3f(-0.71, 0.7, -0.01);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.71, 0.7, -0.01);
	glVertex3f(-0.71, 0.7, 0.225);
	glVertex3f(-0.45, 0.7, 0.225);
	glVertex3f(-0.45, 0.7, -0.01);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.45, 0.7, -0.01);
	glVertex3f(-0.45, 0.7, 0.225);
	glVertex3f(-0.45, 0.1, 0.225);
	glVertex3f(-0.45, 0.1, -0.01);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.45, 0.1, -0.01);
	glVertex3f(-0.71, 0.1, -0.01);
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
	GLUquadricObj* bottomAntenna = NULL;
	bottomAntenna = gluNewQuadric();

	glPushMatrix();
	glScalef(1, 1, 0.8);
	glTranslatef(-0.74, 1.4, 0.125);
	glRotatef(90, 1, 0, 0);
	gluQuadricDrawStyle(bottomAntenna, GLU_LINE);
	gluCylinder(bottomAntenna, 0.03, 0.03, 0.5, 20, 20);
	gluDeleteQuadric(bottomAntenna);
	glPopMatrix();

	GLUquadricObj* topAntenna = NULL;
	topAntenna = gluNewQuadric();

	glPushMatrix();
	glScalef(1, 1, 0.8);
	glTranslatef(-0.74, 1.75, 0.125);
	glRotatef(90, 1, 0, 0);
	gluQuadricDrawStyle(topAntenna, GLU_LINE);
	gluCylinder(topAntenna, 0.02, 0.02, 0.4, 20, 20);
	gluDeleteQuadric(topAntenna);
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

void backArmor1() {
	/* View From The Back */
	glColor3f(0, 1, 0);
	//Front
	glBegin(GL_POLYGON);
	glVertex3f(-0.2, 0.4, 0.4);
	glVertex3f(0.2, 0.4, 0.4);
	glVertex3f(0.15, 0.25, 0.35);
	glVertex3f(-0.15, 0.25, 0.35);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glVertex3f(-0.15, 0.25, 0.35);
	glVertex3f(-0.15, 0.25, 0.3);
	glVertex3f(-0.2, 0.4, 0.3);
	glVertex3f(-0.2, 0.4, 0.4);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glVertex3f(-0.2, 0.4, 0.4);
	glVertex3f(-0.2, 0.4, 0.3);
	glVertex3f(0.2, 0.4, 0.3);
	glVertex3f(0.2, 0.4, 0.4);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glVertex3f(0.2, 0.4, 0.4);
	glVertex3f(0.2, 0.4, 0.3);
	glVertex3f(0.15, 0.25, 0.3);
	glVertex3f(0.15, 0.25, 0.35);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glVertex3f(0.15, 0.25, 0.35);
	glVertex3f(-0.15, 0.25, 0.35);
	glVertex3f(-0.15, 0.25, 0.3);
	glVertex3f(0.15, 0.25, 0.3);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glVertex3f(0.15, 0.25, 0.3);
	glVertex3f(-0.15, 0.25, 0.3);
	glVertex3f(-0.2, 0.4, 0.3);
	glVertex3f(0.2, 0.4, 0.3);
	glEnd();

	glColor3f(1, 1, 1);
}

void backArmor2SmallTrapezium() {
	//Front
	glBegin(GL_POLYGON);
	glVertex3f(0.132, 0.59, 0.41);
	glVertex3f(0.122, 0.63, 0.41);
	glVertex3f(0.1, 0.65, 0.41);
	glVertex3f(0.12, 0.55, 0.41);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glVertex3f(0.122, 0.63, 0.41);
	glVertex3f(0.122, 0.63, 0.4);
	glVertex3f(0.132, 0.59, 0.4);
	glVertex3f(0.132, 0.59, 0.41);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glVertex3f(0.122, 0.63, 0.41);
	glVertex3f(0.122, 0.63, 0.4);
	glVertex3f(0.1, 0.65, 0.4);
	glVertex3f(0.1, 0.65, 0.41);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glVertex3f(0.1, 0.65, 0.41);
	glVertex3f(0.1, 0.65, 0.4);
	glVertex3f(0.12, 0.55, 0.4);
	glVertex3f(0.12, 0.55, 0.41);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glVertex3f(0.132, 0.59, 0.41);
	glVertex3f(0.132, 0.59, 0.4);
	glVertex3f(0.12, 0.55, 0.4);
	glVertex3f(0.12, 0.55, 0.41);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glVertex3f(0.132, 0.59, 0.4);
	glVertex3f(0.122, 0.63, 0.4);
	glVertex3f(0.1, 0.65, 0.4);
	glVertex3f(0.12, 0.55, 0.4);
	glEnd();
}

void backArmor2Details() {
	//Trapezium - Front
	glBegin(GL_POLYGON);
	glVertex3f(-0.06, 0.7, 0.41);
	glVertex3f(0.06, 0.7, 0.41);
	glVertex3f(0.10, 0.4, 0.41);
	glVertex3f(-0.10, 0.4, 0.41);
	glEnd();

	//Trapezium - Left
	glBegin(GL_POLYGON);
	glVertex3f(-0.1, 0.4, 0.41);
	glVertex3f(-0.1, 0.4, 0.4);
	glVertex3f(-0.06, 0.7, 0.4);
	glVertex3f(-0.06, 0.7, 0.41);
	glEnd();

	//Trapezium - Top
	glBegin(GL_POLYGON);
	glVertex3f(-0.06, 0.7, 0.41);
	glVertex3f(-0.06, 0.7, 0.4);
	glVertex3f(0.06, 0.7, 0.4);
	glVertex3f(0.06, 0.7, 0.41);
	glEnd();

	//Trapezium - Right
	glBegin(GL_POLYGON);
	glVertex3f(0.06, 0.7, 0.41);
	glVertex3f(0.06, 0.7, 0.4);
	glVertex3f(0.1, 0.4, 0.4);
	glVertex3f(0.1, 0.4, 0.41);
	glEnd();

	//Trapezium - Bottom
	glBegin(GL_POLYGON);
	glVertex3f(0.1, 0.4, 0.41);
	glVertex3f(-0.1, 0.4, 0.41);
	glVertex3f(-0.1, 0.4, 0.4);
	glVertex3f(0.1, 0.4, 0.4);
	glEnd();

	//Trapezium - Back
	glBegin(GL_POLYGON);
	glVertex3f(0.1, 0.4, 0.4);
	glVertex3f(-0.1, 0.4, 0.4);
	glVertex3f(-0.06, 0.7, 0.4);
	glVertex3f(0.06, 0.7, 0.4);
	glEnd();

	//////////////////////////////////////////
	//LEFT
	backArmor2SmallTrapezium();

	//RIGHT
	glPushMatrix();
	glTranslatef(0, 0, 0.81);
	glRotatef(180, 0, 1, 0);
	backArmor2SmallTrapezium();
	glPopMatrix();
}

void backArmor2() {
	glColor3f(0, 1, 0);
	//Front 
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, 1.0, 0.4);
	glVertex3f(0.25, 1.0, 0.4);
	glVertex3f(0.2, 0.4, 0.4);
	glVertex3f(-0.2, 0.4, 0.4);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glVertex3f(-0.2, 0.4, 0.4);
	glVertex3f(-0.2, 0.4, 0.3);
	glVertex3f(-0.225, 0.8, 0.3);
	glVertex3f(-0.25, 1.0, 0.35);
	glVertex3f(-0.25, 1.0, 0.4);
	glEnd();

	//Top - 1
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, 1.0, 0.4);
	glVertex3f(-0.25, 1.0, 0.35);
	glVertex3f(0.25, 1.0, 0.35);
	glVertex3f(0.25, 1.0, 0.4);
	glEnd();

	//Top - 2
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 1.0, 0.35);
	glVertex3f(-0.25, 1.0, 0.35);
	glVertex3f(-0.225, 0.8, 0.3);
	glVertex3f(0.225, 0.8, 0.3);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 1.0, 0.4);
	glVertex3f(0.25, 1.0, 0.35);
	glVertex3f(0.225, 0.8, 0.3);
	glVertex3f(0.2, 0.4, 0.3);
	glVertex3f(0.2, 0.4, 0.4);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glVertex3f(0.2, 0.4, 0.4);
	glVertex3f(-0.2, 0.4, 0.4);
	glVertex3f(-0.2, 0.4, 0.3);
	glVertex3f(0.2, 0.4, 0.3);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glVertex3f(0.2, 0.4, 0.3);
	glVertex3f(-0.2, 0.4, 0.3);
	glVertex3f(-0.225, 0.8, 0.3);
	glVertex3f(0.225, 0.8, 0.3);
	glEnd();

	glColor3f(1, 0, 0);
	backArmor2Details();
	glColor3f(1, 1, 1);
}

void backArmor3() {
	//Front 
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, 1.5, 0.4);
	glVertex3f(0.25, 1.5, 0.4);
	glVertex3f(0.25, 1.0, 0.4);
	glVertex3f(-0.25, 1.0, 0.4);
	glEnd();

	//Left 
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, 1.0, 0.4);
	glVertex3f(-0.25, 1.0, 0.35);
	glVertex3f(-0.25, 1.5, 0.35);
	glVertex3f(-0.25, 1.5, 0.4);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, 1.5, 0.4);
	glVertex3f(-0.25, 1.5, 0.35);
	glVertex3f(0.25, 1.5, 0.35);
	glVertex3f(0.25, 1.5, 0.4);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 1.5, 0.4);
	glVertex3f(0.25, 1.5, 0.35);
	glVertex3f(0.25, 1.0, 0.35);
	glVertex3f(0.25, 1.0, 0.4);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 1.0, 0.4);
	glVertex3f(-0.25, 1.0, 0.4);
	glVertex3f(-0.25, 1.0, 0.35);
	glVertex3f(0.25, 1.0, 0.35);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 1.0, 0.35);
	glVertex3f(-0.25, 1.0, 0.35);
	glVertex3f(-0.25, 1.5, 0.35);
	glVertex3f(0.25, 1.5, 0.35);
	glEnd();
}

void backArmor4() {
	glColor3f(0, 0, 1);

	/* RIGHT PART */
	//Inner based on Z
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, 1.55, 0.45);
	glVertex3f(-0.25, 1.55, 0.35);
	glVertex3f(-0.25, 1.0, 0.35);
	glVertex3f(-0.25, 1.0, 0.45);
	glEnd();

	//Inner based on X
	glBegin(GL_POLYGON);
	glVertex3f(-0.35, 1.55, 0.35);
	glVertex3f(-0.25, 1.55, 0.35);
	glVertex3f(-0.25, 1.0, 0.35);
	glVertex3f(-0.35, 1.0, 0.35);
	glEnd();

	//Outer
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, 1.55, 0.45);
	glVertex3f(-0.35, 1.55, 0.35);
	glVertex3f(-0.35, 1.0, 0.35);
	glVertex3f(-0.25, 1.0, 0.45);
	glEnd();

	//Upper Triangle
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, 1.55, 0.45);
	glVertex3f(-0.25, 1.55, 0.35);
	glVertex3f(-0.35, 1.55, 0.35);
	glEnd();

	//Below Triangle
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, 1.0, 0.45);
	glVertex3f(-0.25, 1.0, 0.35);
	glVertex3f(-0.35, 1.0, 0.35);
	glEnd();

	//////////////////////////////////////////////////////////////

	/* LEFT PART */
	//Inner based on Z
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 1.55, 0.45);
	glVertex3f(0.25, 1.55, 0.35);
	glVertex3f(0.25, 1.0, 0.35);
	glVertex3f(0.25, 1.0, 0.45);
	glEnd();

	//Inner based on X
	glBegin(GL_POLYGON);
	glVertex3f(0.35, 1.55, 0.35);
	glVertex3f(0.25, 1.55, 0.35);
	glVertex3f(0.25, 1.0, 0.35);
	glVertex3f(0.35, 1.0, 0.35);
	glEnd();

	//Outer
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 1.55, 0.45);
	glVertex3f(0.35, 1.55, 0.35);
	glVertex3f(0.35, 1.0, 0.35);
	glVertex3f(0.25, 1.0, 0.45);
	glEnd();

	//Upper Triangle
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 1.55, 0.45);
	glVertex3f(0.25, 1.55, 0.35);
	glVertex3f(0.35, 1.55, 0.35);
	glEnd();

	//Below Triangle
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 1.0, 0.45);
	glVertex3f(0.25, 1.0, 0.35);
	glVertex3f(0.35, 1.0, 0.35);
	glEnd();

	glColor3f(1, 1, 1);
}
void gun()
{
	GLUquadricObj* guncylinder = NULL;
	//gun part 1 shoot-part
	glPushMatrix();
	glTranslatef(0.95, 1, 0);
	glRotatef(90, 0, 1, 0);
	guncylinder = gluNewQuadric();
	gluQuadricDrawStyle(guncylinder, GLU_LINE);
	gluCylinder(guncylinder, 0.05, 0.1, 0.05, 30, 30);
	gluDeleteQuadric(guncylinder);
	glPopMatrix();

	//gunpart 1 
	glPushMatrix();
	glTranslatef(1, 1, 0);
	glRotatef(90, 0, 1, 0);

	guncylinder = gluNewQuadric();
	gluQuadricDrawStyle(guncylinder, GLU_LINE);
	gluCylinder(guncylinder, 0.1, 0.1, 0.3, 30, 30);
	gluDeleteQuadric(guncylinder);
	glPopMatrix();
	//gun part 2 
	glPushMatrix();
	glTranslatef(1.4, 1, 0);
	glRotatef(90, 0, 1, 0);
	guncylinder = gluNewQuadric();
	gluQuadricDrawStyle(guncylinder, GLU_LINE);
	gluCylinder(guncylinder, 0.1, 0.1, 0.3, 30, 30);
	gluDeleteQuadric(guncylinder);
	glPopMatrix();
	//gun part 2 upper
	glBegin(GL_POLYGON);
	glVertex3f(1.4, 1.1, 0);
	glVertex3f(1.43, 1.15, 0);
	glVertex3f(1.5, 1.15, 0);
	glVertex3f(1.5, 1.1, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.4, 1.1, 0.025);
	glVertex3f(1.43, 1.15, 0.025);
	glVertex3f(1.5, 1.15, 0.025);
	glVertex3f(1.5, 1.1, 0.025);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.4, 1.1, 0);
	glVertex3f(1.43, 1.15, 0);
	glVertex3f(1.43, 1.15, 0.025);
	glVertex3f(1.4, 1.1, 0.025);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.43, 1.15, 0.025);
	glVertex3f(1.43, 1.15, 0);
	glVertex3f(1.5, 1.15, 0);
	glVertex3f(1.5, 1.15, 0.025);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex3f(1.4, 1.1, 0.025);
	glVertex3f(1.4, 1.1, 0);
	glVertex3f(1.5, 1.1, 0);
	glVertex3f(1.5, 1.1, 0.025);
	glEnd();
	//...
	glBegin(GL_POLYGON);
	glVertex3f(1.5, 1.1, -0.02);
	glVertex3f(1.5, 1.18, -0.02);
	glVertex3f(1.6, 1.18, -0.02);
	glVertex3f(1.7, 1.1, -0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.5, 1.1, 0.027);
	glVertex3f(1.5, 1.18, 0.027);
	glVertex3f(1.6, 1.18, 0.027);
	glVertex3f(1.7, 1.1, 0.027);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.5, 1.1, -0.02);
	glVertex3f(1.5, 1.18, -0.02);
	glVertex3f(1.5, 1.18, 0.027);
	glVertex3f(1.5, 1.1, 0.027);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.5, 1.18, -0.02);
	glVertex3f(1.5, 1.18, 0.027);
	glVertex3f(1.6, 1.18, 0.027);
	glVertex3f(1.6, 1.18, -0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.5, 1.1, -0.02);
	glVertex3f(1.5, 1.1, 0.027);
	glVertex3f(1.7, 1.1, 0.027);
	glVertex3f(1.7, 1.1, -0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.6, 1.18, -0.02);
	glVertex3f(1.6, 1.18, 0.027);
	glVertex3f(1.7, 1.1, 0.027);
	glVertex3f(1.7, 1.1, -0.02);
	glEnd();

	//===============
	//gun handle part 2

	glBegin(GL_POLYGON);
	glVertex3f(1.5, 0.9, -0.05);
	glVertex3f(1.55, 0.9, -0.05);
	glVertex3f(1.55, 0.8, -0.05);
	glVertex3f(1.5, 0.8, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.5, 0.9, 0.05);
	glVertex3f(1.55, 0.9, 0.05);
	glVertex3f(1.55, 0.8, 0.05);
	glVertex3f(1.5, 0.8, 0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.55, 0.9, -0.05);
	glVertex3f(1.55, 0.9, 0.05);
	glVertex3f(1.55, 0.8, 0.05);
	glVertex3f(1.55, 0.8, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.5, 0.9, -0.05);
	glVertex3f(1.5, 0.9, 0.05);
	glVertex3f(1.5, 0.8, 0.05);
	glVertex3f(1.5, 0.8, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.5, 0.8, -0.05);
	glVertex3f(1.55, 0.8, -0.05);
	glVertex3f(1.55, 0.8, 0.05);
	glVertex3f(1.5, 0.8, 0.05);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex3f(1.5, 0.9, -0.05);
	glVertex3f(1.55, 0.9, -0.05);
	glVertex3f(1.55, 0.8, -0.05);
	glVertex3f(1.5, 0.8, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.5, 0.9, 0.05);
	glVertex3f(1.55, 0.9, 0.05);
	glVertex3f(1.55, 0.8, 0.05);
	glVertex3f(1.5, 0.8, 0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.55, 0.9, -0.05);
	glVertex3f(1.55, 0.9, 0.05);
	glVertex3f(1.55, 0.8, 0.05);
	glVertex3f(1.55, 0.8, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.5, 0.9, -0.05);
	glVertex3f(1.5, 0.9, 0.05);
	glVertex3f(1.5, 0.8, 0.05);
	glVertex3f(1.5, 0.8, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.5, 0.8, -0.05);
	glVertex3f(1.55, 0.8, -0.05);
	glVertex3f(1.55, 0.8, 0.05);
	glVertex3f(1.5, 0.8, 0.05);
	glEnd();

	//angled grip
	glBegin(GL_POLYGON);
	glVertex3f(1.55, 0.86, -0.025);
	glVertex3f(1.65, 0.86, -0.025);
	glVertex3f(1.65, 0.85, -0.025);
	glVertex3f(1.55, 0.85, -0.025);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(1.55, 0.86, 0.0);
	glVertex3f(1.65, 0.86, 0.0);
	glVertex3f(1.65, 0.85, 0.0);
	glVertex3f(1.55, 0.85, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.55, 0.86, -0.025);
	glVertex3f(1.65, 0.86, -0.025);
	glVertex3f(1.65, 0.86, 0.0);
	glVertex3f(1.55, 0.86, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.55, 0.85, -0.025);
	glVertex3f(1.65, 0.85, -0.025);
	glVertex3f(1.65, 0.85, 0.0);
	glVertex3f(1.55, 0.85, 0.0);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex3f(1.55, 0.85, -0.025);
	glVertex3f(1.55, 0.86, -0.025);
	glVertex3f(1.55, 0.86, 0.0);
	glVertex3f(1.55, 0.85, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.65, 0.85, -0.025);
	glVertex3f(1.65, 0.86, -0.025);
	glVertex3f(1.65, 0.86, 0.0);
	glVertex3f(1.65, 0.85, 0.0);
	glEnd();
	//..... xie mian
	glBegin(GL_POLYGON);
	glVertex3f(1.65, 0.85, -0.025);
	glVertex3f(1.65, 0.86, -0.025);
	glVertex3f(1.68, 0.9, -0.025);
	glVertex3f(1.69, 0.9, -0.025);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.65, 0.85, 0.0);
	glVertex3f(1.65, 0.86, 0.0);
	glVertex3f(1.68, 0.9, 0.0);
	glVertex3f(1.69, 0.9, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.65, 0.85, -0.025);
	glVertex3f(1.65, 0.85, 0.0);
	glVertex3f(1.68, 0.9, 0.0);
	glVertex3f(1.69, 0.9, -0.025);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.65, 0.86, -0.025);
	glVertex3f(1.65, 0.86, 0.0);
	glVertex3f(1.68, 0.9, 0.0);
	glVertex3f(1.69, 0.9, -0.025);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.65, 0.9, -0.025);
	glVertex3f(1.65, 0.9, 0.0);
	glVertex3f(1.68, 0.9, 0.0);
	glVertex3f(1.69, 0.9, -0.025);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex3f(1.65, 0.86, -0.025);
	glVertex3f(1.65, 0.86, 0.0);
	glVertex3f(1.65, 0.85, 0.0);
	glVertex3f(1.65, 0.85, -0.025);
	glEnd();

	//....
	glBegin(GL_POLYGON);
	glVertex3f(1.58, 0.86, -0.025);
	glVertex3f(1.59, 0.86, -0.025);
	glVertex3f(1.59, 0.90, -0.025);
	glVertex3f(1.58, 0.90, -0.025);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.58, 0.86, 0.0);
	glVertex3f(1.59, 0.86, 0.0);
	glVertex3f(1.59, 0.90, 0.0);
	glVertex3f(1.58, 0.90, 0.0);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex3f(1.58, 0.86, -0.025);
	glVertex3f(1.58, 0.86, 0.0);
	glVertex3f(1.58, 0.90, 0.0);
	glVertex3f(1.58, 0.90, -0.025);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.59, 0.86, -0.025);
	glVertex3f(1.59, 0.86, 0.0);
	glVertex3f(1.59, 0.90, 0.0);
	glVertex3f(1.59, 0.90, -0.025);
	glEnd();

	glVertex3f(1.58, 0.9, -0.025);
	glVertex3f(1.58, 0.9, 0.0);
	glVertex3f(1.59, 0.9, 0.0);
	glVertex3f(1.59, 0.90, -0.025);

	glBegin(GL_POLYGON);
	glVertex3f(1.58, 0.86, -0.025);
	glVertex3f(1.58, 0.86, 0.0);
	glVertex3f(1.59, 0.86, 0.0);
	glVertex3f(1.59, 0.86, -0.025);
	glEnd();
	//........
	glBegin(GL_POLYGON);
	glVertex3f(1.63, 0.86, -0.025);
	glVertex3f(1.64, 0.86, -0.025);
	glVertex3f(1.64, 0.90, -0.025);
	glVertex3f(1.63, 0.90, -0.025);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.63, 0.86, 0.0);
	glVertex3f(1.64, 0.86, 0.0);
	glVertex3f(1.64, 0.90, 0.0);
	glVertex3f(1.63, 0.90, 0.0);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex3f(1.63, 0.86, -0.025);
	glVertex3f(1.63, 0.86, 0.0);
	glVertex3f(1.63, 0.90, 0.0);
	glVertex3f(1.63, 0.90, -0.025);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.64, 0.86, -0.025);
	glVertex3f(1.64, 0.86, 0.0);
	glVertex3f(1.64, 0.90, 0.0);
	glVertex3f(1.64, 0.90, -0.025);
	glEnd();

	glVertex3f(1.63, 0.9, -0.025);
	glVertex3f(1.63, 0.9, 0.0);
	glVertex3f(1.64, 0.9, 0.0);
	glVertex3f(1.64, 0.90, -0.025);

	glBegin(GL_POLYGON);
	glVertex3f(1.63, 0.86, -0.025);
	glVertex3f(1.63, 0.86, 0.0);
	glVertex3f(1.64, 0.86, 0.0);
	glVertex3f(1.64, 0.86, -0.025);
	glEnd();
	//......
	//laser
	glPushMatrix();
	glTranslatef(1.45, 0.87, 0);
	glRotatef(90, 0, 1, 0);
	guncylinder = gluNewQuadric();
	gluQuadricDrawStyle(guncylinder, GLU_LINE);
	gluCylinder(guncylinder, 0.01, 0.01, 0.05, 30, 30);
	gluDeleteQuadric(guncylinder);
	glPopMatrix();

	//=====================================		

			//gunpart2 connector
	glPushMatrix();
	glTranslatef(1.3, 1, 0);
	glRotatef(90, 0, 1, 0);
	guncylinder = gluNewQuadric();
	gluQuadricDrawStyle(guncylinder, GLU_LINE);
	gluCylinder(guncylinder, 0.1, 0.05, 0.05, 30, 30);
	gluDeleteQuadric(guncylinder);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.35, 1, 0);
	glRotatef(90, 0, 1, 0);
	guncylinder = gluNewQuadric();
	gluQuadricDrawStyle(guncylinder, GLU_LINE);
	gluCylinder(guncylinder, 0.05, 0.1, 0.05, 30, 30);
	gluDeleteQuadric(guncylinder);
	glPopMatrix();

	//gunpart 3 connector

	glPushMatrix();
	glTranslatef(1.7, 1, 0);
	glRotatef(90, 0, 1, 0);
	guncylinder = gluNewQuadric();
	gluQuadricDrawStyle(guncylinder, GLU_LINE);
	gluCylinder(guncylinder, 0.1, 0.05, 0.05, 30, 30);
	gluDeleteQuadric(guncylinder);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.75, 1, 0);
	glRotatef(90, 0, 1, 0);
	guncylinder = gluNewQuadric();
	gluQuadricDrawStyle(guncylinder, GLU_LINE);
	gluCylinder(guncylinder, 0.05, 0.2, 0.05, 30, 30);
	gluDeleteQuadric(guncylinder);
	glPopMatrix();

	//gunpart 3
	glPushMatrix();
	glTranslatef(1.8, 1, 0);
	glRotatef(90, 0, 1, 0);
	guncylinder = gluNewQuadric();
	gluQuadricDrawStyle(guncylinder, GLU_LINE);
	gluCylinder(guncylinder, 0.2, 0.2, 0.3, 30, 30);
	gluDeleteQuadric(guncylinder);
	glPopMatrix();
	//handle part 3 
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(1.9, 0.8, -0.05);
	glVertex3f(2.0, 0.8, -0.05);
	glVertex3f(2.0, 0.79, -0.05);
	glVertex3f(1.9, 0.79, -0.05);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(1.9, 0.5, -0.05);
	glVertex3f(2.0, 0.5, -0.05);
	glVertex3f(2.0, 0.52, -0.05);
	glVertex3f(1.9, 0.52, -0.05);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(1.9, 0.52, -0.05);
	glVertex3f(2.0, 0.52, -0.05);
	glVertex3f(2.0, 0.57, -0.05);
	glVertex3f(1.9, 0.57, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.9, 0.6, -0.05);
	glVertex3f(2.0, 0.6, -0.05);
	glVertex3f(2.0, 0.65, -0.05);
	glVertex3f(1.9, 0.65, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.9, 0.7, -0.05);
	glVertex3f(2.0, 0.7, -0.05);
	glVertex3f(2.0, 0.75, -0.05);
	glVertex3f(1.9, 0.75, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.9, 0.5, -0.05);
	glVertex3f(1.91, 0.5, -0.05);
	glVertex3f(1.91, 0.8, -0.05);
	glVertex3f(1.9, 0.8, -0.05);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex3f(1.99, 0.5, -0.05);
	glVertex3f(2.0, 0.5, -0.05);
	glVertex3f(2.0, 0.8, -0.05);
	glVertex3f(1.99, 0.8, -0.05);
	glEnd();



	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(1.9, 0.8, 0.05);
	glVertex3f(2.0, 0.8, 0.05);
	glVertex3f(2.0, 0.5, 0.05);
	glVertex3f(1.9, 0.5, 0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.0, 0.8, -0.05);
	glVertex3f(2.0, 0.8, 0.05);
	glVertex3f(2.0, 0.5, 0.05);
	glVertex3f(2.0, 0.5, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.9, 0.8, -0.05);
	glVertex3f(1.9, 0.8, 0.05);
	glVertex3f(1.9, 0.5, 0.05);
	glVertex3f(1.9, 0.5, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(1.9, 0.5, -0.05);
	glVertex3f(2.0, 0.5, -0.05);
	glVertex3f(2.0, 0.5, 0.05);
	glVertex3f(1.9, 0.5, 0.05);
	glEnd();

	//==========================================================

		//gun part 4 
	glPushMatrix();
	glTranslatef(2.1, 1, 0);
	glRotatef(90, 0, 1, 0);
	guncylinder = gluNewQuadric();
	gluQuadricDrawStyle(guncylinder, GLU_LINE);
	gluCylinder(guncylinder, 0.25, 0.25, 0.2, 30, 30);
	gluDeleteQuadric(guncylinder);
	glPopMatrix();
	//handle part4 
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(2.2, 0.75, -0.05);
	glVertex3f(2.3, 0.75, -0.05);
	glVertex3f(2.3, 0.65, -0.05);
	glVertex3f(2.2, 0.65, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.2, 0.65, -0.05);
	glVertex3f(2.3, 0.65, -0.05);
	glVertex3f(2.3, 0.65, 0.05);
	glVertex3f(2.2, 0.65, 0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.2, 0.35, -0.05);
	glVertex3f(2.3, 0.35, -0.05);
	glVertex3f(2.3, 0.3, -0.05);
	glVertex3f(2.2, 0.3, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.2, 0.35, -0.05);
	glVertex3f(2.3, 0.35, -0.05);
	glVertex3f(2.3, 0.35, 0.05);
	glVertex3f(2.2, 0.35, 0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.2, 0.55, -0.05);
	glVertex3f(2.3, 0.55, -0.05);
	glVertex3f(2.3, 0.55, 0.05);
	glVertex3f(2.2, 0.55, 0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.2, 0.55, -0.05);
	glVertex3f(2.3, 0.55, -0.05);
	glVertex3f(2.3, 0.5, -0.05);
	glVertex3f(2.2, 0.5, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.2, 0.5, -0.05);
	glVertex3f(2.3, 0.5, -0.05);
	glVertex3f(2.3, 0.5, 0.05);
	glVertex3f(2.2, 0.5, 0.05);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(2.2, 0.65, -0.05);
	glVertex3f(2.3, 0.65, -0.05);
	glVertex3f(2.3, 0.6, -0.05);
	glVertex3f(2.2, 0.6, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.2, 0.6, -0.05);
	glVertex3f(2.3, 0.6, -0.05);
	glVertex3f(2.3, 0.6, 0.05);
	glVertex3f(2.2, 0.6, 0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.2, 0.45, -0.05);
	glVertex3f(2.3, 0.45, -0.05);
	glVertex3f(2.3, 0.4, -0.05);
	glVertex3f(2.2, 0.4, -0.05);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex3f(2.2, 0.45, -0.05);
	glVertex3f(2.3, 0.45, -0.05);
	glVertex3f(2.3, 0.45, 0.05);
	glVertex3f(2.2, 0.45, 0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.2, 0.4, -0.05);
	glVertex3f(2.3, 0.4, -0.05);
	glVertex3f(2.3, 0.4, 0.05);
	glVertex3f(2.2, 0.4, 0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.2, 0.75, -0.05);
	glVertex3f(2.21, 0.75, -0.05);
	glVertex3f(2.21, 0.3, -0.05);
	glVertex3f(2.2, 0.3, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.29, 0.75, -0.05);
	glVertex3f(2.3, 0.75, -0.05);
	glVertex3f(2.3, 0.3, -0.05);
	glVertex3f(2.29, 0.3, -0.05);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(2.2, 0.75, 0.05);
	glVertex3f(2.3, 0.75, 0.05);
	glVertex3f(2.3, 0.3, 0.05);
	glVertex3f(2.2, 0.3, 0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.3, 0.75, -0.05);
	glVertex3f(2.3, 0.75, 0.05);
	glVertex3f(2.3, 0.3, 0.05);
	glVertex3f(2.3, 0.3, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.2, 0.75, -0.05);
	glVertex3f(2.2, 0.75, 0.05);
	glVertex3f(2.2, 0.3, 0.05);
	glVertex3f(2.2, 0.3, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.2, 0.3, -0.05);
	glVertex3f(2.3, 0.3, -0.05);
	glVertex3f(2.3, 0.3, 0.05);
	glVertex3f(2.2, 0.3, 0.05);
	glEnd();
	//gun tail
//==========================================
	/*
	glBegin(GL_POLYGON);
	glVertex3f(2.3,0.75,-0.25);
	glVertex3f(2.5, 0.75, -0.25);
	glVertex3f(2.5, 1.3, -0.25);
	glVertex3f(2.3, 1.4, -0.25);
	glEnd();
	*/
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(2.3, 1.3, -0.25);
	glVertex3f(2.5, 1.3, -0.25);
	glVertex3f(2.3, 1.4, -0.25);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.47, 1.2, -0.25);

	glVertex3f(2.40, 1.3, -0.25);
	glVertex3f(2.47, 1.3, -0.25);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.47, 1.2, -0.25);
	glVertex3f(2.3, 1.2, -0.25);
	glVertex3f(2.3, 1.25, -0.25);
	glVertex3f(2.47, 1.25, -0.25);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.47, 1.1, -0.25);
	glVertex3f(2.3, 1.1, -0.25);
	glVertex3f(2.3, 1.15, -0.25);
	glVertex3f(2.47, 1.15, -0.25);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.47, 1.0, -0.25);
	glVertex3f(2.3, 1.0, -0.25);
	glVertex3f(2.3, 1.05, -0.25);
	glVertex3f(2.47, 1.05, -0.25);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex3f(2.47, 0.9, -0.25);
	glVertex3f(2.3, 0.9, -0.25);
	glVertex3f(2.3, 0.95, -0.25);
	glVertex3f(2.47, 0.95, -0.25);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.47, 0.8, -0.25);
	glVertex3f(2.3, 0.8, -0.25);
	glVertex3f(2.3, 0.85, -0.25);
	glVertex3f(2.47, 0.85, -0.25);
	glEnd();



	glBegin(GL_POLYGON);
	glVertex3f(2.3, 0.75, -0.25);
	glVertex3f(2.3, 1.3, -0.25);
	glVertex3f(2.33, 1.3, -0.25);
	glVertex3f(2.33, 0.75, -0.25);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.3, 0.75, -0.25);
	glVertex3f(2.5, 0.75, -0.25);
	glVertex3f(2.5, 0.85, -0.25);
	glVertex3f(2.3, 0.85, -0.25);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.47, 0.75, -0.25);
	glVertex3f(2.47, 1.3, -0.25);
	glVertex3f(2.5, 1.3, -0.25);
	glVertex3f(2.5, 0.75, -0.25);
	glEnd();
	glColor3f(1.0, 1.0, 1.0);



	glBegin(GL_POLYGON);
	glVertex3f(2.3, 0.75, 0.25);
	glVertex3f(2.5, 0.75, 0.25);
	glVertex3f(2.5, 1.3, 0.25);
	glVertex3f(2.3, 1.4, 0.25);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.5, 0.75, -0.25);
	glVertex3f(2.5, 0.75, 0.25);
	glVertex3f(2.5, 1.30, 0.25);
	glVertex3f(2.5, 1.30, -0.25);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(2.3, 1.4, -0.25);
	glVertex3f(2.3, 1.4, 0.25);
	glVertex3f(2.5, 1.30, 0.25);
	glVertex3f(2.5, 1.30, -0.25);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(2.5, 0.75, -0.25);
	glVertex3f(2.5, 1.3, -0.25);
	glVertex3f(2.3, 1.4, -0.25);
	glVertex3f(2.3, 1.4, 0.25);
	glVertex3f(2.5, 1.3, 0.25);
	glVertex3f(2.5, 0.75, 0.25);
	glEnd();



	glBegin(GL_POLYGON);
	glVertex3f(2.3, 0.75, -0.25);
	glVertex3f(2.3, 1.4, -0.25);
	glVertex3f(2.3, 1.4, 0.25);
	glVertex3f(2.3, 0.75, 0.25);

	glEnd();


	glBegin(GL_POLYGON);
	glVertex3f(2.3, 0.75, -0.25);
	glVertex3f(2.5, 0.75, -0.25);
	glVertex3f(2.5, 0.75, 0.25);
	glVertex3f(2.3, 0.75, -0.25);
	glEnd();



	//=========================================================


}
void blade()
{
	glColor3f(1.0, 0.0, 0.0);
	//RT1
	glBegin(GL_POLYGON);
	glVertex3f(-1.51, 1.0, 0.02);
	glVertex3f(-1.43, 0.9, 0.02);
	glVertex3f(-1.51, 0.9, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.51, 1.0, 0.03);
	glVertex3f(-1.43, 0.9, 0.03);
	glVertex3f(-1.51, 1.0, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.51, 1.0, 0.03);
	glVertex3f(-1.51, 1.0, 0.02);
	glVertex3f(-1.51, 0.9, 0.02);
	glVertex3f(-1.51, 0.9, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.51, 1.0, 0.03);
	glVertex3f(-1.51, 1.0, 0.02);
	glVertex3f(-1.43, 0.9, 0.02);
	glVertex3f(-1.43, 0.9, 0.03);
	glEnd();



	//RC1
	glBegin(GL_POLYGON);
	glVertex3f(-1.51, 0.9, 0.02);
	glVertex3f(-1.43, 0.9, 0.02);
	glVertex3f(-1.43, 0.4, 0.02);
	glVertex3f(-1.51, 0.4, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.51, 0.9, 0.03);
	glVertex3f(-1.43, 0.9, 0.03);
	glVertex3f(-1.43, 0.4, 0.03);
	glVertex3f(-1.51, 0.4, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.51, 0.9, 0.03);
	glVertex3f(-1.51, 0.4, 0.03);
	glVertex3f(-1.51, 0.4, 0.02);
	glVertex3f(-1.51, 0.9, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.43, 0.9, 0.03);
	glVertex3f(-1.43, 0.4, 0.03);
	glVertex3f(-1.43, 0.4, 0.02);
	glVertex3f(-1.43, 0.9, 0.02);
	glEnd();



	//RT2
	glBegin(GL_POLYGON);
	glVertex3f(-1.51, 0.45, 0.02);
	glVertex3f(-1.51, 0.4, 0.02);
	glVertex3f(-1.59, 0.4, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.51, 0.45, 0.03);
	glVertex3f(-1.51, 0.4, 0.03);
	glVertex3f(-1.59, 0.4, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.51, 0.45, 0.02);
	glVertex3f(-1.51, 0.4, 0.02);
	glVertex3f(-1.51, 0.4, 0.03);
	glVertex3f(-1.51, 0.45, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.51, 0.4, 0.03);
	glVertex3f(-1.51, 0.4, 0.02);
	glVertex3f(-1.59, 0.4, 0.02);
	glVertex3f(-1.59, 0.4, 0.03);
	glEnd();

	//RT3
	glBegin(GL_POLYGON);
	glVertex3f(-1.43, 0.4, 0.02);
	glVertex3f(-1.51, 0.4, 0.02);
	glVertex3f(-1.51, 0.36, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.43, 0.4, 0.03);
	glVertex3f(-1.51, 0.4, 0.03);
	glVertex3f(-1.51, 0.36, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.51, 0.4, 0.03);
	glVertex3f(-1.51, 0.36, 0.03);
	glVertex3f(-1.51, 0.36, 0.02);
	glVertex3f(-1.51, 0.4, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.53, 0.4, 0.03);
	glVertex3f(-1.53, 0.4, 0.02);
	glVertex3f(-1.51, 0.4, 0.02);
	glVertex3f(-1.51, 0.4, 0.03);
	glEnd();



	//RC2
	glBegin(GL_POLYGON);
	glVertex3f(-1.51, 0.4, 0.02);
	glVertex3f(-1.59, 0.4, 0.02);
	glVertex3f(-1.59, 0.0, 0.02);
	glVertex3f(-1.51, 0.0, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.51, 0.4, 0.03);
	glVertex3f(-1.59, 0.4, 0.03);
	glVertex3f(-1.59, 0.0, 0.03);
	glVertex3f(-1.51, 0.0, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.59, 0.4, 0.03);
	glVertex3f(-1.59, 0.0, 0.03);
	glVertex3f(-1.59, 0.0, 0.02);
	glVertex3f(-1.59, 0.4, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.51, 0.4, 0.03);
	glVertex3f(-1.51, 0.0, 0.03);
	glVertex3f(-1.51, 0.0, 0.02);
	glVertex3f(-1.51, 0.4, 0.02);
	glEnd();


	//RT4
	glBegin(GL_POLYGON);
	glVertex3f(-1.59, 0.05, 0.02);
	glVertex3f(-1.59, 0.0, 0.02);
	glVertex3f(-1.61, 0.0, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.59, 0.05, 0.03);
	glVertex3f(-1.59, 0.0, 0.03);
	glVertex3f(-1.61, 0.0, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.59, 0.05, 0.02);
	glVertex3f(-1.59, 0.0, 0.02);
	glVertex3f(-1.59, 0.0, 0.03);
	glVertex3f(-1.59, 0.05, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.59, 0.05, 0.02);
	glVertex3f(-1.59, 0.0, 0.03);
	glVertex3f(-1.61, 0.0, 0.03);
	glVertex3f(-1.61, 0.0, 0.02);
	glEnd();


	//RT5
	glBegin(GL_POLYGON);
	glVertex3f(-1.51, 0.0, 0.02);
	glVertex3f(-1.53, 0.0, 0.02);
	glVertex3f(-1.53, -0.05, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.51, 0.0, 0.03);
	glVertex3f(-1.53, 0.0, 0.03);
	glVertex3f(-1.53, -0.05, 0.03);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-1.53, 0.0, 0.03);
	glVertex3f(-1.53, -0.05, 0.03);
	glVertex3f(-1.53, -0.05, 0.02);
	glVertex3f(-1.53, 0.0, 0.02);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-1.51, 0.0, 0.03);
	glVertex3f(-1.51, 0.0, 0.02);
	glVertex3f(-1.53, -0.05, 0.02);
	glVertex3f(-1.53, -0.05, 0.03);
	glEnd();
	//RC3
	glBegin(GL_POLYGON);
	glVertex3f(-1.53, 0.0, 0.02);
	glVertex3f(-1.61, 0.0, 0.02);
	glVertex3f(-1.61, -0.3, 0.02);
	glVertex3f(-1.53, -0.3, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.53, 0.0, 0.03);
	glVertex3f(-1.61, 0.0, 0.03);
	glVertex3f(-1.61, -0.3, 0.03);
	glVertex3f(-1.53, -0.3, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.53, 0.0, 0.02);
	glVertex3f(-1.53, -0.3, 0.02);
	glVertex3f(-1.53, -0.3, 0.03);
	glVertex3f(-1.53, 0.0, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-1.61, 0.0, 0.02);
	glVertex3f(-1.61, -0.3, 0.02);
	glVertex3f(-1.61, -0.3, 0.03);
	glVertex3f(-1.61, 0.0, 0.03);
	glEnd();
	glColor3f(1.0, 1.0, 1.0);

	//T1
	glBegin(GL_POLYGON);
	glVertex3f(-1.52, 0.9, 0.0);
	glVertex3f(-1.60, 0.8, 0.0);
	glVertex3f(-1.52, 0.8, 0.0);
	glEnd();
	//C1
	glBegin(GL_POLYGON);
	glVertex3f(-1.60, 0.8, 0.0);
	glVertex3f(-1.52, 0.8, 0.0);
	glVertex3f(-1.52, 0.4, 0.0);
	glVertex3f(-1.60, 0.4, 0.0);
	glEnd();
	//T2
	glBegin(GL_POLYGON);
	glVertex3f(-1.52, 0.45, 0.0);
	glVertex3f(-1.52, 0.4, 0.0);
	glVertex3f(-1.44, 0.4, 0.0);
	glEnd();
	//T3
	glBegin(GL_POLYGON);
	glVertex3f(-1.60, 0.4, 0.0);
	glVertex3f(-1.52, 0.4, 0.0);
	glVertex3f(-1.52, 0.36, 0.0);
	glEnd();
	//C2
	glBegin(GL_POLYGON);
	glVertex3f(-1.52, 0.4, 0.0);
	glVertex3f(-1.44, 0.4, 0.0);
	glVertex3f(-1.44, 0.0, 0.0);
	glVertex3f(-1.52, 0.0, 0.0);
	glEnd();
	//T4
	glBegin(GL_POLYGON);
	glVertex3f(-1.44, 0.05, 0.0);
	glVertex3f(-1.44, 0.0, 0.0);
	glVertex3f(-1.42, 0.0, 0.0);
	glEnd();

	//T5
	glBegin(GL_POLYGON);
	glVertex3f(-1.52, 0.0, 0.0);
	glVertex3f(-1.48, 0.0, 0.0);
	glVertex3f(-1.48, -0.05, 0.0);
	glEnd();
	//C3
	glBegin(GL_POLYGON);
	glVertex3f(-1.48, 0.0, 0.0);
	glVertex3f(-1.42, 0.0, 0.0);
	glVertex3f(-1.42, -0.3, 0.0);
	glVertex3f(-1.48, -0.3, 0.0);
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
	chestArmor1();
	chestMirrorFrame();
	chest();
	middleChest();
	sixPackArmor1();
	head();
	chestArmor2();
	backArmor1();
	backArmor2();
	backArmor3();
	backArmor4();
	blade();
	gun();
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
	lowerArmArmor1();
	lowerArmArmor2();
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

	/* Translate Lower Arm & Hand To The Right Part */
	glPushMatrix();
	glTranslatef(1.16, 0, 0);
	glPushMatrix();
	glTranslatef(0, 0.65, 0.15);
	glRotatef(rightArmUpSpeed, 1, 0, 0);
	glTranslatef(0, -0.65, -0.15);
	lowerArm();
	lowerArmArmor1();
	lowerArmArmor2();
	hand();
	glPopMatrix();
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
	armAntenna();
	muscleLowerArmJoint();
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
		glMatrixMode(GL_PROJECTION);
		//gluPerspective(30, 0.5, 0.1, 100);
		//glFrustum(5, -5, -5, 5, 2, 10);
		glOrtho(-3, 3, -3, 3, -10, 10);
		glLoadIdentity();
		glTranslatef(x, y, z);
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