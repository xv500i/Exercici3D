
#include "PixelBasedFloor.h"
#include "Texture.h"
#include <iostream>
#include "Vector3D.h"
#include <gl/glut.h>
#include <windows.h>


PixelBasedFloor::PixelBasedFloor() {}

PixelBasedFloor::PixelBasedFloor(int texId, char *filename, float centerX, float centerZ, float distanceBetweenPixels, float maxHeight, float minHeigth)
	: textureId(texId), centerX(centerX), centerZ(centerZ), distanceBetweenPixels(distanceBetweenPixels), maxHeight(maxHeight), minHeigth(minHeigth)
{
	Texture *tex = new Texture();
	tex->getMapPixelsHeight(filename, points, GL_RGBA);
	floorCreated = false;
	delete tex;
}

PixelBasedFloor::~PixelBasedFloor(void) {}


void PixelBasedFloor::render(GameData &data)
{	
	if (!floorCreated) {
		createFloor(data);
		floorCreated = true;
	}

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, data.getTextureID(textureId));
		glRotatef(90.0, 0.0f, 1.0f, 0.0f);
		glScalef(-1.0f, 1.0f, 1.0f);
		glCallList(FLOOR);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
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
	unsigned int i = max( min(roundedX , points.size()-1), 0);
	unsigned int j = max( min(roundedZ , points[0].size()-1), 0);
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


/* Displaylist creation */
void PixelBasedFloor::createFloor(GameData &data)
{
	// Map coordinates
	float initialX = -(distanceBetweenPixels * ( (float)getPixelsWidth() / 2));
	float initialZ = -(distanceBetweenPixels * ( (float)getPixelsHeigth() / 2));
	float factor = maxHeight - minHeigth;

	// Texture coordinates
	int texWidth, texHeight;
	float s, t;
	data.getTextureSizeInPixels(textureId, &texWidth, &texHeight);
	float offsetS = 1.0f/(float)getPixelsWidth();
	float offsetT = 1.0f/(float)getPixelsHeigth();

	glNewList(FLOOR, GL_COMPILE);
		glBegin(GL_QUADS);
			for (int i = 0; i < getPixelsHeigth(); i++) {
				float auxX = initialX;
				for (int j = 0; j < getPixelsWidth(); j++) {
					s = offsetS*(float)j;
					t = offsetT*(float)i;

					// Top-left
					glTexCoord2f(s, t);
					glVertex3f(auxX, points[i][j]*factor, initialZ);
					// Top-right
					glTexCoord2f(s + offsetS, t);
					glVertex3f(auxX+distanceBetweenPixels, points[i][j+1]*factor, initialZ);
					// Bottom-right
					glTexCoord2f(s + offsetS, t + offsetT);
					glVertex3f(auxX+distanceBetweenPixels, points[i+1][j+1]*factor, initialZ+distanceBetweenPixels);
					// Bottom-left
					glTexCoord2f(s, t + offsetT);
					glVertex3f(auxX, points[i+1][j]*factor, initialZ+distanceBetweenPixels);
					
					auxX += distanceBetweenPixels;
				}
				initialZ += distanceBetweenPixels;
			}
		glEnd();
	glEndList();
}