
#pragma once

#include "Camera.h"


class FirstPersonCamera : public Camera
{
private:
	float xzAngle, yAngle;		/* Angles that determine the reference point */

public:
	FirstPersonCamera(void);
	virtual ~FirstPersonCamera(void);

	/* Use the camera (gluLookAt) */
	void use();

	/* Setters */
	void setXZDirection(float newXZAngle);
	void setYDirection(float newYAngle);
};

