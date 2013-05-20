
#include "Utility.h"


float radiansToDegrees(float angleInRadians)
{
	return angleInRadians*180.0f/(float)M_PI;
}

float degreesToRadians(float angleInDegrees)
{
	return angleInDegrees*(float)M_PI/180.0f;
}

float distance2D(float x1, float y1, float x2, float y2)
{
	float difX = x1 - x2;
	float difY = y1 - y2;
	return sqrt(difX*difX + difY*difY);
}