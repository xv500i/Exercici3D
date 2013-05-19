
#include "CameraHandler.h"


const float CameraHandler::STATIC_CAMERA_EYEY = 15.0f;
const float CameraHandler::STATIC_CAMERA_EYEXZ = 30.0f;


CameraHandler::CameraHandler(void) : activeCamera(CameraType::FREE)
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
void CameraHandler::panFreeCamera(float panX, float panY, float panZ)
{
	freeCamera.pan(panX, panY, panZ);
}

/* Use the camera */
void CameraHandler::useActiveCamera()
{
	switch (activeCamera) {
	//case FIRST_PERSON:  firstPersonCamera.use(); break;
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
