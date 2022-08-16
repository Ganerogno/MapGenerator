#include "Enemy.h"
Enemy::Enemy(bool gravInfluence, GLfloat obHight, Vector3D obStartPosition, unsigned int obColor, GLfloat obStartAngle, GLfloat obSpeed, GLfloat obAngleSpeed, GLfloat obHealthPoint, GLfloat obDamage, Shape* pShape, Camera* pCamera)
	: Alive(gravInfluence, obHight, obStartPosition, obColor, obStartAngle, obSpeed, obAngleSpeed, obHealthPoint, obDamage, pShape)
{
	camera = pCamera;
	attackDistance = 5;
}
void Enemy::movementCheck()
{
	Vector3D distance = { camera->GetPosition().x - position.x, camera->GetPosition().y - position.y, 0 };
	rotationAngle = toDegrees(FindAngle({ 0,1,0 }, distance));
	GLfloat modulDistance = CreateModul(distance);
	if (modulDistance < attackDistance)
	{
		movement = { 0,0,0 };
	}
}
void Enemy::CreateMovement()
{
	movement = { camera->GetPosition().x - position.x, camera->GetPosition().y - position.y, 0 };
}
void Enemy::CheckAttack()
{
	Vector3D distance = { camera->GetPosition().x - position.x, camera->GetPosition().y - position.y, 0 };
	if (CreateModul(distance) < attackDistance && attackTime + attackDeltaTime < std::chrono::steady_clock::now())
	{
		camera->TakeDamage(damage);
		attackTime = std::chrono::steady_clock::now();
	}
}
void Enemy::Die()
{
	MustDeletedR();
	MustDeletedU();
}