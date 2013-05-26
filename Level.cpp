
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
	// Landscape
	landscape = Landscape(GameData::LANDSCAPE_TEXTURE_INDEX);

	// Map
	map = PixelBasedFloor("mapa.png", 0.0f, 0.0f, 2.0f);

	// Enemies
	enemies = std::vector<Enemy>(0);

	// Obstacles
	obstacles = std::vector<Obstacle>(3);
	obstacles[0] = Obstacle(7.0, map.getHeightAt(7,7), 7.0, 11.0, 1.0, TREE);
	obstacles[1] = Obstacle(-7.0, map.getHeightAt(-7,7), 7.0, 11.0, 1.0, TREE);
	obstacles[2] = Obstacle(7.0, map.getHeightAt(7,-7), -7.0, 11.0, 1.0, TREE);

	// Items
	items = std::vector<ItemObject>(4);
	items[0] = ItemObject(true);
	items[0].setXPosition(0.0f); items[0].setYPosition(map.getHeightAt(0,70)); items[0].setZPosition(70.0f);
	items[1] = ItemObject(true);
	items[1].setXPosition(0.0f); items[1].setYPosition(map.getHeightAt(0,-70)); items[1].setZPosition(-70.0f);
	items[2] = ItemObject(true);
	items[2].setXPosition(-70.0f); items[2].setYPosition(map.getHeightAt(-70,0)); items[2].setZPosition(0.0f);
	items[3] = ItemObject(true);
	items[3].setXPosition(70.0f); items[3].setYPosition(map.getHeightAt(70,0)); items[3].setZPosition(0.0f);

	// Altars
	altars = std::vector<Altar>(4);
	altars[0].setXPosition(70.0f); altars[0].setYPosition(map.getHeightAt(70,70)); altars[0].setZPosition(70.0f);
	altars[1].setXPosition(70.0f); altars[1].setYPosition(map.getHeightAt(70,-70)); altars[1].setZPosition(-70.0f);
	altars[2].setXPosition(-70.0f); altars[2].setYPosition(map.getHeightAt(-70,70)); altars[2].setZPosition(70.0f);
	altars[3].setXPosition(-70.0f); altars[3].setYPosition(map.getHeightAt(-70,-70)); altars[3].setZPosition(-70.0f);
}

void Level::loadSecondLevel()
{
	// Landscape
	landscape = Landscape(GameData::ICESCAPE_TEXTURE_INDEX);

	// Map
	map = PixelBasedFloor("mapa2.png", 0.0f, 0.0f, 2.0f);

	// Enemies
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
	enemies[0].setXPosition(15.0f);enemies[0].setZPosition(15.0f);enemies[0].setYPosition(map.getHeightAt(15,15));
	enemies[1].setXPosition(-15.0f);enemies[1].setZPosition(-15.0f);enemies[1].setYPosition(map.getHeightAt(-15,-15));
	enemies[3].setXPosition(15.0f);enemies[3].setZPosition(-15.0f);enemies[3].setYPosition(map.getHeightAt(15,-15));
	enemies[3].setGuardState(*v2);
	enemies[2].setXPosition(-15.0f);enemies[2].setZPosition(15.0f);enemies[2].setYPosition(map.getHeightAt(-15,15));
	enemies[2].setGuardState(*v);

	// Obstacles
	obstacles = std::vector<Obstacle>(3);
	obstacles[0] = Obstacle(7.0, map.getHeightAt(7,7), 7.0, 8.0, 1.0, TREE);
	obstacles[1] = Obstacle(-7.0, map.getHeightAt(-7,7), 7.0, 8.0, 1.0, TREE);
	obstacles[2] = Obstacle(7.0, map.getHeightAt(7,-7), -7.0, 8.0, 1.0, TREE);

	// Items
	items = std::vector<ItemObject>(3);
	items[0] = ItemObject(false);
	items[0].setXPosition(10.0f); items[0].setYPosition(map.getHeightAt(10,10)); items[0].setZPosition(10.0f);
	items[1] = ItemObject(true);
	items[1].setXPosition(10.0f); items[1].setYPosition(map.getHeightAt(10,-10)); items[1].setZPosition(-10.0f);
	items[2] = ItemObject(true);
	items[2].setXPosition(-10.0f); items[2].setYPosition(map.getHeightAt(-10,-10)); items[2].setZPosition(-10.0f);

	// Altars
	altars = std::vector<Altar>(2);
	altars[0].setXPosition(25.0f); altars[0].setYPosition(map.getHeightAt(25,15)); altars[0].setZPosition(15.0f);
	altars[1].setXPosition(35.0f); altars[1].setYPosition(map.getHeightAt(35,50)); altars[1].setZPosition(50.0f);
}

