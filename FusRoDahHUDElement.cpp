
#include "FusRoDahHUDElement.h"


FusRoDahHUDElement::FusRoDahHUDElement(void) {}

FusRoDahHUDElement::FusRoDahHUDElement(int x, int y, int width, int height, int textureIndex) : HUDElement(x, y, width, height, textureIndex) {}

FusRoDahHUDElement::~FusRoDahHUDElement(void) {}


/* Update */
void FusRoDahHUDElement::update(int fusRoDahTics)
{
	this->fusRoDahTics = fusRoDahTics;
}


/* Render */
void FusRoDahHUDElement::render(GameData &data)
{
	// Get parameters
	int x, y, width, height;
	getPosition(x, y);
	getSize(width, height);
	int textureIndex = getTextureIndex();

	float quadCoord = (float)((1000 - fusRoDahTics)*width)/1000.0f;
	float texCoord = (float)(1000 - fusRoDahTics)/1000.0f;

	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, data.getTextureID(textureIndex));
		// Texture quad
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(x + MARGIN, y + MARGIN);
			glTexCoord2f(texCoord, 0.0f);
			glVertex2f(x + quadCoord - MARGIN, y + MARGIN);
			glTexCoord2f(texCoord, 1.0f);
			glVertex2f(x + quadCoord - MARGIN, y + height - MARGIN);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(x + MARGIN, y + height - MARGIN);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		// Black quad
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
			glVertex2i(x, y);
			glVertex2i(x + width, y);
			glVertex2i(x + width, y + height);
			glVertex2i(x, y + height);
		glEnd();
	glPopMatrix();
}
