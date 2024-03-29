#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <iostream>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")
#pragma comment(lib, "winmm.lib")

#pragma warning(disable:4305)

#define WINDOW_TITLE "Optimus Prime"

// for movement
float stepmovementz = 0.0;
float stepmovementx = 0.0;
float speed = 0.1; 
float bulletspeed = 0.1;
float anglespeed = 5;
float turnrate = 0.0;
char s[256];
//========================================
//texture
BITMAP BMP;
HBITMAP hBMP = NULL;
GLuint texture = 0;
int leftOrRight = 0; /* [None - 0] [Left - 1] [Right - 2] */

//for gun
int stepcounter = 0;

bool trigger = false;
float amb[] = { 0.93,0.44,0.12 };
float pos[] = { 0.0,1.0,0.0 };
float firebullet = 0.0;
int backNormal = 0;
bool drawGun = false;
bool usegun = false;
//============================
//for blade
int swingBlade = 0;
float bladesize = 0.3;
bool drawBlade = false;
float bladelocation = -1.2;
/* Whole Arm Up And Down Speed*/
float leftWholeArmSpeed = 0.0;
float rightWholeArmSpeed = 0.0;

/* Arm Up And Down Speed */
float leftArmUpSpeed = 0.0;
float rightArmUpSpeed = 0.0;

/* Fingers Movement */
float leftUpperFingerDegree = 30.0;
float leftMiddleFingerDegree = 30.0;
float rightUpperFingerDegree = 30.0;
float rightMiddleFingerDegree = 30.0;

float thumbLowerFingerDegree = 0.0;
float thumbUpperFingerDegree = 0.0;

/* Head Turn Rate */
float headTurn = 0.0;

/* Projection Method */
boolean goPerspective = false;
boolean goOrtho = false;
boolean goBackOrigin = false;
int inWhatProjectionMode = 0; /* [0 - None] [1 - Ortho] [2 - Perspective] */

float x = 0.0, y = 0.0, z = 0.0;

/* Image Variable */
LPCSTR majorPartImage = "red.bmp";

void shootSound() {
	PlaySound(TEXT("shoot.wav"), NULL, SND_ASYNC | SND_FILENAME);
}

void startingSound() {
	PlaySound(TEXT("start.wav"), NULL, SND_ASYNC | SND_FILENAME);
}

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
		else if (wParam == ' ')
		{

			stepmovementx = 0;
			stepmovementz = 0;
			leftOrRight = 0;
			stepcounter = 0;
			trigger = false;
			firebullet = 0.0;
			turnrate = 0.0;
			backNormal = 0;
			drawGun = false;
			usegun = false;
			swingBlade = 0;
			bladesize = 0.3;
			drawBlade = false;
			bladelocation = -1.2;
			goPerspective = false;
			goOrtho = false;
			goBackOrigin = false;
			leftUpperFingerDegree = 30.0;
			leftMiddleFingerDegree = 30.0;
			rightUpperFingerDegree = 30.0;
			rightMiddleFingerDegree = 30.0;
			leftWholeArmSpeed = 0.0;
			rightWholeArmSpeed = 0.0;
			leftArmUpSpeed = 0.0;
			rightArmUpSpeed = 0.0;
			thumbLowerFingerDegree = 0.0;
			thumbUpperFingerDegree = 0.0;
			//reset everything
		}
		else if (wParam == VK_LEFT)
			glRotatef(1, 0, 1, 0);
		else if (wParam == VK_RIGHT)
			glRotatef(-1, 0, 1, 0);
		else if (wParam == VK_UP)
			glRotatef(-1, 1, 0, 0);
		else if (wParam == VK_DOWN)
			glRotatef(1, 1, 0, 0);
		else if (wParam == 'W')
			y -= 0.1;
		else if (wParam == 'S')
			y += 0.1;
		else if (wParam == 'A')
			x += 0.1;
		else if (wParam == 'D')
			x -= 0.1;
		else if (wParam == 'Q')
			z -= 0.1;
		else if (wParam == 'E')
			z += 0.1;
		else if (wParam == 'N')
			leftOrRight = 1;
		else if (wParam == 'M')
			leftOrRight = 2;
		else if (wParam == 'F')
		{
			if (drawGun == true) {
				trigger = true;
				shootSound();
			}
		}
		else if (wParam == 'T')
			turnrate += 90;
		else if (wParam == 'Y')
			turnrate -= 90;
		else if (wParam == 'K')
			swingBlade = 1;
		else if (wParam == 'G')
			if (drawGun == false)drawGun = true; else drawGun = false;
		else if (wParam == 'B')
		{
			if (drawBlade == false)drawBlade = true; else drawBlade = false;
		}
		else if (wParam == '1')
		{
			stepcounter++;
		}
		if (turnrate == 360)
			turnrate = 0;
		if (turnrate == -90)
			turnrate = 270;

		else if (wParam == '0')
		{
			if (leftOrRight == 1) {
				leftUpperFingerDegree++;
				if (leftMiddleFingerDegree >= 90) {
					leftUpperFingerDegree = 90;
					leftMiddleFingerDegree = 90;
				}
				else if (leftUpperFingerDegree >= 90) {
					leftMiddleFingerDegree++;
					leftUpperFingerDegree = 90;
				}
			}
			else if (leftOrRight == 2) 
			{
				rightUpperFingerDegree++;
				if (rightMiddleFingerDegree >= 90) {
					rightUpperFingerDegree = 90;
					rightMiddleFingerDegree = 90;
				}
				else if (rightUpperFingerDegree >= 90) {
					rightMiddleFingerDegree++;
					rightUpperFingerDegree = 90;
				}
			}
		}
		else if (wParam == '9')
		{
			if (leftOrRight == 1) {
				leftMiddleFingerDegree--;
				if (leftUpperFingerDegree <= 30) {
					leftUpperFingerDegree = 30;
					leftMiddleFingerDegree = 30;
				}
				else if (leftMiddleFingerDegree <= 30) {
					leftUpperFingerDegree--;
					leftMiddleFingerDegree = 30;
				}
			}
			else if (leftOrRight == 2) {
				rightMiddleFingerDegree--;
				if (rightUpperFingerDegree <= 30) {
					rightUpperFingerDegree = 30;
					rightMiddleFingerDegree = 30;
				}
				else if (rightMiddleFingerDegree <= 30) {
					rightUpperFingerDegree--;
					rightMiddleFingerDegree = 30;
				}
			}
		}
		else if (wParam == '8')
		{
			if (leftOrRight == 1) {
				leftMiddleFingerDegree--;
				if (leftUpperFingerDegree <= 0) {
					leftUpperFingerDegree = 0;
					leftMiddleFingerDegree = 0;
				}
				else if (leftMiddleFingerDegree <= 0) {
					leftUpperFingerDegree--;
					leftMiddleFingerDegree = 0;
				}
			}
			else if (leftOrRight == 2) {
				rightMiddleFingerDegree--;
				if (rightUpperFingerDegree <= 0) {
					rightUpperFingerDegree = 0;
					rightMiddleFingerDegree = 0;
				}
				else if (rightMiddleFingerDegree <= 0) {
					rightUpperFingerDegree--;
					rightMiddleFingerDegree = 0;
				}
			}
		}
		else if (wParam == '7')
		{
			thumbLowerFingerDegree++;
			if (thumbUpperFingerDegree >= 20) {
				thumbUpperFingerDegree = 20;
				thumbLowerFingerDegree = 20;
			}
			else if (thumbLowerFingerDegree++ >= 20) {
				thumbUpperFingerDegree++;
				thumbLowerFingerDegree = 20;
			}
		}
		else if (wParam == '6') 
		{
			if (leftOrRight == 1) {
				leftArmUpSpeed++;
				if (leftArmUpSpeed >= 130)
					leftArmUpSpeed = 130;
			}
			else if (leftOrRight == 2) {
				rightArmUpSpeed++;
				if (rightArmUpSpeed >= 130)
					rightArmUpSpeed = 130;
			}
		}
		else if (wParam == '5') {
			if (leftOrRight == 1) {
				leftArmUpSpeed--;
				if (leftArmUpSpeed <= 0)
					leftArmUpSpeed = 0;
			}
			else if (leftOrRight == 2) {
				rightArmUpSpeed--;
				if (rightArmUpSpeed <= 0)
					rightArmUpSpeed = 0;
			}
		}
		else if (wParam == '4') 
		{
			if (leftOrRight == 1) 
			{
				leftWholeArmSpeed++;
				if (leftWholeArmSpeed >= 220)
					leftWholeArmSpeed = 220;
			}
			else if (leftOrRight == 2) 
			{
				rightWholeArmSpeed++;
				if (rightWholeArmSpeed >= 220)
					rightWholeArmSpeed = 220;
			}
		}
		else if (wParam == '3')
		{
			if (leftOrRight == 1)
			{
				leftWholeArmSpeed--;
				if (leftWholeArmSpeed <= 0)
					leftWholeArmSpeed = 0;
			}
			else if (leftOrRight == 2)
			{
				rightWholeArmSpeed--;
				if (rightWholeArmSpeed <= 0)
					rightWholeArmSpeed = 0;
			}
		}
		else if (wParam == '2') 
		{
			if (leftOrRight == 1) {
				headTurn++;
				if (headTurn >= 20)
					headTurn = 20;
			}
			else if (leftOrRight == 2) {
				headTurn--;
				if (headTurn <= -20)
					headTurn = -20;
			}

		}
		else if (wParam == 'Z')
			goPerspective = true;
		else if (wParam == 'X')
			goOrtho = true;
		else if (wParam == 'C')
			goBackOrigin = true;
		else if (wParam == VK_NUMPAD0)
			majorPartImage = "red.bmp";
		else if (wParam == VK_NUMPAD1)
			majorPartImage = "green.bmp";
		else if (wParam == VK_NUMPAD2)
			majorPartImage = "army.bmp";

		sprintf_s(s, "x=%f,y=%f,z=%f\n", x, y, z);
		OutputDebugString(s);

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
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"blue.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, -1.9, -0.4);
	glTexCoord2f(0.2, 1); glVertex3f(-0.1, -1.9, -0.4);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.1, -2, -0.4);
	glTexCoord2f(0, 0.3); glVertex3f(-0.4, -2, -0.4);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, -2, -0.4);
	glTexCoord2f(0.2, 1); glVertex3f(-0.4, -2, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.4, -1.7, -0.3);
	glTexCoord2f(0, 0.3); glVertex3f(-0.4, -1.9, -0.4);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, -1.9, -0.4);
	glTexCoord2f(0.2, 1); glVertex3f(-0.4, -1.7, -0.3);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.1, -1.7, -0.3);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -1.9, -0.4);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -1.9, -0.4);
	glTexCoord2f(0.2, 1); glVertex3f(-0.1, -1.7, -0.3);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.1, -2, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -2, -0.4);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -2, -0.4);
	glTexCoord2f(0.2, 1); glVertex3f(-0.4, -2, -0.4);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.4, -2, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -2, -0.2);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -2, -0.2);
	glTexCoord2f(0.2, 1); glVertex3f(-0.4, -2, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.4, -1.7, -0.3);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -1.7, -0.3);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void shoePart2() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"blue.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, -1.6, -0.3);
	glTexCoord2f(0.2, 1); glVertex3f(-0.1, -1.6, -0.3);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.1, -1.7, -0.3);
	glTexCoord2f(0, 0.3); glVertex3f(-0.4, -1.7, -0.3);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, -1.7, -0.3);
	glTexCoord2f(0.2, 1); glVertex3f(-0.4, -2, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.4, -1.9, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.4, -1.6, -0.3);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, -1.6, -0.3);
	glTexCoord2f(0.2, 1); glVertex3f(-0.4, -1.9, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.1, -1.9, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -1.6, -0.3);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -1.6, -0.3);
	glTexCoord2f(0.2, 1); glVertex3f(-0.1, -1.9, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.1, -2, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -1.7, -0.3);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -1.7, -0.3);
	glTexCoord2f(0.2, 1); glVertex3f(-0.4, -1.7, -0.3);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.4, -2, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -2, -0.2);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -2, -0.2);
	glTexCoord2f(0.2, 1); glVertex3f(-0.4, -2, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.4, -1.9, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -1.9, -0.2);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void shoePart3() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"blue.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, -1.4, -0.26);
	glTexCoord2f(0.2, 1); glVertex3f(-0.1, -1.4, -0.26);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.1, -1.6, -0.3);
	glTexCoord2f(0, 0.3); glVertex3f(-0.4, -1.6, -0.3);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, -1.6, -0.3);
	glTexCoord2f(0.2, 1); glVertex3f(-0.4, -1.9, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.4, -1.4, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.4, -1.4, -0.26);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, -1.4, -0.26);
	glTexCoord2f(0.2, 1); glVertex3f(-0.4, -1.4, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.1, -1.4, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -1.4, -0.26);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -1.4, -0.26);
	glTexCoord2f(0.2, 1); glVertex3f(-0.1, -1.4, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.1, -1.9, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -1.6, -0.3);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -1.6, -0.3);
	glTexCoord2f(0.2, 1); glVertex3f(-0.4, -1.6, -0.3);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.4, -1.9, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -1.9, -0.2);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -1.9, -0.2);
	glTexCoord2f(0.2, 1); glVertex3f(-0.4, -1.9, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.4, -1.4, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -1.4, -0.2);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void legArmor1() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"blue.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);


	//Front 1
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, -0.75, -0.28);
	glTexCoord2f(0.2, 1); glVertex3f(-0.35, -0.75, -0.28);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.35, -1.4, -0.28);
	glTexCoord2f(0, 0.3); glVertex3f(-0.4, -1.4, -0.28);
	glEnd();

	//Front 2
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.35, -0.95, -0.28);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -0.95, -0.28);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, -1.1, -0.28);
	glTexCoord2f(0, 0.3); glVertex3f(-0.35, -1.1, -0.28);
	glEnd();

	//Front 3
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, -0.75, -0.28);
	glTexCoord2f(0.2, 1); glVertex3f(-0.1, -0.75, -0.28);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.1, -1.4, -0.28);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, -1.4, -0.28);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, -1.4, -0.28);
	glTexCoord2f(0.2, 1); glVertex3f(-0.4, -1.4, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.4, -0.75, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.4, -0.75, -0.28);
	glEnd();

	//Top 1
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, -0.75, -0.28);
	glTexCoord2f(0.2, 1); glVertex3f(-0.4, -0.75, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.35, -0.75, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.35, -0.75, -0.28);
	glEnd();

	//Top 2
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.35, -0.75, -0.28);
	glTexCoord2f(0.2, 1); glVertex3f(-0.35, -0.75, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.35, -0.95, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.35, -0.95, -0.28);
	glEnd();

	//Top 3
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.35, -0.95, -0.28);
	glTexCoord2f(0.2, 1); glVertex3f(-0.35, -0.95, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, -0.95, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, -0.95, -0.28);
	glEnd();

	//Top 4
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, -0.95, -0.28);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -0.95, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, -0.75, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, -0.75, -0.28);
	glEnd();

	//Top 5
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, -0.75, -0.28);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -0.75, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.1, -0.75, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -0.75, -0.28);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -0.75, -0.28);
	glTexCoord2f(0.2, 1); glVertex3f(-0.1, -0.75, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.1, -1.4, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -1.4, -0.28);
	glEnd();

	//Bottom 1
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -1.4, -0.28);
	glTexCoord2f(0.2, 1); glVertex3f(-0.1, -1.4, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, -1.4, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, -1.4, -0.28);
	glEnd();

	//Bottom 2
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, -1.4, -0.28);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -1.4, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, -1.1, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, -1.1, -0.28);
	glEnd();

	//Bottom 3
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, -1.1, -0.28);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -1.1, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.35, -1.1, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.35, -1.1, -0.28);
	glEnd();

	//Bottom 4
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.35, -1.1, -0.28);
	glTexCoord2f(0.2, 1); glVertex3f(-0.35, -1.1, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.35, -1.4, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.35, -1.4, -0.28);
	glEnd();

	//Bottom 5
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.35, -1.4, -0.28);
	glTexCoord2f(0.2, 1); glVertex3f(-0.4, -1.4, -0.28);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.4, -1.4, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.35, -1.4, -0.2);
	glEnd();

	//Back 1
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, -0.75, -0.2);
	glTexCoord2f(0.2, 1); glVertex3f(-0.35, -0.75, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.35, -1.4, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.4, -1.4, -0.2);
	glEnd();

	//Back 2
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.35, -0.95, -0.2);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -0.95, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, -1.1, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.35, -1.1, -0.2);
	glEnd();

	//Back 3
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, -0.75, -0.2);
	glTexCoord2f(0.2, 1); glVertex3f(-0.1, -0.75, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.1, -1.4, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, -1.4, -0.2);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	//Metal Plate 1 
	glBegin(GL_POLYGON);
	glVertex3f(-0.35, -1.1, -0.25);
	glVertex3f(-0.15, -1.1, -0.25);
	glVertex3f(-0.15, -1.17, -0.25);
	glVertex3f(-0.35, -1.17, -0.25);
	glEnd();

	//Metal Plate 2
	glBegin(GL_POLYGON);
	glVertex3f(-0.35, -1.175, -0.25);
	glVertex3f(-0.15, -1.175, -0.25);
	glVertex3f(-0.15, -1.245, -0.25);
	glVertex3f(-0.35, -1.245, -0.25);
	glEnd();

	//Metal Plate 3
	glBegin(GL_POLYGON);
	glVertex3f(-0.35, -1.25, -0.25);
	glVertex3f(-0.15, -1.25, -0.25);
	glVertex3f(-0.15, -1.32, -0.25);
	glVertex3f(-0.35, -1.32, -0.25);
	glEnd();

	//Metal Plate 4
	glBegin(GL_POLYGON);
	glVertex3f(-0.35, -1.325, -0.25);
	glVertex3f(-0.15, -1.325, -0.25);
	glVertex3f(-0.15, -1.395, -0.25);
	glVertex3f(-0.35, -1.395, -0.25);
	glEnd();


}

