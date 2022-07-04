#include "Menu.h"

Menu::Menu()
{
	backgroundColor = { 0,0,0 };
	backgroundColorButton = { 0,0,0 };
	lineColorButton = { 0,0,0 };
	textColorButton = { 0,0,0 };
	buttonsNum = 0;
	buttons = nullptr;
	haveColor = false;
	spaceBetweenButton = 0;
	decoration = nullptr;
}
Menu::Menu(Button* buttonlist, int num, Decoration* decor) : Menu()
{
	buttons = buttonlist;
	buttonsNum = num;
	buttonSize = 0.05;
	for (int i = 0; i < num; i++)
	{
		buttons[i].FindOwner(this);
	}
	MoveButtons({ -0.8f,0.8f });
	decoration = decor;
}
void Menu::Colored(Vector3D bColor, Vector3D bColorB, Vector3D lColorB, Vector3D tColorB)
{
	backgroundColor = bColor;
	backgroundColorButton = bColorB;
	lineColorButton = lColorB;
	textColorButton = tColorB;
	haveColor = true;
}
void Menu::MoveButtons(POINTFLOAT startPosition)
{
	for (int i = 0; i < buttonsNum; i++)
	{
		buttons[i].MoveButton({ startPosition.x, startPosition.y - (0.2f + 0.1f) * i });
		buttons[i].ResizeButton({ 0.5f,0.2f });
	}
}
void Menu::Draw()
{
	glPushMatrix();
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2);
	for (int i = 0; i < buttonsNum; i++)
	{
		buttons[i].DrawButton(backgroundColorButton, lineColorButton, textColorButton);
	}
	glLineWidth(5);
	decoration->DrawDecoration();
	glPopMatrix();
}