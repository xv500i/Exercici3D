
#include "FreeCamera.h"
#define _USE_MATH_DEFINES
#include <math.h>


FreeCamera::FreeCamera(void) : xzAngle(0.0f) {}

FreeCamera::~FreeCamera(void) {}


/* Panning */
void FreeCamera::pan(float panX, float panZ)
{
	float eyeX, eyeY, eyeZ;
	float centerX, centerY, centerZ;
	getEyePosition(eyeX, eyeY, eyeZ);
	getReferencePoint(centerX, centerY, centerZ);

	// TODO: TEST
	float deltaX = panX*cos(xzAngle*(float)M_PI/180.0f) + panZ*sin(xzAngle*(float)M_PI/180.0f);
	float deltaZ = panZ*cos(xzAngle*(float)M_PI/180.0f) + panX*sin(xzAngle*(float)M_PI/180.0f);

	eyeX += deltaX;
	centerX += deltaX;
	eyeZ += deltaZ;
	centerZ += deltaZ;

	setEyePosition(eyeX, eyeY, eyeZ);
	setReferencePoint(centerX, centerY, centerZ);
}

/* Rotating */
void FreeCamera::rotate(float angle)
{

}