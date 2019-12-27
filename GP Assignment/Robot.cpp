#include <Windows.h>
#include <gl/GL.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Optimus Prime"

float armUpSpeed = 0.0;
boolean armUpStatus = false;
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
		else if (wParam == 'U')
			armUpStatus = true;
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
void leg() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, -0.7,-0.3);
	glVertex3f(-0.1, -0.7, -0.3);
	glVertex3f(-0.1, -2, -0.3);
	glVertex3f(-0.4, -2, -0.3);
	glEnd();	

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, -2, -0.3);
	glVertex3f(-0.4, -2, 0.3);
	glVertex3f(-0.4, -0.7, 0.3);
	glVertex3f(-0.4, -0.7, -0.3);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, -0.7, -0.3);
	glVertex3f(-0.4, -0.7, 0.3);
	glVertex3f(-0.1, -0.7, 0.3);
	glVertex3f(-0.1, -0.7, -0.3);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -0.7, -0.3);
	glVertex3f(-0.1, -0.7, 0.3);
	glVertex3f(-0.1, -2, 0.3);
	glVertex3f(-0.1, -2, -0.3);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -2, -0.3);
	glVertex3f(-0.4, -2, -0.3);
	glVertex3f(-0.4, -2, 0.3);
	glVertex3f(-0.1, -2, 0.3);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, -2, 0.3);
	glVertex3f(-0.4, -2, 0.3);
	glVertex3f(-0.4, -0.7, 0.3);
	glVertex3f(-0.1, -0.7, 0.3);
	glEnd();
}

void thigh() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.35, 0, -0.25);
	glVertex3f(-0.15, 0, -0.25);
	glVertex3f(-0.15, -0.7, -0.25);
	glVertex3f(-0.35, -0.7, -0.25);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.35, -0.7, -0.25);
	glVertex3f(-0.35, -0.7, 0.25);
	glVertex3f(-0.35, 0, 0.25);
	glVertex3f(-0.35, 0, -0.25);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.35, 0, -0.25);
	glVertex3f(-0.35, 0, 0.25);
	glVertex3f(-0.15, 0, 0.25);
	glVertex3f(-0.15, 0, -0.25);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, 0, -0.25);
	glVertex3f(-0.15, 0, 0.25);
	glVertex3f(-0.15, -0.7, 0.25);
	glVertex3f(-0.15, -0.7, -0.25);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.7, -0.25);
	glVertex3f(-0.35, -0.7, -0.25);
	glVertex3f(-0.35, -0.7, 0.25);
	glVertex3f(-0.15, -0.7, 0.25);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.15, -0.7, 0.25);
	glVertex3f(-0.35, -0.7, 0.25);
	glVertex3f(-0.35, 0, 0.25);
	glVertex3f(-0.15, 0, 0.25);
	glEnd();
}

void butt() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 0.5, -0.35);
	glVertex3f(0.4, 0.5, -0.35);
	glVertex3f(0.4, 0, -0.35);
	glVertex3f(-0.4, 0, -0.35);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 0, -0.35);
	glVertex3f(-0.4, 0, 0.35);
	glVertex3f(-0.4, 0.5, 0.35);
	glVertex3f(-0.4, 0.5, -0.35);
	glEnd();

	//Top
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.4, 0.5, -0.35);
	glVertex3f(-0.4, 0.5, 0.35);
	glVertex3f(0.4, 0.5, 0.35);
	glVertex3f(0.4, 0.5, -0.35);
	glEnd();

	//Right
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.4, 0.5, -0.35);
	glVertex3f(0.4, 0.5, 0.35);
	glVertex3f(0.4, 0, 0.35);
	glVertex3f(0.4, 0, -0.35);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.4, 0, -0.35);
	glVertex3f(-0.4, 0, -0.35);
	glVertex3f(-0.4, 0, 0.35);
	glVertex3f(0.4, 0, 0.35);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.4, 0, 0.35);
	glVertex3f(-0.4, 0, 0.35);
	glVertex3f(-0.4, 0.5, 0.35);
	glVertex3f(0.4, 0.5, 0.35);
	glEnd();
}

void sixpack() {
	//Front
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.3, 0.8, -0.25);
	glVertex3f(0.3, 0.8, -0.25);
	glVertex3f(0.3, 0.5, -0.25);
	glVertex3f(-0.3, 0.5, -0.25);
	glEnd();

	//Left
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.3, 0.5, -0.25);
	glVertex3f(-0.3, 0.5, 0.25);
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
	glVertex3f(0.3, 0.5, 0.25);
	glVertex3f(0.3, 0.5, -0.25);
	glEnd();

	//Bottom
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.3, 0.5, -0.25);
	glVertex3f(-0.3, 0.5, -0.25);
	glVertex3f(-0.3, 0.5, 0.25);
	glVertex3f(0.3, 0.5, 0.25);
	glEnd();

	//Back
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.3, 0.5, 0.25);
	glVertex3f(-0.3, 0.5, 0.25);
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
	leg();
	thigh();
	butt();
	sixpack();
	chest();
	head();
	upperArmJoint();
	upperArm();

	if (armUpStatus) {
		glPushMatrix();
		lowerArm();
		glRotatef(armUpSpeed, 1, 0, 0);
		hand();
		glPopMatrix();
	}


	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	leg();
	thigh();

	//Due to not symmetric, translate it to make it symmetric
	glPushMatrix();
	glTranslatef(0, 0, -0.1);
	upperArmJoint();
	glPopMatrix();

	//Due to not symmetric, translate it to make it symmetric
	glPushMatrix();
	glTranslatef(0, 0, -0.2);
	upperArm();

	if (armUpStatus) {
		glPushMatrix();
		lowerArm();
		glRotatef(armUpSpeed, 1, 0, 0);
		hand();
		glPopMatrix();
	}

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

		optimusPrime();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------