void legArmor2() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"blue.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, -0.7, -0.2);
	glTexCoord2f(0.2, 1); glVertex3f(-0.1, -0.7, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.1, -2, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, -2, -0.2);
	glEnd();

	//Left 1
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, -0.7, -0.2);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -0.7, -0.15);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, -2, -0.15);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, -2, -0.2);
	glEnd();

	//Left 2
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, -0.7, -0.15);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -0.7, 0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, -1, 0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, -1, -0.15);
	glEnd();

	//Left 3
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, -1.5, -0.15);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -1.5, 0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, -1.6, 0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, -1.6, -0.15);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, -0.7, -0.2);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -0.7, 0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.1, -0.7, 0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -0.7, -0.2);
	glEnd();

	//Right 1
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -0.7, -0.2);
	glTexCoord2f(0.2, 1); glVertex3f(-0.1, -0.7, -0.15);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.1, -2, -0.15);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -2, -0.2);
	glEnd();

	//Right 2
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -0.7, -0.15);
	glTexCoord2f(0.2, 1); glVertex3f(-0.1, -0.7, 0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.1, -1, 0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -1, -0.15);
	glEnd();

	//Right 3
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -1.5, -0.15);
	glTexCoord2f(0.2, 1); glVertex3f(-0.1, -1.5, 0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.1, -1.6, 0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -1.6, -0.15);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, -2, -0.2);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -2, 0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.1, -2, 0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -2, -0.2);
	glEnd();

	//Back 1
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -0.7, -0.2);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -0.7, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, -1, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -1, -0.2);
	glEnd();

	//Back 2
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -1, 0.2);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -1, 0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, -1, -0.15);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -1, -0.15);
	glEnd();

	//Back 3
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -1, -0.15);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -1, -0.15);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, -1.5, -0.15);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -1.5, -0.15);
	glEnd();

	//Back 4
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -1.5, -0.15);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -1.5, -0.15);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, -1.5, 0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -1.5, 0.2);
	glEnd();

	//Back 5
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -1.5, 0.2);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -1.5, 0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, -1.6, 0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -1.6, 0.2);
	glEnd();

	//Back 6
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -1.6, 0.2);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -1.6, 0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, -1.6, -0.15);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -1.6, -0.15);
	glEnd();

	//Back 7
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -1.6, -0.15);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -1.6, -0.15);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, -2, -0.15);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -2, -0.15);
	glEnd();

	//Back 8
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -2, -0.15);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -2, -0.15);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, -2, 0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.1, -2, 0.2);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void legArmor3() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"silver.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	GLUquadricObj *legCylinder = NULL;
	legCylinder = gluNewQuadric();

	glPushMatrix();
	glTranslatef(-0.4, -0.75, 0);
	glRotatef(90, 1, 0, 0);
	gluQuadricDrawStyle(legCylinder, GLU_FILL);
	gluQuadricTexture(legCylinder, true);
	gluCylinder(legCylinder, 0.05, 0.05, 0.3, 20, 20);
	gluDeleteQuadric(legCylinder);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void legTyre() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"silver.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Rim Above 
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++)
	{
		float degInRad = i * (3.14159 / 180);
		glTexCoord2f((cos(degInRad)*(0.15 - 0.02)) + 0.1, (sin(degInRad)*(0.15 + 0.05)) - 1.3);
		glVertex3f(-0.45, (sin(degInRad)*(0.15 + 0.05)) - 1.3, (cos(degInRad)*(0.15 - 0.02)) + 0.1);
	}
	glEnd();

	//Rim Below
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 360; i++)
	{
		float degInRad = i * (3.14159 / 180);
		glTexCoord2f((cos(degInRad)*(0.15 - 0.02)) + 0.1, (sin(degInRad)*(0.15 + 0.05)) - 1.75);
		glVertex3f(-0.45, (sin(degInRad)*(0.15 + 0.05)) - 1.75, (cos(degInRad)*(0.15 - 0.02)) + 0.1);
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"tyre.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	
	GLUquadricObj *legTyre1 = NULL;
	legTyre1 = gluNewQuadric();

	//Tyre Above
	glPushMatrix();
	glTranslatef(-0.45, -1.3, 0.1);
	glScalef(1, 1, 0.65);
	glRotatef(90, 0, 1, 0);
	gluQuadricDrawStyle(legTyre1, GLU_FILL);
	gluQuadricTexture(legTyre1, true);
	gluCylinder(legTyre1, 0.2, 0.2, 0.15, 20, 20);
	gluDeleteQuadric(legTyre1);
	glPopMatrix();

	//Tyre Below 
	GLUquadricObj *legTyre2 = NULL;
	legTyre2 = gluNewQuadric();

	glPushMatrix();
	glTranslatef(-0.45, -1.75, 0.1);
	glScalef(1, 1, 0.65);
	glRotatef(90, 0, 1, 0);
	gluQuadricDrawStyle(legTyre2, GLU_FILL);
	gluQuadricTexture(legTyre2, true);
	gluCylinder(legTyre2, 0.2, 0.2, 0.15, 20, 20);
	gluDeleteQuadric(legTyre2);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void leg() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"blue.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, -0.7, -0.2);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -0.7, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, -2, -0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.4, -2, -0.2);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, -2, -0.2);
	glTexCoord2f(0.2, 1); glVertex3f(-0.4, -2, 0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.4, -0.7, 0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.4, -0.7, -0.2);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, -0.7, -0.2);
	glTexCoord2f(0.2, 1); glVertex3f(-0.4, -0.7, 0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, -0.7, 0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, -0.7, -0.2);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, -0.7, -0.2);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -0.7, 0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, -2, 0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, -2, -0.2);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, -2, -0.2);
	glTexCoord2f(0.2, 1); glVertex3f(-0.4, -2, -0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.4, -2, 0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, -2, 0.2);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, -2, 0.2);
	glTexCoord2f(0.2, 1); glVertex3f(-0.4, -2, 0.2);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.4, -0.7, 0.2);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, -0.7, 0.2);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void thighArmor1() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"darkWhite.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);


	//Outer Part - Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.33, 0.1, -0.175);
	glTexCoord2f(1, 1); glVertex3f(-0.17, 0.1, -0.175);
	glTexCoord2f(1, 0); glVertex3f(-0.2, -0.4, -0.175);
	glTexCoord2f(0, 0); glVertex3f(-0.3, -0.4, -0.175);
	glEnd();

	//Outer Part - Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.3, -0.4, -0.175);
	glTexCoord2f(1, 1); glVertex3f(-0.3, -0.4, -0.15);
	glTexCoord2f(1, 0); glVertex3f(-0.325, 0.1, -0.15);
	glTexCoord2f(0, 0); glVertex3f(-0.325, 0.1, -0.175);
	glEnd();

	//Outer Part - Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.325, 0.1, -0.175);
	glTexCoord2f(1, 1); glVertex3f(-0.325, 0.1, -0.15);
	glTexCoord2f(1, 0); glVertex3f(-0.175, 0.1, -0.15);
	glTexCoord2f(0, 0); glVertex3f(-0.175, 0.1, -0.175);
	glEnd();

	//Outer Part - Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.175, 0.1, -0.175);
	glTexCoord2f(1, 1); glVertex3f(-0.175, 0.1, -0.15);
	glTexCoord2f(1, 0); glVertex3f(-0.2, -0.4, -0.15);
	glTexCoord2f(0, 0); glVertex3f(-0.2, -0.4, -0.175);
	glEnd();

	//Outer Part - Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.2, -0.4, -0.175);
	glTexCoord2f(1, 1); glVertex3f(-0.3, -0.4, -0.175);
	glTexCoord2f(1, 0); glVertex3f(-0.3, -0.4, -0.15);
	glTexCoord2f(0, 0); glVertex3f(-0.2, -0.4, -0.15);
	glEnd();

	//Outer Part - Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.2, -0.4, -0.15);
	glTexCoord2f(1, 1); glVertex3f(-0.3, -0.4, -0.15);
	glTexCoord2f(1, 0); glVertex3f(-0.33, 0.1, -0.15);
	glTexCoord2f(0, 0); glVertex3f(-0.17, 0.1, -0.15);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"white.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Inner Part 1
	glBegin(GL_POLYGON);
	glTexCoord2f(0.2, 1); glVertex3f(-0.28, -0.1, -0.18);
	glTexCoord2f(0.8, 1); glVertex3f(-0.22, -0.1, -0.18);
	glTexCoord2f(1, 0.5); glVertex3f(-0.21, -0.125, -0.18);
	glTexCoord2f(0.8, 0); glVertex3f(-0.22, -0.15, -0.18);
	glTexCoord2f(0.2, 10); glVertex3f(-0.28, -0.15, -0.18);
	glTexCoord2f(0, 0.5); glVertex3f(-0.29, -0.125, -0.18);
	glEnd();

	//Inner Part 2
	glBegin(GL_POLYGON);
	glTexCoord2f(0.2, 1); glVertex3f(-0.28, -0.2, -0.18);
	glTexCoord2f(0.8, 1); glVertex3f(-0.22, -0.2, -0.18);
	glTexCoord2f(1, 0.5); glVertex3f(-0.21, -0.225, -0.18);
	glTexCoord2f(0.8, 0); glVertex3f(-0.22, -0.25, -0.18);
	glTexCoord2f(0.2, 10); glVertex3f(-0.28, -0.25, -0.18);
	glTexCoord2f(0, 0.5); glVertex3f(-0.29, -0.225, -0.18);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void thightSmallestTrapezium() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"darkWhite.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.33, -0.5, -0.175);
	glTexCoord2f(1, 1); glVertex3f(-0.305, -0.48, -0.175);
	glTexCoord2f(1, 0); glVertex3f(-0.325, -0.6, -0.175);
	glTexCoord2f(0, 0); glVertex3f(-0.34, -0.56, -0.175);
	glEnd();

	//Left 
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.34, -0.56, -0.175);
	glTexCoord2f(1, 1); glVertex3f(-0.34, -0.56, -0.15);
	glTexCoord2f(1, 0); glVertex3f(-0.33, -0.5, -0.15);
	glTexCoord2f(0, 0); glVertex3f(-0.33, -0.5, -0.175);
	glEnd();

	//Top 
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.33, -0.5, -0.175);
	glTexCoord2f(1, 1); glVertex3f(-0.33, -0.5, -0.15);
	glTexCoord2f(1, 0); glVertex3f(-0.305, -0.48, -0.15);
	glTexCoord2f(0, 0); glVertex3f(-0.305, -0.48, -0.175);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.305, -0.48, -0.175);
	glTexCoord2f(1, 1); glVertex3f(-0.305, -0.48, -0.15);
	glTexCoord2f(1, 0); glVertex3f(-0.325, -0.6, -0.15);
	glTexCoord2f(0, 0); glVertex3f(-0.325, -0.6, -0.175);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.325, -0.6, -0.175);
	glTexCoord2f(1, 1); glVertex3f(-0.34, -0.56, -0.175);
	glTexCoord2f(1, 0); glVertex3f(-0.34, -0.56, -0.15);
	glTexCoord2f(0, 0); glVertex3f(-0.325, -0.6, -0.15);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.325, -0.6, -0.15);
	glTexCoord2f(1, 1); glVertex3f(-0.34, -0.56, -0.15);
	glTexCoord2f(1, 0); glVertex3f(-0.33, -0.5, -0.15);
	glTexCoord2f(0, 0); glVertex3f(-0.305, -0.48, -0.15);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void thighArmor2() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"darkWhite.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Biggest Trapezium - Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.28, -0.45, -0.175);
	glTexCoord2f(1, 1); glVertex3f(-0.22, -0.45, -0.175);
	glTexCoord2f(1, 0); glVertex3f(-0.17, -0.7, -0.175);
	glTexCoord2f(0, 0); glVertex3f(-0.33, -0.7, -0.175);
	glEnd();

	//Biggest Trapezium - Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.33, -0.7, -0.175);
	glTexCoord2f(1, 1); glVertex3f(-0.33, -0.7, -0.15);
	glTexCoord2f(1, 0); glVertex3f(-0.28, -0.45, -0.15);
	glTexCoord2f(0, 0); glVertex3f(-0.28, -0.45, -0.175);
	glEnd();

	//Biggest Trapezium - Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.28, -0.45, -0.175);
	glTexCoord2f(1, 1); glVertex3f(-0.28, -0.45, -0.15);
	glTexCoord2f(1, 0); glVertex3f(-0.22, -0.45, -0.15);
	glTexCoord2f(0, 0); glVertex3f(-0.22, -0.45, -0.175);
	glEnd();

	//Biggest Trapezium - Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.22, -0.45, -0.175);
	glTexCoord2f(1, 1); glVertex3f(-0.22, -0.45, -0.15);
	glTexCoord2f(1, 0); glVertex3f(-0.17, -0.7, -0.15);
	glTexCoord2f(0, 0); glVertex3f(-0.17, -0.7, -0.175);
	glEnd();

	//Biggest Trapezium - Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.17, -0.7, -0.175);
	glTexCoord2f(1, 1); glVertex3f(-0.33, -0.7, -0.175);
	glTexCoord2f(1, 0); glVertex3f(-0.33, -0.7, -0.15);
	glTexCoord2f(0, 0); glVertex3f(-0.17, -0.7, -0.15);
	glEnd();

	//Biggest Trapezium - Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.17, -0.7, -0.15);
	glTexCoord2f(1, 1); glVertex3f(-0.33, -0.7, -0.15);
	glTexCoord2f(1, 0); glVertex3f(-0.28, -0.45, -0.15);
	glTexCoord2f(0, 0); glVertex3f(-0.22, -0.45, -0.15);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

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
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"darkWhite.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0.2, 1); glVertex3f(-0.14, -0.4, -0.03);
	glTexCoord2f(0.8, 1); glVertex3f(-0.14, -0.4, 0.03);
	glTexCoord2f(1, 0.5); glVertex3f(-0.14, -0.425, 0.04);
	glTexCoord2f(0.8, 0); glVertex3f(-0.14, -0.45, 0.03);
	glTexCoord2f(0.2, 0); glVertex3f(-0.14, -0.45, -0.03);
	glTexCoord2f(0, 0.5); glVertex3f(-0.14, -0.425, -0.04);
	glEnd();

	//Left Up
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.14, -0.425, -0.04);
	glTexCoord2f(1, 1); glVertex3f(-0.15, -0.425, -0.04);
	glTexCoord2f(1, 0); glVertex3f(-0.15, -0.4, -0.03);
	glTexCoord2f(0, 0); glVertex3f(-0.14, -0.4, -0.03);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.14, -0.4, -0.03);
	glTexCoord2f(1, 1); glVertex3f(-0.15, -0.4, -0.03);
	glTexCoord2f(1, 0); glVertex3f(-0.15, -0.4, 0.03);
	glTexCoord2f(0, 0); glVertex3f(-0.14, -0.4, 0.03);
	glEnd();

	//Right Up
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.14, -0.4, 0.03);
	glTexCoord2f(1, 1); glVertex3f(-0.15, -0.4, 0.03);
	glTexCoord2f(1, 0); glVertex3f(-0.15, -0.425, 0.04);
	glTexCoord2f(0, 0); glVertex3f(-0.14, -0.425, 0.04);
	glEnd();

	//Right Down
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.14, -0.425, 0.04);
	glTexCoord2f(1, 1); glVertex3f(-0.15, -0.425, 0.04);
	glTexCoord2f(1, 0); glVertex3f(-0.15, -0.45, 0.03);
	glTexCoord2f(0, 0); glVertex3f(-0.14, -0.45, 0.03);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.14, -0.45, 0.03);
	glTexCoord2f(1, 1); glVertex3f(-0.15, -0.45, 0.03);
	glTexCoord2f(1, 0); glVertex3f(-0.15, -0.45, -0.03);
	glTexCoord2f(0, 0); glVertex3f(-0.14, -0.45, -0.03);
	glEnd();

	//Left Down
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.14, -0.45, -0.03);
	glTexCoord2f(1, 1); glVertex3f(-0.15, -0.45, -0.03);
	glTexCoord2f(1, 0); glVertex3f(-0.15, -0.425, -0.04);
	glTexCoord2f(0, 0); glVertex3f(-0.14, -0.425, -0.04);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, -0.425, -0.04);
	glTexCoord2f(0.8, 1); glVertex3f(-0.15, -0.4, -0.03);
	glTexCoord2f(1, 0.5); glVertex3f(-0.15, -0.4, 0.03);
	glTexCoord2f(0.8, 0); glVertex3f(-0.15, -0.425, 0.04);
	glTexCoord2f(0.2, 0); glVertex3f(-0.15, -0.45, 0.03);
	glTexCoord2f(0, 0.5); glVertex3f(-0.15, -0.45, -0.03);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
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
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"darkWhite.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Outer Area
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.3, -0.15, 0.155);
	glTexCoord2f(1, 1); glVertex3f(-0.2, -0.15, 0.155);
	glTexCoord2f(1, 0); glVertex3f(-0.15, -0.7, 0.155);
	glTexCoord2f(0, 0); glVertex3f(-0.35, -0.7, 0.155);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"white.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Inner Area
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.28, -0.35, 0.16);
	glTexCoord2f(1, 1); glVertex3f(-0.22, -0.35, 0.16);
	glTexCoord2f(1, 0); glVertex3f(-0.15, -0.7, 0.16);
	glTexCoord2f(0, 0); glVertex3f(-0.35, -0.7, 0.16);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void thigh() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"white.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.35, 0.1, -0.15);
	glTexCoord2f(0.3, 1); glVertex3f(-0.15, 0.1, -0.15);
	glTexCoord2f(0.3, 0.7); glVertex3f(-0.15, -0.7, -0.15);
	glTexCoord2f(0, 0.7); glVertex3f(-0.35, -0.7, -0.15);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.35, -0.7, -0.15);
	glTexCoord2f(0.3, 1); glVertex3f(-0.35, -0.7, 0.15);
	glTexCoord2f(0.3, 0.7); glVertex3f(-0.35, 0.1, 0.15);
	glTexCoord2f(0, 0.7); glVertex3f(-0.35, 0.1, -0.15);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.35, 0.1, -0.15);
	glTexCoord2f(0.3, 1); glVertex3f(-0.35, 0.1, 0.15);
	glTexCoord2f(0.3, 0.7); glVertex3f(-0.15, 0.1, 0.15);
	glTexCoord2f(0, 0.7); glVertex3f(-0.15, 0.1, -0.15);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, 0.1, -0.15);
	glTexCoord2f(0.3, 1); glVertex3f(-0.15, 0.1, 0.15);
	glTexCoord2f(0.3, 0.7); glVertex3f(-0.15, -0.7, 0.15);
	glTexCoord2f(0, 0.7); glVertex3f(-0.15, -0.7, -0.15);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, -0.7, -0.15);
	glTexCoord2f(0.3, 1); glVertex3f(-0.35, -0.7, -0.15);
	glTexCoord2f(0.3, 0.7); glVertex3f(-0.35, -0.7, 0.15);
	glTexCoord2f(0, 0.7); glVertex3f(-0.15, -0.7, 0.15);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, -0.7, 0.15);
	glTexCoord2f(0.3, 1); glVertex3f(-0.35, -0.7, 0.15);
	glTexCoord2f(0.3, 0.7); glVertex3f(-0.35, 0.1, 0.15);
	glTexCoord2f(0, 0.7); glVertex3f(-0.15, 0.1, 0.15);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void buttTriangle() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"yellow.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Triangle
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.35, 0.32, -0.31);
	glTexCoord2f(1, 1); glVertex3f(-0.2, 0.32, -0.31);
	glTexCoord2f(1, 0); glVertex3f(-0.2, 0.22, -0.31);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void buttDesign() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"yellow.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Rectangle
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, 0.3, -0.31);
	glTexCoord2f(1, 1); glVertex3f(0.15, 0.3, -0.31);
	glTexCoord2f(1, 0); glVertex3f(0.15, 0, -0.31);
	glTexCoord2f(0, 0); glVertex3f(-0.15, 0, -0.31);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	//Left Part Triangle in Butt Area
	buttTriangle();

	glPushMatrix();
	glTranslatef(-0.01, -0.15, 0);
	glScalef(0.9, 0.9, 1);
	buttTriangle();
	glPopMatrix();


	//Right Part Triangle in Butt Area
	glPushMatrix();
	glTranslatef(0, 0, -0.62);
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
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"blue.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.13, -0.15, -0.33);
	glTexCoord2f(0.2, 1); glVertex3f(0.13, -0.15, -0.33);
	glTexCoord2f(0.2, 0.7); glVertex3f(0.1, -0.35, -0.25);
	glTexCoord2f(0, 0.7); glVertex3f(-0.1, -0.35, -0.25);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.1, -0.35, -0.25);
	glTexCoord2f(0.2, 1); glVertex3f(-0.1, -0.35, 0.3);
	glTexCoord2f(0.2, 0.7); glVertex3f(-0.13, -0.15, 0.4);
	glTexCoord2f(0, 0.7); glVertex3f(-0.13, -0.15, -0.33);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.13, -0.15, -0.33);
	glTexCoord2f(0.2, 1); glVertex3f(-0.13, -0.15, 0.4);
	glTexCoord2f(0.2, 0.7); glVertex3f(0.13, -0.15, 0.4);
	glTexCoord2f(0, 0.7); glVertex3f(0.13, -0.15, -0.33);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.13, -0.15, -0.33);
	glTexCoord2f(0.2, 1); glVertex3f(0.13, -0.15, 0.4);
	glTexCoord2f(0.2, 0.7); glVertex3f(0.1, -0.35, 0.3);
	glTexCoord2f(0, 0.7); glVertex3f(0.1, -0.35, -0.25);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.1, -0.35, -0.25);
	glTexCoord2f(0.2, 1); glVertex3f(-0.1, -0.35, -0.25);
	glTexCoord2f(0.2, 0.7); glVertex3f(-0.1, -0.35, 0.3);
	glTexCoord2f(0, 0.7); glVertex3f(0.1, -0.35, 0.3);
	glEnd();

	/*
	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.1, -0.3, 0.3);
	glTexCoord2f(1, 1); glVertex3f(-0.1, -0.3, 0.3);
	glTexCoord2f(1, 0); glVertex3f(-0.13, -0.1, 0.4);
	glTexCoord2f(0, 0); glVertex3f(0.13, -0.1, 0.4);
	glEnd();
	*/

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void buttArmor2() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"blue.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.13, 0.2, 0.4);
	glTexCoord2f(0.2, 1); glVertex3f(-0.13, 0.35, 0.3);
	glTexCoord2f(0.2, 0.7); glVertex3f(-0.13, -0.35, 0.3);
	glTexCoord2f(0, 0.7); glVertex3f(-0.13, -0.15, 0.4);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.13, -0.15, 0.4);
	glTexCoord2f(0.2, 1); glVertex3f(0.13, -0.15, 0.4);
	glTexCoord2f(0.2, 0.7); glVertex3f(0.13, 0.2, 0.4);
	glTexCoord2f(0, 0.7); glVertex3f(-0.13, 0.2, 0.4);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.7); glVertex3f(-0.13, 0.2, 0.4);
	glTexCoord2f(0.2, 1); glVertex3f(0.13, 0.2, 0.4);
	glTexCoord2f(0.2, 0.7); glVertex3f(0.13, 0.35, 0.3);
	glTexCoord2f(0, 0.7); glVertex3f(-0.13, 0.35, 0.3);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.7); glVertex3f(-0.13, 0.35, 0.3);
	glTexCoord2f(0.2, 1); glVertex3f(0.13, 0.35, 0.3);
	glTexCoord2f(0.2, 0.7); glVertex3f(0.13, -0.35, 0.3);
	glTexCoord2f(0, 0.7); glVertex3f(-0.13, -0.35, 0.3);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.7); glVertex3f(-0.13, -0.35, 0.3);
	glTexCoord2f(0.2, 1); glVertex3f(-0.13, -0.15, 0.4);
	glTexCoord2f(0.2, 0.7); glVertex3f(0.13, -0.15, 0.4);
	glTexCoord2f(0, 0.7); glVertex3f(0.13, -0.35, 0.3);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.7); glVertex3f(0.13, -0.35, 0.3);
	glTexCoord2f(0.2, 1); glVertex3f(0.13, -0.15, 0.4);
	glTexCoord2f(0.2, 0.7); glVertex3f(0.13, 0.2, 0.4);
	glTexCoord2f(0, 0.7); glVertex3f(0.13, 0.35, 0.3);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void butt() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"whitemetal.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, 0.4, -0.3);
	glTexCoord2f(1, 1); glVertex3f(0.4, 0.4, -0.3);
	glTexCoord2f(1, 0.6); glVertex3f(0.4, 0.1, -0.3);
	glTexCoord2f(0.6, 0); glVertex3f(0.13, -0.15, -0.3);
	glTexCoord2f(0.4, 0); glVertex3f(-0.13, -0.15, -0.3);
	glTexCoord2f(0, 0.6); glVertex3f(-0.4, 0.1, -0.3);
	glEnd();

	//Left Below
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, 0.1, -0.3);
	glTexCoord2f(1, 1); glVertex3f(-0.4, 0.1, 0.3);
	glTexCoord2f(1, 0); glVertex3f(-0.13, -0.15, 0.3);
	glTexCoord2f(0, 0); glVertex3f(-0.13, -0.15, -0.3);
	glEnd();

	//Left Above
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, 0.1, -0.3);
	glTexCoord2f(1, 1); glVertex3f(-0.4, 0.1, 0.3);
	glTexCoord2f(1, 0); glVertex3f(-0.4, 0.4, 0.3);
	glTexCoord2f(0, 0); glVertex3f(-0.4, 0.4, -0.3);
	glEnd();

	//Top 
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, 0.4, -0.3);
	glTexCoord2f(1, 1); glVertex3f(-0.4, 0.4, 0.3);
	glTexCoord2f(1, 0); glVertex3f(0.4, 0.4, 0.3);
	glTexCoord2f(0, 0); glVertex3f(0.4, 0.4, -0.3);
	glEnd();

	//Right Above
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.4, 0.4, -0.3);
	glTexCoord2f(1, 1); glVertex3f(0.4, 0.4, 0.3);
	glTexCoord2f(1, 0); glVertex3f(0.4, 0.1, 0.3);
	glTexCoord2f(0, 0); glVertex3f(0.4, 0.1, -0.3);
	glEnd();

	//Right Below
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.4, 0.1, -0.3);
	glTexCoord2f(1, 1); glVertex3f(0.4, 0.1, 0.3);
	glTexCoord2f(1, 0); glVertex3f(0.13, -0.15, 0.3);
	glTexCoord2f(0, 0); glVertex3f(0.13, -0.15, -0.3);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.13, -0.15, -0.3);
	glTexCoord2f(1, 1); glVertex3f(0.13, -0.15, 0.3);
	glTexCoord2f(1, 0); glVertex3f(-0.13, -0.15, 0.3);
	glTexCoord2f(0, 0); glVertex3f(-0.13, -0.15, -0.3);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, 0.4, 0.3);
	glTexCoord2f(1, 1); glVertex3f(0.4, 0.4, 0.3);
	glTexCoord2f(1, 0.6); glVertex3f(0.4, 0.1, 0.3);
	glTexCoord2f(0.6, 0); glVertex3f(0.13, -0.15, 0.3);
	glTexCoord2f(0.4, 0); glVertex3f(-0.13, -0.15, 0.3);
	glTexCoord2f(0, 0.6); glVertex3f(-0.4, 0.1, 0.3);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	//Butt is Designed
	buttDesign();
}

