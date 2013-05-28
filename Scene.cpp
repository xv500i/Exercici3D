
#include "Scene.h"
#include <gl/glut.h>
#include <iostream>
// DEBUG
#include "Globals.h"


Scene::Scene(void) {}

Scene::~Scene(void) {}


/* Scene initialization */
bool Scene::init(int screenWidth, int screenHeight)
{
	currentLevel = 1;
	isCurrentLevelCompleted = false;
	hud.load(screenWidth, screenHeight, Player::MAX_LIFE);
	return true;
}


/* Input */
void Scene::resolveInput(InputHandler &input)
{
	// PLAYER INPUT --> TODO: anar en diagonal
	if (input.keyIsDown(input.getKey(MOVE_FORWARD)))	   player.moveForward();
	else if (input.keyIsDown(input.getKey(MOVE_BACKWARD))) player.moveBackwards();
	if (input.keyIsDown(input.getKey(MOVE_LEFT)))		   player.moveLeft();
	else if (input.keyIsDown(input.getKey(MOVE_RIGHT)))	   player.moveRight();
	if (input.keyIsDown(input.getKey(ROTATE_LEFT)))		   player.turnLeft();
	else if (input.keyIsDown(input.getKey(ROTATE_RIGHT)))  player.turnRight();
	if (input.keyIsDown(input.getKey(JUMP)))			   player.jump();

	// Next level (automatic)
	if (input.keyIsDown('n')) isCurrentLevelCompleted = true;

	// Enable/disable debug mode
	if (input.keyIsDown('m')) {
		DEBUG = !DEBUG;
	}
}


/* Update */
void Scene::update(CameraHandler &camera)
{
	// Level (and player)
	level.update(player);

	// Third person camera
	Point3D playerPos = player.getPosition();
	float xzAngle = player.getYAngle();
	camera.updateThirdPersonCamera(playerPos.getX(), playerPos.getY(), playerPos.getZ(), xzAngle);

	// HUD
	hud.update(player.getLife(), player.getEnergy());
}


/* Render */
void Scene::render(GameData &data)
{
	// Level
	level.render(data);

	// Player
	player.render(data);
	
	// HUD (It must be the last render)
	hud.render(data);
}



bool Scene::playerIsDead()
{
	return player.isDead();
}

void Scene::loadLevel(int levelNumber)
{
	player = Player();
	level.load(levelNumber);
	switch(levelNumber) {
	case 1:
		player.setXPosition(0.0f);
		player.setZPosition(0.0f);
		player.setFriction(0.90f);
		player.setGravity(-0.25f);
		player.setMaxAcceleration(0.1f);
		break;
	case 2:
		player.setXPosition(-93.0f);
		player.setZPosition(-93.0f);
		player.setFriction(0.98f);
		player.setGravity(-0.25f);
		player.setMaxAcceleration(0.05f);
		break;
	case 3:
		player.setXPosition(0.0f);
		player.setZPosition(0.0f);
		player.setFriction(0.85f);
		player.setGravity(-0.05f);
		player.setMaxAcceleration(0.05f);
		break;
	}
	isCurrentLevelCompleted = false;
	currentLevel = levelNumber;
}

void Scene::nextLevel()
{
	loadLevel(currentLevel + 1);
}

bool Scene::isLevelCompleted()
{
	return isCurrentLevelCompleted || level.isLevelCompleted();
}

bool Scene::isLastLevel()
{
	return currentLevel == NUM_LEVELS;
}

void Scene::resetRot()
{
	player.resetRot();
}

int Scene::getCurrentLevel()
{
	return currentLevel;
}