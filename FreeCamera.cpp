
#include "FreeCamera.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Utility.h"


FreeCamera::FreeCamera(void) : xzAngle(0.0f) {}

FreeCamera::~FreeCamera(void) {}


/* Panning */
void FreeCamera::pan(float panX, float panZ)
{
	float eyeX, eyeY, eyeZ;
	float centerX, centerY, centerZ;
	getEyePosition(eyeX, eyeY, eyeZ);
	getReferencePoint(centerX, centerY, centerZ);

	float deltaX = panX*cos(degreesToRadians(xzAngle)) + panZ*cos(degreesToRadians(xzAngle + 90.0f));
	float deltaZ = panX*sin(degreesToRadians(xzAngle)) + panZ*sin(degreesToRadians(xzAngle + 90.0f));
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
	float eyeX, eyeY, eyeZ;
	float centerX, centerY, centerZ;
	getEyePosition(eyeX, eyeY, eyeZ);
	getReferencePoint(centerX, centerY, centerZ);

	float distance = distance2D(eyeX, eyeZ, centerX, centerZ);
	centerX += distance*(cos(degreesToRadians(xzAngle + angle)) - cos(degreesToRadians(xzAngle)));
	centerZ += distance*(sin(degreesToRadians(xzAngle + angle)) - sin(degreesToRadians(xzAngle)));
	xzAngle += angle;

	setReferencePoint(centerX, centerY, centerZ);
}