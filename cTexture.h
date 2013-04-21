#pragma once

#pragma comment(lib,"corona")

#include "Globals.h"
#include <vector>
class cTexture
{
public:
	cTexture(void);
	~cTexture(void);

	bool Load(char *filename,int type = GL_RGBA,int wraps = GL_REPEAT,int wrapt = GL_REPEAT,
			  int magf = GL_LINEAR,int minf = GL_LINEAR,bool mipmap = true);
	int  GetID();
	void GetSize(int *w,int *h);
	bool getMapPixelsHeight(char *filename, std::vector< std::vector<float> > &pixels, int type = GL_RGB);
private:
	GLuint id;
	int width;
	int height;
};
