
#include "ThirdPersonCamera.h"
#include "Globals.h"


const float ThirdPersonCamera::Y_OFFSET = 15.0f;
const float ThirdPersonCamera::XZ_OFFSET = 30.0f;


ThirdPersonCamera::ThirdPersonCamera(void) : xzAngle(0.0f) {}

ThirdPersonCamera::~ThirdPersonCamera(void) {}


/* Setters */
void ThirdPersonCamera::setXZDirection(float newXZAngle)
{
	xzAngle = newXZAngle;

	float centerX, centerY, centerZ;
	getReferencePoint(centerX, centerY, centerZ);

	// CHANGE (sin and cos)
	float eyeX = centerX + XZ_OFFSET;
	float eyeY = centerY + Y_OFFSET;
	float eyeZ = centerZ;

	setEyePosition(eyeX, eyeY, eyeZ);
}