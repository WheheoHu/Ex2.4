#pragma once
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "glut.h"
#include "CoordinateXY.h"

using namespace std;

constexpr auto WHITE = 0;
constexpr auto RED = 1;
constexpr auto GREEN = 2;
constexpr auto BLUE = 3;
constexpr auto WINDOW_WIDTH = 600;
constexpr auto WINDOW_HEIGHT = 600;

constexpr auto PI = 3.14159;
//生成圆的角度增量（角度值
constexpr auto CIRCLE_POINT_NUM = 50;
//圆的半径
constexpr auto CIRCLE_R = 100.0;
//线段模式
constexpr auto GL_LINES_MODE = 1;
constexpr auto GL_LINE_STRIP_MODE = 2;
constexpr auto GL_LINE_LOOP_MODE = 3;
//螺旋线内外半径
constexpr auto R_INNER = 30;
constexpr auto R_OUTER = 200;


static int iColor = WHITE;
static CoordinateXY   coorxy;
vector< CoordinateXY> datapoint;
fstream datafile;

//初始化菜单
void InitMenu();

//点颜色子菜单回调
void ColorPointMenu_CB(int MenuID);
//画圆子菜单回调
void CircleMenu_CB(int MenuID);
//LineMode submenu
void CircleLineModeMenu_CB(int MenuID);
//textsheet submenu callback
void TextSheet_CB(int MenuID);
//主菜单回调
void MainMenu_CB(int MenuID);
//保存数据
void savedata(vector<CoordinateXY> datapoint);
//读取Data.txt数据
void loaddata(fstream &datafile);
//清屏&重置数据
void removeall(fstream &datafile);
//画圆
void RenderACircle(int CiclePointNum);
void RenderACircle(int CiclePointNum, int  CicleLineMode);
//螺旋线
void RenderAHelix(float fRadiusInner, float fRadiusOut, int iNumOfDot = 100);
//绘制图表
void RenderText();
//保存xy数据
void setXY(int x, int y);


void setXY(int x, int y) {
	coorxy.setX(x);
	coorxy.setY(y);
	coorxy.setColor(iColor);
	coorxy.plusnum();
	datapoint.push_back(CoordinateXY(x, y, iColor));
}

void InitMenu()
{
	int MainMenu;
	int ColorPointMenu;
	int CircleMenu;
	int CircleLineModeMenu;
	int TextSheet;

	ColorPointMenu = glutCreateMenu(ColorPointMenu_CB);
	//glutSetMenu(ColorPointMenu);
	glutAddMenuEntry("White", 0);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("SAVE", 4);
	glutAddMenuEntry("LOAD", 5);
	glutAddMenuEntry("CLEAN ALL!", 6);

	CircleLineModeMenu = glutCreateMenu(CircleLineModeMenu_CB);
	glutAddMenuEntry("GL_LINES", 1);
	glutAddMenuEntry("GL_LINE_STRIP", 2);
	glutAddMenuEntry("GL_LINE_LOOP", 3);

	CircleMenu = glutCreateMenu(CircleMenu_CB);
	glutAddMenuEntry("Circle50", 1);
	glutAddSubMenu("CircleLineMode", CircleLineModeMenu);
	glutAddMenuEntry("Helix", 2);

	TextSheet = glutCreateMenu(TextSheet_CB);
	glutAddMenuEntry("TextSheet", 1);

	MainMenu = glutCreateMenu(MainMenu_CB);
	//glutSetMenu(MainMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutAddSubMenu("ColorPoint", ColorPointMenu);
	glutAddSubMenu("Circles", CircleMenu);
	glutAddSubMenu("TextSheet", TextSheet);
	glutAddMenuEntry("EXIT", 0);


}

inline void ColorPointMenu_CB(int MenuID) {
	switch (MenuID)
	{
	case 0: {
		iColor = WHITE;
		glColor3f(1, 1, 1);
		break;
	}
	case 1: {
		iColor = RED;
		glColor3f(1, 0, 0);
		break;
	}
	case 2: {
		iColor = GREEN;
		glColor3f(0, 1, 0);
		break;
	}
	case 3: {
		iColor = BLUE;
		glColor3f(0, 0, 1);
		break;
	}
	case 4: {
		savedata(datapoint);
		break;
	}
	case 5: {
		loaddata(datafile);
		break;
	}
	case 6: {

		removeall(datafile);
		break;
	}
	}
}

inline void CircleMenu_CB(int MenuID)
{
	switch (MenuID)
	{
	case 1: {
		RenderACircle(CIRCLE_POINT_NUM);
		break;
	}
	case 2: {
		RenderAHelix(R_INNER, R_OUTER);
		break;
	}
	}
}

inline void CircleLineModeMenu_CB(int MenuID)
{
	switch (MenuID)
	{
	case 1: {
		RenderACircle(CIRCLE_POINT_NUM, GL_LINES_MODE);
		break;
	}
	case 2: {
		RenderACircle(CIRCLE_POINT_NUM, GL_LINE_STRIP_MODE);
		break;
	}
	case 3: {
		RenderACircle(CIRCLE_POINT_NUM, GL_LINE_LOOP_MODE);
		break;
	}
	}
}

inline void TextSheet_CB(int MenuID)
{
	switch (MenuID)
	{
	case 1: {
		RenderText();
		break;
	}
	}
}

void MainMenu_CB(int MenuID) {
	switch (MenuID)
	{
	case 0: {
		exit(0);
		break; }
	}

}



void savedata(vector<CoordinateXY> datapoint)
{
	//remove("Data.txt");
	datafile.open("Data.txt", ios::out | ios::app);
	for (auto iter = datapoint.begin(); iter != datapoint.end(); iter++)
	{
		datafile << iter->getCoorX() << " " << iter->getCoorY() << " " << iter->getColor() << endl;
	}
	datafile.close();
}