void sixPackBlader() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"silver.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//1st Blade
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.225, 0.95, -0.255);
	glTexCoord2f(1, 1); glVertex3f(-0.01, 0.95, -0.255);
	glTexCoord2f(1, 0); glVertex3f(-0.01, 0.89, -0.265);
	glTexCoord2f(0, 0); glVertex3f(-0.225, 0.89, -0.265);
	glEnd();

	//2nd Blade
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.225, 0.88, -0.255);
	glTexCoord2f(1, 1); glVertex3f(-0.01, 0.88, -0.255);
	glTexCoord2f(1, 0); glVertex3f(-0.01, 0.82, -0.265);
	glTexCoord2f(0, 0); glVertex3f(-0.225, 0.82, -0.265);
	glEnd();

	//3rd Blade
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.225, 0.81, -0.255);
	glTexCoord2f(1, 1); glVertex3f(-0.01, 0.81, -0.255);
	glTexCoord2f(1, 0); glVertex3f(-0.01, 0.75, -0.265);
	glTexCoord2f(0, 0); glVertex3f(-0.225, 0.75, -0.265);
	glEnd();

	//4th Blade
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.225, 0.74, -0.255);
	glTexCoord2f(1, 1); glVertex3f(-0.01, 0.74, -0.255);
	glTexCoord2f(1, 0); glVertex3f(-0.01, 0.68, -0.265);
	glTexCoord2f(0, 0); glVertex3f(-0.225, 0.68, -0.265);
	glEnd();

	//5th Blade
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.225, 0.67, -0.255);
	glTexCoord2f(1, 1); glVertex3f(-0.01, 0.67, -0.255);
	glTexCoord2f(1, 0); glVertex3f(-0.01, 0.61, -0.265);
	glTexCoord2f(0, 0); glVertex3f(-0.225, 0.61, -0.265);
	glEnd();

	//6th Blade
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.225, 0.60, -0.255);
	glTexCoord2f(1, 1); glVertex3f(-0.01, 0.60, -0.255);
	glTexCoord2f(1, 0); glVertex3f(-0.01, 0.54, -0.265);
	glTexCoord2f(0, 0); glVertex3f(-0.225, 0.54, -0.265);
	glEnd();

	//7th Blade
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.225, 0.53, -0.255);
	glTexCoord2f(1, 1); glVertex3f(-0.01, 0.53, -0.255);
	glTexCoord2f(1, 0); glVertex3f(-0.01, 0.47, -0.265);
	glTexCoord2f(0, 0); glVertex3f(-0.225, 0.47, -0.265);
	glEnd();

	//8th Blade
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.225, 0.46, -0.255);
	glTexCoord2f(1, 1); glVertex3f(-0.01, 0.46, -0.255);
	glTexCoord2f(1, 0); glVertex3f(-0.01, 0.4, -0.265);
	glTexCoord2f(0, 0); glVertex3f(-0.225, 0.4, -0.265);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void sixPackArmor1() {
	//Left Six-Pack Blader
	sixPackBlader();

	//Right Six-Pack Blader
	glPushMatrix();
	glTranslatef(0.235, 0, 0);
	sixPackBlader();
	glPopMatrix();

	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"white.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front 1
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.25, 1, -0.275);
	glTexCoord2f(1, 1); glVertex3f(-0.225, 1, -0.275);
	glTexCoord2f(1, 0); glVertex3f(-0.225, 0.4, -0.275);
	glTexCoord2f(0, 0); glVertex3f(-0.25, 0.4, -0.275);
	glEnd();

	//Front 2
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.25, 1, -0.275);
	glTexCoord2f(1, 1); glVertex3f(0.25, 1, -0.275);
	glTexCoord2f(1, 0); glVertex3f(0.25, 0.95, -0.275);
	glTexCoord2f(0, 0); glVertex3f(-0.25, 0.95, -0.275);
	glEnd();

	//Front 3
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.225, 1, -0.275);
	glTexCoord2f(1, 1); glVertex3f(0.25, 1, -0.275);
	glTexCoord2f(0, 0); glVertex3f(0.25, 0.4, -0.275);
	glTexCoord2f(0, 0); glVertex3f(0.225, 0.4, -0.275);
	glEnd();

	//Front 4
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.225, 1, -0.275);
	glTexCoord2f(1, 1); glVertex3f(-0.225, 1, -0.251);
	glTexCoord2f(1, 0); glVertex3f(-0.225, 0.4, -0.251);
	glTexCoord2f(0, 0); glVertex3f(-0.225, 0.4, -0.275);
	glEnd();

	//Front 5
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.225, 1, -0.275);
	glTexCoord2f(1, 1); glVertex3f(-0.225, 1, -0.251);
	glTexCoord2f(1, 0); glVertex3f(0.225, 0.95, -0.251);
	glTexCoord2f(0, 0); glVertex3f(0.225, 0.95, -0.275);
	glEnd();

	//Front 6
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.225, 1, -0.275);
	glTexCoord2f(1, 1); glVertex3f(0.225, 1, -0.251);
	glTexCoord2f(1, 0); glVertex3f(0.225, 0.4, -0.251);
	glTexCoord2f(0, 0); glVertex3f(0.225, 0.4, -0.275);
	glEnd();

	//Front 7
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.01, 1, -0.27);
	glTexCoord2f(1, 1); glVertex3f(0.01, 1, -0.251);
	glTexCoord2f(1, 0); glVertex3f(0.01, 0.4, -0.251);
	glTexCoord2f(0, 0); glVertex3f(-0.01, 0.4, -0.27);
	glEnd();

	//Front 8
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.01, 1, -0.27);
	glTexCoord2f(1, 1); glVertex3f(-0.01, 1, -0.251);
	glTexCoord2f(1, 0); glVertex3f(-0.01, 0.4, -0.251);
	glTexCoord2f(0, 0); glVertex3f(-0.01, 0.4, -0.27);
	glEnd();

	//Front 9
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.01, 1, -0.27);
	glTexCoord2f(1, 1); glVertex3f(0.01, 1, -0.251);
	glTexCoord2f(1, 0); glVertex3f(0.01, 0.4, -0.251);
	glTexCoord2f(0, 0); glVertex3f(0.01, 0.4, -0.27);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.25, 0.4, -0.275);
	glTexCoord2f(1, 1); glVertex3f(-0.25, 0.4, -0.251);
	glTexCoord2f(1, 0); glVertex3f(-0.25, 1, -0.251);
	glTexCoord2f(0, 0); glVertex3f(-0.25, 1, -0.275);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.25, 1, -0.275);
	glTexCoord2f(1, 1); glVertex3f(-0.25, 1, -0.251);
	glTexCoord2f(1, 0); glVertex3f(0.25, 1, -0.251);
	glTexCoord2f(0, 0); glVertex3f(0.25, 1, -0.275);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.25, 1, -0.275);
	glTexCoord2f(1, 1); glVertex3f(0.25, 1, -0.251);
	glTexCoord2f(1, 0); glVertex3f(0.25, 0.4, -0.251);
	glTexCoord2f(0, 0); glVertex3f(0.25, 0.4, -0.275);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.25, 0.4, -0.275);
	glTexCoord2f(1, 1); glVertex3f(-0.25, 0.4, -0.275);
	glTexCoord2f(1, 0); glVertex3f(-0.25, 0.4, -0.251);
	glTexCoord2f(0, 0); glVertex3f(0.25, 0.4, -0.251);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.25, 0.4, -0.25);
	glTexCoord2f(1, 1); glVertex3f(-0.25, 0.4, -0.25);
	glTexCoord2f(1, 0); glVertex3f(-0.25, 1, -0.251);
	glTexCoord2f(0, 0); glVertex3f(0.25, 1, -0.251);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void sixpack() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		majorPartImage, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.3, 0.8, -0.25);
	glTexCoord2f(0.2, 0.6); glVertex3f(0.3, 0.8, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.3, 0.4, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(-0.3, 0.4, -0.25);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.3, 0.4, -0.25);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.3, 0.4, 0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.3, 0.8, 0.25);
	glTexCoord2f(0, 0.4); glVertex3f(-0.3, 0.8, -0.25);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.3, 0.8, -0.25);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.3, 0.8, 0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.3, 0.8, 0.25);
	glTexCoord2f(0, 0.4); glVertex3f(0.3, 0.8, -0.25);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.3, 0.8, -0.25);
	glTexCoord2f(0.2, 0.6); glVertex3f(0.3, 0.8, 0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.3, 0.4, 0.25);
	glTexCoord2f(0, 0.4); glVertex3f(0.3, 0.4, -0.25);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.3, 0.4, -0.25);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.3, 0.4, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.3, 0.4, 0.25);
	glTexCoord2f(0, 0.4); glVertex3f(0.3, 0.4, 0.25);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.3, 0.4, 0.25);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.3, 0.4, 0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.3, 0.8, 0.25);
	glTexCoord2f(0, 0.4); glVertex3f(0.3, 0.8, 0.25);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void chestMirrorFrameSide() {

	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		majorPartImage, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Frame Side 1 - Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.4, 1.4, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.35, 1.35, -0.35);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.35, 1.05, -0.35);
	glTexCoord2f(0, 0.4); glVertex3f(-0.4, 1.0, -0.35);
	glEnd();

	//Frame Side 1 - Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.4, 1.0, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.4, 1.0, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.4, 1.4, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(-0.4, 1.4, -0.35);
	glEnd();

	//Frame Side 1 - Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.4, 1.4, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.4, 1.4, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.35, 1.35, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(-0.35, 1.35, -0.35);
	glEnd();

	//Frame Side 1 - Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.35, 1.35, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.35, 1.35, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.35, 1.05, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(-0.35, 1.05, -0.35);
	glEnd();

	//Frame Side 1 - Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.35, 1.05, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.4, 1.0, -0.35);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.4, 1.0, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(-0.35, 1.05, -0.25);
	glEnd();

	//Frame Side 1 - Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.35, 1.05, -0.25);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.4, 1.0, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.4, 1.4, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(-0.35, 1.35, -0.25);
	glEnd();

	//////////////////////////////////////// Frame Side 2 ////////////////////////////////////////////
	//Frame Side 2 - Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.4, 1.4, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(0, 1.4, -0.35);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.05, 1.35, -0.35);
	glTexCoord2f(0, 0.4); glVertex3f(-0.35, 1.35, -0.35);
	glEnd();

	//Frame Side 2 - Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.35, 1.35, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.35, 1.35, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.4, 1.4, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(-0.4, 1.4, -0.35);
	glEnd();

	//Frame Side 2 - Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.4, 1.4, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.4, 1.4, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(0, 1.4, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(0, 1.4, -0.35);
	glEnd();

	//Frame Side 2 - Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0, 1.4, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(0, 1.4, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.05, 1.35, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(-0.05, 1.35, -0.35);
	glEnd();

	//Frame Side 2 - Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.05, 1.35, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.35, 1.35, -0.35);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.35, 1.35, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(-0.05, 1.35, -0.25);
	glEnd();

	//Frame Side 2 - Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.05, 1.35, -0.25);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.35, 1.35, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.4, 1.4, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(0, 1.4, -0.25);
	glEnd();

	//////////////////////////////////////// Frame Side 3 ////////////////////////////////////////////
	//Frame Side 3 - Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.05, 1.35, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(0.0, 1.4, -0.35);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.0, 1.0, -0.35);
	glTexCoord2f(0, 0.4); glVertex3f(-0.05, 1.05, -0.35);
	glEnd();

	//Frame Side 3 - Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.05, 1.05, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.05, 1.05, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.05, 1.35, -0.25);
	glVertex3f(-0.05, 1.35, -0.35);
	glEnd();

	//Frame Side 3 - Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.05, 1.35, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.05, 1.35, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.0, 1.4, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(0.0, 1.4, -0.35);
	glEnd();

	//Frame Side 3 - Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.0, 1.4, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(0.0, 1.4, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.0, 1.0, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(0.0, 1.0, -0.35);
	glEnd();

	//Frame Side 3 - Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.0, 1.0, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.05, 1.05, -0.35);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.05, 1.05, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(0.0, 1.0, -0.25);
	glEnd();

	//Frame Side 3 - Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.0, 1.0, -0.25);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.05, 1.05, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.05, 1.35, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(0.0, 1.4, -0.25);
	glEnd();

	//////////////////////////////////////// Frame Side 4 ////////////////////////////////////////////

	//Frame Side 4 - Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.35, 1.05, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.05, 1.05, -0.35);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.0, 1.0, -0.35);
	glTexCoord2f(0, 0.4); glVertex3f(-0.4, 1.0, -0.35);
	glEnd();

	//Frame Side 4 - Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.4, 1.0, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.4, 1.0, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.35, 1.05, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(-0.35, 1.05, -0.35);
	glEnd();

	//Frame Side 4 - Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.35, 1.05, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.35, 1.05, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.05, 1.05, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(-0.05, 1.05, -0.35);
	glEnd();

	//Frame Side 4 - Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.05, 1.05, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.05, 1.05, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.0, 1.0, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(0.0, 1.0, -0.35);
	glEnd();

	//Frame Side 4 - Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.0, 1.0, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.4, 1.0, -0.35);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.4, 1.0, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(0.0, 1.0, -0.25);
	glEnd();

	//Frame Side 4 - Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.0, 1.0, -0.25);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.4, 1.0, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.35, 1.05, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(-0.05, 1.05, -0.25);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void chestMirror() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"windshield.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1);	glVertex3f(-0.35, 1.35, -0.31);
	glTexCoord2f(1, 1); glVertex3f(-0.05, 1.35, -0.31);
	glTexCoord2f(1, 0); glVertex3f(-0.05, 1.05, -0.31);
	glTexCoord2f(0, 0); glVertex3f(-0.35, 1.05, -0.31);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.35, 1.05, -0.31);
	glTexCoord2f(1, 1); glVertex3f(-0.35, 1.05, -0.29);
	glTexCoord2f(1, 0); glVertex3f(-0.35, 1.35, -0.29);
	glTexCoord2f(0, 0); glVertex3f(-0.35, 1.35, -0.31);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.35, 1.35, -0.31);
	glTexCoord2f(1, 1); glVertex3f(-0.35, 1.35, -0.29);
	glTexCoord2f(1, 0); glVertex3f(-0.05, 1.35, -0.29);
	glTexCoord2f(0, 0); glVertex3f(-0.05, 1.35, -0.31);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.05, 1.35, -0.31);
	glTexCoord2f(1, 1); glVertex3f(-0.05, 1.35, -0.29);
	glTexCoord2f(1, 0); glVertex3f(-0.05, 1.05, -0.29);
	glTexCoord2f(0, 0); glVertex3f(-0.05, 1.05, -0.31);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.05, 1.05, -0.31);
	glTexCoord2f(1, 1); glVertex3f(-0.35, 1.05, -0.31);
	glTexCoord2f(1, 0); glVertex3f(-0.35, 1.05, -0.29);
	glTexCoord2f(0, 0); glVertex3f(-0.05, 1.05, -0.29);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.05, 1.05, -0.29);
	glTexCoord2f(1, 1); glVertex3f(-0.35, 1.05, -0.29);
	glTexCoord2f(1, 0); glVertex3f(-0.35, 1.35, -0.29);
	glTexCoord2f(0, 0); glVertex3f(-0.05, 1.35, -0.29);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
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
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		majorPartImage, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.4, 1.0, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.4, 1.0, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.4, 1.5, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(-0.4, 1.4, -0.35);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.4, 1.4, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.4, 1.5, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.4, 1.5, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(0.4, 1.4, -0.35);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.4, 1.4, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(0.4, 1.5, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.4, 1.0, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(0.4, 1.0, -0.35);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.4, 1.0, -0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.4, 1.0, -0.35);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.4, 1.0, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(0.4, 1.0, -0.25);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.4, 1.0, -0.25);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.4, 1.0, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.4, 1.5, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(0.4, 1.5, -0.25);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void chestArmor2() {
	GLUquadricObj *upperChestCylinder1 = NULL;
	upperChestCylinder1 = gluNewQuadric();

	glPushMatrix();
	glTranslatef(-0.35, 1.5, -0.275);
	gluQuadricDrawStyle(upperChestCylinder1, GLU_LINE);
	gluCylinder(upperChestCylinder1, 0.02, 0.02, 0.05, 20, 20);
	gluDeleteQuadric(upperChestCylinder1);
	glPopMatrix();

	GLUquadricObj *upperChestCylinder2 = NULL;
	upperChestCylinder2 = gluNewQuadric();

	glPushMatrix();
	glTranslatef(-0.3, 1.5, -0.275);
	gluQuadricDrawStyle(upperChestCylinder2, GLU_LINE);
	gluCylinder(upperChestCylinder2, 0.02, 0.02, 0.05, 20, 20);
	gluDeleteQuadric(upperChestCylinder2);
	glPopMatrix();

	GLUquadricObj *upperChestCylinder3 = NULL;
	upperChestCylinder3 = gluNewQuadric();

	glPushMatrix();
	glTranslatef(0.3, 1.5, -0.275);
	gluQuadricDrawStyle(upperChestCylinder3, GLU_LINE);
	gluCylinder(upperChestCylinder3, 0.02, 0.02, 0.05, 20, 20);
	gluDeleteQuadric(upperChestCylinder3);
	glPopMatrix();

	GLUquadricObj *upperChestCylinder4 = NULL;
	upperChestCylinder4 = gluNewQuadric();

	glPushMatrix();
	glTranslatef(0.35, 1.5, -0.275);
	gluQuadricDrawStyle(upperChestCylinder4, GLU_LINE);
	gluCylinder(upperChestCylinder4, 0.02, 0.02, 0.05, 20, 20);
	gluDeleteQuadric(upperChestCylinder4);
	glPopMatrix();
}

