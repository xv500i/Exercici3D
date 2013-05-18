
#pragma once


class Camera
{
private:
	float eyeX, eyeY, eyeZ;				/* Eye point position */
	float centerX, centerY, centerZ;	/* Reference point position	(where to look)	*/
	float upX, upY, upZ;				/* UP vector direction */

public:
	Camera(void);
	virtual ~Camera(void);

	/* Use the camera (gluLookAt) */
	virtual void use();

	/* Getters */
	void getEyePosition(float &eyeX, float &eyeY, float &eyeZ);
	void getReferencePoint(float &centerX, float &centerY, float &centerZ);
	void getUpVector(float &upX, float &upY, float &upZ);

	/* Setters */
	void setEyePosition(float newEyeX, float newEyeY, float newEyeZ);
	void setReferencePoint(float newCenterX, float newCenterY, float newCenterZ);
	void setUpVector(float newUpX, float newUpY, float newUpZ);
};

