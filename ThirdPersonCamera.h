
#pragma once

#include "Camera.h"


class ThirdPersonCamera : public Camera
{
public:
	ThirdPersonCamera(void);
	virtual ~ThirdPersonCamera(void);

	/* Use the camera (gluLookAt) */
	void use();
};

