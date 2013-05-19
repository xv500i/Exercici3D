
#pragma once

#include "Camera.h"


/* Camera used for debugging reasons, independent from the player movement */
class FreeCamera : public Camera
{
private:
	float xzAngle;

public:
	FreeCamera(void);
	virtual ~FreeCamera(void);

	/* Panning */
	void pan(float panX, float panZ);

	/* Rotating */
	void rotate(float angle);
};