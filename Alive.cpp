#include "Alive.h"
Alive::Alive(bool gravInfluence, GLfloat obHight, Vector3D obStartPosition, unsigned int obColor, GLfloat obStartAngle, GLfloat obSpeed, GLfloat obAngleSpeed, GLfloat obHealthPoint, GLfloat obDamage, Shape* pShape)
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
void Alive::movementCheck()
{

}
void Alive::Move()
{
	Normalize(movement);
	movement *= speed * 0.016;
	movementCheck();
	position += movement;
	position.x += currentForce.x * 0.016;
	position.y += currentForce.y * 0.016;
	position.z += currentForce.z * 0.016;
	if (gravitationInfluence)
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
void Alive::TakeDamage(GLfloat damage)
{
	currentHP -= damage;
	if (currentHP < 1)
	{
		currentHP = 0;
		Die();
	}
}
void Alive::UpdateForces()
{
	currentForce.x *= 0.95;
	if (currentForce.x < 0.05 && currentForce.x > -0.05)
		currentForce.x = 0;
	currentForce.y *= 0.95;
	if (currentForce.y < 0.05 && currentForce.y > -0.05)
		currentForce.y = 0;
	if (gravitationInfluence)
		currentForce.z -= gravitation;
}
void Alive::Update()
{
	CheckAttack();
	CreateMovement();
	Move();
	UpdateForces();
}
void Alive::Render()
{
	glPushMatrix();
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotationAngle, 0, 0, 1);
	glColor3ub(color, 0, 0);
	shape->Draw();
	glPopMatrix();
}
void Alive::StopRender()
{
	canRender = false;
	StopUpdate();
}
void Alive::ContinueRender()
{
	canRender = true;
	ContinueUpdate();
}
std::chrono::steady_clock::time_point Alive::GetAttackTime()
{
	return attackTime;
}
GLfloat Alive::GetDamage()
{
	return damage;
}
GLfloat Alive::GetHealthPoint()
{
	return healthPoint;
}
GLfloat& Alive::GetCurrentHP()
{
	return currentHP;
}
GLfloat Alive::GetGrowth()
{
	return growth;
}