void chest() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		majorPartImage, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);	

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.4, 1.5, -0.25);
	glTexCoord2f(0.2, 0.6); glVertex3f(0.4, 1.5, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.4, 1, -0.25);
	glTexCoord2f(0, 0.4); glVertex3f(-0.4, 1, -0.25);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.4, 1, -0.25);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.4, 1, 0.35);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.4, 1.5, 0.35);
	glTexCoord2f(0, 0.4); glVertex3f(-0.4, 1.5, -0.25);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.4, 1.5, -0.25);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.4, 1.5, 0.35);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.4, 1.5, 0.35);
	glTexCoord2f(0, 0.4); glVertex3f(0.4, 1.5, -0.25);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.4, 1.5, -0.25);
	glTexCoord2f(0.2, 0.6); glVertex3f(0.4, 1.5, 0.35);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.4, 1, 0.35);
	glTexCoord2f(0, 0.4); glVertex3f(0.4, 1, -0.25);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.4, 1, -0.25);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.4, 1, -0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.4, 1, 0.35);
	glTexCoord2f(0, 0.4); glVertex3f(0.4, 1, 0.35);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.4, 1, 0.35);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.4, 1, 0.35);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.4, 1.5, 0.35);
	glTexCoord2f(0, 0.4); glVertex3f(0.4, 1.5, 0.35);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void middleChest() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"silver.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);


	//Left Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.4, 1, -0.35);
	glTexCoord2f(1, 1); glVertex3f(-0.25, 1, -0.35);
	glTexCoord2f(1, 0); glVertex3f(-0.27, 0.8, -0.3);
	glTexCoord2f(0, 0); glVertex3f(-0.35, 0.8, -0.3);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.35, 0.8, -0.3);
	glTexCoord2f(1, 1); glVertex3f(-0.35, 0.8, 0.3);
	glTexCoord2f(1, 0); glVertex3f(-0.4, 1, 0.35);
	glTexCoord2f(0, 0); glVertex3f(-0.4, 1, -0.35);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(-0.4, 1, -0.35);
	glTexCoord2f(0, 1); glVertex3f(-0.4, 1, 0.35);
	glTexCoord2f(1, 1); glVertex3f(0.4, 1, 0.35);
	glTexCoord2f(1, 0); glVertex3f(0.4, 1, -0.35);
	glTexCoord2f(0.8, 0); glVertex3f(0.25, 1, -0.35);
	glTexCoord2f(0.8, 0.5); glVertex3f(0.25, 1, -0.25);
	glTexCoord2f(0.2, 0.5); glVertex3f(-0.25, 1, -0.25);
	glTexCoord2f(0.2, 0); glVertex3f(-0.25, 1, -0.35);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.4, 1, -0.35);
	glTexCoord2f(1, 1); glVertex3f(0.4, 1, 0.35);
	glTexCoord2f(1, 0); glVertex3f(0.35, 0.8, 0.3);
	glTexCoord2f(0, 0); glVertex3f(0.35, 0.8, -0.3);
	glEnd();


	//Right Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.25, 1, -0.35);
	glTexCoord2f(1, 1); glVertex3f(0.4, 1, -0.35);
	glTexCoord2f(1, 0); glVertex3f(0.35, 0.8, -0.3);
	glTexCoord2f(0, 0); glVertex3f(0.27, 0.8, -0.3);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(1, 0); glVertex3f(0.35, 0.8, -0.3);
	glTexCoord2f(0.8, 0); glVertex3f(0.27, 0.8, -0.3);
	glTexCoord2f(0.8, 0.5); glVertex3f(0.27, 0.8, -0.25);
	glTexCoord2f(0.2, 0.5); glVertex3f(-0.27, 0.8, -0.25);
	glTexCoord2f(0.2, 0); glVertex3f(-0.27, 0.8, -0.3);
	glTexCoord2f(0, 0); glVertex3f(-0.35, 0.8, -0.3);
	glTexCoord2f(0, 1); glVertex3f(-0.35, 0.8, 0.3);
	glTexCoord2f(1, 1); glVertex3f(0.35, 0.8, 0.3);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.35, 0.8, 0.3);
	glTexCoord2f(1, 1); glVertex3f(-0.35, 0.8, 0.3);
	glTexCoord2f(1, 0); glVertex3f(-0.4, 1, 0.35);
	glTexCoord2f(0, 0); glVertex3f(0.4, 1, 0.35);
	glEnd();

	//Internal 1
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.25, 1, -0.35);
	glTexCoord2f(1, 1); glVertex3f(-0.25, 1, -0.25);
	glTexCoord2f(1, 0); glVertex3f(-0.27, 0.8, -0.25);
	glTexCoord2f(0, 0); glVertex3f(-0.27, 0.8, -0.3);
	glEnd();

	//Internal 2
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.25, 1, -0.25);
	glTexCoord2f(1, 1); glVertex3f(0.25, 1, -0.25);
	glTexCoord2f(1, 0); glVertex3f(0.27, 0.8, -0.25);
	glTexCoord2f(0, 0); glVertex3f(-0.27, 0.8, -0.25);
	glEnd();

	//Internal 3
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.25, 1, -0.35);
	glTexCoord2f(1, 1); glVertex3f(0.25, 1, -0.25);
	glTexCoord2f(1, 0); glVertex3f(0.27, 0.8, -0.25);
	glTexCoord2f(0, 0); glVertex3f(0.27, 0.8, -0.3);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void head()
{
	//head x=-0.15/0.15 y=1.5/1.9 z=-0.05/0.25
	//lefteye x=-0.12/-0.03 y=1.7/1.75 z=-0.05
	//righteye x=0.03/0.12 y=1.7/1.725 z=-0.05
	//mouth x=-0.15/0.15 y=1.5/1.65 z=-0.05/-0.07

	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"headcrown.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//head dxxx
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(-0.05, 1.9, -0.05);
	glTexCoord2f(1, 0); glVertex3f(0.05, 1.9, -0.05);
	glTexCoord2f(1, 0.8); glVertex3f(0.05, 2.05, -0.0);
	glTexCoord2f(0.5, 1); glVertex3f(0.00, 2.1, -0.0);
	glTexCoord2f(0, 0.8); glVertex3f(-0.05, 2.05, -0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(-0.05, 1.9, -0.07);
	glTexCoord2f(1, 0); glVertex3f(0.05, 1.9, -0.07);
	glTexCoord2f(1, 0.8); glVertex3f(0.05, 2.05, -0.02);
	glTexCoord2f(0.5, 1); glVertex3f(0.00, 2.1, -0.02);
	glTexCoord2f(0, 0.8); glVertex3f(-0.05, 2.05, -0.02);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"blue.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.05, 1.9, -0.07);
	glTexCoord2f(0.5, 1); glVertex3f(-0.05, 1.9, -0.05);
	glTexCoord2f(1, 1); glVertex3f(-0.05, 2.05, -0.0);
	glTexCoord2f(1, 0.5); glVertex3f(0.0, 2.1, -0.0);
	glTexCoord2f(0.5, 0.5); glVertex3f(0.0, 2.1, -0.02);
	glTexCoord2f(0, 0.5); glVertex3f(-0.05, 2.05, -0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.05, 1.9, -0.07);
	glTexCoord2f(0.5, 1); glVertex3f(0.05, 1.9, -0.05);
	glTexCoord2f(1, 1); glVertex3f(0.05, 2.05, -0.0);
	glTexCoord2f(1, 0.5); glVertex3f(0.0, 2.1, -0.0);
	glTexCoord2f(0.5, 0.5); glVertex3f(0.0, 2.1, -0.02);
	glTexCoord2f(0, 0.5); glVertex3f(0.05, 2.05, -0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.05, 2.0, -0.00);
	glTexCoord2f(0.2, 1); glVertex3f(0.05, 2.0, -0.00);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.05, 2.0, 0.25);
	glTexCoord2f(0, 0.3); glVertex3f(-0.05, 2.0, 0.25);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"blue.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//upper-part helmet
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, 1.9, -0.05);
	glTexCoord2f(0.2, 1); glVertex3f(-0.14, 1.91, -0.05);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.13, 1.92, -0.04);
	glTexCoord2f(0, 0.3); glVertex3f(-0.12, 1.93, -0.03);
	glTexCoord2f(0, 1); glVertex3f(-0.11, 1.94, -0.02);
	glTexCoord2f(0.2, 1); glVertex3f(-0.10, 1.95, -0.01);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.05, 2, 0);
	glTexCoord2f(0, 0.3); glVertex3f(0.05, 2.0, 0.0);
	glTexCoord2f(0, 1); glVertex3f(0.10, 1.95, 0.0);
	glTexCoord2f(0.2, 1); glVertex3f(0.11, 1.94, -0.01);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.12, 1.93, -0.02);
	glTexCoord2f(0, 0.3); glVertex3f(0.13, 1.92, -0.03);
	glTexCoord2f(0, 1); glVertex3f(0.14, 1.91, -0.04);
	glTexCoord2f(0.2, 1); glVertex3f(0.14, 1.91, -0.05);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.15, 1.9, -0.06);
	glEnd();


	//left-upper-part-helmet
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.05, 2.0, 0.27);
	glTexCoord2f(0.2, 1); glVertex3f(-0.06, 1.97, 0.27);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.07, 1.95, 0.27);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, 1.9, 0.25);
	glTexCoord2f(0, 1); glVertex3f(-0.15, 1.88, 0.10);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, 1.9, -0.05);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, 1.9, -0.05);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, 1.9, -0.05);
	glTexCoord2f(0, 1); glVertex3f(-0.14, 1.91, -0.05);
	glTexCoord2f(0.2, 1); glVertex3f(-0.13, 1.92, -0.04);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.12, 1.93, -0.03);
	glTexCoord2f(0, 0.3); glVertex3f(-0.11, 1.94, -0.02);
	glTexCoord2f(0, 1); glVertex3f(-0.10, 1.95, -0.01);
	glTexCoord2f(0.2, 1); glVertex3f(-0.05, 2, 0);
	glEnd();




	glBegin(GL_POLYGON);
	glVertex3f(-0.15, 1.9, 0.25);
	glVertex3f(-0.15, 1.8, 0.25);
	glVertex3f(-0.15, 1.88, 0.10);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.05, 2.0, 0.27);
	glTexCoord2f(0.2, 1); glVertex3f(0.06, 1.97, 0.27);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.07, 1.95, 0.27);
	glTexCoord2f(0, 0.3); glVertex3f(0.15, 1.9, 0.25);
	glTexCoord2f(0, 1); glVertex3f(0.15, 1.8, 0.25);
	glTexCoord2f(0.2, 1); glVertex3f(0.15, 1.88, 0.10);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.15, 1.9, -0.05);
	glTexCoord2f(0, 0.3); glVertex3f(0.15, 1.9, -0.05);
	glTexCoord2f(0, 1); glVertex3f(0.15, 1.9, -0.05);
	glTexCoord2f(0.2, 1); glVertex3f(0.14, 1.91, -0.05);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.13, 1.92, -0.04);
	glTexCoord2f(0, 0.3); glVertex3f(0.12, 1.93, -0.03);
	glTexCoord2f(0, 1); glVertex3f(0.11, 1.94, -0.02);
	glTexCoord2f(0.2, 1); glVertex3f(0.10, 1.95, -0.01);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.05, 2, 0);
	glEnd();


	//top part helmet
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, 1.88, -0.07);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, 1.9, -0.07);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.15, 1.9, -0.07);
	glTexCoord2f(0, 0.3); glVertex3f(0.15, 1.88, -0.07);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, 1.88, -0.05);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, 1.9, -0.05);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.15, 1.9, -0.05);
	glTexCoord2f(0, 0.3); glVertex3f(0.15, 1.88, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, 1.88, -0.05);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, 1.9, -0.05);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, 1.9, -0.07);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, 1.88, -0.07);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.15, 1.88, -0.05);
	glTexCoord2f(0.2, 1); glVertex3f(0.15, 1.9, -0.05);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.15, 1.9, -0.07);
	glTexCoord2f(0, 0.3); glVertex3f(0.15, 1.88, -0.07);
	glEnd();
	//top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, 1.9, -0.05);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, 1.9, -0.07);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, 1.9, -0.07);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, 1.9, -0.05);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, 1.88, -0.05);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, 1.88, -0.07);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, 1.88, -0.07);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, 1.88, -0.05);
	glEnd();



	//back-part helmet
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.15, 1.5, 0.25);
	glTexCoord2f(1, 1); glVertex3f(0.15, 1.9, 0.25);
	glTexCoord2f(1, 0.8); glVertex3f(0.07, 1.95, 0.27);
	glTexCoord2f(1, 0.6); glVertex3f(0.06, 1.97, 0.27);
	glTexCoord2f(1, 0.5); glVertex3f(0.05, 2.0, 0.27);
	glTexCoord2f(1, 0.4); glVertex3f(0.0, 2.0, 0.27);
	glTexCoord2f(1, 0.3); glVertex3f(-0.05, 2.0, 0.27);
	glTexCoord2f(1, 0.2); glVertex3f(-0.06, 1.97, 0.27);
	glTexCoord2f(1, 0.1); glVertex3f(-0.07, 1.95, 0.27);
	glTexCoord2f(1, 0); glVertex3f(-0.15, 1.9, 0.25);
	glTexCoord2f(0, 0); glVertex3f(-0.15, 1.5, 0.25);
	glEnd();



	//============================
	//right upper-part helmet

	//top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.15, 1.9, -0.05);
	glTexCoord2f(0.5, 1); glVertex3f(0.15, 1.88, 0.10);
	glTexCoord2f(1, 1); glVertex3f(0.15, 1.8, 0.25);
	glTexCoord2f(1, 0.5); glVertex3f(0.17, 1.8, 0.25);
	glTexCoord2f(0.5, 0.5); glVertex3f(0.17, 1.88, 0.10);
	glTexCoord2f(0, 0.5); glVertex3f(0.17, 1.9, -0.05);
	glEnd();
	//left

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.17, 1.7, -0.05);
	glTexCoord2f(0.5, 1); glVertex3f(0.17, 1.7, 0.25);
	glTexCoord2f(1, 0.5); glVertex3f(0.17, 1.8, 0.25);
	glTexCoord2f(0.5, 0.5); glVertex3f(0.17, 1.88, 0.10);
	glTexCoord2f(0, 0.5); glVertex3f(0.17, 1.9, -0.05);
	glEnd();

	//right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.15, 1.7, -0.05);
	glTexCoord2f(0.5, 1); glVertex3f(0.15, 1.7, 0.25);
	glTexCoord2f(1, 0.5); glVertex3f(0.15, 1.8, 0.25);
	glTexCoord2f(0.5, 0.5); glVertex3f(0.15, 1.88, 0.10);
	glTexCoord2f(0, 0.5); glVertex3f(0.15, 1.9, -0.05);
	glEnd();
	//front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.15, 1.7, -0.05);
	glTexCoord2f(0.2, 1); glVertex3f(0.17, 1.7, -0.05);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.17, 1.9, -0.05);
	glTexCoord2f(0, 0.3); glVertex3f(0.15, 1.9, -0.05);
	glEnd();
	//back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.15, 1.7, 0.25);
	glTexCoord2f(0.2, 1); glVertex3f(0.17, 1.7, 0.25);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.17, 1.8, 0.25);
	glTexCoord2f(0, 0.3); glVertex3f(0.15, 1.8, 0.25);
	glEnd();
	//============================
