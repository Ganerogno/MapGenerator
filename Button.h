#pragma once
#include <Windows.h>
#include <GLFW/glfw3.h>
#include "Menu.h"
#include "Math3D.h"
class Menu;
class Button
{
	Menu* owner;
	POINTFLOAT size;
	GLfloat vert[12]{};
	Vector3D backgroundColor;
	Vector3D lineColor;
	Vector3D textColor;
	bool haveColor;
public:
	Button();
	Button(POINTFLOAT coordinates, POINTFLOAT bSize);
	void MoveButton(POINTFLOAT coordinates);
	void ResizeButton(POINTFLOAT bSize);
	void Colored(Vector3D bColor, Vector3D lColor, Vector3D tColor);
	void DrawButton(Vector3D bColor, Vector3D lColor, Vector3D tColor);
	void FindOwner(Menu* ownerMenu);
	GLfloat GetButtonSizeY();
	GLfloat GetButtonSizeX();
};