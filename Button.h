#pragma once
#include <Windows.h>
#include <string>
#include "Math3D.h"
#include "Texture.h"

class Button
{
	POINTFLOAT size;
	GLfloat vert[12]{};
	Vector3D backgroundColor;
	Vector3D lineColor;
	Vector3D textColor;
	bool haveColor;
	std::string word;
	Texture* text;
	GLfloat textCoordinates[8]{ 0,0,1,0,1,1,0,1 };
	GLfloat symbolsCoordinates[8]{};
	GLfloat symbolSize;
public:
	void (*function)();
	static GLfloat symbolWidth[];

	Button(const char* bWord, Texture* bTexture, void (*bFunction)() = nullptr);
	void MoveButton(POINTFLOAT coordinates);
	void ResizeButton(GLfloat bSize);
	void Colored(Vector3D bColor, Vector3D lColor, Vector3D tColor);
	void DrawButton(Vector3D bColor, Vector3D lColor, Vector3D tColor);
	void DrawButtonText(Vector3D tColor = {0,0,0});
	void FindSymbol(char symbol);
	static void FindSymbolWidth(Texture* texture);
	GLfloat GetButtonSizeY();
	GLfloat GetButtonSizeX();
	GLfloat* GetVertArray();
	void SetNumber(int number);
	bool TestCoordinate(double x, double y);
};