
#include "PixelBasedFloor.h"
#include "Texture.h"
#include <iostream>
#include "Vector3D.h"
#include "Globals.h"


PixelBasedFloor::PixelBasedFloor(void)
{
}

PixelBasedFloor::PixelBasedFloor(char *filename, float centerX, float centerZ, float distanceBetweenPixels, float maxHeight, float minHeigth)
	: centerX(centerX), centerZ(centerZ), distanceBetweenPixels(distanceBetweenPixels), maxHeight(maxHeight), minHeigth(minHeigth)
{
	Texture *tex = new Texture();
	tex->getMapPixelsHeight(filename, points, GL_RGBA);
	delete tex;
}

PixelBasedFloor::~PixelBasedFloor(void)
{
}

void PixelBasedFloor::render(GameData *data) const
{
	glEnable(GL_TEXTURE_2D);
	//TODO
	float initialX = -(distanceBetweenPixels * ( (float)getPixelsWidth() / 2));
	float initialZ = -(distanceBetweenPixels * ( (float)getPixelsHeigth() / 2));
	float factor = maxHeight - minHeigth;
	
	float offsetS = 1.0/(float)getPixelsWidth();
	float offsetT = 1.0/(float)getPixelsHeigth();

	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, data->getTextureID(GameData::LEVEL1_TEXTURE_INDEX));
		glRotatef(90.0, 0.0f, 1.0f, 0.0f);
		glScalef(-1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
			for (int i = 0; i < getPixelsHeigth(); i++) {
				float auxX = initialX;
				for (int j = 0; j < getPixelsWidth(); j++) {
					//if ((j+i)%2 == 0) glColor3f(1.0f, 0.0f, 0.0f);
					//else glColor3f(0.0f, 1.0f, 0.0f);
					float s = offsetS*(float)j;
					float t = offsetT*(float)i;

					glTexCoord2f(s, t + offsetT);
					glVertex3f(auxX, points[i][j]*factor, initialZ);

					glTexCoord2f(s + offsetS, t + offsetT);
					glVertex3f(auxX+distanceBetweenPixels, points[i][j+1]*factor, initialZ);

					glTexCoord2f(s + offsetS, t);
					glVertex3f(auxX+distanceBetweenPixels, points[i+1][j+1]*factor, initialZ+distanceBetweenPixels);

					glTexCoord2f(s, t);
					glVertex3f(auxX, points[i+1][j]*factor, initialZ+distanceBetweenPixels);
					
					auxX += distanceBetweenPixels;
				}
				initialZ += distanceBetweenPixels;
			}
		glEnd();
	glPopMatrix();
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

void PixelBasedFloor::getPerpendicularVector(Vector3D &v, float x, float z)
{
	float fx = x/distanceBetweenPixels + (points.size()/2);
	float fz = z/distanceBetweenPixels + (points[0].size()/2);
	unsigned int roundedX = (unsigned int)fx;
	unsigned int roundedZ = (unsigned int)fz;
	unsigned int i = max( min (roundedX , points.size()-2), 0);
	unsigned int j = max( min (roundedZ , points[0].size()-2), 0);
	v = Vector3D();
	float A = points[i][j];
	float B = points[i+1][j];
	float C = points[i][j+1];
	Vector3D v2 = Vector3D(distanceBetweenPixels, B - A, 0);
	Vector3D v1 = Vector3D(0, C - A, distanceBetweenPixels);
	v = *v1.vectorialProduct(v2);
}