//left upper-part helmet
//top

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, 1.9, -0.05);
	glTexCoord2f(0.5, 1); glVertex3f(-0.15, 1.88, 0.10);
	glTexCoord2f(1, 1); glVertex3f(-0.15, 1.8, 0.25);
	glTexCoord2f(1, 0.5); glVertex3f(-0.17, 1.8, 0.25);
	glTexCoord2f(0.5, 0.5); glVertex3f(-0.17, 1.88, 0.10);
	glTexCoord2f(0, 0.5); glVertex3f(-0.17, 1.9, -0.05);
	glEnd();
	//left

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.17, 1.7, -0.05);
	glTexCoord2f(0.2, 1); glVertex3f(-0.17, 1.7, 0.25);
	glTexCoord2f(1, 0.5); glVertex3f(-0.17, 1.8, 0.25);
	glTexCoord2f(0.5, 0.5); glVertex3f(-0.17, 1.88, 0.10);
	glTexCoord2f(0, 0.5); glVertex3f(-0.17, 1.9, -0.05);
	glEnd();

	//right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, 1.7, -0.05);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, 1.7, 0.25);
	glTexCoord2f(1, 0.5); glVertex3f(-0.15, 1.8, 0.25);
	glTexCoord2f(0.5, 0.5); glVertex3f(-0.15, 1.88, 0.10);
	glTexCoord2f(0, 0.5); glVertex3f(-0.15, 1.9, -0.05);
	glEnd();
	//front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, 1.7, -0.05);
	glTexCoord2f(0.2, 1); glVertex3f(-0.17, 1.7, -0.05);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.17, 1.9, -0.05);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, 1.9, -0.05);
	glEnd();
	//back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, 1.7, 0.25);
	glTexCoord2f(0.2, 1); glVertex3f(-0.17, 1.7, 0.25);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.17, 1.8, 0.25);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, 1.8, 0.25);
	glEnd();



	//=====================================================================
		//left-bottom-part helmet 


	GLUquadricObj* sphere = NULL;
	sphere = gluNewQuadric();
	glPushMatrix();
	glTranslatef(-0.19, 1.7, 0.1);
	glRotatef(90, 0, 1, 0);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, true);
	gluSphere(sphere, 0.05, 50, 50);

	gluDeleteQuadric(sphere);
	glPopMatrix();

	GLUquadricObj* cylinder = NULL;
	cylinder = gluNewQuadric();
	glPushMatrix();
	glTranslatef(-0.19, 1.7, 0.1);
	glRotatef(-90, 1, 0, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, 0.03, 0.0, 0.3, 40, 40);

	gluDeleteQuadric(cylinder);
	glPopMatrix();

	//front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, 1.7, -0.05);
	glTexCoord2f(0.3, 1); glVertex3f(-0.15, 1.65, -0.1);
	glTexCoord2f(0.6, 1); glVertex3f(-0.15, 1.55, -0.1);
	glTexCoord2f(1, 1); glVertex3f(-0.15, 1.5, -0.05);
	glTexCoord2f(0.6, 0.5); glVertex3f(-0.17, 1.5, -0.05);
	glTexCoord2f(0.3, 0.5); glVertex3f(-0.17, 1.55, -0.1);
	glTexCoord2f(0, 0.5); glVertex3f(-0.17, 1.65, -0.1);
	glTexCoord2f(0, 0.5); glVertex3f(-0.17, 1.7, -0.05);
	glEnd();

	//left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.17, 1.5, -0.05);
	glTexCoord2f(0.5, 1); glVertex3f(-0.17, 1.55, -0.1);
	glTexCoord2f(1, 1); glVertex3f(-0.17, 1.65, -0.1);
	glTexCoord2f(1, 0.5); glVertex3f(-0.17, 1.7, -0.05);
	glTexCoord2f(0.5, 0.5); glVertex3f(-0.17, 1.7, 0.25);
	glTexCoord2f(0, 0.5); glVertex3f(-0.17, 1.5, 0.25);
	glEnd();

	//right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, 1.5, -0.05);
	glTexCoord2f(0.5, 1); glVertex3f(-0.15, 1.55, -0.1);
	glTexCoord2f(1, 1); glVertex3f(-0.15, 1.65, -0.1);
	glTexCoord2f(1, 0.5); glVertex3f(-0.15, 1.7, -0.05);
	glTexCoord2f(0.5, 0.5); glVertex3f(-0.15, 1.7, 0.25);
	glTexCoord2f(0, 0.5); glVertex3f(-0.15, 1.5, 0.25);
	glEnd();

	//back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, 1.7, 0.25);
	glTexCoord2f(0.2, 1); glVertex3f(-0.17, 1.7, 0.25);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.17, 1.5, 0.25);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, 1.5, 0.25);
	glEnd();

	//bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, 1.5, -0.05);
	glTexCoord2f(0.2, 1); glVertex3f(-0.17, 1.5, -0.05);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.17, 1.7, 0.25);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, 1.7, 0.25);
	glEnd();
	


	//====================================================================
	//right bottom part helmet

	sphere = gluNewQuadric();
	glPushMatrix();
	glTranslatef(0.19, 1.7, 0.1);
	glRotatef(90, 0, 1, 0);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, true);
	gluSphere(sphere, 0.05, 50, 50);
	gluDeleteQuadric(sphere);
	glPopMatrix();


	cylinder = gluNewQuadric();
	glPushMatrix();
	glTranslatef(0.19, 1.7, 0.1);
	glRotatef(-90, 1, 0, 0);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, 0.03, 0.0, 0.3, 40, 40);
	gluDeleteQuadric(cylinder);
	glPopMatrix();

	//front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.15, 1.7, -0.05);
	glTexCoord2f(0.3, 1); glVertex3f(0.15, 1.65, -0.1);
	glTexCoord2f(0.6, 1); glVertex3f(0.15, 1.55, -0.1);
	glTexCoord2f(1, 1); glVertex3f(0.15, 1.5, -0.05);
	glTexCoord2f(0.6, 0.5); glVertex3f(0.17, 1.5, -0.05);
	glTexCoord2f(0.3, 0.5); glVertex3f(0.17, 1.55, -0.1);
	glTexCoord2f(0, 0.5); glVertex3f(0.17, 1.65, -0.1);
	glTexCoord2f(0, 0.5); glVertex3f(0.17, 1.7, -0.05);
	glEnd();

	//left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.17, 1.5, -0.05);
	glTexCoord2f(0.5, 1); glVertex3f(0.17, 1.55, -0.1);
	glTexCoord2f(1, 1); glVertex3f(0.17, 1.65, -0.1);
	glTexCoord2f(1, 0.5); glVertex3f(0.17, 1.7, -0.05);
	glTexCoord2f(0.5, 0.5); glVertex3f(0.17, 1.7, 0.25);
	glTexCoord2f(0, 0.5); glVertex3f(0.17, 1.5, 0.25);
	glEnd();

	//right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.15, 1.5, -0.05);
	glTexCoord2f(0.5, 1); glVertex3f(0.15, 1.55, -0.1);
	glTexCoord2f(1, 1); glVertex3f(0.15, 1.65, -0.1);
	glTexCoord2f(1, 0.5); glVertex3f(0.15, 1.7, -0.05);
	glTexCoord2f(0.5, 0.5); glVertex3f(0.15, 1.7, 0.25);
	glTexCoord2f(0, 0.5); glVertex3f(0.15, 1.5, 0.25);
	glEnd();

	//back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.15, 1.7, 0.25);
	glTexCoord2f(0.2, 1); glVertex3f(0.17, 1.7, 0.25);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.17, 1.5, 0.25);
	glTexCoord2f(0, 0.3); glVertex3f(0.15, 1.5, 0.25);
	glEnd();

	//bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.15, 1.5, -0.05);
	glTexCoord2f(0.2, 1); glVertex3f(0.17, 1.5, -0.05);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.17, 1.7, 0.25);
	glTexCoord2f(0, 0.3); glVertex3f(0.15, 1.7, 0.25);
	glEnd();

	//Front Face
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(-0.15, 1.9, -0.04);
	glTexCoord2f(0.2, 1); glVertex3f(0.15, 1.9, -0.04);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.15, 1.5, -0.04);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, 1.5, -0.04);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
	//====================================================================

	/*
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

	*/
	
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"eye.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front Face - UP
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(-0.12, 1.8, -0.05);
	glTexCoord2f(1, 1); glVertex3f(0.12, 1.8, -0.05);
	glTexCoord2f(1, 0); glVertex3f(0.12, 1.7, -0.05);
	glTexCoord2f(0, 0); glVertex3f(-0.12, 1.7, -0.05);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"mouth.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front Face - Down
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex3f(-0.08, 1.7, -0.05);
	glTexCoord2f(1, 1); glVertex3f(0.08, 1.7, -0.05);
	glTexCoord2f(1, 0); glVertex3f(0.08, 1.5, -0.05);
	glTexCoord2f(0, 0); glVertex3f(-0.08, 1.5, -0.05);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);


}

void upperArmJoint() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		majorPartImage, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.45, 1.4, 0);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.4, 1.4, 0);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.4, 1.15, 0);
	glTexCoord2f(0, 0.4); glVertex3f(-0.45, 1.15, 0);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.45, 1.15, 0);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.45, 1.15, 0.1);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.45, 1.4, 0.1);
	glTexCoord2f(0, 0.4); glVertex3f(-0.45, 1.4, 0);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.45, 1.4, 0);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.45, 1.4, 0.1);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.4, 1.4, 0.1);
	glTexCoord2f(0, 0.4); glVertex3f(-0.4, 1.4, 0);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.4, 1.4, 0);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.4, 1.4, 0.1);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.4, 1.15, 0.1);
	glTexCoord2f(0, 0.4); glVertex3f(-0.4, 1.15, 0);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.4, 1.15, 0);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.45, 1.15, 0);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.45, 1.15, 0.1);
	glTexCoord2f(0, 0.4); glVertex3f(-0.4, 1.15, 0.1);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.4, 1.15, 0.1);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.45, 1.15, 0.1);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.45, 1.4, 0.1);
	glTexCoord2f(0, 0.4); glVertex3f(-0.4, 1.4, 0.1);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void upperArm(boolean isRight) {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		majorPartImage, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.7, 1.55, -0.05);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.45, 1.55, -0.05);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.45, 1.1, -0.05);
	glTexCoord2f(0, 0.4); glVertex3f(-0.7, 1.1, -0.05);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.7, 1.1, -0.05);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.7, 1.1, 0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.7, 1.55, 0.25);
	glTexCoord2f(0, 0.4); glVertex3f(-0.7, 1.55, -0.05);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.7, 1.55, -0.05);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.7, 1.55, 0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.45, 1.55, 0.25);
	glTexCoord2f(0, 0.4); glVertex3f(-0.45, 1.55, -0.05);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.45, 1.55, -0.05);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.45, 1.55, 0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.45, 1.1, 0.25);
	glTexCoord2f(0, 0.4); glVertex3f(-0.45, 1.1, -0.05);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.45, 1.1, -0.05);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.7, 1.1, -0.05);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.7, 1.1, 0.25);
	glTexCoord2f(0, 0.4); glVertex3f(-0.45, 1.1, 0.25);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.45, 1.1, 0.25);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.7, 1.1, 0.25);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.7, 1.55, 0.25);
	glTexCoord2f(0, 0.4); glVertex3f(-0.45, 1.55, 0.25);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	/* For Logo Decoration */

	if (isRight) {
		/* Texture */
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
			"autobot.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
			LR_LOADFROMFILE);
		GetObject(hBMP, sizeof(BMP), &BMP);

		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
			BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

		glBegin(GL_POLYGON);
		glTexCoord2f(1, 0); glVertex3f(-0.5, 1.2, 0.26);
		glTexCoord2f(0, 0); glVertex3f(-0.65, 1.2, 0.26);
		glTexCoord2f(0, 1); glVertex3f(-0.65, 1.45, 0.26);
		glTexCoord2f(1, 1); glVertex3f(-0.5, 1.45, 0.26);
		glEnd();

		glDisable(GL_TEXTURE_2D);
		DeleteObject(hBMP);
		glDeleteTextures(1, &texture);
	}
}

