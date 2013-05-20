
#include "FirstPersonCamera.h"
#include <gl/glut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Utility.h"


FirstPersonCamera::FirstPersonCamera(void) : xzAngle(0.0f), yAngle(0.0f) {}

FirstPersonCamera::~FirstPersonCamera(void) {}


void FirstPersonCamera::use()
{
	// Obtain the reference point determined by the angles
	float eyeX, eyeY, eyeZ;
	getEyePosition(eyeX, eyeY, eyeZ);
	float centerX = eyeX + cos(degreesToRadians(xzAngle))*cos(degreesToRadians(yAngle));
	float centerY = eyeY + sin(degreesToRadians(yAngle));
	float centerZ = eyeZ + sin(degreesToRadians(xzAngle))*cos(degreesToRadians(yAngle));
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
	int yAngleModule = (int)yAngle%360;
	if (yAngleModule < 0) yAngleModule += 360;
	if (yAngleModule > 90 && yAngleModule < 270) setUpVector(0.0f, -1.0f, 0.0f);
	else if (yAngleModule < 90 || yAngleModule > 270) setUpVector(0.0f, 1.0f, 0.0f);
}