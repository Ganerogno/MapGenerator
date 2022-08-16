#include "Menu.h"

Menu::Menu(GLFWwindow* win)
{
	window = win;
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
Menu::Menu( Button* buttonlist, int num, Decoration* decor, GLFWwindow* win) : Menu(win)
{
	buttons = buttonlist;
	buttonsNum = num;
	buttonSize = 0.05;
	MoveButtons({ -0.8f,0.5f });
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
		buttons[i].ResizeButton({ 0.2f });
	}
}
void Menu::Render()
{
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();
	glLineWidth(5);
	decoration->DrawDecoration();
	glLineWidth(2);
	for (int i = 0; i < buttonsNum; i++)
	{
		if (!Menu::continueGame && !i)
			continue;
		buttons[i].DrawButton(backgroundColorButton, lineColorButton, textColorButton);
	}

	if (choicenButton)
	{
		glEnable(GL_VERTEX_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, choicenButton->GetVertArray());
		glColor4f(0.5, 0.5, 0.5, 0.5);
		glDrawArrays(GL_QUADS, 0, 4);

		glDisable(GL_VERTEX_ARRAY);
	}

	glPopMatrix();
}
void Menu::StopRender()
{
	canRender = false;
	StopUpdate();
	decoration->StopUpdate();
}
void Menu::ContinueRender()
{
	canRender = true;
	ContinueUpdate();
	decoration->ContinueUpdate();
}
void Menu::Update()
{
	double x, y;
	bool flag = false;
	glfwGetCursorPos(window, &x, &y);
	x -= 500;
	y -= 500;
	x /= 500;
	y /= -500;

	for (int i = 0; i < buttonsNum; i++)
	{
		if (buttons[i].TestCoordinate(x, y))
		{
			choicenButton = &buttons[i];
			if (choicenButton == &buttons[0] && !Menu::continueGame)
			{
				flag = false;
			}
			else
			{
				flag = true;
			}
		}
	}
	if (!flag)
	{
		choicenButton = nullptr;
	}
	if (Camera::leftMouseButton && Menu::drawMenu)
	{
		if (choicenButton && choicenButton->function != nullptr)
		{
			choicenButton->function();
		}
	}
}