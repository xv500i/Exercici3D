#pragma once

#include <vector>

class PixelBasedFloor
{
public:
	PixelBasedFloor(void);
	PixelBasedFloor(char *filename, int distanceBetweenPixels = 1.0f);
	~PixelBasedFloor(void);
	void render() const;

private:
	std::vector< std::vector<float> > points;
	float distanceBetweenPixels;
};

