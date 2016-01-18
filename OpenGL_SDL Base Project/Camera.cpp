#include "Camera.h"
#include "Constants.h"
#include <math.h>
#include "../gl/glut.h"

static Camera* instance = 0;
static float moveSpeed = 0.3f;
static float lookSpeed = 0.3f;

Camera::Camera()
{
}

Camera::~Camera()
{
}

Camera* Camera::GetInstance()
{
	if (instance == 0)
	{
		instance = new Camera();
	}

	return instance;

}

void Camera::SetPos(Vector3D eye, Vector3D to, Vector3D newUp)
{
	position = eye;
	forward = to;
	up = newUp;
	

}

void Camera::Update(float deltaTime, SDL_Event e)
{
	

	right = Vector3D(
		sin(yaw - 3.14f / 2.0f),
		0,
		cos(yaw - 3.14f / 2.0f));

	up = Vector3D((right.y*forward.z) - (right.z*forward.y), (right.z*forward.x) - (right.x*forward.z), (right.x*forward.y) - (right.y*forward.x));

	//Event Handler
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			//move forwards
			position += forward * moveSpeed;
			break;

		case SDLK_s:
			position -= forward * moveSpeed;
			break;

		case SDLK_d:
			position += right * moveSpeed;
			break;

		case SDLK_a:
			position -= right * moveSpeed;
			break;

		case SDLK_UP:
			pitch += lookSpeed;
			break;

		case SDLK_DOWN:
			pitch -= lookSpeed;
			break;

		case SDLK_RIGHT:
			yaw += lookSpeed;
			break;

		case SDLK_LEFT:
			yaw -= lookSpeed;
			break;


		}
	}
}

void Camera::SetForward(Vector3D newForward)
{
	forward = newForward;
}

void Camera::Render(){
	Vector3D lookatPos = position + forward;//make sure looking at a point in front of camera
	glLoadIdentity();
	gluLookAt(position.x, position.y, position.z, lookatPos.x, lookatPos.y, lookatPos.z, up.x, up.y, up.z);
}