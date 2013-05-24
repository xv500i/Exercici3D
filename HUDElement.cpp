
#include "HUDElement.h"
#include <gl/glut.h>


HUDElement::HUDElement() {}

HUDElement::HUDElement(int x, int y, int width, int height, int textureIndex) : x(x), y(y), width(width), height(height), textureIndex(textureIndex) {}

HUDElement::~HUDElement(void) {}


/* Render */
void HUDElement::render(GameData &data)
{
	glBindTexture(GL_TEXTURE_2D, data.getTextureID(textureIndex));
	glPushMatrix();
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
}


/* Setters */
void HUDElement::setTextureIndex(int newTextureIndex)
{
	textureIndex = newTextureIndex;
}