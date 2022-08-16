#include "Button.h"

Button::Button(const char* bWord, Texture* bTexture, void (*bFunction)())
{
	word = bWord;
	text = bTexture;
	function = bFunction;
	size = { 0,0 };
	backgroundColor = { 0,0,0 };
	lineColor = { 0,0,0 };
	textColor = { 0,0,0 };
	haveColor = false;
	symbolSize = 0.07;
}


void Button::MoveButton(POINTFLOAT coordinates)
{
	vert[0] = vert[9] = coordinates.x;
	vert[1] = vert[4] = coordinates.y;
	vert[3] = vert[6] = vert[0] + size.x;
	vert[7] = vert[10] = vert[1] + size.y;
}
void Button::ResizeButton(GLfloat bSize)
{
	size.x = 0;
	for (int i = 0; i < word.size(); i++)
	{
		size.x += symbolWidth[(unsigned char)word[i]] * symbolSize;
	}
	size.x += 0.04;
	size.y = bSize;
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
	DrawButtonText(tColor);
}
void Button::DrawButtonText(Vector3D tColor)
{
	/*glBindTexture(GL_TEXTURE_2D, text->GetTexture());
	glColor3f(1, 1, 1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3,GL_FLOAT, 0, vertex);
	glTexCoordPointer(2, GL_FLOAT, 0, text->textureCoordinates);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
	*/
	glPushMatrix();
	glTranslatef(vert[0] + 0.02, vert[1] - symbolSize - 0.07, 0);
	glScalef(symbolSize, symbolSize, symbolSize);
	if(haveColor)
		glColor3f(textColor.x, textColor.y, textColor.z);
	else
		glColor3f(tColor.x, tColor.y, tColor.z);
	glBindTexture(GL_TEXTURE_2D, text->GetTexture());
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vert);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	for (int i = 0; i < word.size(); i++)
	{
		FindSymbol(word[i]);
		glVertexPointer(2, GL_FLOAT, 0, textCoordinates);
		glTexCoordPointer(2, GL_FLOAT, 0, symbolsCoordinates);
		glDrawArrays(GL_QUADS, 0, 4);
		glTranslatef(symbolWidth[(unsigned char)word[i]], 0, 0);
	}
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}

void Button::FindSymbol(char symbol)
{
	int x,y;
	GLfloat symbolSize = 1/16.0;
	y = symbol >> 4;
	x = symbol & 0b1111;
	symbolsCoordinates[0] = symbolsCoordinates[6] = x * symbolSize;
	symbolsCoordinates[2] = symbolsCoordinates[4] = x * symbolSize + symbolSize * symbolWidth[(unsigned char)symbol];
	symbolsCoordinates[5] = symbolsCoordinates[7] = y * symbolSize;
	symbolsCoordinates[1] = symbolsCoordinates[3] = y * symbolSize + symbolSize;
	textCoordinates[2] = textCoordinates[4] = symbolWidth[(unsigned char)symbol];
}
void Button::FindSymbolWidth(Texture* texture)
{
	//symbolWidth[(unsigned char)'å'] = 0.6;
	int symbolSize = texture->GetWidth() / 16;
	for (int num = 0; num < 256; num++)
	{
		int x = (num % 16) * symbolSize;
		int y = num / 16 * symbolSize;
		int i;
		unsigned char symbol;
		for (i = x + symbolSize - 1; i > x; i--)
		{
			for (int j = y + symbolSize - 1; j > y; j--)
			{
				symbol = texture->GetData()[(j * texture->GetWidth() + i) * texture->GetBytesNumber()];
				if (symbol > 0)
					break;
			}
			if (symbol > 0)
				break;
		}
		i += symbolSize / 10;
		if (i > x + symbolSize - 1)
			i = x + symbolSize - 1;
		if (num == 32)
			i += x + symbolSize / 2;
		symbolWidth[num] = (i - x) / (GLfloat)symbolSize;
	}
}
GLfloat Button::GetButtonSizeY()
{
	return size.y;
}
GLfloat Button::GetButtonSizeX()
{
	return size.x;
}
GLfloat* Button::GetVertArray()
{
	return vert;
}
void Button::SetNumber(int number)
{
	word = std::to_string(number);
}
bool Button::TestCoordinate(double x, double y)
{
	if (x > vert[0] && x < vert[3])
	{
		if (y < vert[1] && y > vert[7])
		{
			return true;
		}
	}
	return false;
}