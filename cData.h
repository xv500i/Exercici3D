#pragma once

#include "cTexture.h"
#include "Globals.h"

//Image array size
#define NUM_IMG		3

//Image identifiers
#define IMG_WALL	0
#define IMG_FLOOR	1
#define IMG_ROOF	2

class cData
{
public:
	cData(void);
	~cData(void);

	int  GetID(int img);
	void GetSize(int img,int *w,int *h);
	bool LoadImage(int img,char *filename,int type = GL_RGBA);

private:
	cTexture texture[NUM_IMG];
};
