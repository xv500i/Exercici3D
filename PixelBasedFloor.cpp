#include "PixelBasedFloor.h"
#include "cTexture.h"

PixelBasedFloor::PixelBasedFloor(void)
{
}

PixelBasedFloor::PixelBasedFloor(char *filename, float centerX, float centerZ, float distanceBetweenPixels, float maxHeight, float minHeigth)
	: centerX(centerX), centerZ(centerZ), distanceBetweenPixels(distanceBetweenPixels), maxHeight(maxHeight), minHeigth(minHeigth)
{
	cTexture *tex = new cTexture();
	tex->getMapPixelsHeight(filename, points, GL_RGB);
	delete tex;
}

PixelBasedFloor::~PixelBasedFloor(void)
{
}

void PixelBasedFloor::render() const
{
	//TODO
	float initialZ = -(distanceBetweenPixels * ( (float)getPixelsWidth() / 2));
	float initialX = -(distanceBetweenPixels * ( (float)getPixelsHeigth() / 2));
	float factor = maxHeight - minHeigth;
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
	// FIXME
	return 0.0f;
}
