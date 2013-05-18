
#include "ThirdPersonCamera.h"
#include "Globals.h"


ThirdPersonCamera::ThirdPersonCamera(void) {}

ThirdPersonCamera::~ThirdPersonCamera(void) {}


void ThirdPersonCamera::use()
{
	// TODO: NO ESTA ACABAT
	float centerX, centerY, centerZ;
	getReferencePoint(centerX, centerY, centerZ);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -5.0f);
	glTranslatef(centerX, centerY, centerZ);
	glMatrixMode(GL_MODELVIEW);
}