#pragma once

#include <vector>
#include "Vector3D.h"
#include "GameObject.h"


class PixelBasedFloor
{
public:
	PixelBasedFloor(void);
	PixelBasedFloor(char *filename, float centerX, float centerZ, float distanceBetweenPixels = 0.2f, float maxHeight = 6.0f, float minHeigth = 0.0f);
	~PixelBasedFloor(void);
	void render(GameData &data) const;
	int getPixelsWidth() const;
	int getPixelsHeigth() const;
	float getDistanceBetweenPixels() const;
	float getHeightAt(float x, float z);
	void getPerpendicularVector(Vector3D &v, float x, float z);
private:
	std::vector< std::vector<float> > points;
	float distanceBetweenPixels;
	float maxHeight;
	float minHeigth;
	float centerX;
	float centerZ;
};

