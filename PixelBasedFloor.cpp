#include "PixelBasedFloor.h"
#include "cTexture.h"
#include <iostream>

PixelBasedFloor::PixelBasedFloor(void)
{
}

PixelBasedFloor::PixelBasedFloor(char *filename, float centerX, float centerZ, float distanceBetweenPixels, float maxHeight, float minHeigth)
	: centerX(centerX), centerZ(centerZ), distanceBetweenPixels(distanceBetweenPixels), maxHeight(maxHeight), minHeigth(minHeigth)
{
	cTexture *tex = new cTexture();
	tex->getMapPixelsHeight(filename, points, GL_RGBA);
	delete tex;
}

PixelBasedFloor::~PixelBasedFloor(void)
{
}

void PixelBasedFloor::render() const
{
	glDisable(GL_TEXTURE_2D);
	//TODO
	float initialX = -(distanceBetweenPixels * ( (float)getPixelsWidth() / 2));
	float initialZ = -(distanceBetweenPixels * ( (float)getPixelsHeigth() / 2));
	float factor = maxHeight - minHeigth;
	glPushMatrix();
	glRotatef(90.0, 0.0f, 1.0f, 0.0f);
	glScalef(-1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	for (int i = 0; i < getPixelsHeigth(); i++) {
		float auxX = initialX;
		for (int j = 0; j < getPixelsWidth(); j++) {
			if ((j+i)%2 == 0) glColor3f(1.0f, 0.0f, 0.0f);
			else glColor3f(0.0f, 1.0f, 0.0f);
			// FIXME textura
			glVertex3f(auxX, points[i][j]*factor, initialZ);
			glVertex3f(auxX+distanceBetweenPixels, points[i][j+1]*factor, initialZ);
			glVertex3f(auxX+distanceBetweenPixels, points[i+1][j+1]*factor, initialZ+distanceBetweenPixels);
			glVertex3f(auxX, points[i+1][j]*factor, initialZ+distanceBetweenPixels);
			auxX += distanceBetweenPixels;
			
		}
		initialZ += distanceBetweenPixels;
	}
	glEnd();
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

int PixelBasedFloor::getPixelsWidth() const
{
	return (points.size() > 0 ? points[0].size()-1 : 0);
}
	
int PixelBasedFloor::getPixelsHeigth() const
{
	return points.size()-1;
}

float PixelBasedFloor::getDistanceBetweenPixels() const
{
	return distanceBetweenPixels;
}

float PixelBasedFloor::getHeightAt(float x, float z)
{
	float fx = x/distanceBetweenPixels + (points.size()/2);
	float fz = z/distanceBetweenPixels + (points[0].size()/2);
	unsigned int roundedX = (unsigned int)fx;
	unsigned int roundedZ = (unsigned int)fz;
	unsigned int i = max( min (roundedX , points.size()-1), 0);
	unsigned int j = max( min (roundedZ , points[0].size()-1), 0);
	float factor =  (maxHeight - minHeigth);
	float res = minHeigth + points[i][j] * factor;
	// interpolar
	//x
	if (i < points.size() - 1) {
		float decimalX = fx - roundedX;
		float heigthDelta = (points[i+1][j] - points[i][j])*factor;
		res += heigthDelta * decimalX;
	}
	//y
	if (j < points[0].size() - 1) {
		float decimalZ = fz - roundedZ;
		float heigthDelta = (points[i][j+1] - points[i][j])*factor;
		res += heigthDelta * decimalZ;
	}
	return res;
}

void PixelBasedFloor::getPerpendicularVector(Vector3D &v, float x, float y)
{
	float fx = x/distanceBetweenPixels + (points.size()/2);
	float fz = z/distanceBetweenPixels + (points[0].size()/2);
	unsigned int roundedX = (unsigned int)fx;
	unsigned int roundedZ = (unsigned int)fz;
	unsigned int i = max( min (roundedX , points.size()-1), 0);
	unsigned int j = max( min (roundedZ , points[0].size()-1), 0);
	v = Vector3D();
	if (i < points.size() - 1) {
		
	}
	//y
	if (j < points[0].size() - 1) {
		
	}
}
