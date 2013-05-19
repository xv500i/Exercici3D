
#include "FreeCamera.h"


FreeCamera::FreeCamera(void) {}

FreeCamera::~FreeCamera(void) {}


/* Panning */
void FreeCamera::pan(float panX, float panY, float panZ)
{
	float eyeX, eyeY, eyeZ;
	float centerX, centerY, centerZ;
	getEyePosition(eyeX, eyeY, eyeZ);
	getReferencePoint(centerX, centerY, centerZ);

	eyeX += panX;
	centerX += panX;
	eyeY += panY;
	centerY += panY;
	eyeZ += panZ;
	centerZ += panZ;

	setEyePosition(eyeX, eyeY, eyeZ);
	setReferencePoint(centerX, centerY, centerZ);
}