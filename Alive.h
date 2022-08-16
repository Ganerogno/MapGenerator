#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Math3D.h"
#include "Update.h"
#include "Render.h"
#include "Shape.h"
GLfloat FindZ(GLfloat x, GLfloat y);
class Alive : public RenderItem, public UpdateItem
{
public:
	Shape* shape;
	unsigned int color;
	Vector3D position;
	GLfloat rotationAngle;
	GLfloat angleSpeed;
	Vector3D movement;
	GLfloat growth;
	GLfloat speed;
	GLfloat healthPoint;
	GLfloat currentHP;
	GLfloat statusResist;
	GLfloat damage;
	static GLfloat gravitation;
	bool gravitationInfluence;
	bool jumping;
	GLfloat jumpForce;
	Vector3D currentForce;
	std::chrono::steady_clock::time_point attackTime;
	Alive( bool gravInfluence, GLfloat obHight, Vector3D obStartPosition, unsigned int obColor, GLfloat obStartAngle, GLfloat obSpeed,GLfloat obAngleSpeed, GLfloat obHealthPoint, GLfloat obDamage, Shape* pShape = nullptr)
	{
		gravitationInfluence = gravInfluence;
		growth = obHight;
		position = obStartPosition;
		color = obColor;
		rotationAngle = obStartAngle;
		speed = obSpeed;
		angleSpeed = obAngleSpeed;
		currentHP = healthPoint = obHealthPoint;
		damage = obDamage;
		shape = pShape;
		jumping = false;
		jumpForce = 80;
		currentForce = { 0,0,0 };
		attackTime = std::chrono::steady_clock::now();
	}
	void virtual movementCheck()
	{

	}
	void Move()
	{
		Normalize(movement);
		movement *= speed * 0.016;
		movementCheck();
		position += movement;
		position.x += currentForce.x * 0.016;
		position.y += currentForce.y * 0.016;
		position.z += currentForce.z * 0.016;
		if(gravitationInfluence)
		{
			if (position.x < 0)
				position.x = 0;
			if (position.x > 200)
				position.x = 200;
			if (position.y < 0)
				position.y = 0;
			if (position.y > 200)
				position.y = 200;
			GLfloat z = FindZ(position.x, position.y);
			if (position.z < z + growth)
			{
				position.z = z + growth;
				jumping = false;
				currentForce = { 0,0,0 };
			}
			if (position.z + growth > z && !jumping)
				position.z = z + growth;
		}
	}
	virtual void CreateMovement() = 0;
	virtual void TakeDamage(GLfloat damage)
	{
		currentHP -= damage;
		if (currentHP < 1)
		{
			currentHP = 0;
			Die();
		}
	}
	virtual void CheckAttack() = 0;
	virtual void Die() = 0;
	void UpdateForces()
	{
		currentForce.x *= 0.95;
		if (currentForce.x < 0.05 && currentForce.x > -0.05)
			currentForce.x = 0;
		currentForce.y *= 0.95;
		if (currentForce.y < 0.05 && currentForce.y > -0.05)
			currentForce.y = 0;
		if(gravitationInfluence)
			currentForce.z -= gravitation;
	}
	void Update() override
	{
		CheckAttack();
		CreateMovement();
		Move();
		UpdateForces();
	}
	void Render() override
	{
		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glRotatef(rotationAngle, 0, 0, 1);
		glColor3ub(color, 0, 0);
		shape->Draw();
		glPopMatrix();
	}
	void StopRender() override
	{
		canRender = false;
		StopUpdate();
	}
	void ContinueRender() override
	{
		canRender = true;
		ContinueUpdate();
	}
};