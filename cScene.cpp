#include "cScene.h"
#include "Globals.h"
#include <iostream>

cScene::cScene(void) {}
cScene::~cScene(void){}

/*
void cScene::Draw(cData *Data)
{
	float d  = SCENE_DEPTH/2.0f,
		  w  = SCENE_WIDTH/2.0f,
		  h  = SCENE_HEIGHT/2.0f,
		  //Tiling
		  td = SCENE_DEPTH/4.0f,
		  tw = SCENE_WIDTH/4.0f,
		  th = SCENE_HEIGHT/4.0f;

	
	// DRAW SCENE AXIS
	glPushMatrix();
		glLineWidth(3.0f);
		glBegin(GL_LINES);
			// X Axis --> RED
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(100.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			// Y Axis --> GREEN
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.0f, 100.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);

			// Z Axis --> BLUE
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.0f, 0.0f, 100.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
		glEnd();
	glPopMatrix();
	/*
	// DRAW ROOM
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Data->GetID(IMG_WALL));
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
	*/
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
/*
	pbf->render();
	// DRAW SPHERE
	if (drawPlayer) {
		go.render();
	}
}
*/
void cScene::render(GameData &gd)
{
	pbf->render();
	// DRAW SPHERE
	if (drawPlayer) {
		go.render();
	}
}

bool cScene::Init()
{
	drawPlayer = true;
	go = MobileGameObject();
	pbf = new PixelBasedFloor("mapa.png", 0.0f, 0.0f, 0.20f);
	return true;
}

bool cScene::drawEntity(bool draw)
{
	drawPlayer = draw;
	return drawPlayer;
}

void cScene::update(InputHandler &input)
{
	if (input.keyIsDown(input.getKey(MOVE_FORWARD))) {
		go.moveForward();
		//Scene.entityX += cos(Scene.angle * 3.1415 / 180.0f)*0.05;
		//Scene.entityZ += sin(Scene.angle * 3.1415 / 180.0f)*0.05;
	} else if (input.keyIsDown(input.getKey(MOVE_BACKWARD))) {
		go.moveBackwards();
		//Scene.entityX -= cos(Scene.angle * 3.1415 / 180.0f)*0.05;
		//Scene.entityZ -= sin(Scene.angle * 3.1415 / 180.0f)*0.05;
	}
	if (input.keyIsDown(input.getKey(MOVE_LEFT))) {
		go.moveLeft();
		//Scene.entityX += cos((Scene.angle - 90) * 3.1415 / 180.0f)*0.05;
		//Scene.entityZ += sin((Scene.angle - 90) * 3.1415 / 180.0f)*0.05;
	} else if (input.keyIsDown(input.getKey(MOVE_RIGHT))) {
		go.moveRight();
		//Scene.entityX += cos((Scene.angle + 90) * 3.1415 / 180.0f)*0.05;
		//Scene.entityZ += sin((Scene.angle + 90) * 3.1415 / 180.0f)*0.05;
	}
	if (input.keyIsDown(input.getKey(ROTATE_LEFT))) {
		go.turnLeft();
		//Scene.angle -= 0.15;
	} else if (input.keyIsDown(input.getKey(ROTATE_RIGHT))) {
		go.turnRight();
		//Scene.angle += 0.15;
	}
	go.update();
	float test = pbf->getHeightAt(go.getXPosition(), go.getZPosition());
	// FIXME I'M FAMOUS
	go.setYPosition(test);
}

void cScene::getFirstPersonParameters(float &eyex, float &eyey, float &eyez, float &centerx, float &centery, float &centerz) const
{
	// HARDCODED
	float marginY = 2.0f;
	eyex = go.getXPosition();
	eyey = go.getYPosition() + marginY;
	eyez = go.getZPosition();
	centerx = eyex + 5*cos(go.getYAngle() * 3.1415f / 180.0f);
	centery = eyey;
	centerz = eyez + 5*sin(go.getYAngle() * 3.1415f / 180.0f);
}