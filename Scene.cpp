
#include "Scene.h"
#include <gl/glut.h>
#include <iostream>


Scene::Scene(void) {}

Scene::~Scene(void) {}


/* Scene initialization */
bool Scene::init()
{
	drawPlayer = true;
	currentLevel = 1;
	isCurrentLevelCompleted = false;
	// TODO HARDCODED
	hud.load(800, 600, Player::MAX_LIFE);
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
	if (input.keyIsDown('n'))							   isCurrentLevelCompleted = true;
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
	if (drawPlayer) player.render(data);
	
	// HUD (It must be the last render)
	hud.render(data);
}



bool Scene::drawEntity(bool draw)
{
	drawPlayer = draw;
	return drawPlayer;
}


bool Scene::playerIsDead()
{
	return player.isDead();
}

void Scene::loadLevel(int levelNumber)
{
	player = Player();
	level.load(levelNumber);
	isCurrentLevelCompleted = false;
	currentLevel = levelNumber;
}

void Scene::nextLevel()
{
	loadLevel(currentLevel + 1);
}

bool Scene::isLevelCompleted()
{
	// FIXME: aqui vull saber quan el nivell actual s'ha completat i cal passar a la pantalla de next level
	return isCurrentLevelCompleted;
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