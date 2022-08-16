#pragma once
#include <Windows.h>
#include "Math3D.h"
#include "Button.h"
#include "Decoration.h"
#include "Render.h"
#include "Update.h"
#include "Camera.h"

class Menu : public RenderItem, public UpdateItem
{
	Button* buttons;
	int buttonsNum;
	Button* choicenButton;
	Vector3D backgroundColor;
	Vector3D backgroundColorButton;
	Vector3D lineColorButton;
	Vector3D textColorButton;
	bool haveColor;
	GLfloat spaceBetweenButton;
	GLfloat buttonSize;
	Decoration* decoration;
	GLFWwindow* window;
public:
	static bool drawMenu;

	Menu(GLFWwindow* win);
	Menu(Button* buttonlist, int num, Decoration* decor, GLFWwindow* win);
	void Colored(Vector3D bColor, Vector3D bColorB, Vector3D lColorB, Vector3D tColorB);
	void MoveButtons(POINTFLOAT startPosition);
	void Render() override;
	void StopRender() override;
	void ContinueRender() override;
	void Update() override;
};