void armMuscle1() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		majorPartImage, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.7, 1.1, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.46, 1.1, -0.025);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.46, 0.95, -0.025);
	glTexCoord2f(0, 0.4); glVertex3f(-0.7, 0.95, -0.025);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.7, 0.95, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.7, 0.95, 0.225);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.7, 1.1, 0.225);
	glTexCoord2f(0, 0.4); glVertex3f(-0.7, 1.1, -0.025);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.7, 1.1, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.7, 1.1, 0.225);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.46, 1.1, 0.225);
	glTexCoord2f(0, 0.4); glVertex3f(-0.46, 1.1, -0.025);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.46, 1.1, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.46, 1.1, 0.225);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.46, 0.95, 0.225);
	glTexCoord2f(0, 0.4); glVertex3f(-0.46, 0.95, -0.025);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.46, 0.95, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.7, 0.95, -0.025);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.7, 0.95, 0.225);
	glTexCoord2f(0, 0.4); glVertex3f(-0.46, 0.95, 0.225);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.46, 0.95, 0.225);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.7, 0.95, 0.225);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.7, 1.1, 0.225);
	glTexCoord2f(0, 0.4); glVertex3f(-0.46, 1.1, 0.225);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void armMuscle2() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		majorPartImage, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.7, 0.95, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.46, 0.95, -0.025);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.46, 0.8, -0.025);
	glTexCoord2f(0, 0.4); glVertex3f(-0.7, 0.8, -0.025);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.7, 0.8, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.7, 0.8, 0.225);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.7, 0.95, 0.225);
	glTexCoord2f(0, 0.4); glVertex3f(-0.7, 0.95, -0.025);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.7, 0.95, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.7, 0.95, 0.225);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.46, 0.95, 0.225);
	glTexCoord2f(0, 0.4); glVertex3f(-0.46, 0.95, -0.025);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.46, 0.95, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.46, 0.95, 0.225);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.46, 0.8, 0.225);
	glTexCoord2f(0, 0.4); glVertex3f(-0.46, 0.8, -0.025);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.46, 0.8, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.7, 0.8, -0.025);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.7, 0.8, 0.225);
	glTexCoord2f(0, 0.4); glVertex3f(-0.46, 0.8, 0.225);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.46, 0.8, 0.225);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.7, 0.8, 0.225);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.7, 0.95, 0.225);
	glTexCoord2f(0, 0.4); glVertex3f(-0.46, 0.95, 0.225);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void muscleLowerArmJoint() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		majorPartImage, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.68, 0.8, -0.01);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.47, 0.8, -0.01);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.47, 0.7, -0.01);
	glTexCoord2f(0, 0.4); glVertex3f(-0.68, 0.7, -0.01);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.68, 0.7, -0.01);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.68, 0.7, 0.21);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.68, 0.8, 0.21);
	glTexCoord2f(0, 0.4); glVertex3f(-0.68, 0.8, -0.01);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.68, 0.8, -0.01);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.68, 0.8, 0.21);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.47, 0.8, 0.21);
	glTexCoord2f(0, 0.4); glVertex3f(-0.47, 0.8, -0.01);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.47, 0.8, -0.01);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.47, 0.8, 0.21);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.47, 0.7, 0.21);
	glTexCoord2f(0, 0.4); glVertex3f(-0.47, 0.7, -0.01);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.47, 0.7, -0.01);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.68, 0.7, -0.01);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.68, 0.7, 0.21);
	glTexCoord2f(0, 0.4); glVertex3f(-0.47, 0.7, 0.21);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.47, 0.7, 0.21);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.68, 0.7, 0.21);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.68, 0.8, 0.21);
	glTexCoord2f(0, 0.4); glVertex3f(-0.47, 0.8, 0.21);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void lowerArmArmor1() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		majorPartImage, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);


	//Lower Arm Shield (Front) - 1
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.71, 0.5, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.45, 0.5, -0.025);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.45, 0.1, -0.025);
	glTexCoord2f(0, 0.4); glVertex3f(-0.71, 0.1, -0.025);
	glEnd();

	//Lower Arm Shield (Left) - 1
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.71, 0.1, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.71, 0.1, -0.01);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.71, 0.5, -0.01);
	glTexCoord2f(0, 0.4); glVertex3f(-0.71, 0.5, -0.025);
	glEnd();

	//Lower Arm Shield (Right) - 1
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.45, 0.5, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.45, 0.5, -0.01);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.45, 0.1, -0.01);
	glTexCoord2f(0, 0.4); glVertex3f(-0.45, 0.1, -0.025);
	glEnd();

	//Lower Arm Shield (Bottom) - 1
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.45, 0.1, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.71, 0.1, -0.025);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.71, 0.1, -0.01);
	glTexCoord2f(0, 0.4); glVertex3f(-0.45, 0.1, -0.01);
	glEnd();

	////////////////////////////////////////////////////////////////////////////

	//Lower Arm Shield (Front) - 2
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.71, 0.65, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.63, 0.65, -0.025);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.63, 0.1, -0.025);
	glTexCoord2f(0, 0.4); glVertex3f(-0.71, 0.1, -0.025);
	glEnd();

	//Lower Arm Shield (Left) - 2
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.71, 0.1, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.71, 0.1, -0.01);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.71, 0.7, -0.01);
	glTexCoord2f(0, 0.4); glVertex3f(-0.71, 0.65, -0.025);
	glEnd();

	//Lower Arm Shield (Top) - 2
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.71, 0.65, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.71, 0.7, -0.01);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.63, 0.7, -0.01);
	glTexCoord2f(0, 0.4); glVertex3f(-0.63, 0.65, -0.025);
	glEnd();

	//Lower Arm Shield (Right) - 2
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.63, 0.65, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.63, 0.7, -0.01);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.63, 0.1, -0.01);
	glTexCoord2f(0, 0.4); glVertex3f(-0.63, 0.1, -0.025);
	glEnd();

	//Lower Arm Shield (Bottom) - 2
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.63, 0.1, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.71, 0.1, -0.025);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.71, 0.1, -0.01);
	glTexCoord2f(0, 0.4); glVertex3f(-0.63, 0.1, -0.01);
	glEnd();

	//Lower Arm Shield (Back) - 2
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.63, 0.1, -0.01);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.71, 0.1, -0.01);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.71, 0.7, -0.01);
	glTexCoord2f(0, 0.4); glVertex3f(-0.63, 0.7, -0.01);
	glEnd();

	////////////////////////////////////////////////////////////////////////////

	//Lower Arm Shield (Front) - 3
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.53, 0.65, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.45, 0.65, -0.025);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.45, 0.1, -0.025);
	glTexCoord2f(0, 0.4); glVertex3f(-0.53, 0.1, -0.025);
	glEnd();

	//Lower Arm Shield (Left) - 3
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.53, 0.1, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.53, 0.1, -0.01);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.53, 0.7, -0.01);
	glTexCoord2f(0, 0.4); glVertex3f(-0.53, 0.65, -0.025);
	glEnd();

	//Lower Arm Shield (Top) - 3
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.53, 0.65, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.53, 0.7, -0.01);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.45, 0.7, -0.01);
	glTexCoord2f(0, 0.4); glVertex3f(-0.45, 0.65, -0.025);
	glEnd();

	//Lower Arm Shield (Right) - 3
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.45, 0.65, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.45, 0.7, -0.01);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.45, 0.1, -0.01);
	glTexCoord2f(0, 0.4); glVertex3f(-0.45, 0.1, -0.025);
	glEnd();

	//Lower Arm Shield (Bottom) - 3
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.45, 0.1, -0.025);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.53, 0.1, -0.025);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.53, 0.1, -0.01);
	glTexCoord2f(0, 0.4); glVertex3f(-0.45, 0.1, -0.01);
	glEnd();

	//Lower Arm Shield (Back) - 3
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.45, 0.1, -0.01);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.53, 0.1, -0.01);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.53, 0.7, -0.01);
	glTexCoord2f(0, 0.4); glVertex3f(-0.45, 0.7, -0.01);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
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
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		majorPartImage, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.71, 0.7, -0.01);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.45, 0.7, -0.01);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.45, 0.1, -0.01);
	glTexCoord2f(0, 0.4); glVertex3f(-0.71, 0.1, -0.01);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.71, 0.1, -0.01);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.71, 0.1, 0.225);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.71, 0.7, 0.225);
	glTexCoord2f(0, 0.4); glVertex3f(-0.71, 0.7, -0.01);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.71, 0.7, -0.01);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.71, 0.7, 0.225);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.45, 0.7, 0.225);
	glTexCoord2f(0, 0.4); glVertex3f(-0.45, 0.7, -0.01);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.45, 0.7, -0.01);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.45, 0.7, 0.225);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.45, 0.1, 0.225);
	glTexCoord2f(0, 0.4); glVertex3f(-0.45, 0.1, -0.01);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.45, 0.1, -0.01);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.71, 0.1, -0.01);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.71, 0.1, 0.225);
	glTexCoord2f(0, 0.4); glVertex3f(-0.45, 0.1, 0.225);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.45, 0.1, 0.225);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.71, 0.1, 0.225);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.71, 0.7, 0.225);
	glTexCoord2f(0, 0.4); glVertex3f(-0.45, 0.7, 0.225);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void armAntenna() {

	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"silver.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	GLUquadricObj *bottomAntenna = NULL;
	bottomAntenna = gluNewQuadric();

	glPushMatrix();
	glScalef(1, 1, 0.8);
	glTranslatef(-0.74, 1.4, 0.125);
	glRotatef(90, 1, 0, 0);
	gluQuadricDrawStyle(bottomAntenna, GLU_FILL);
	gluQuadricTexture(bottomAntenna, true);
	gluCylinder(bottomAntenna, 0.03, 0.03, 0.5, 20, 20);
	gluDeleteQuadric(bottomAntenna);
	glPopMatrix();

	GLUquadricObj *topAntenna = NULL;
	topAntenna = gluNewQuadric();

	glPushMatrix();
	glScalef(1, 1, 0.8);
	glTranslatef(-0.74, 1.75, 0.125);
	glRotatef(90, 1, 0, 0);
	gluQuadricDrawStyle(topAntenna, GL_FILL);
	gluQuadricTexture(topAntenna, true);
	gluCylinder(topAntenna, 0.02, 0.02, 0.4, 20, 20);
	gluDeleteQuadric(topAntenna);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void thumbFingers() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"blue.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glPushMatrix();
	glRotatef(thumbLowerFingerDegree, 1, 0, 0);

	/* Lower Thumb Section */
	//Thumb Finger - Front 
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.58, 0.05, -0.0425);
	glTexCoord2f(0.2, 1); glVertex3f(-0.53, 0.05, -0.0425);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.53, -0.05, -0.0425);
	glTexCoord2f(0, 0.3); glVertex3f(-0.58, -0.05, -0.0425);
	glEnd();

	//Thumb Finger - Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.58, -0.05, -0.0425);
	glTexCoord2f(0.2, 1); glVertex3f(-0.58, -0.05, 0.0075);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.58, 0.05, 0.0075);
	glTexCoord2f(0, 0.3); glVertex3f(-0.58, 0.05, -0.0425);
	glEnd();

	//Thumb Finger - Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.58, 0.05, -0.0425);
	glTexCoord2f(0.2, 1); glVertex3f(-0.58, 0.05, 0.0075);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.53, 0.05, 0.0075);
	glTexCoord2f(0, 0.3); glVertex3f(-0.53, 0.05, -0.0425);
	glEnd();

	//Thumb Finger - Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.53, 0.05, -0.0425);
	glTexCoord2f(0.2, 1); glVertex3f(-0.53, 0.05, 0.0075);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.53, -0.05, 0.0075);
	glTexCoord2f(0, 0.3); glVertex3f(-0.53, -0.05, -0.0425);
	glEnd();

	//Thumb Finger - Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.53, -0.05, -0.0425);
	glTexCoord2f(0.2, 1); glVertex3f(-0.58, -0.05, -0.0425);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.58, -0.05, 0.0075);
	glTexCoord2f(0, 0.3); glVertex3f(-0.53, -0.05, 0.0075);
	glEnd();

	//Thumb Finger - Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.53, -0.05, 0.0075);
	glTexCoord2f(0.2, 1); glVertex3f(-0.58, -0.05, 0.0075);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.58, 0.05, 0.0075);
	glTexCoord2f(0, 0.3); glVertex3f(-0.53, 0.05, 0.0075);
	glEnd();


	////////////////////////////////////////////////////////////////

	/* Upper Thumb Section */

	glPushMatrix();
	glRotatef(thumbUpperFingerDegree, 1, 0, 0);

	//Thumb Finger - Front 
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.58, -0.05, -0.0425);
	glTexCoord2f(0.2, 1); glVertex3f(-0.53, -0.05, -0.0425);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.53, -0.1, -0.0425);
	glTexCoord2f(0, 0.3); glVertex3f(-0.58, -0.1, -0.0425);
	glEnd();

	//Thumb Finger - Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.58, -0.1, -0.0425);
	glTexCoord2f(0.2, 1); glVertex3f(-0.58, -0.1, 0.0075);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.58, -0.05, 0.0075);
	glTexCoord2f(0, 0.3); glVertex3f(-0.58, -0.05, -0.0425);
	glEnd();

	//Thumb Finger - Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.58, -0.05, -0.0425);
	glTexCoord2f(0.2, 1); glVertex3f(-0.58, -0.05, 0.0075);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.53, -0.05, 0.0075);
	glTexCoord2f(0, 0.3); glVertex3f(-0.53, -0.05, -0.0425);
	glEnd();

	//Thumb Finger - Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.53, -0.05, -0.0425);
	glTexCoord2f(0.2, 1); glVertex3f(-0.53, -0.05, 0.0075);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.53, -0.1, 0.0075);
	glTexCoord2f(0, 0.3); glVertex3f(-0.53, -0.1, -0.0425);
	glEnd();

	//Thumb Finger - Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.53, -0.1, -0.0425);
	glTexCoord2f(0.2, 1); glVertex3f(-0.58, -0.1, -0.0425);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.58, -0.1, 0.0075);
	glTexCoord2f(0, 0.3); glVertex3f(-0.53, -0.1, 0.0075);
	glEnd();

	//Thumb Finger - Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.53, -0.1, 0.0075);
	glTexCoord2f(0.2, 1); glVertex3f(-0.58, -0.1, 0.0075);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.58, -0.05, 0.0075);
	glTexCoord2f(0, 0.3); glVertex3f(-0.53, -0.05, 0.0075);
	glEnd();
	glPopMatrix();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void otherFingers(int leftRight) {

	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"blue.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	if (leftRight == 1) {
		/* Lower Part */
		//Front
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.65, -0.05, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.6, -0.05, 0.0075);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.6, -0.16, 0.0075);
		glTexCoord2f(0, 0.3); glVertex3f(-0.65, -0.16, 0.0075);
		glEnd();

		//Left
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.65, -0.16, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.16, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.65, -0.05, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.65, -0.05, 0.0075);
		glEnd();

		//Top
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.65, -0.05, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.05, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.6, -0.05, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.05, 0.0075);
		glEnd();

		//Right
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.6, -0.05, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.6, -0.05, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.6, -0.16, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.16, 0.0075);
		glEnd();

		//Bottom
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.6, -0.16, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.16, 0.0075);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.65, -0.16, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.16, 0.0575);
		glEnd();

		//Back
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.6, -0.16, 0.0575);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.16, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.65, -0.05, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.05, 0.0575);
		glEnd();

		////////////////////////////////////////////////////////////////////

		/* Middle Part */
		glPushMatrix();
		glTranslatef(-0.6, -0.16, 0.0075);
		glRotatef((rightMiddleFingerDegree * -1.0), 0, 0, 1);
		glTranslatef(0.6, 0.16, -0.0075);

		//Front
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.65, -0.16, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.6, -0.16, 0.0075);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.6, -0.24, 0.0075);
		glTexCoord2f(0, 0.3); glVertex3f(-0.65, -0.24, 0.0075);
		glEnd();

		//Left
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.65, -0.24, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.24, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.65, -0.16, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.65, -0.16, 0.0075);
		glEnd();

		//Top
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.65, -0.16, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.16, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.6, -0.16, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.16, 0.0075);
		glEnd();

		//Right
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.6, -0.16, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.6, -0.16, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.6, -0.24, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.24, 0.0075);
		glEnd();

		//Bottom
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.6, -0.24, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.24, 0.0075);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.65, -0.24, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.24, 0.0575);
		glEnd();

		//Back
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.6, -0.24, 0.0575);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.24, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.65, -0.16, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.16, 0.0575);
		glEnd();


		////////////////////////////////////////////////////////////////////

		/* Upper Part */
		glPushMatrix();
		glTranslatef(-0.6, -0.24, 0.0075);
		glRotatef((rightUpperFingerDegree * -1.0), 0, 0, 1);
		glTranslatef(0.6, 0.24, -0.0075);

		//Front
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.65, -0.24, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.6, -0.24, 0.0075);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.6, -0.3, 0.0075);
		glTexCoord2f(0, 0.3); glVertex3f(-0.65, -0.3, 0.0075);
		glEnd();

		//Left
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.65, -0.3, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.3, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.65, -0.24, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.65, -0.24, 0.0075);
		glEnd();

		//Top
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.65, -0.24, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.24, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.6, -0.24, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.24, 0.0075);
		glEnd();

		//Right
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.6, -0.24, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.6, -0.24, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.6, -0.3, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.3, 0.0075);
		glEnd();

		//Bottom
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.6, -0.3, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.3, 0.0075);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.65, -0.3, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.3, 0.0575);
		glEnd();

		//Back
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.6, -0.3, 0.0575);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.3, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.65, -0.24, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.24, 0.0575);
		glEnd();
		glPopMatrix();

		glPopMatrix();
	}
	else if (leftRight == 2) {
		/* Lower Part */
		//Front
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.65, -0.05, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.6, -0.05, 0.0075);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.6, -0.16, 0.0075);
		glTexCoord2f(0, 0.3); glVertex3f(-0.65, -0.16, 0.0075);
		glEnd();

		//Left
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.65, -0.16, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.16, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.65, -0.05, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.65, -0.05, 0.0075);
		glEnd();

		//Top
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.65, -0.05, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.05, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.6, -0.05, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.05, 0.0075);
		glEnd();

		//Right
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.6, -0.05, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.6, -0.05, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.6, -0.16, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.16, 0.0075);
		glEnd();

		//Bottom
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.6, -0.16, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.16, 0.0075);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.65, -0.16, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.16, 0.0575);
		glEnd();

		//Back
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.6, -0.16, 0.0575);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.16, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.65, -0.05, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.05, 0.0575);
		glEnd();

		////////////////////////////////////////////////////////////////////

		/* Middle Part */
		glPushMatrix();
		glTranslatef(-0.65, -0.16, 0.0075);
		glRotatef((leftMiddleFingerDegree * 1.0), 0, 0, 1);
		glTranslatef(0.65, 0.16, -0.0075);

		//Front
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.65, -0.16, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.6, -0.16, 0.0075);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.6, -0.24, 0.0075);
		glTexCoord2f(0, 0.3); glVertex3f(-0.65, -0.24, 0.0075);
		glEnd();

		//Left
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.65, -0.24, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.24, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.65, -0.16, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.65, -0.16, 0.0075);
		glEnd();

		//Top
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.65, -0.16, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.16, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.6, -0.16, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.16, 0.0075);
		glEnd();

		//Right
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.6, -0.16, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.6, -0.16, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.6, -0.24, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.24, 0.0075);
		glEnd();

		//Bottom
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.6, -0.24, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.24, 0.0075);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.65, -0.24, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.24, 0.0575);
		glEnd();

		//Back
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.6, -0.24, 0.0575);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.24, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.65, -0.16, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.16, 0.0575);
		glEnd();


		////////////////////////////////////////////////////////////////////

		/* Upper Part */
		glPushMatrix();
		glTranslatef(-0.65, -0.24, 0.0075);
		glRotatef((leftUpperFingerDegree * 1.0), 0, 0, 1);
		glTranslatef(0.65, 0.24, -0.0075);

		//Front
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.65, -0.24, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.6, -0.24, 0.0075);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.6, -0.3, 0.0075);
		glTexCoord2f(0, 0.3); glVertex3f(-0.65, -0.3, 0.0075);
		glEnd();

		//Left
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.65, -0.3, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.3, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.65, -0.24, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.65, -0.24, 0.0075);
		glEnd();

		//Top
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.65, -0.24, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.24, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.6, -0.24, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.24, 0.0075);
		glEnd();

		//Right
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.6, -0.24, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.6, -0.24, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.6, -0.3, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.3, 0.0075);
		glEnd();

		//Bottom
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.6, -0.3, 0.0075);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.3, 0.0075);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.65, -0.3, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.3, 0.0575);
		glEnd();

		//Back
		glBegin(GL_POLYGON);
		glTexCoord2f(0, 1); glVertex3f(-0.6, -0.3, 0.0575);
		glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.3, 0.0575);
		glTexCoord2f(0.2, 0.3); glVertex3f(-0.65, -0.24, 0.0575);
		glTexCoord2f(0, 0.3); glVertex3f(-0.6, -0.24, 0.0575);
		glEnd();
		glPopMatrix();

		glPopMatrix();
	}
	
	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void hand(int leftRight) {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"blue.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.65, 0.1, 0.0075);
	glTexCoord2f(0.2, 1); glVertex3f(-0.53, 0.1, 0.0075);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.53, -0.05, 0.0075);
	glTexCoord2f(0, 0.3); glVertex3f(-0.65, -0.05, 0.0075);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.65, -0.05, 0.0075);
	glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.05, 0.2075);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.65, 0.1, 0.2075);
	glTexCoord2f(0, 0.3); glVertex3f(-0.65, 0.1, 0.0075);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.65, 0.1, 0.0075);
	glTexCoord2f(0.2, 1); glVertex3f(-0.65, 0.1, 0.2075);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.53, 0.1, 0.2075);
	glTexCoord2f(0, 0.3); glVertex3f(-0.53, 0.1, 0.0075);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.53, 0.1, 0.0075);
	glTexCoord2f(0.2, 1); glVertex3f(-0.53, 0.1, 0.2075);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.53, -0.05, 0.2075);
	glTexCoord2f(0, 0.3); glVertex3f(-0.53, -0.05, 0.0075);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.53, -0.05, 0.0075);
	glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.05, 0.0075);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.65, -0.05, 0.2075);
	glTexCoord2f(0, 0.3); glVertex3f(-0.53, -0.05, 0.2075);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.53, -0.05, 0.2075);
	glTexCoord2f(0.2, 1); glVertex3f(-0.65, -0.05, 0.2075);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.65, 0.1, 0.2075);
	glTexCoord2f(0, 0.3); glVertex3f(-0.53, 0.1, 0.2075);
	glEnd();


	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	/* FINGERS */
	if (leftRight == 1) {
		/* Right Hand */
		//Thumb Finger
		glPushMatrix();
		glTranslatef(-0.07, 0, 0);
		thumbFingers();
		glPopMatrix();

		//Index Finger
		glPushMatrix();
		glTranslatef(0.07, 0, 0);
		otherFingers(1);
		glPopMatrix();

		//Middle Finger
		glPushMatrix();
		glTranslatef(0.07, 0, 0.05);
		otherFingers(1);
		glPopMatrix();

		//Ring Finger
		glPushMatrix();
		glTranslatef(0.07, 0, 0.1);
		otherFingers(1);
		glPopMatrix();

		//Little Finger/ Pinky
		glPushMatrix();
		glTranslatef(0.07, 0, 0.15);
		otherFingers(1);
		glPopMatrix();
	}
	else {
		/* Left Hand */
		//Thumb Finger
		thumbFingers();

		//Index Finger
		glPushMatrix();
		glTranslatef(0, 0, 0);
		otherFingers(2);
		glPopMatrix();

		//Middle Finger
		glPushMatrix();
		glTranslatef(0, 0, 0.05);
		otherFingers(2);
		glPopMatrix();

		//Ring Finger
		glPushMatrix();
		glTranslatef(0, 0, 0.1);
		otherFingers(2);
		glPopMatrix();

		//Little Finger/ Pinky
		glPushMatrix();
		glTranslatef(0, 0, 0.15);
		otherFingers(2);
		glPopMatrix();
	}


}

void backArmor1() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"blue.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.2, 0.4, 0.4);
	glTexCoord2f(0.2, 1); glVertex3f(0.2, 0.4, 0.4);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.15, 0.25, 0.35);
	glTexCoord2f(0, 0.3); glVertex3f(-0.15, 0.25, 0.35);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.15, 0.25, 0.35);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, 0.25, 0.3);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.2, 0.4, 0.3);
	glTexCoord2f(0, 0.3); glVertex3f(-0.2, 0.4, 0.4);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.2, 0.4, 0.4);
	glTexCoord2f(0.2, 1); glVertex3f(-0.2, 0.4, 0.3);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.2, 0.4, 0.3);
	glTexCoord2f(0, 0.3); glVertex3f(0.2, 0.4, 0.4);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.2, 0.4, 0.4);
	glTexCoord2f(0.2, 1); glVertex3f(0.2, 0.4, 0.3);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.15, 0.25, 0.3);
	glTexCoord2f(0, 0.3); glVertex3f(0.15, 0.25, 0.35);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.15, 0.25, 0.35);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, 0.25, 0.35);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.15, 0.25, 0.3);
	glTexCoord2f(0, 0.3); glVertex3f(0.15, 0.25, 0.3);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.15, 0.25, 0.3);
	glTexCoord2f(0.2, 1); glVertex3f(-0.15, 0.25, 0.3);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.2, 0.4, 0.3);
	glTexCoord2f(0, 0.3); glVertex3f(0.2, 0.4, 0.3);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void backArmor2SmallTrapezium() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		majorPartImage, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.132, 0.59, 0.41);
	glTexCoord2f(0.2, 0.6); glVertex3f(0.122, 0.63, 0.41);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.1, 0.65, 0.41);
	glTexCoord2f(0, 0.4); glVertex3f(0.12, 0.55, 0.41);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.122, 0.63, 0.41);
	glTexCoord2f(0.2, 0.6); glVertex3f(0.122, 0.63, 0.4);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.132, 0.59, 0.4);
	glTexCoord2f(0, 0.4); glVertex3f(0.132, 0.59, 0.41);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.122, 0.63, 0.41);
	glTexCoord2f(0.2, 0.6); glVertex3f(0.122, 0.63, 0.4);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.1, 0.65, 0.4);
	glTexCoord2f(0, 0.4); glVertex3f(0.1, 0.65, 0.41);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.1, 0.65, 0.41);
	glTexCoord2f(0.2, 0.6); glVertex3f(0.1, 0.65, 0.4);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.12, 0.55, 0.4);
	glTexCoord2f(0, 0.4); glVertex3f(0.12, 0.55, 0.41);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.132, 0.59, 0.41);
	glTexCoord2f(0.2, 0.6); glVertex3f(0.132, 0.59, 0.4);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.12, 0.55, 0.4);
	glTexCoord2f(0, 0.4); glVertex3f(0.12, 0.55, 0.41);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.132, 0.59, 0.4);
	glTexCoord2f(0.2, 0.6); glVertex3f(0.122, 0.63, 0.4);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.1, 0.65, 0.4);
	glTexCoord2f(0, 0.4); glVertex3f(0.12, 0.55, 0.4);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void backArmor2Details() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		majorPartImage, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Trapezium - Front
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.06, 0.7, 0.41);
	glTexCoord2f(0.2, 0.6); glVertex3f(0.06, 0.7, 0.41);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.10, 0.4, 0.41);
	glTexCoord2f(0, 0.4); glVertex3f(-0.10, 0.4, 0.41);
	glEnd();

	//Trapezium - Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.1, 0.4, 0.41);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.1, 0.4, 0.4);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.06, 0.7, 0.4);
	glTexCoord2f(0, 0.4); glVertex3f(-0.06, 0.7, 0.41);
	glEnd();

	//Trapezium - Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(-0.06, 0.7, 0.41);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.06, 0.7, 0.4);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.06, 0.7, 0.4);
	glTexCoord2f(0, 0.4); glVertex3f(0.06, 0.7, 0.41);
	glEnd();

	//Trapezium - Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.06, 0.7, 0.41);
	glTexCoord2f(0.2, 0.6); glVertex3f(0.06, 0.7, 0.4);
	glTexCoord2f(0.2, 0.4); glVertex3f(0.1, 0.4, 0.4);
	glTexCoord2f(0, 0.4); glVertex3f(0.1, 0.4, 0.41);
	glEnd();

	//Trapezium - Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.1, 0.4, 0.41);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.1, 0.4, 0.41);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.1, 0.4, 0.4);
	glTexCoord2f(0, 0.4); glVertex3f(0.1, 0.4, 0.4);
	glEnd();

	//Trapezium - Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0.6); glVertex3f(0.1, 0.4, 0.4);
	glTexCoord2f(0.2, 0.6); glVertex3f(-0.1, 0.4, 0.4);
	glTexCoord2f(0.2, 0.4); glVertex3f(-0.06, 0.7, 0.4);
	glTexCoord2f(0, 0.4); glVertex3f(0.06, 0.7, 0.4);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

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
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"blue.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front 
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.25, 1.0, 0.4);
	glTexCoord2f(0.2, 1); glVertex3f(0.25, 1.0, 0.4);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.2, 0.4, 0.4);
	glTexCoord2f(0, 0.3); glVertex3f(-0.2, 0.4, 0.4);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.2, 0.4, 0.4);
	glTexCoord2f(1, 1); glVertex3f(-0.2, 0.4, 0.3);
	glTexCoord2f(1, 0.8); glVertex3f(-0.225, 0.8, 0.3);
	glTexCoord2f(1, 0); glVertex3f(-0.25, 1.0, 0.35);
	glTexCoord2f(0, 0); glVertex3f(-0.25, 1.0, 0.4);
	glEnd();

	//Top - 1
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.25, 1.0, 0.4);
	glTexCoord2f(0.2, 1); glVertex3f(-0.25, 1.0, 0.35);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.25, 1.0, 0.35);
	glTexCoord2f(0, 0.3); glVertex3f(0.25, 1.0, 0.4);
	glEnd();

	//Top - 2
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.25, 1.0, 0.35);
	glTexCoord2f(0.2, 1); glVertex3f(-0.25, 1.0, 0.35);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.225, 0.8, 0.3);
	glTexCoord2f(0, 0.3); glVertex3f(0.225, 0.8, 0.3);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.25, 1.0, 0.4);
	glTexCoord2f(1, 1); glVertex3f(0.25, 1.0, 0.35);
	glTexCoord2f(1, 0.8); glVertex3f(0.225, 0.8, 0.3);
	glTexCoord2f(1, 0); glVertex3f(0.2, 0.4, 0.3);
	glTexCoord2f(0, 0); glVertex3f(0.2, 0.4, 0.4);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.2, 0.4, 0.4);
	glTexCoord2f(0.2, 1); glVertex3f(-0.2, 0.4, 0.4);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.2, 0.4, 0.3);
	glTexCoord2f(0, 0.3); glVertex3f(0.2, 0.4, 0.3);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.2, 0.4, 0.3);
	glTexCoord2f(0.2, 1); glVertex3f(-0.2, 0.4, 0.3);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.225, 0.8, 0.3);
	glTexCoord2f(0, 0.3); glVertex3f(0.225, 0.8, 0.3);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	backArmor2Details();
}

