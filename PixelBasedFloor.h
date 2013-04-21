#pragma once

#include <vector>

class PixelBasedFloor
{
public:
	PixelBasedFloor(void);
	PixelBasedFloor(char *filename, float centerX, float centerZ, float distanceBetweenPixels = 2.0f, float maxHeight = 2.0f, float minHeigth = 0.0f);
	~PixelBasedFloor(void);
	void render() const;
	int getPixelsWidth() const;
	int getPixelsHeigth() const;
	float getDistanceBetweenPixels() const;
	float getHeightAt(float x, float z);
private:
	std::vector< std::vector<float> > points;
	float distanceBetweenPixels;
	float maxHeight;
	float minHeigth;
	float centerX;
	float centerZ;
};

