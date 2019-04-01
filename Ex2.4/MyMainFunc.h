#pragma once
#pragma comment(lib,"glut32.lib")

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "glut.h"
#include "CoordinateXY.h"
#include  "MenuFunc.h"
#include "MouseFunc.h"

using namespace std;

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define WHITE 0
#define RED 1
#define GREEN 2
#define	BLUE 3

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;



//初始化窗口
void InitWindow();
//鼠标以及显示，在main函数中调用
void MainGraphFunc();
//渲染
void RenderScene();

void Specialkey(int key, int x, int y);

void ChangeSize(int w, int h);




void InitWindow()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Rotate");
	InitMenu();
	glMatrixMode(GL_PROJECTION);// sets the current matrix to projection
	glLoadIdentity();//multiply the current matrix by identity matrix
	glOrtho(0.0, WINDOW_WIDTH, 0, WINDOW_HEIGHT,100,-100);//sets the parallel(orthographic) projection of the full frame buffer 

}

inline void MainGraphFunc()
{
	glutMouseFunc(mouseProcess);
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(Specialkey);
	glutReshapeFunc(ChangeSize);
	glutMainLoop();
}

void RenderScene()
{	// Clear the window with current clearing color
	//glClear(GL_COLOR_BUFFER_BIT);

	// Save matrix state and do the rotation
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glClearColor(1, 1, 1, 1);
	glPointSize(5);
	if (creak)
	{
		glBegin(GL_POINTS);
		glVertex3i(coorxy.getCoorX(), coorxy.getCoorY(),0);
		glEnd();
	}
	cout << coorxy.getpointnum() << " [" << coorxy.getCoorX() << "," << coorxy.getCoorY() << "]" << endl;
	// Restore transformations
	glPopMatrix();

	// Flush drawing commands
	glutSwapBuffers();
}

inline void Specialkey(int key, int x, int y)
{
	if (key==GLUT_KEY_UP)
	{
		xRot += 5;
	}
	if (key==GLUT_KEY_DOWN)
	{
		xRot += 5;
	}
	if (key == GLUT_KEY_LEFT)
	{
		yRot -= 5;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		yRot += 5;
	}
	if (key > 356.0f)
		xRot = 0.0f;

	if (key < -1.0f)
		xRot = 355.0f;

	if (key > 356.0f)
		yRot = 0.0f;

	if (key < -1.0f)
		yRot = 355.0f;

	// Refresh the Window
	glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
	GLfloat nRange = 100.0f;

	// Prevent a divide by zero
	if (h == 0)
		h = 1;

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange * h / w, nRange*h / w, -nRange, nRange);
	else
		glOrtho(-nRange * w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

