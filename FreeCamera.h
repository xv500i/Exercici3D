
#pragma once

#include "Camera.h"

/* Camera used for debugging reasons, independent from the player movement */
class FreeCamera : public Camera
{
public:
	FreeCamera(void);
	virtual ~FreeCamera(void);

	void pan(float panX, float panY, float panZ);
};