void loaddata(fstream & datafile)
{
	datafile.open("Data.txt", ios::in);
	int coorx;
	int coory;
	int pointcolor;

	while (!datafile.eof())
	{
		datafile >> coorx;
		datafile >> coory;
		datafile >> pointcolor;
		iColor = pointcolor;
		switch (iColor)
		{
		case RED: {
			glColor3f(1, 0, 0);
			break;
		}
		case GREEN: {
			glColor3f(0, 1, 0);
			break;
		}
		case BLUE: {
			glColor3f(0, 0, 1);
			break;
		}
		case WHITE: {
			glColor3f(1, 1, 1);
			break;
		}
		}
		glBegin(GL_POINTS);
		glVertex2i(coorx, coory);
		glEnd();
		glutPostRedisplay();
	}
	datafile.close();
}

void removeall(fstream & datafile)
{
	datafile.open("Data.txt", ios::out);
	datafile.close();
	loaddata(datafile);
	glClear(GL_COLOR_BUFFER_BIT);
}

inline void RenderACircle(int CiclePointNum)
{
	glColor3f(0, 0, 0);
	int coorx;
	int coory;
	glPointSize(2);
	glBegin(GL_POINTS);
	for (auto angle = 0.; angle < 360; angle += 360. / CiclePointNum)
	{

		coorx = CIRCLE_R * cos(angle*PI / 180) + WINDOW_WIDTH / 2;
		coory = CIRCLE_R * sin(angle*PI / 180) + WINDOW_HEIGHT / 2;
		cout << coorx << " " << coory << endl;
		glVertex2i(coorx, coory);
	}
	glEnd();
	glutPostRedisplay();
}

inline void RenderACircle(int CiclePointNum, int CicleLineMode)
{
	
	int coorx;
	int coory;
	glPointSize(2);
	if (CicleLineMode == GL_LINES_MODE)
	{
		glBegin(GL_LINES);
		for (float angle = 0; angle < 360; angle += 360. / CiclePointNum)
		{
			coorx = CIRCLE_R * cos(angle*PI / 180) + WINDOW_WIDTH / 2;
			coory = CIRCLE_R * sin(angle*PI / 180) + WINDOW_HEIGHT / 2;
			cout << coorx << " " << coory << endl;
			glVertex2i(coorx, coory);
		}
		glEnd();
	}
	else if (CicleLineMode == GL_LINE_STRIP_MODE)
	{
		glBegin(GL_LINE_STRIP);
		for (float angle = 0; angle < 360; angle += 360. / CiclePointNum)
		{
			coorx = CIRCLE_R * cos(angle*PI / 180) + WINDOW_WIDTH / 2;
			coory = CIRCLE_R * sin(angle*PI / 180) + WINDOW_HEIGHT / 2;
			cout << coorx << " " << coory << endl;
			glVertex2i(coorx, coory);
		}
		glEnd();
	}
	else if (CicleLineMode == GL_LINE_LOOP_MODE)
	{
		glBegin(GL_LINE_LOOP);
		for (float angle = 0; angle < 360; angle += 360. / CiclePointNum)
		{
			coorx = CIRCLE_R * cos(angle*PI / 180) + WINDOW_WIDTH / 2;
			coory = CIRCLE_R * sin(angle*PI / 180) + WINDOW_HEIGHT / 2;
			cout << coorx << " " << coory << endl;
			glVertex2i(coorx, coory);
		}
		glEnd();
	}
	glutPostRedisplay();
}

inline void RenderAHelix(float fRadiusInner, float fRadiusOut, int iNumOfDot)
{
	float fR_step = (fRadiusOut - fRadiusInner) / iNumOfDot;
	float fR_temp = fRadiusInner;
	int icoorx = 0;
	int icoory = 0;
	glPointSize(3);
	glBegin(GL_POINTS);
	for (float angle = 0; angle < 360 * 3; angle += 360 * 3 / iNumOfDot)
	{
		icoorx = fR_temp * cos(angle*PI / 180) + WINDOW_WIDTH / 2;
		icoory = fR_temp * sin(angle*PI / 180) + WINDOW_HEIGHT / 2;

		glColor3f(rand() % 100 / 100., rand() % 100 / 100., rand() % 100 / 100.);

		cout << icoorx << " " << icoory << endl;
		glVertex2i(icoorx, icoory);
		fR_temp += fR_step;

	}
	glEnd();
	glutPostRedisplay();

}

inline void RenderText()
{
	//月份标签数组
	GLubyte label[36] = {
				'J', 'a', 'n',
				'F', 'e', 'b',
				'M', 'a', 'r',
				'A', 'p', 'r',
				'M', 'a', 'y',
				'J', 'u', 'n',
				'J', 'u', 'l',
				'A', 'u', 'g',
				'S', 'e', 'p',
				'O', 'c', 't',
				'N', 'o', 'v',
				'D', 'e', 'c' };
	//折线图数值项
	GLint dataValue[12] = { 420, 342, 324, 310, 262, 185, 190, 196, 217, 240, 312, 438 };

	constexpr auto kRemainLREdgePixel = 20;
	constexpr auto kCoorXStep = (WINDOW_WIDTH - 2 * kRemainLREdgePixel) / 12;
	constexpr auto kBottonEdge = 50;
	int icoorx = kRemainLREdgePixel;
	auto icoory = 0;
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 12; i++)
	{
		icoory = dataValue[i] + kBottonEdge;
		glVertex2i(icoorx,icoory);
		cout << icoorx << " " << icoory << endl;
		icoorx += kCoorXStep;
	}
	glEnd();
	glutPostRedisplay();

}
