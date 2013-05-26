
#include "Texture.h"
#include <iostream>
#include <sstream>
#include <Windows.h>


Texture::Texture(void) {}

Texture::~Texture(void) {}


/* Loading */
bool Texture::load(const char *filename, const char *ext, int type, int wraps, int wrapt, int magf, int minf, bool mipmap)
{
	// Open the file
	std::stringstream ss;
	ss << filename << ext;
	corona::Image* img = corona::OpenImage(ss.str().c_str());

	int components;
	if (type == GL_RGB) components = 3;
	else if (type == GL_RGBA) components = 4;
    else return false;

	if (img == NULL) {
		std::cout << "Error carregant la textura " << filename << ext << std::endl;
		return false;
	}

	// Get the image width and height
	widthInPixels = img->getWidth();
	heightInPixels = img->getHeight();

	// Generate the texture
	glGenTextures(1, &id);				// Generate 1 texture name
	glBindTexture(GL_TEXTURE_2D, id);	// Active the texture id with the GL_TEXTURE_2D bound

	// Texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wraps);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapt);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magf);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minf);

	// Texture loading
	if (!mipmap) glTexImage2D(GL_TEXTURE_2D, 0, components, widthInPixels, heightInPixels, 0, type, GL_UNSIGNED_BYTE, img->getPixels());
	else gluBuild2DMipmaps(GL_TEXTURE_2D, components, widthInPixels, heightInPixels, type, GL_UNSIGNED_BYTE, img->getPixels());
	return true;
}

bool Texture::getMapPixelsHeight(char *filename, std::vector< std::vector<float> > &pixels, int type)
{
	corona::Image* img;
	int components;

	img = corona::OpenImage(filename);
	if(type==GL_RGB)
	{
		//img = corona::OpenImage(filename,corona::PF_R8G8B8);
		components = 3;
	}
	else if(type==GL_RGBA)
	{
		//img = corona::OpenImage(filename,corona::PF_R8G8B8A8);
		components = 4;
	}
	else return false;

	if(img==NULL) return false;

	widthInPixels  = img->getWidth();
	heightInPixels = img->getHeight();

	srand (3218551);
	pixels = std::vector< std::vector<float> >(heightInPixels, std::vector<float>(widthInPixels));
	byte *p = (byte*) img->getPixels();
	for (int i = 0; i < heightInPixels; i++) {
		for (int j = 0; j < widthInPixels; j++) {
			unsigned int red = (unsigned int) *p++;
			unsigned int green = (unsigned int) *p++;
			unsigned int blue = (unsigned int) *p++;
			// skip alpha channel
			if (components == 4) p++;
			float maxValue = 256;
			float value = (red/maxValue)/3 + (green/maxValue)/3 + (blue/maxValue)/3;
			pixels[i][j] = value;//((float) rand()) / (float) RAND_MAX; // BETWEEN 0 AND 1
		}
	}
	return true;
}

/* Getters */
int Texture::getID() 
{
	return id;
}
	
void Texture::getSizeInPixels(int *width, int *height)
{
	*width = this->widthInPixels;
	*height = this->heightInPixels;
}