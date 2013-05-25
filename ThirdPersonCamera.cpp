
#include "ThirdPersonCamera.h"
#include <gl/glut.h>
#include <cmath>
#include "Utility.h"


const float ThirdPersonCamera::Y_OFFSET = 7.0f;
const float ThirdPersonCamera::XZ_OFFSET = -25.0f;


ThirdPersonCamera::ThirdPersonCamera(void) : xzAngle(0.0f) {}

ThirdPersonCamera::~ThirdPersonCamera(void) {}


/* Update */
void ThirdPersonCamera::update()
{
	float centerX, centerY, centerZ;
	getReferencePoint(centerX, centerY, centerZ);

	float eyeX = centerX + XZ_OFFSET*cos(degreesToRadians(xzAngle));
	float eyeY = centerY + Y_OFFSET;
	float eyeZ = centerZ + XZ_OFFSET*sin(degreesToRadians(xzAngle));

	setEyePosition(eyeX, eyeY, eyeZ);
}

/* Setters */
void ThirdPersonCamera::setXZDirection(float newXZAngle)
{
	xzAngle = newXZAngle;
}