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




//初始化窗口
void InitWindow();
//鼠标以及显示，在main函数中调用
void MainGraphFunc();
//渲染
void RenderScene();





void InitWindow()
{
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("CircleModeADD");
	InitMenu();
	glMatrixMode(GL_PROJECTION);// sets the current matrix to projection
	glLoadIdentity();//multiply the current matrix by identity matrix
	gluOrtho2D(0.0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);//sets the parallel(orthographic) projection of the full frame buffer 

}

inline void MainGraphFunc()
{
	glutMouseFunc(mouseProcess);
	glutDisplayFunc(RenderScene);


	glutMainLoop();
}

void RenderScene()
{
	glClearColor(1, 1, 1, 1);
	glPointSize(5);
	if (creak)
	{
		glBegin(GL_POINTS);
		glVertex2i(coorxy.getCoorX(), coorxy.getCoorY());
		glEnd();
	}
	cout << coorxy.getpointnum() << " [" << coorxy.getCoorX() << "," << coorxy.getCoorY() << "]" << endl;
	glFlush();

}