void Level::loadThirdLevel()
{
	// Landscape
	landscape = Landscape(GameData::SPACESCAPE_TEXTURE_INDEX);

	// Map
	map = PixelBasedFloor("mapa3.png", 0.0f, 0.0f, 2.0f);

	// Enemies
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
	enemies[0].setXPosition(15.0f);enemies[0].setZPosition(15.0f);enemies[0].setYPosition(map.getHeightAt(15,15));
	enemies[1].setXPosition(-15.0f);enemies[1].setZPosition(-15.0f);enemies[1].setYPosition(map.getHeightAt(-15,-15));
	enemies[3].setXPosition(15.0f);enemies[3].setZPosition(-15.0f);enemies[3].setYPosition(map.getHeightAt(15,-15));
	enemies[3].setGuardState(*v2);
	enemies[2].setXPosition(-15.0f);enemies[2].setZPosition(15.0f);enemies[2].setYPosition(map.getHeightAt(-15,15));
	enemies[2].setGuardState(*v);

	// Obstacles
	obstacles = std::vector<Obstacle>(3);
	obstacles[0] = Obstacle(7.0, map.getHeightAt(7,7), 7.0, 8.0, 1.0, TREE);
	obstacles[1] = Obstacle(-7.0, map.getHeightAt(-7,7), 7.0, 8.0, 1.0, TREE);
	obstacles[2] = Obstacle(7.0, map.getHeightAt(7,-7), -7.0, 8.0, 1.0, TREE);

	// Items
	items = std::vector<ItemObject>(3);
	items[0] = ItemObject(false);
	items[0].setXPosition(10.0f); items[0].setYPosition(map.getHeightAt(10,10)); items[0].setZPosition(10.0f);
	items[1] = ItemObject(true);
	items[1].setXPosition(10.0f); items[1].setYPosition(map.getHeightAt(10,-10)); items[1].setZPosition(-10.0f);
	items[2] = ItemObject(true);
	items[2].setXPosition(-10.0f); items[2].setYPosition(map.getHeightAt(-10,-10)); items[2].setZPosition(-10.0f);

	// Altars
	altars = std::vector<Altar>(2);
	altars[0].setXPosition(25.0f); altars[0].setYPosition(map.getHeightAt(25,15)); altars[0].setZPosition(15.0f);
	altars[1].setXPosition(35.0f); altars[1].setYPosition(map.getHeightAt(35,50)); altars[1].setZPosition(50.0f);
}


/* Update */
void Level::update(Player &player)
{
	// Vector with all the objects 
	std::vector<GameObject*> objects = std::vector<GameObject*>();
	objects.reserve(1 + enemies.size() + obstacles.size() + altars.size() + items.size());
	objects.push_back(&player);
	for (unsigned int i = 0; i < enemies.size(); i++) objects.push_back(&enemies[i]);
	for (unsigned int i = 0; i < obstacles.size(); i++) objects.push_back(&obstacles[i]);
	for (unsigned int i = 0; i < altars.size(); i++) objects.push_back(&altars[i]);
	for (unsigned int i = 0; i < items.size(); i++) {
		if (!items[i].isPickedUp()) objects.push_back(&items[i]);
	}

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

	// Enemies
	for (unsigned int i = 0; i < enemies.size(); i++) {
		map.getPerpendicularVector(inclination, enemies[i].getXPosition(), enemies[i].getZPosition());
		enemies[i].update(inclination, objects, player.getXPosition(), player.getZPosition());
		enemies[i].setYPosition(map.getHeightAt(enemies[i].getXPosition(), enemies[i].getZPosition()));
	}

	// Altars
	for (unsigned int i = 0; i < altars.size(); i++) altars[i].update();

	// Items
	for (unsigned int i = 0; i < items.size(); i++) items[i].update();

	// Landscape
	landscape.update();
}


/* Render */
void Level::render(GameData &data)
{
	map.render(data);
	for (unsigned int i = 0; i < enemies.size(); i++) enemies[i].render(data);
	for (unsigned int i = 0; i < obstacles.size(); i++) obstacles[i].render(data);
	for (unsigned int i = 0; i < altars.size(); i++) altars[i].render(data);
	for (unsigned int i = 0; i < items.size(); i++) items[i].render(data);
	landscape.render(data);
}


/* Level completed */
bool Level::isLevelCompleted()
{
	bool completed = true;
	for (unsigned int i = 0; i < altars.size(); i++) {
		if (!altars[i].isActive()) completed = false;
	}
	return completed;
}