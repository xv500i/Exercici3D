
#include "Utility.h"


float radiansToDegrees(float angleInRadians)
{
	return angleInRadians*180.0f/(float)M_PI;
}

float degreesToRadians(float angleInDegrees)
{
	return angleInDegrees*(float)M_PI/180.0f;
}