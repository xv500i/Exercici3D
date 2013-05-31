
#include "HUDElement.h"
#include <gl/glut.h>


HUDElement::HUDElement() {}

HUDElement::HUDElement(int x, int y, int width, int height, int textureIndex) 
	: x(x), y(y), width(width), height(height), textureIndex(textureIndex) 
{}

HUDElement::~HUDElement(void) {}


/* Render */
void HUDElement::render(GameData &data)
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, data.getTextureID(textureIndex));
		glBegin(GL_QUADS);
			// Top-left
			glTexCoord2f(0.0f, 0.0f);
			glVertex2i(x, y);
			// Top-right
			glTexCoord2f(1.0f, 0.0f);
			glVertex2i(x + width, y);
			// Bottom-right
			glTexCoord2f(1.0f, 1.0f);
			glVertex2i(x + width, y + height);
			// Bottom-left
			glTexCoord2f(0.0f, 1.0f);
			glVertex2i(x, y + height);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}


/* Setters */
void HUDElement::setTextureIndex(int newTextureIndex)
{
	textureIndex = newTextureIndex;
}


/* Getters */
int HUDElement::getTextureIndex()
{
	return textureIndex;
}

void HUDElement::getPosition(int &x, int &y)
{
	x = this->x;
	y = this->y;
}

void HUDElement::getSize(int &width, int &height)
{
	width = this->width;
	height = this->height;
}