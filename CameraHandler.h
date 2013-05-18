
#pragma once

#include "FirstPersonCamera.h"
#include "ThirdPersonCamera.h"
#include "FreeCamera.h"


enum CameraType {
	FIRST_PERSON,
	THIRD_PERSON,
	FREE,
	STATIC1,
	STATIC2,
	STATIC3,
	STATIC4
};

class CameraHandler
{
private:
	const static float STATIC_CAMERA_EYEY;
	const static float STATIC_CAMERA_EYEXZ;

	//FirstPersonCamera firstPersonCamera;	// NOT USED
	ThirdPersonCamera thirdPersonCamera;	/* Third person camera (the game actual camera) */
	FreeCamera freeCamera;					/* Free camera for debuging purposes */
	
	/* Static cameras */
	Camera staticCamera1;
	Camera staticCamera2;
	Camera staticCamera3;
	Camera staticCamera4;

	CameraType activeCamera;	/* The camera used at the moment */

public:
	CameraHandler(void);
	virtual ~CameraHandler(void);

	/* Reset all cameras */
	void resetDefaults();

	/* Set active camera */
	void setActiveCamera(CameraType newActiveCamera);

	/* Use the camera */
	void useActiveCamera();
};

