#pragma once
#include <glad/glad.h>
#include "Math3D.h"
#include "Menu.h"
#include "Camera.h"

class UI : public RenderItem
{
	Camera* camera;
	Vector3D aimColor;
	int aimWidth;
	Button* button;
public:
	UI(Camera* pCamera, Vector3D color, int lineWidth, Button* timerText)
	{
		camera = pCamera;
		aimColor = color;
		aimWidth = lineWidth;
		button = timerText;
		button->MoveButton({ -button->symbolWidth[(unsigned char)"0"] * 0.07f, 0.9});
		button->ResizeButton(0.2f);
	}
	void Render() override
	{
		glDepthMask(GL_FALSE);
		glPushMatrix();
		glLoadIdentity();
		glLineWidth(aimWidth);
		glBegin(GL_LINES);
		glColor3f(aimColor.x, aimColor.y, aimColor.z);
		glVertex3f(0.0f, 0.05f, 0.0f);
		glVertex3f(0.0f, 0.01f, 0.0f);
		glVertex3f(0.0f, -0.05f, 0.0f);
		glVertex3f(0.0f, -0.01f, 0.0f);
		glVertex3f(0.05f, 0.0f, 0.0f);
		glVertex3f(0.01f, 0.0f, 0.0f);
		glVertex3f(-0.05f, 0.0f, 0.0f);
		glVertex3f(-0.01f, 0.0f, 0.0f);
		glEnd();
		glBegin(GL_QUADS);
		glColor3f(1, 0, 0);
		glVertex3f(0.4, -0.8, 0.0);
		glVertex3f(0.8,-0.8,0.0);
		glVertex3f(0.8,-0.9,0.0);
		glVertex3f(0.4,-0.9,0.0);
		glColor3f(0, 1, 0);
		glVertex3f(0.4, -0.8, 0.0);
		glVertex3f(0.4 + 0.4 * camera->currentHP / 100, -0.8, 0.0);
		glVertex3f(0.4 + 0.4 * camera->currentHP / 100, -0.9, 0.0);
		glVertex3f(0.4, -0.9, 0.0);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glColor3f(0, 0, 0);
		glVertex3f(0.4, -0.8, 0.0);
		glVertex3f(0.8, -0.8, 0.0);
		glVertex3f(0.8, -0.9, 0.0);
		glVertex3f(0.4, -0.9, 0.0);
		glEnd();
		if (camera->GetWavesTimer() != -1)
		{
			button->SetNumber(camera->GetWavesTimer());
			button->DrawButtonText({ 1,1,1 });
		}
		glPopMatrix();
		glDepthMask(GL_LESS);
	}
	bool GetCanRender() override
	{
		return camera->GetCanRender();
	}
	bool GetMustDeletedR() override
	{
		return ((RenderItem*)camera)->GetMustDeletedR();
	}
};