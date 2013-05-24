
#include "CameraHandler.h"


const float CameraHandler::STATIC_CAMERA_EYEY = 15.0f;
const float CameraHandler::STATIC_CAMERA_EYEXZ = 30.0f;


CameraHandler::CameraHandler(void) : activeCamera(THIRD_PERSON)
{
	resetDefaults();
}

CameraHandler::~CameraHandler(void) {}


/* Reset all cameras */
void CameraHandler::resetDefaults()
{
	/* Static cameras */
	staticCamera1.setEyePosition(STATIC_CAMERA_EYEXZ, STATIC_CAMERA_EYEY, 0.0f);
	staticCamera2.setEyePosition(0.0f, STATIC_CAMERA_EYEY, STATIC_CAMERA_EYEXZ);
	staticCamera3.setEyePosition(-STATIC_CAMERA_EYEXZ, STATIC_CAMERA_EYEY, 0.0f);
	staticCamera4.setEyePosition(0.0f, STATIC_CAMERA_EYEY, -STATIC_CAMERA_EYEXZ);

	/* Free camera */
	freeCamera.setEyePosition(-STATIC_CAMERA_EYEXZ, STATIC_CAMERA_EYEY, 0.0f);
}


/* Free camera */
void CameraHandler::panFreeCamera(float panX, float panZ)
{
	freeCamera.pan(panX, panZ);
}

void CameraHandler::rotateFreeCamera(float angle)
{
	freeCamera.rotate(angle);
}


/* Third Person camera */
void CameraHandler::updateThirdPersonCamera(float centerX, float centerY, float centerZ, float xzAngle)
{
	thirdPersonCamera.setReferencePoint(centerX, centerY, centerZ);
	thirdPersonCamera.setXZDirection(xzAngle);
	thirdPersonCamera.update();
}


/* Use the camera */
void CameraHandler::useActiveCamera()
{
	switch (activeCamera) {
	case THIRD_PERSON:	thirdPersonCamera.use(); break;
	case FREE:			freeCamera.use(); break;
	case STATIC1:		staticCamera1.use(); break;
	case STATIC2:		staticCamera2.use(); break;
	case STATIC3:		staticCamera3.use(); break;
	case STATIC4:		staticCamera4.use(); break;
	default: break;
	}
}


/* Get active camera */
CameraType CameraHandler::getActiveCamera()
{
	return activeCamera;
}


/* Set active camera */
void CameraHandler::setActiveCamera(CameraType newActiveCamera)
{
	activeCamera = newActiveCamera;
}