#include "Camera.h"

Camera::Camera(bool gravInfluence, GLfloat obHight, Vector3D obStartPosition, unsigned int obColor, GLfloat obStartAngle, GLfloat obSpeed, GLfloat obAngleSpeed, GLfloat obHealthPoint, GLfloat obDamage, GLFWwindow* glWindow)
	: Alive(gravInfluence, obHight, obStartPosition, obColor, obStartAngle, obSpeed, obAngleSpeed, obHealthPoint, obDamage)
{
	angle = { 90, 0, obStartAngle };
	window = glWindow;
	baze = last = { 500,500 };
	glfwSetCursorPos(window, baze.x, baze.y);
	cursorUpdate = false;
	sensitivity = 0.5;
}
Vector2D Camera::GetBazeCoordinate()
{
	return baze;
}
void Camera::SetBazeCoordinate()
{
	last.x = baze.x;
	last.y = baze.y;
}
bool Camera::GetCursorUpdate()
{
	return cursorUpdate;
}
void Camera::SetCursorUpdate(bool flag)
{
	cursorUpdate = flag;
}
void Camera::Rotate()
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	x -= last.x;
	y -= last.y;
	y = -y;
	angle.z += x * sensitivity;
	angle.x += y * sensitivity;
	if (angle.x < 0)
		angle.x = 0;
	if (angle.x > 180)
		angle.x = 180;
	last.x += x;
	last.y -= y;
	if (last.x > 900 || last.x < 100)
		cursorUpdate = true;
	if (last.y > 900 || last.y < 100)
		cursorUpdate = true;
	if (cursorUpdate)
	{
		while (cursorUpdate)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		last.x = baze.x;
		last.y = baze.y;
	}


}
void Camera::CreateMovement()
{
	movement = { 0,0,0 };
	Rotate();
	if (!jumping)
	{
		if (keyboardKeys[GLFW_KEY_W])
		{
			movement.x += sin(angle.z / 180 * M_PI);
			movement.y += cos(angle.z / 180 * M_PI);
		}
		if (keyboardKeys[GLFW_KEY_A])
		{
			movement.x -= sin(angle.z / 180 * M_PI + M_PI / 2);
			movement.y += cos(-angle.z / 180 * M_PI + M_PI / 2);
		}
		if (keyboardKeys[GLFW_KEY_S])
		{
			movement.x -= sin(angle.z / 180 * M_PI);
			movement.y -= cos(angle.z / 180 * M_PI);
		}
		if (keyboardKeys[GLFW_KEY_D])
		{
			movement.x += sin(angle.z / 180 * M_PI + M_PI / 2);
			movement.y -= cos(-angle.z / 180 * M_PI + M_PI / 2);
		}
		if (keyboardKeys[GLFW_KEY_SPACE])
		{
			if (gravitationInfluence)
			{
				currentForce = movement;
				currentForce *= 100;
				currentForce.z += jumpForce;
				jumping = true;
			}
			else
			{
				movement.z++;
			}
		}
	}
	if (keyboardKeys[GLFW_KEY_X])
	{
		movement.z--;
	}
}
void Camera::CheckAttack()
{

}
void Camera::Die()
{
	dead = true;
	StopUpdate();
}
void Camera::SetWavesTimer(int time)
{
	wavesTimer = time;
}
int Camera::GetWavesTimer()
{
	return wavesTimer;
}
Vector3D Camera::GetPosition()
{
	return position;
}