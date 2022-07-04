#include "Button.h"

Button::Button()
{
	owner = nullptr;
	size = { 0,0 };
	backgroundColor = { 0,0,0 };
	lineColor = { 0,0,0 };
	textColor = { 0,0,0 };
	haveColor = false;
}

Button::Button( POINTFLOAT coordinates, POINTFLOAT bSize) : Button()
{
	size = bSize;
	MoveButton(coordinates);
	ResizeButton(bSize);
}

void Button::MoveButton(POINTFLOAT coordinates)
{
	vert[0] = vert[9] = coordinates.x;
	vert[1] = vert[4] = coordinates.y;
	vert[3] = vert[6] = vert[0] + size.x;
	vert[7] = vert[10] = vert[1] + size.y;
}
void Button::ResizeButton(POINTFLOAT bSize)
{
	size.x = bSize.x;
	size.y = bSize.y;
	vert[3] = vert[6] = vert[0] + size.x;
	vert[7] = vert[10] = vert[1] - size.y;
}
void Button::Colored(Vector3D bColor, Vector3D lColor, Vector3D tColor)
{
	backgroundColor = bColor;
	lineColor = lColor;
	textColor = tColor;
	haveColor = true;
}
void Button::DrawButton(Vector3D bColor, Vector3D lColor, Vector3D tColor)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vert);

	if (haveColor)
		glColor3f(backgroundColor.x, backgroundColor.y, backgroundColor.z);
	else
		glColor3f(bColor.x, bColor.y, bColor.z);
	glDrawArrays(GL_QUADS, 0, 4);

	if (haveColor)
		glColor3f(lineColor.x, lineColor.y, lineColor.z);
	else
		glColor3f(lColor.x, lColor.y, lColor.z);
	glDrawArrays(GL_LINE_LOOP, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
}
void Button::FindOwner(Menu* ownerMenu)
{
	owner = ownerMenu;
}
GLfloat Button::GetButtonSizeY()
{
	return size.y;
}
GLfloat Button::GetButtonSizeX()
{
	return size.x;
}