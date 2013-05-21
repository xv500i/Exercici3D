
#pragma once

#include "Camera.h"


class ThirdPersonCamera : public Camera
{
private:
	/* Distance between the camera and the player */
	const static float Y_OFFSET;
	const static float XZ_OFFSET;

	float xzAngle;	/* Angle that determines the direction on the xz plan */

public:
	ThirdPersonCamera(void);
	virtual ~ThirdPersonCamera(void);

	/* Update */
	void update();

	/* Setters */
	void setXZDirection(float newXZAngle);
};