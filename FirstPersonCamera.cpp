
#include "FirstPersonCamera.h"
#include <gl/glut.h>
#define _USE_MATH_DEFINES
#include <math.h>


FirstPersonCamera::FirstPersonCamera(void) : xzAngle(0.0f), yAngle(0.0f) {}

FirstPersonCamera::~FirstPersonCamera(void) {}


void FirstPersonCamera::use()
{
	// Obtain the reference point determined by the angles
	float eyeX, eyeY, eyeZ;
	getEyePosition(eyeX, eyeY, eyeZ);
	float centerX = eyeX + cos(xzAngle)*cos(yAngle);
	float centerY = eyeY + sin(yAngle);
	float centerZ = eyeZ + sin(xzAngle)*cos(yAngle);
	setReferencePoint(centerX, centerY, centerZ);
	
	// Use the camera
	Camera::use();
}

void FirstPersonCamera::setXZDirection(float newXZAngle)
{
	xzAngle = newXZAngle;
}

void FirstPersonCamera::setYDirection(float newYAngle)
{
	yAngle = newYAngle;

	// Change up vector if necessary
	int yAngleDegree = yAngle*(180.0f/M_PI);
	yAngleDegree = yAngleDegree%360;
	if (yAngleDegree < 0) yAngleDegree += 360;
	if (yAngleDegree > 90 && yAngleDegree < 270) setUpVector(0.0f, -1.0f, 0.0f);
	else if (yAngleDegree < 90 || yAngleDegree > 270) setUpVector(0.0f, 1.0f, 0.0f);
}