void backArmor3() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"blue.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front 
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.25, 1.5, 0.4);
	glTexCoord2f(0.2, 1); glVertex3f(0.25, 1.5, 0.4);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.25, 1.0, 0.4);
	glTexCoord2f(0, 0.3); glVertex3f(-0.25, 1.0, 0.4);
	glEnd();

	//Left 
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.25, 1.0, 0.4);
	glTexCoord2f(0.2, 1); glVertex3f(-0.25, 1.0, 0.35);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.25, 1.5, 0.35);
	glTexCoord2f(0, 0.3); glVertex3f(-0.25, 1.5, 0.4);
	glEnd();

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.25, 1.5, 0.4);
	glTexCoord2f(0.2, 1); glVertex3f(-0.25, 1.5, 0.35);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.25, 1.5, 0.35);
	glTexCoord2f(0, 0.3); glVertex3f(0.25, 1.5, 0.4);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.25, 1.5, 0.4);
	glTexCoord2f(0.2, 1); glVertex3f(0.25, 1.5, 0.35);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.25, 1.0, 0.35);
	glTexCoord2f(0, 0.3); glVertex3f(0.25, 1.0, 0.4);
	glEnd();

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.25, 1.0, 0.4);
	glTexCoord2f(0.2, 1); glVertex3f(-0.25, 1.0, 0.4);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.25, 1.0, 0.35);
	glTexCoord2f(0, 0.3); glVertex3f(0.25, 1.0, 0.35);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.25, 1.0, 0.35);
	glTexCoord2f(0.2, 1); glVertex3f(-0.25, 1.0, 0.35);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.25, 1.5, 0.35);
	glTexCoord2f(0, 0.3); glVertex3f(0.25, 1.5, 0.35);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void backArmor4() {
	/* Texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"blue.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	/* RIGHT PART */
	//Inner based on Z
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.25, 1.55, 0.45);
	glTexCoord2f(0.2, 1); glVertex3f(-0.25, 1.55, 0.35);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.25, 1.0, 0.35);
	glTexCoord2f(0, 0.3); glVertex3f(-0.25, 1.0, 0.45);
	glEnd();

	//Inner based on X
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.35, 1.55, 0.35);
	glTexCoord2f(0.2, 1); glVertex3f(-0.25, 1.55, 0.35);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.25, 1.0, 0.35);
	glTexCoord2f(0, 0.3); glVertex3f(-0.35, 1.0, 0.35);
	glEnd();

	//Outer
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(-0.25, 1.55, 0.45);
	glTexCoord2f(0.2, 1); glVertex3f(-0.35, 1.55, 0.35);
	glTexCoord2f(0.2, 0.3); glVertex3f(-0.35, 1.0, 0.35);
	glTexCoord2f(0, 0.3); glVertex3f(-0.25, 1.0, 0.45);
	glEnd();



	//////////////////////////////////////////////////////////////

	/* LEFT PART */
	//Inner based on Z
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.25, 1.55, 0.45);
	glTexCoord2f(0.2, 1); glVertex3f(0.25, 1.55, 0.35);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.25, 1.0, 0.35);
	glTexCoord2f(0, 0.3); glVertex3f(0.25, 1.0, 0.45);
	glEnd();

	//Inner based on X
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.35, 1.55, 0.35);
	glTexCoord2f(0.2, 1); glVertex3f(0.25, 1.55, 0.35);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.25, 1.0, 0.35);
	glTexCoord2f(0, 0.3); glVertex3f(0.35, 1.0, 0.35);
	glEnd();

	//Outer
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(0.25, 1.55, 0.45);
	glTexCoord2f(0.2, 1); glVertex3f(0.35, 1.55, 0.35);
	glTexCoord2f(0.2, 0.3); glVertex3f(0.35, 1.0, 0.35);
	glTexCoord2f(0, 0.3); glVertex3f(0.25, 1.0, 0.45);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	////////////////////////////////////////////////////////////////////

	//Left - Upper Triangle
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, 1.55, 0.45);
	glVertex3f(-0.25, 1.55, 0.35);
	glVertex3f(-0.35, 1.55, 0.35);
	glEnd();

	//Left - Below Triangle
	glBegin(GL_POLYGON);
	glVertex3f(-0.25, 1.0, 0.45);
	glVertex3f(-0.25, 1.0, 0.35);
	glVertex3f(-0.35, 1.0, 0.35);
	glEnd();

	//Right - Upper Triangle
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 1.55, 0.45);
	glVertex3f(0.25, 1.55, 0.35);
	glVertex3f(0.35, 1.55, 0.35);
	glEnd();

	//Right - Below Triangle
	glBegin(GL_POLYGON);
	glVertex3f(0.25, 1.0, 0.45);
	glVertex3f(0.25, 1.0, 0.35);
	glVertex3f(0.35, 1.0, 0.35);
	glEnd();
}

void gun()
{

	GLUquadricObj* guncylinder = NULL;
	//gun part 1 shoot-part
	if (trigger == true)
	{
		glEnable(GL_LIGHTING);

		glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
		glLightfv(GL_LIGHT1, GL_POSITION, pos);

		glEnable(GL_LIGHT1);
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "metal.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);



	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	glPushMatrix();
	glTranslatef(0.95, 1, 0);
	glRotatef(90, 0, 1, 0);
	guncylinder = gluNewQuadric();
	gluQuadricDrawStyle(guncylinder, GLU_FILL);
	gluQuadricTexture(guncylinder, true);
	gluCylinder(guncylinder, 0.05, 0.1, 0.05, 30, 30);
	gluDeleteQuadric(guncylinder);
	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
	glPopMatrix();
	if (trigger == true)
	{
		glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHTING);
	}
	//gunpart 1 
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "metal1.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);



	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	glPushMatrix();
	glTranslatef(1, 1, 0);
	glRotatef(90, 0, 1, 0);

	guncylinder = gluNewQuadric();
	gluQuadricDrawStyle(guncylinder, GLU_FILL);
	gluQuadricTexture(guncylinder, true);
	gluCylinder(guncylinder, 0.1, 0.1, 0.3, 30, 30);

	gluDeleteQuadric(guncylinder);
	glPopMatrix();
	//gun part 2 

	glPushMatrix();
	glTranslatef(1.4, 1, 0);
	glRotatef(90, 0, 1, 0);
	guncylinder = gluNewQuadric();
	gluQuadricDrawStyle(guncylinder, GLU_FILL);
	gluQuadricTexture(guncylinder, true);
	gluCylinder(guncylinder, 0.1, 0.1, 0.3, 30, 30);

	gluDeleteQuadric(guncylinder);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
	//gun part 2 upper
	glColor3f(0.59, 0.04, 0.04);
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
	glColor3f(1.0, 1.0, 1.0);
	//===============
	//gun handle part 2
	glColor3f(1.0, 0.25, 0.1);
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
	glColor3f(1.0, 1.0, 1.0);
	//angled grip
	glColor3f(1.0, 0.0, 0.0);
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
	glColor3f(1.0, 1.0, 1.0);
	//=====================================		

	//gunpart2 connector
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "metal.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);



	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	glPushMatrix();
	glTranslatef(1.3, 1, 0);
	glRotatef(90, 0, 1, 0);
	guncylinder = gluNewQuadric();
	gluQuadricDrawStyle(guncylinder, GLU_FILL);
	gluQuadricTexture(guncylinder, true);
	gluCylinder(guncylinder, 0.1, 0.05, 0.05, 30, 30);
	gluDeleteQuadric(guncylinder);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.35, 1, 0);
	glRotatef(90, 0, 1, 0);
	guncylinder = gluNewQuadric();
	gluQuadricDrawStyle(guncylinder, GLU_FILL);
	gluQuadricTexture(guncylinder, true);
	gluCylinder(guncylinder, 0.05, 0.1, 0.05, 30, 30);
	gluDeleteQuadric(guncylinder);
	glPopMatrix();

	//gunpart 3 connector

	glPushMatrix();
	glTranslatef(1.7, 1, 0);
	glRotatef(90, 0, 1, 0);
	guncylinder = gluNewQuadric();
	gluQuadricDrawStyle(guncylinder, GLU_LINE);
	gluQuadricTexture(guncylinder, true);

	gluCylinder(guncylinder, 0.1, 0.05, 0.05, 30, 30);
	gluDeleteQuadric(guncylinder);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.75, 1, 0);
	glRotatef(90, 0, 1, 0);
	guncylinder = gluNewQuadric();
	gluQuadricDrawStyle(guncylinder, GLU_LINE);
	gluQuadricTexture(guncylinder, true);
	gluCylinder(guncylinder, 0.05, 0.2, 0.05, 30, 30);
	gluDeleteQuadric(guncylinder);
	glPopMatrix();
	//gun part 4 connector
	glPushMatrix();
	glTranslatef(2.08, 1, 0);
	glRotatef(90, 0, 1, 0);
	guncylinder = gluNewQuadric();
	gluQuadricDrawStyle(guncylinder, GLU_LINE);
	gluQuadricTexture(guncylinder, true);

	gluCylinder(guncylinder, 0.2, 0.25, 0.02, 30, 30);
	gluDeleteQuadric(guncylinder);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.75, 1, 0);
	glRotatef(90, 0, 1, 0);
	guncylinder = gluNewQuadric();
	gluQuadricDrawStyle(guncylinder, GLU_LINE);
	gluQuadricTexture(guncylinder, true);
	gluCylinder(guncylinder, 0.05, 0.2, 0.05, 30, 30);
	gluDeleteQuadric(guncylinder);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
	//gunpart 3


	glPushMatrix();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "gunskin.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);



	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	glTranslatef(1.8, 1, 0);
	glRotatef(90, 0, 1, 0);
	guncylinder = gluNewQuadric();
	gluQuadricDrawStyle(guncylinder, GLU_FILL);
	gluQuadricTexture(guncylinder, true);
	gluCylinder(guncylinder, 0.2, 0.2, 0.3, 30, 30);

	gluDeleteQuadric(guncylinder);
	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
	glPopMatrix();


	//handle part 3 
	glColor3f(0.51, 0.54, 0.59);
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




	glColor3f(0.0, 0.00, 0.0);
	;	glBegin(GL_POLYGON);
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
	glColor3f(1.0, 1.0, 1.0);
	//==========================================================

		//gun part 4 
	glPushMatrix();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "gunskin.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);



	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	glTranslatef(2.1, 1, 0);
	glRotatef(90, 0, 1, 0);
	guncylinder = gluNewQuadric();
	gluQuadricDrawStyle(guncylinder, GLU_FILL);
	gluQuadricTexture(guncylinder, true);
	gluCylinder(guncylinder, 0.25, 0.25, 0.2, 30, 30);
	gluDeleteQuadric(guncylinder);
	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
	glPopMatrix();

	//handle part4 
	glColor3f(0.51, 0.54, 0.59);
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

	glColor3f(0.0, 0.0, 0.0);
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
	glColor3f(1.0, 1.0, 1.0);
	//gun tail
//==========================================
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
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "guntail.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);



	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);





	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0); glVertex3f(2.3, 0.75, 0.25);
	glTexCoord2d(1, 0); glVertex3f(2.5, 0.75, 0.25);
	glTexCoord2d(1, 1); glVertex3f(2.5, 1.3, 0.25);
	glTexCoord2d(0, 1); glVertex3f(2.3, 1.4, 0.25);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 0); glVertex3f(2.5, 0.75, -0.25);
	glTexCoord2d(0, 1); glVertex3f(2.5, 0.75, 0.25);
	glTexCoord2d(1, 1); glVertex3f(2.5, 1.30, 0.25);
	glTexCoord2d(1, 0); glVertex3f(2.5, 1.30, -0.25);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 0); glVertex3f(2.3, 1.4, -0.25);
	glTexCoord2d(1, 1); glVertex3f(2.3, 1.4, 0.25);
	glTexCoord2d(0, 1); glVertex3f(2.5, 1.30, 0.25);
	glTexCoord2d(0, 0); glVertex3f(2.5, 1.30, -0.25);
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
	glTexCoord2d(0, 0); glVertex3f(2.3, 0.75, -0.25);
	glTexCoord2d(1, 0); glVertex3f(2.3, 1.4, -0.25);
	glTexCoord2d(1, 1); glVertex3f(2.3, 1.4, 0.25);
	glTexCoord2d(0, 1); glVertex3f(2.3, 0.75, 0.25);

	glEnd();


	glBegin(GL_POLYGON);
	glTexCoord2d(0, 1); glVertex3f(2.3, 0.75, 0.25);
	glTexCoord2d(1, 1); glVertex3f(2.5, 0.75, 0.25);
	glTexCoord2d(1, 0); glVertex3f(2.5, 0.75, -0.25);
	glTexCoord2d(0, 0); glVertex3f(2.3, 0.75, -0.25);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);


	//=========================================================


}

void blade()
{
	if (bladelocation < 0.2)
		glColor3f(0.8, 0.0, 0.0);
	//RT1
	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.51, 1.0, 0.02);
	glTexCoord2d(0, 0); glVertex3f(-1.43, 0.9, 0.02);
	glTexCoord2d(1, 0); glVertex3f(-1.51, 0.9, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.51, 1.0, 0.03);
	glTexCoord2d(0, 0); glVertex3f(-1.43, 0.9, 0.03);
	glTexCoord2d(1, 0); glVertex3f(-1.51, 1.0, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.51, 1.0, 0.03);
	glTexCoord2d(1, 0); glVertex3f(-1.51, 1.0, 0.02);
	glTexCoord2d(0, 0); glVertex3f(-1.51, 0.9, 0.02);
	glTexCoord2d(0, 1); glVertex3f(-1.51, 0.9, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.51, 1.0, 0.03);
	glTexCoord2d(1, 0); glVertex3f(-1.51, 1.0, 0.02);
	glTexCoord2d(0, 0); glVertex3f(-1.43, 0.9, 0.02);
	glTexCoord2d(0, 1); glVertex3f(-1.43, 0.9, 0.03);
	glEnd();



	//RC1
	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.51, 0.9, 0.02);
	glTexCoord2d(0, 1); glVertex3f(-1.43, 0.9, 0.02);
	glTexCoord2d(0, 0); glVertex3f(-1.43, 0.4, 0.02);
	glTexCoord2d(1, 0); glVertex3f(-1.51, 0.4, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.51, 0.9, 0.03);
	glTexCoord2d(0, 1); glVertex3f(-1.43, 0.9, 0.03);
	glTexCoord2d(0, 0); glVertex3f(-1.43, 0.4, 0.03);
	glTexCoord2d(1, 0); glVertex3f(-1.51, 0.4, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.51, 0.9, 0.03);
	glTexCoord2d(0, 1); glVertex3f(-1.51, 0.4, 0.03);
	glTexCoord2d(0, 0); glVertex3f(-1.51, 0.4, 0.02);
	glTexCoord2d(1, 0); glVertex3f(-1.51, 0.9, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.43, 0.9, 0.03);
	glTexCoord2d(0, 1); glVertex3f(-1.43, 0.4, 0.03);
	glTexCoord2d(0, 0); glVertex3f(-1.43, 0.4, 0.02);
	glTexCoord2d(1, 0); glVertex3f(-1.43, 0.9, 0.02);
	glEnd();



	//RT2
	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.51, 0.45, 0.02);
	glTexCoord2d(1, 0); glVertex3f(-1.51, 0.4, 0.02);
	glTexCoord2d(0, 0); glVertex3f(-1.59, 0.4, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.51, 0.45, 0.03);
	glTexCoord2d(1, 0); glVertex3f(-1.51, 0.4, 0.03);
	glTexCoord2d(0, 0); glVertex3f(-1.59, 0.4, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 0); glVertex3f(-1.51, 0.45, 0.02);
	glTexCoord2d(0, 0); glVertex3f(-1.51, 0.4, 0.02);
	glTexCoord2d(0, 1); glVertex3f(-1.51, 0.4, 0.03);
	glTexCoord2d(1, 1); glVertex3f(-1.51, 0.45, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.51, 0.4, 0.03);
	glTexCoord2d(1, 0); glVertex3f(-1.51, 0.4, 0.02);
	glTexCoord2d(0, 0); glVertex3f(-1.59, 0.4, 0.02);
	glTexCoord2d(0, 1); glVertex3f(-1.59, 0.4, 0.03);
	glEnd();

	//RT3
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 1); glVertex3f(-1.43, 0.4, 0.02);
	glTexCoord2d(1, 1); glVertex3f(-1.51, 0.4, 0.02);
	glTexCoord2d(1, 0); glVertex3f(-1.51, 0.36, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.43, 0.4, 0.03);
	glTexCoord2d(0, 1); glVertex3f(-1.51, 0.4, 0.03);
	glTexCoord2d(0, 0); glVertex3f(-1.51, 0.36, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.51, 0.4, 0.03);
	glTexCoord2d(0, 1); glVertex3f(-1.51, 0.36, 0.03);
	glTexCoord2d(0, 1); glVertex3f(-1.51, 0.36, 0.02);
	glTexCoord2d(1, 1); glVertex3f(-1.51, 0.4, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.53, 0.4, 0.03);
	glTexCoord2d(1, 0); glVertex3f(-1.53, 0.4, 0.02);
	glTexCoord2d(0, 0); glVertex3f(-1.51, 0.4, 0.02);
	glTexCoord2d(0, 1); glVertex3f(-1.51, 0.4, 0.03);
	glEnd();



	//RC2
	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.51, 0.4, 0.02);
	glTexCoord2d(0, 1); glVertex3f(-1.59, 0.4, 0.02);
	glTexCoord2d(0, 0); glVertex3f(-1.59, 0.0, 0.02);
	glTexCoord2d(1, 0); glVertex3f(-1.51, 0.0, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.51, 0.4, 0.03);
	glTexCoord2d(0, 1); glVertex3f(-1.59, 0.4, 0.03);
	glTexCoord2d(0, 0); glVertex3f(-1.59, 0.0, 0.03);
	glTexCoord2d(1, 0); glVertex3f(-1.51, 0.0, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.59, 0.4, 0.03);
	glTexCoord2d(0, 1); glVertex3f(-1.59, 0.0, 0.03);
	glTexCoord2d(0, 0); glVertex3f(-1.59, 0.0, 0.02);
	glTexCoord2d(1, 0); glVertex3f(-1.59, 0.4, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.51, 0.4, 0.03);
	glTexCoord2d(0, 1); glVertex3f(-1.51, 0.0, 0.03);
	glTexCoord2d(0, 0); glVertex3f(-1.51, 0.0, 0.02);
	glTexCoord2d(1, 0); glVertex3f(-1.51, 0.4, 0.02);
	glEnd();


	//RT4
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 1); glVertex3f(-1.59, 0.05, 0.02);
	glTexCoord2d(0, 0); glVertex3f(-1.59, 0.0, 0.02);
	glTexCoord2d(1, 0); glVertex3f(-1.61, 0.0, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 1); glVertex3f(-1.59, 0.05, 0.03);
	glTexCoord2d(0, 0); glVertex3f(-1.59, 0.0, 0.03);
	glTexCoord2d(1, 0); glVertex3f(-1.61, 0.0, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 0); glVertex3f(-1.59, 0.05, 0.02);
	glTexCoord2d(0, 0); glVertex3f(-1.59, 0.0, 0.02);
	glTexCoord2d(0, 1); glVertex3f(-1.59, 0.0, 0.03);
	glTexCoord2d(1, 1); glVertex3f(-1.59, 0.05, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 1); glVertex3f(-1.59, 0.05, 0.02);
	glTexCoord2d(0, 0); glVertex3f(-1.59, 0.0, 0.03);
	glTexCoord2d(1, 0); glVertex3f(-1.61, 0.0, 0.03);
	glTexCoord2d(1, 1); glVertex3f(-1.61, 0.05, 0.02);
	glEnd();


	//RT5
	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.51, 0.0, 0.02);
	glTexCoord2d(0, 1); glVertex3f(-1.53, 0.0, 0.02);
	glTexCoord2d(0, 0); glVertex3f(-1.53, -0.05, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 1); glVertex3f(-1.51, 0.0, 0.03);
	glTexCoord2d(1, 1); glVertex3f(-1.53, 0.0, 0.03);
	glTexCoord2d(1, 0); glVertex3f(-1.53, -0.05, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.53, 0.0, 0.03);
	glTexCoord2d(0, 1); glVertex3f(-1.53, -0.05, 0.03);
	glTexCoord2d(0, 0); glVertex3f(-1.53, -0.05, 0.02);
	glTexCoord2d(1, 0); glVertex3f(-1.53, 0.0, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 1); glVertex3f(-1.51, 0.0, 0.03);
	glTexCoord2d(0, 0); glVertex3f(-1.51, 0.0, 0.02);
	glTexCoord2d(1, 0); glVertex3f(-1.53, -0.05, 0.02);
	glTexCoord2d(1, 1); glVertex3f(-1.53, -0.05, 0.03);
	glEnd();
	//RC3
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 1); glVertex3f(-1.53, 0.0, 0.02);
	glTexCoord2d(1, 1); glVertex3f(-1.61, 0.0, 0.02);
	glTexCoord2d(1, 0); glVertex3f(-1.61, -0.3, 0.02);
	glTexCoord2d(0, 0); glVertex3f(-1.53, -0.3, 0.02);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(0, 1); glVertex3f(-1.53, 0.0, 0.03);
	glTexCoord2d(1, 1); glVertex3f(-1.61, 0.0, 0.03);
	glTexCoord2d(1, 0); glVertex3f(-1.61, -0.3, 0.03);
	glTexCoord2d(0, 0); glVertex3f(-1.53, -0.3, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 0); glVertex3f(-1.53, 0.0, 0.02);
	glTexCoord2d(0, 0);	glVertex3f(-1.53, -0.3, 0.02);
	glTexCoord2d(0, 1); glVertex3f(-1.53, -0.3, 0.03);
	glTexCoord2d(1, 1); glVertex3f(-1.53, 0.0, 0.03);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2d(1, 0); glVertex3f(-1.61, 0.0, 0.02);
	glTexCoord2d(0, 0); glVertex3f(-1.61, -0.3, 0.02);
	glTexCoord2d(0, 1); glVertex3f(-1.61, -0.3, 0.03);
	glTexCoord2d(1, 1); glVertex3f(-1.61, 0.0, 0.03);
	glEnd();
	if (bladelocation < 0.2)
		glColor3ub(255, 69, 0);

	//T1
	glBegin(GL_POLYGON);
	glTexCoord2d(0, 1); glVertex3f(-1.52, 0.9, 0.0);
	glTexCoord2d(1, 0); glVertex3f(-1.60, 0.8, 0.0);
	glTexCoord2d(0, 0); glVertex3f(-1.52, 0.8, 0.0);
	glEnd();

	//C1
	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.60, 0.8, 0.0);
	glTexCoord2d(0, 1); glVertex3f(-1.52, 0.8, 0.0);
	glTexCoord2d(0, 0); glVertex3f(-1.52, 0.4, 0.0);
	glTexCoord2d(1, 0); glVertex3f(-1.60, 0.4, 0.0);
	glEnd();
	//T2
	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.52, 0.45, 0.0);
	glTexCoord2d(1, 0);	glVertex3f(-1.52, 0.4, 0.0);
	glTexCoord2d(0, 0); glVertex3f(-1.44, 0.4, 0.0);
	glEnd();
	//T3
	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.60, 0.4, 0.0);
	glTexCoord2d(0, 1); glVertex3f(-1.52, 0.4, 0.0);
	glTexCoord2d(0, 0); glVertex3f(-1.52, 0.36, 0.0);
	glEnd();
	//C2
	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.52, 0.4, 0.0);
	glTexCoord2d(0, 1); glVertex3f(-1.44, 0.4, 0.0);
	glTexCoord2d(0, 0); glVertex3f(-1.44, 0.0, 0.0);
	glTexCoord2d(1, 0); glVertex3f(-1.52, 0.0, 0.0);
	glEnd();
	//T4
	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.44, 0.05, 0.0);
	glTexCoord2d(1, 0); glVertex3f(-1.44, 0.0, 0.0);
	glTexCoord2d(0, 0); glVertex3f(-1.42, 0.0, 0.0);
	glEnd();

	//T5
	glBegin(GL_POLYGON);
	glTexCoord2d(1, 0); glVertex3f(-1.52, 0.0, 0.0);
	glTexCoord2d(0, 0); glVertex3f(-1.48, 0.0, 0.0);
	glTexCoord2d(0, 1); glVertex3f(-1.48, -0.05, 0.0);
	glEnd();
	//C3
	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3f(-1.48, 0.0, 0.0);
	glTexCoord2d(0, 1); glVertex3f(-1.42, 0.0, 0.0);
	glTexCoord2d(0, 0); glVertex3f(-1.42, -0.3, 0.0);
	glTexCoord2d(1, 0); glVertex3f(-1.48, -0.3, 0.0);
	glEnd();


	glColor3f(1.0, 1.0, 1.0);
}

