
#include "Camera.h"
#include <gl/glut.h>


Camera::Camera(void) : eyeX(1.0f), eyeY(0.0f), eyeZ(1.0f), centerX(0.0f), centerY(0.0f), centerZ(0.0f), upX(0.0f), upY(1.0f), upZ(0.0f) {}

Camera::~Camera(void) {}


/* Use the camera (gluLookAt) */
void Camera::use()
{
	gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
}


/* Getters */
void Camera::getEyePosition(float &eyeX, float &eyeY, float &eyeZ)
{
	eyeX = this->eyeX;
	eyeY = this->eyeY;
	eyeZ = this->eyeZ;
}

void Camera::getReferencePoint(float &centerX, float &centerY, float &centerZ)
{
	centerX = this->centerX;
	centerY = this->centerY;
	centerZ = this->centerZ;
}

void Camera::getUpVector(float &upX, float &upY, float &upZ)
{
	upX = this->upX;
	upY = this->upY;
	upZ = this->upZ;
}

float Camera::getXZDirection()
{
	// TODO: Implementar
	return 0.0f;
}


/* Setters */
void Camera::setEyePosition(float newEyeX, float newEyeY, float newEyeZ)
{
	eyeX = newEyeX;
	eyeY = newEyeY;
	eyeZ = newEyeZ;
}

void Camera::setReferencePoint(float newCenterX, float newCenterY, float newCenterZ)
{
	centerX = newCenterX;
	centerY = newCenterY;
	centerZ = newCenterZ;
}

void Camera::setUpVector(float newUpX, float newUpY, float newUpZ)
{
	upX = newUpX;
	upY = newUpY;
	upZ = newUpZ;
}