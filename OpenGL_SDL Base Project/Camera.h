#ifndef _CAMERA_H
#define _CAMERA_H

#include "Commons.h"
#include <SDL.h>
#include "object3DS.h"


class Camera

{

public :
	Camera();
	~Camera();
	static		Camera* GetInstance();
	void		Update(float deltaTime, SDL_Event e);
	void		Render();
	void		SetForward(Vector3D newForward);
	void		SetPos(Vector3D eye, Vector3D to, Vector3D up);

private:
	Vector3D position = Vector3D(0.0f, 0.0f, 0.0f);
	Vector3D forward = Vector3D(0.0f,0.0f,0.0f);
	Vector3D up = Vector3D(0.0f, 0.0f, 0.0f);
	Vector3D right = Vector3D(0.0f, 0.0f, 0.0f);

	float yaw = 3.14f;

	float pitch = 0.0f;
};

#endif //_CAMERA_H