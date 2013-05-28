
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


/* Input */
void CameraHandler::resolveInput(InputHandler &input)
{
	if (input.keyIsDown(input.getKey(THIRD_PERSON_CAMERA))) setActiveCamera(THIRD_PERSON);
	else if (input.keyIsDown(input.getKey(FREE_CAMERA)))	setActiveCamera(FREE);
	else if (input.keyIsDown(input.getKey(STATIC1_CAMERA))) setActiveCamera(STATIC1);
	else if (input.keyIsDown(input.getKey(STATIC2_CAMERA))) setActiveCamera(STATIC2);
	else if (input.keyIsDown(input.getKey(STATIC3_CAMERA))) setActiveCamera(STATIC3);
	else if (input.keyIsDown(input.getKey(STATIC4_CAMERA))) setActiveCamera(STATIC4);
}


/* Free camera */
void CameraHandler::resolveFreeCameraInput(InputHandler &input)
{		
	float panX = 0.0f;
	float panZ = 0.0f;
	float angle = 0.0f;
	if (input.keyIsDown(input.getKey(CAMERA_MOVE_FORWARD)))	 panX += 1.0f;
	if (input.keyIsDown(input.getKey(CAMERA_MOVE_BACKWARD))) panX -= 1.0f;
	if (input.keyIsDown(input.getKey(CAMERA_MOVE_LEFT)))	 panZ -= 1.0f;
	if (input.keyIsDown(input.getKey(CAMERA_MOVE_RIGHT)))	 panZ += 1.0f;
	if (input.keyIsDown(input.getKey(CAMERA_ROTATE_LEFT)))	 angle -= 3.0f;
	if (input.keyIsDown(input.getKey(CAMERA_ROTATE_RIGHT)))  angle += 3.0f;
	panFreeCamera(panX, panZ);
	rotateFreeCamera(angle);
}

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

float CameraHandler::getActiveCameraYAngle()
{
	switch (activeCamera) {
	case THIRD_PERSON:	return thirdPersonCamera.getXZDirection();
	case FREE:			return freeCamera.getXZDirection();
	// TODO: HARDCODED
	case STATIC1:		return 180.0f;
	case STATIC2:		return 270.0f;
	case STATIC3:		return 0.0f;
	case STATIC4:		return 90.0f;
	default: break;
	}
	return 0.0f;
}


/* Set active camera */
void CameraHandler::setActiveCamera(CameraType newActiveCamera)
{
	activeCamera = newActiveCamera;
}