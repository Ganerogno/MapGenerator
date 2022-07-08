#pragma once
#include <Windows.h>
#include "Math3D.h"
#include "Button.h"
#include "Decoration.h"
#include "Render.h"
class Button;

class Menu : public RenderItem
{
	Button* buttons;
	int buttonsNum;
	Vector3D backgroundColor;
	Vector3D backgroundColorButton;
	Vector3D lineColorButton;
	Vector3D textColorButton;
	bool haveColor;
	GLfloat spaceBetweenButton;
	GLfloat buttonSize;
	Decoration* decoration;
public:
	Menu();
	Menu(Button* buttonlist, int num, Decoration* decor);
	void Colored(Vector3D bColor, Vector3D bColorB, Vector3D lColorB, Vector3D tColorB);
	void MoveButtons(POINTFLOAT startPosition);
	void Render();
};