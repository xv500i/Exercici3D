#include "cScene.h"
#include "Globals.h"

cScene::cScene(void) {}
cScene::~cScene(void){}

void cScene::Draw(cData *Data)
{
	float d  = SCENE_DEPTH/2.0f,
		  w  = SCENE_WIDTH/2.0f,
		  h  = SCENE_HEIGHT/2.0f,
		  //Tiling
		  td = SCENE_DEPTH/4.0f,
		  tw = SCENE_WIDTH/4.0f,
		  th = SCENE_HEIGHT/4.0f;

	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_WALL));
	glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-w, -h,  d);
		glTexCoord2f(  tw, 0.0f); glVertex3f( w, -h,  d);
		glTexCoord2f(  tw,   th); glVertex3f( w,  h,  d);
		glTexCoord2f(0.0f,   th); glVertex3f(-w,  h,  d);
		// Back Face
		glTexCoord2f(  tw, 0.0f); glVertex3f(-w, -h, -d);
		glTexCoord2f(  tw,   th); glVertex3f(-w,  h, -d);
		glTexCoord2f(0.0f,   th); glVertex3f( w,  h, -d);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( w, -h, -d);
		// Right face
		glTexCoord2f(  td, 0.0f); glVertex3f( w, -h, -d);
		glTexCoord2f(  td,   th); glVertex3f( w,  h, -d);
		glTexCoord2f(0.0f,   th); glVertex3f( w,  h,  d);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( w, -h,  d);
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-w, -h, -d);
		glTexCoord2f(  td, 0.0f); glVertex3f(-w, -h,  d);
		glTexCoord2f(  td,   th); glVertex3f(-w,  h,  d);
		glTexCoord2f(0.0f,   th); glVertex3f(-w,  h, -d);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_FLOOR));
	glBegin(GL_QUADS);
		// Bottom Face
		glTexCoord2f(  tw,   td); glVertex3f(-w, -h, -d);
		glTexCoord2f(0.0f,   td); glVertex3f( w, -h, -d);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( w, -h,  d);
		glTexCoord2f(  tw, 0.0f); glVertex3f(-w, -h,  d);
	glEnd();
	/*
	glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_ROOF));
	glBegin(GL_QUADS);
		// Top Face
		glTexCoord2f(0.0f,   td); glVertex3f(-w,  h, -d);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-w,  h,  d);
		glTexCoord2f(  tw, 0.0f); glVertex3f( w,  h,  d);
		glTexCoord2f(  tw,   td); glVertex3f( w,  h, -d);
	glEnd();
	*/
	if (drawPlayer) {
		go.render();
	}
}

bool cScene::Init()
{
	drawPlayer = true;
	go = MobileGameObject();
	return true;
}

bool cScene::drawEntity(bool draw)
{
	drawPlayer = draw;
	return drawPlayer;
}

void cScene::resolveInput(unsigned char *keys)
{
	if (keys['w']) {
		go.moveForward();
		//Scene.entityX += cos(Scene.angle * 3.1415 / 180.0f)*0.05;
		//Scene.entityZ += sin(Scene.angle * 3.1415 / 180.0f)*0.05;
	} else if (keys['s']) {
		go.moveBackwards();
		//Scene.entityX -= cos(Scene.angle * 3.1415 / 180.0f)*0.05;
		//Scene.entityZ -= sin(Scene.angle * 3.1415 / 180.0f)*0.05;
	}
	if (keys['q']) {
		go.moveLeft();
		//Scene.entityX += cos((Scene.angle - 90) * 3.1415 / 180.0f)*0.05;
		//Scene.entityZ += sin((Scene.angle - 90) * 3.1415 / 180.0f)*0.05;
	} else if (keys['e']) {
		go.moveRight();
		//Scene.entityX += cos((Scene.angle + 90) * 3.1415 / 180.0f)*0.05;
		//Scene.entityZ += sin((Scene.angle + 90) * 3.1415 / 180.0f)*0.05;
	}
	if (keys['a']) {
		go.turnLeft();
		//Scene.angle -= 0.15;
	} else if (keys['d']) {
		go.turnRight();
		//Scene.angle += 0.15;
	}
}