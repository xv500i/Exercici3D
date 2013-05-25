
#include "Level.h"
#include <cmath>


Level::Level(void) {}

Level::~Level(void) {}


/* Level loading */
void Level::load(int level)
{
	switch (level) {
	case 1: loadFirstLevel(); break;
	case 2: loadSecondLevel(); break;
	case 3: loadThirdLevel(); break;
	default: break;
	}
}


/* Loading of different levels */
void Level::loadFirstLevel()
{
	// TODO PRIMER NIVELL

	// TEST LEVEL
	landscape = Landscape(GameData::LANDSCAPE_TEXTURE_INDEX);
	map = PixelBasedFloor("mapa.png", 0.0f, 0.0f, 2.0f);
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
	obstacles[0] = Obstacle(7.0, 5.0, 7.0, 8.0, 1.0, TREE);
	obstacles[1] = Obstacle(-7.0, 5.0, 7.0, 8.0, 1.0, TREE);
	obstacles[2] = Obstacle(7.0, 5.0, -7.0, 8.0, 1.0, TREE);
}

void Level::loadSecondLevel()
{
	// TODO SEGON NIVELL
	landscape = Landscape(GameData::ICESCAPE_TEXTURE_INDEX);
}

void Level::loadThirdLevel()
{
	// TODO TERCER NIVELL
	landscape = Landscape(GameData::SPACESCAPE_TEXTURE_INDEX);
}


/* Update */
void Level::update(Player &player)
{
	// Vector with all the objects 
	std::vector<GameObject*> objects = std::vector<GameObject*>();
	objects.reserve(1 + enemies.size() + obstacles.size());
	objects.push_back(&player);
	for(unsigned int i = 0; i < enemies.size(); i++) objects.push_back(&enemies[i]);
	for(unsigned int i = 0; i < obstacles.size(); i++) objects.push_back(&obstacles[i]);

	Vector3D inclination;
	map.getPerpendicularVector(inclination, player.getXPosition(), player.getZPosition());
	player.update(inclination, objects);
	float test = map.getHeightAt(player.getXPosition(), player.getZPosition());
	// FIXME I'M FAMOUS
	if (test >= player.getYPosition() ) {
		// FOOT ON GROUND
		player.floorReached();
		player.clearYVelocity();
	} 
	else {
		// FLYING FREE	
	}
	player.setYPosition(std::max(test, player.getYPosition()));
	for (unsigned int i = 0; i < enemies.size(); i++) {
		map.getPerpendicularVector(inclination, enemies[i].getXPosition(), enemies[i].getZPosition());
		enemies[i].update(inclination, objects, player.getXPosition(), player.getZPosition());
		enemies[i].setYPosition(map.getHeightAt(enemies[i].getXPosition(), enemies[i].getZPosition()));
	}
}


/* Render */
void Level::render(GameData &data)
{
	map.render(data);
	for (unsigned int i = 0; i < enemies.size(); i++) enemies[i].render(data);
	for (unsigned int i = 0; i < obstacles.size(); i++) obstacles[i].render(data);
	landscape.render(data);
}