#pragma once
#include "Camera.h"

class Enemy : public Alive
{
	Camera* camera;
	GLfloat attackDistance;
	static std::chrono::steady_clock::duration attackDeltaTime;
public:
	Enemy(bool gravInfluence, GLfloat obHight, Vector3D obStartPosition, unsigned int obColor, GLfloat obStartAngle, GLfloat obSpeed, GLfloat obAngleSpeed, GLfloat obHealthPoint, GLfloat obDamage,Shape* pShape, Camera* pCamera)
		: Alive(gravInfluence, obHight, obStartPosition, obColor, obStartAngle, obSpeed, obAngleSpeed, obHealthPoint, obDamage, pShape)
	{
		camera = pCamera;
		attackDistance = 10;
	}
	void movementCheck() override
	{
		/*Vector3D nextPosition = position;
		nextPosition += movement;
		Vector3D fromCamera = { nextPosition.x - camera->position.x, nextPosition.y - camera->position.y, 0 };
		GLfloat distance = CreateModul(fromCamera);
		if (distance < attackDistance - 0.01)
		{
			movement = { 0,0,0 };
		}
		else
		{
			fromCamera *= -1;
			Normalize(fromCamera);
			fromCamera *= attackDistance - 0.1;
			movement -= fromCamera;
		}*/
		Vector3D distance = { camera->position.x - position.x, camera->position.y - position.y, 0 };
		rotationAngle = toDegrees(FindAngle({ 0,1,0 }, distance));
		GLfloat modulDistance = CreateModul(distance);
		if (modulDistance < attackDistance)
		{
			movement = { 0,0,0 };
		}
		else if (modulDistance < attackDistance - 0.1 + CreateModul(movement))
		{
			Normalize(distance);
			distance *= attackDistance - 0.1;
			movement -= distance;
		}
	}
	void CreateMovement() override
	{
		movement = { camera->position.x - position.x, camera->position.y - position.y, 0 };
	}
	void CheckAttack() override
	{
		Vector3D distance = { camera->position.x - position.x, camera->position.y - position.y, 0 };
		if (CreateModul(distance) < attackDistance && attackTime + attackDeltaTime < std::chrono::steady_clock::now())
		{
			camera->TakeDamage(damage);
			attackTime = std::chrono::steady_clock::now();
		}
	}
	void Die() override
	{
		MustDeletedR();
		MustDeletedU();
	}
};