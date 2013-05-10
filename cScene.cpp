#include "cScene.h"
#include "Globals.h"
#include <iostream>
// FIXME:
#include "GuardPathState.h"

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
	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i].render();
	}
	for (unsigned int i = 0; i < obstacles.size(); i++) {
		obstacles[i].render();
	}
}

bool cScene::Init()
{
	drawPlayer = true;
	go = MobileGameObject();
	pbf = new PixelBasedFloor("mapa.png", 0.0f, 0.0f, 0.20f);

	/* TEST VECTOR */
	//Vector3D v = Vector3D(1,-2,2);
	//Vector3D u = Vector3D(-4,2,-2);
	//Vector3D *w = v.vectorialProduct(u);
	std::vector<GuardPathState> *v = new std::vector<GuardPathState>(4);
	v->at(0) = GuardPathState(0.2f, 0.0f, 30);
	v->at(1) = GuardPathState(0.0f, 0.2f, 30);
	v->at(2) = GuardPathState(-0.2f, 0.0f, 30);
	v->at(3) = GuardPathState(0.0f, -0.2f, 30);
	std::vector<GuardPathState> *v2 = new std::vector<GuardPathState>(2);
	v2->at(0) = GuardPathState(0.2f, 0.2f, 20);
	v2->at(1) = GuardPathState(-0.2f, -0.2f, 20);
	enemies = std::vector<Enemy>(4);
	enemies[0] = Enemy(STATIC_PURSUER);
	enemies[1] = Enemy(RANDOM);
	enemies[2] = Enemy(PATH);
	enemies[3] = Enemy(PATH_PURSUER);
	enemies[0].setXPosition(15.0f);enemies[0].setZPosition(15.0f);
	enemies[1].setXPosition(-15.0f);enemies[1].setZPosition(-15.0f);
	enemies[3].setXPosition(15.0f);enemies[3].setZPosition(-15.0f);
	enemies[3].setGuardState(*v2);
	enemies[2].setXPosition(-15.0f);enemies[2].setZPosition(15.0f);
	enemies[2].setGuardState(*v);

	obstacles = std::vector<Obstacle>(3);
	obstacles[0] = Obstacle(7.0, 5.0, 7.0, 5.0, 1.0, TREE);
	obstacles[1] = Obstacle(-7.0, 5.0, 7.0, 5.0, 1.0, TREE);
	obstacles[2] = Obstacle(7.0, 5.0, -7.0, 5.0, 1.0, TREE);
	return true;
}

bool cScene::drawEntity(bool draw)
{
	drawPlayer = draw;
	return drawPlayer;
}

void cScene::update(InputHandler &input)
{
	// vector with all objects
	std::vector<GameObject*> objects = std::vector<GameObject*>();
	objects.reserve(1+enemies.size());
	objects.push_back(&go);
	for(unsigned int i = 0; i < enemies.size(); i++) objects.push_back(&enemies[i]);

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
	// HARDCODED arreglar input
	if (input.keyIsDown(' ')) {
		go.jump();
	}
	Vector3D inclination;
	pbf->getPerpendicularVector( inclination, go.getXPosition(), go.getZPosition());
	go.update(inclination, objects);
	float test = pbf->getHeightAt(go.getXPosition(), go.getZPosition());
	// FIXME I'M FAMOUS
	if (test >= go.getYPosition() ) {
		// FOOT ON GROUND
		go.floorReached();
		go.clearYVelocity();
	} else {
		// FLYING FREE
		
	}
	go.setYPosition( max( test, go.getYPosition() ));
	for (unsigned int i = 0; i < enemies.size(); i++) {
		pbf->getPerpendicularVector( inclination, enemies[i].getXPosition(), enemies[i].getZPosition());
		enemies[i].update(inclination, objects, go.getXPosition(), go.getZPosition());
		enemies[i].setYPosition(pbf->getHeightAt(enemies[i].getXPosition(), enemies[i].getZPosition()));
	}
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