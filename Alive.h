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
protected:
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
public:
	Alive(bool gravInfluence, GLfloat obHight, Vector3D obStartPosition, unsigned int obColor, GLfloat obStartAngle, GLfloat obSpeed, GLfloat obAngleSpeed, GLfloat obHealthPoint, GLfloat obDamage, Shape* pShape = nullptr);
	virtual void movementCheck();
	void Move();
	virtual void CreateMovement() = 0;
	virtual void TakeDamage(GLfloat damage);
	virtual void CheckAttack() = 0;
	virtual void Die() = 0;
	void UpdateForces();
	void Update() override;
	void Render() override;
	void StopRender() override;
	void ContinueRender() override;
	std::chrono::steady_clock::time_point GetAttackTime();
	GLfloat GetDamage();
	GLfloat GetHealthPoint();
	GLfloat &GetCurrentHP();
	GLfloat GetGrowth();
};