void bullet()
{
	GLUquadricObj* bullet = NULL;

	glPushMatrix();
	glTranslatef(1, 1, 0);
	glRotatef(90, 0, 1, 0);
	bullet = gluNewQuadric();
	gluQuadricDrawStyle(bullet, GLU_FILL);
	gluCylinder(bullet, 0.01, 0.05, 0.1, 30, 30);
	gluDeleteQuadric(bullet);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.1, 1, 0);
	glRotatef(90, 0, 1, 0);
	bullet = gluNewQuadric();
	gluQuadricDrawStyle(bullet, GLU_FILL);
	gluCylinder(bullet, 0.05, 0.05, 0.1, 30, 30);
	gluDeleteQuadric(bullet);
	glPopMatrix();
}

void background() {
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"bg1.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Front
	glBegin(GL_POLYGON);
	glTexCoord2f(1, 1); glVertex3f(-10, 10, -10);
	glTexCoord2f(0, 1); glVertex3f(10, 10, -10);
	glTexCoord2f(0, 0); glVertex3f(10, -2, -10);
	glTexCoord2f(1, 0); glVertex3f(-10, -2, -10);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glTexCoord2f(1, 0); glVertex3f(-10, -2, -10);
	glTexCoord2f(0, 0); glVertex3f(-10, -2, 10);
	glTexCoord2f(0, 1); glVertex3f(-10, 10, 10);
	glTexCoord2f(1, 1); glVertex3f(-10, 10, -10);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex3f(10, 10, -10);
	glTexCoord2f(1, 1); glVertex3f(10, 10, 10);
	glTexCoord2f(1, 0); glVertex3f(10, -2, 10);
	glTexCoord2f(0, 0); glVertex3f(10, -2, -10);
	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glTexCoord2f(1, 0); glVertex3f(10, -2, 10);
	glTexCoord2f(0, 0); glVertex3f(-10, -2, 10);
	glTexCoord2f(0, 1); glVertex3f(-10, 10, 10);
	glTexCoord2f(1, 1); glVertex3f(10, 10, 10);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"sky.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Top
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(-10, 10, -10);
	glTexCoord2f(0, 1); glVertex3f(-10, 10, 10);
	glTexCoord2f(1, 1); glVertex3f(10, 10, 10);
	glTexCoord2f(1, 0); glVertex3f(10, 10, -10);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"floor.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth,
		BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//Bottom
	glBegin(GL_POLYGON);
	glTexCoord2f(1, 1); glVertex3f(10, -2, -10);
	glTexCoord2f(1, 0); glVertex3f(-10, -2, -10);
	glTexCoord2f(0, 0); glVertex3f(-10, -2, 10);
	glTexCoord2f(0, 1); glVertex3f(10, -2, 10);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);
}

void optimusPrime()
{
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

	glPushMatrix();
	glRotatef(headTurn, 0, 1, 0);
	head();
	glPopMatrix();

	chestArmor2();
	backArmor1();
	backArmor2();
	backArmor3();
	backArmor4();


	/////////////////////////////// LEFT PART FROM SCREEN VIEW ///////////////////////////////
	glPushMatrix();
	if (stepcounter % 6 == 1)
	{
		glRotatef(20, 1, 0, 0); // leg movement
		//stepcounter++;
	}
	if (stepcounter % 6 == 3)
	{
		glRotatef(-20, 1, 0, 0); // leg movement
		//stepcounter++;
	}

	if (stepcounter % 6 == 5)
	{
		glRotatef(20, 1, 0, 0); // leg movement
		//stepcounter++;
	}
	
	leg();
	shoePart1();
	shoePart2();
	shoePart3();
	legArmor1();
	legArmor2();
	legArmor3();
	//legArmor4();
	legTyre();
	thigh();
	thighArmor1();
	thighArmor2();
	thighArmor3();
	thighArmor4();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1.27, 0.1);
	glRotatef(leftWholeArmSpeed, 1, 0, 0);
	glTranslatef(0, -1.27, -0.1);

	upperArmJoint();
	upperArm(false);
	armMuscle1();
	armMuscle2();
	muscleLowerArmJoint();
	armAntenna();

	/* Move the Left Arm Up & Down */
	glPushMatrix();
	glTranslatef(0, 0.65, 0.15);
	glRotatef(leftArmUpSpeed, 1, 0, 0);
	glTranslatef(0, -0.65, -0.15);
	glPushMatrix();
	glScalef(0.6, 1.0, 0.7);
	glRotatef(270, 0, 1, 0);
	glRotatef(90, 0, 0, 1);
	glTranslatef(-2.3, -0.6, 1.0);
	if (usegun == true)
	{
		gun();
		leftUpperFingerDegree = 90;
		leftMiddleFingerDegree = 90;
	}
	if (trigger == true)
	{
		glPushMatrix();
		glTranslatef(firebullet -= bulletspeed, 0, 0);
		pos[0] = -2 + firebullet;
		pos[1] = 1 + 0.5;
		pos[2] = 0;
		glEnable(GL_LIGHTING);

		glLightfv(GL_LIGHT0, GL_DIFFUSE, amb);
		glLightfv(GL_LIGHT0, GL_POSITION, pos);
		glEnable(GL_LIGHT0);
		bullet();
		glPopMatrix();

		glMaterialfv(GL_FRONT, GL_DIFFUSE, amb);
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
	}
	if (firebullet < -3.0)
	{
		trigger = false;
		firebullet = 0.0;

	}
	//glTranslatef(-1, -1, 0);

	glPopMatrix();
	lowerArm();
	lowerArmArmor1();
	lowerArmArmor2();
	hand(0);

	glPopMatrix();

	glPopMatrix();

	/////////////////////////////// RIGHT PART FROM SCREEN VIEW ///////////////////////////////
	/* RIGHT ARM LOGO*/

	/* Translate Shoe To The Right Part*/
	glPushMatrix();
		if (stepcounter % 6 == 3)
			glRotatef(20, 1.0, 0.0, 0.0); //stepmovementz
		if (stepcounter % 6 == 5)
			glRotatef(-20, 1.0, 0.0, 0.0);
		glTranslatef(0.5, 0, 0);
		shoePart1();
		shoePart2();
		shoePart3();
		legArmor1();
		//legArmor4();
		thighArmor1();
		thighArmor2();
		thighArmor4();
	glPopMatrix();


		glPushMatrix();
			glTranslatef(0, 1.27, 0.1);
			glRotatef(rightWholeArmSpeed, 1, 0, 0);
			glTranslatef(0, -1.27, -0.1);


			glPushMatrix();
					glRotatef(180, 0, 1, 0);

					/* Due to not symmetric, translate it to make it symmetric */
					glPushMatrix();
						glTranslatef(0, 0, -0.2);
						upperArm(true);
						armMuscle1();
						armMuscle2();
						armAntenna();
						muscleLowerArmJoint();
					glPopMatrix();

					/* Due to not symmetric, translate it to make it symmetric */
					glPushMatrix();
						glTranslatef(0, 0, -0.1);
						upperArmJoint();
					glPopMatrix();
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
				hand(1);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
		//glScalef(1.0, 0.5, 1.0);
		glTranslatef(0, 0.65, 0.15);
		glRotatef(rightArmUpSpeed, 1, 0, 0);
		glTranslatef(0, -0.65, -0.15);

		if (drawBlade == true)
		{
			glPushMatrix();
			glRotatef(180, 1.0, 0.0, 0.0);
			glRotatef(90, 0.0, 1.0, 0.0);
			if (bladelocation <= 0.2)
			{
				bladelocation += speed;
				bladesize += speed;

			}
			glScalef(1.0, bladesize, 1.0);
			glTranslatef(1.6 , bladelocation, 0.7 );
			if (bladelocation >= 0.2) //blade fully extend only show fire
			{
				glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

				hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "flameblade.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
				GetObject(hBMP, sizeof(BMP), &BMP);



				glEnable(GL_TEXTURE_2D);
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);


				blade();

				glDisable(GL_TEXTURE_2D);
				DeleteObject(hBMP);
				glDeleteTextures(1, &texture);

			}
			else
			{
				blade();
			}
			glPopMatrix();
		}
		else
		{
			glPushMatrix();
			glRotatef(180, 1.0, 0.0, 0.0);
			glRotatef(90, 0.0, 1.0, 0.0);
			if (bladelocation >= -1.2)
			{
				bladelocation -= speed;
				bladesize -= speed;

			}
			glScalef(1.0, bladesize, 1.0);
			glTranslatef(1.6 , bladelocation, 0.65 );

			blade();


			glPopMatrix();
		}
		glPopMatrix();

	glPopMatrix();

	/* Translate Leg Armor 2 To The Right Part */
	glPushMatrix();
		if (stepcounter % 6 == 3)
			glRotatef(20, 1.0, 0.0, 0.0); //step movement
		if (stepcounter % 6 == 5)
			glRotatef(-20, 1.0, 0.0, 0.0);
		glTranslatef(0.25, 0, 0);
		legArmor2();
	glPopMatrix();

	/* Translate Thigh Armor 3 To The Right Part */
	glPushMatrix();
		if (stepcounter % 6 == 3)
			glRotatef(20, 1.0, 0.0, 0.0); //step movement
		if (stepcounter % 6 == 5)
			glRotatef(-20, 1.0, 0.0, 0.0);
		glTranslatef(0.29, 0, 0);
		thighArmor3();
	glPopMatrix();
	/* Rotate 180 To Duplicate Another Part */
	glPushMatrix();
	//glRotatef(20, 1.0, 0.0, 0.0);

		glPushMatrix();
			if (stepcounter % 6 == 3)
				glRotatef(20, 1.0, 0.0, 0.0); //step movement
			if (stepcounter % 6 == 5)
				glRotatef(-20, 1.0, 0.0, 0.0);
			glRotatef(180, 0, 1, 0);
			leg();
			legArmor3();
			thigh();

			glPushMatrix();
				glTranslatef(0, 0, -0.2);
				legTyre();
			glPopMatrix();
		
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glScalef(0.6, 1.0, 0.7);
	glRotatef(270, 0, 1, 0);
	glRotatef(90, 0, 0, 1);
	glTranslatef(-1.1, -1.7, 0.9);



	//gun();
	if (drawGun == true && backNormal == 0)
	{
		if (leftWholeArmSpeed <= 200)
		{
			leftWholeArmSpeed += anglespeed;
		}
		else
			leftWholeArmSpeed = 200.1;
		if (leftArmUpSpeed <= 115)
		{
			leftArmUpSpeed += anglespeed;
		}
		else
			leftArmUpSpeed = 115.1;
		if (leftWholeArmSpeed > 200 && leftArmUpSpeed > 115)
		{
			usegun = true;
			backNormal = 1;

		}
	}

	if (drawGun == false && backNormal == 2)
	{
		if (leftWholeArmSpeed <= 200)
		{
			leftWholeArmSpeed += anglespeed;
		}
		else
			leftWholeArmSpeed = 200.1;
		if (leftArmUpSpeed <= 115)
		{
			leftArmUpSpeed += anglespeed;
		}
		else
			leftArmUpSpeed = 115.1;
		if (leftWholeArmSpeed > 200 && leftArmUpSpeed > 115)
		{
			usegun = false;
			backNormal = 3;

		}
	}

	if (backNormal == 1)
	{
		if (leftWholeArmSpeed >= 45)
		{
			leftWholeArmSpeed -= anglespeed;
		}
		else
			leftWholeArmSpeed = 44.9;
		if (leftArmUpSpeed >= 45)
		{
			leftArmUpSpeed -= anglespeed;
		}
		else
			leftArmUpSpeed = 44.9;
		if (leftWholeArmSpeed < 45 && leftArmUpSpeed < 45)
			backNormal = 2;

	}

	if (backNormal == 3)
	{
		if (leftWholeArmSpeed > 0)
		{
			leftWholeArmSpeed -= anglespeed;
		}
		else
			leftWholeArmSpeed = 0;
		if (leftArmUpSpeed > 0)
		{
			leftArmUpSpeed-= anglespeed;
		}
		else
			leftArmUpSpeed = 0;
		
		if (leftWholeArmSpeed <= 0 && leftArmUpSpeed <= 0)
			backNormal = 0;

	}

	if (usegun == false&&backNormal==3)
	{
		leftUpperFingerDegree = 30;
		leftMiddleFingerDegree = 30;
		gun();
	}
	if (usegun == false)
		gun();

	glPopMatrix();

	if (swingBlade == 1 && drawBlade == true)
	{
		if (rightWholeArmSpeed < 90)
		{
			rightWholeArmSpeed += anglespeed;
		}
		else
			rightWholeArmSpeed = 90;
		if (rightWholeArmSpeed >= 90)
			swingBlade++;
	}
	if (swingBlade == 2 && drawBlade == true)
	{
		if (rightWholeArmSpeed > 45)
		{
			rightWholeArmSpeed -= anglespeed;

		}
		else
			rightWholeArmSpeed = 45;
		if (rightArmUpSpeed < 90)
		{
			rightArmUpSpeed += anglespeed;
		}
		else
			rightArmUpSpeed = 90;
		if ((rightWholeArmSpeed <= 45) && (rightArmUpSpeed >= 90))
			swingBlade++;
	}
	if (swingBlade == 3 && drawBlade == true)
	{
		if (rightWholeArmSpeed > 0)
		{
			rightWholeArmSpeed -= anglespeed;

		}
		else
			rightWholeArmSpeed = 0;
		if (rightArmUpSpeed > 0)
		{
			rightArmUpSpeed -= anglespeed;
		}
		else
			rightArmUpSpeed = 0;
		if ((rightWholeArmSpeed <= 0) && (rightArmUpSpeed <= 0))
			swingBlade = 4;
	}
}
//--------------------------------------------------------------------

void goPerspectiveView() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glScalef(0.4, 0.4, 0.4);
	gluPerspective(30.0, 1.0, 0.5, 20);
	glFrustum(-2, 2, -2, 2, 1, 20);

}

void goOrthoView() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glScalef(0.4, 0.4, 0.4);
	glOrtho(-2, 2 , -0.8, 3.8, 1, -10);
}

void goBackOriginView() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

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

	float temp = 0.0;

	startingSound();

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (goPerspective)
		{
			goPerspectiveView();
			goPerspective = false;
			inWhatProjectionMode = 2;
		}

		if (goOrtho)
		{
			goOrthoView();
			goOrtho = false;
			inWhatProjectionMode = 1;
		}

		if (goBackOrigin) {
			goBackOriginView();
			goBackOrigin = false;
			inWhatProjectionMode = 0;
		}

		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClearColor(0.53, 0.81, 0.92, 0);
		glEnable(GL_DEPTH_TEST);

		glMatrixMode(GL_MODELVIEW);

		if (stepcounter % 6 == 2 || stepcounter % 6 == 4)
		{
			stepcounter++;
			if (turnrate == 0)
				stepmovementz -= 0.1;
			else if (turnrate == 90)
				stepmovementx -= 0.1;
			else if (turnrate == 180)
				stepmovementz += 0.1;
			else if (turnrate == 270)
				stepmovementx += 0.1;
		}
		

		glPushMatrix();

		if (inWhatProjectionMode == 1)
		{
			if (y > 0)
				y = 0;
			else if (y < -0.5)
				y = -0.5;

			if (x > 4.999998)
				x = 4.999998;
			else if (x < -4.999997)
				x = -4.999997;

			if (z > 7.499995)
				z = 7.499995;
			else if (z < -2.1)
				z = -2.1;
		}
		else if (inWhatProjectionMode == 2) 
		{
			
			if (y > 0.600000)
				y = 0.600000;
			else if (y < -8.499996)
				y = -8.499996;

			if (x > 8.499996)
				x = 8.499996;
			else if (x < -8.499996)
				x = -8.499996;
				
			if (z > 6.199996)
				z = 6.199996;
			else if (z < -13.700016)
				z = -13.700016;
		}

		glTranslatef(x, y, z);

		glPushMatrix();
		glTranslatef(stepmovementx, 0.0, stepmovementz);
		glRotatef(turnrate, 0.0, 1.0, 0.0);
		optimusPrime();
		glPopMatrix();

		background();
		glPopMatrix();
		

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------