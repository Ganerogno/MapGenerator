#pragma once
#include <iostream>
#include <Windows.h>
#include <GLFW/glfw3.h>
#include "Math3D.h"

class Button
{
	Menu* owner;
	POINTFLOAT location;
	POINTFLOAT size;
	Vector3D backgroundColor;
	Vector3D lineColor;
	bool hasColor = false;
public:
	Button(Menu* menu, POINTFLOAT coordinates, POINTFLOAT bSize)
	{
		owner = menu;
		location = coordinates;
		size = bSize;
	}
	Button(Menu* menu, POINTFLOAT coordinates, POINTFLOAT bSize, Vector3D bgColor, Vector3D lColor) : Button(menu, coordinates, bSize)
	{
		backgroundColor = bgColor;
		lineColor = lColor;
		hasColor = true;
	}
	void DrawButton()
	{
		glPushMatrix();
		glBegin(GL_QUADS);
		glTranslatef(location.x, location.y, 0);
	}
};
class Menu
{

};
class UI
{

};