#pragma once
#include "Camera.h"

class Enemy : public Alive
{
	Camera* camera;
	GLfloat attackDistance;
	static std::chrono::steady_clock::duration attackDeltaTime;
public:
	Enemy(bool gravInfluence, GLfloat obHight, Vector3D obStartPosition, unsigned int obColor, GLfloat obStartAngle, GLfloat obSpeed, GLfloat obAngleSpeed, GLfloat obHealthPoint, GLfloat obDamage, Shape* pShape, Camera* pCamera);
	void movementCheck() override;
	void CreateMovement() override;
	void CheckAttack() override;
	void Die() override;
};