
#include "Level.h"
#include <cmath>


Level::Level(void) {}

Level::~Level(void) {}


/* Level loading */
void Level::load(int level)
{
	fusRoDahUsed = false;
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
	map = PixelBasedFloor(GameData::LEVEL1_TEXTURE_INDEX ,"mapa.png", 0.0f, 0.0f, 2.0f);

	// Enemies
	enemies = std::vector<Enemy>(0);

	// Obstacles
	obstacles = std::vector<Obstacle>(4 + 5*8);
	obstacles[0] = Obstacle(10.0, map.getHeightAt(10,10), 10.0, 11.0, 2.0, TREE);
	obstacles[1] = Obstacle(-10.0, map.getHeightAt(-10,10), 10.0, 11.0, 2.0, TREE);
	obstacles[2] = Obstacle(10.0, map.getHeightAt(10,-10), -10.0, 11.0, 2.0, TREE);
	obstacles[3] = Obstacle(-10.0, map.getHeightAt(10,-10), -10.0, 11.0, 2.0, TREE);

	for(int i = 0; i < 5; i++) {
		obstacles[4+i] = Obstacle(50.0, map.getHeightAt(50,76-i*4), 76.0-i*4, 11.0, 2.0, TREE); 
	}
	for(int i = 0; i < 5; i++){
		obstacles[9+i] = Obstacle(-50.0, map.getHeightAt(-50,76-i*4), 76.0-i*4, 11.0, 2.0, TREE);
	}
	for(int i = 0; i < 5; i++){
		obstacles[14+i] = Obstacle(-50.0, map.getHeightAt(-50,-76+i*4), -76.0+i*4, 11.0, 2.0, TREE);
	}
	for(int i = 0; i < 5; i++){
		obstacles[19+i] = Obstacle(50.0, map.getHeightAt(50,-76+i*4), -76.0+i*4, 11.0, 2.0, TREE);
	}
	for(int i = 0; i < 5; i++) {
		obstacles[24+i] = Obstacle(76-i*4, map.getHeightAt(76-i*4,50), 50, 11.0, 2.0, TREE); 
	}
	for(int i = 0; i < 5; i++){
		obstacles[29+i] = Obstacle(76-i*4, map.getHeightAt(76-i*4,-50), -50, 11.0, 2.0, TREE);
	}
	for(int i = 0; i < 5; i++){
		obstacles[34+i] = Obstacle(-76+i*4, map.getHeightAt(-76+i*4,-50), -50, 11.0, 2.0, TREE);
	}
	for(int i = 0; i < 5; i++){
		obstacles[39+i] = Obstacle(-76+i*4, map.getHeightAt(-76+i*4,50), 50, 11.0, 2.0, TREE);
	}
	

	// Items
	energies = std::vector<EnergyObject>(4);
	energies[0] = EnergyObject();
	energies[0].setXPosition(0.0f); energies[0].setYPosition(map.getHeightAt(0,70)); energies[0].setZPosition(70.0f);
	energies[1] = EnergyObject();
	energies[1].setXPosition(0.0f); energies[1].setYPosition(map.getHeightAt(0,-70)); energies[1].setZPosition(-70.0f);
	energies[2] = EnergyObject();
	energies[2].setXPosition(-70.0f); energies[2].setYPosition(map.getHeightAt(-70,0)); energies[2].setZPosition(0.0f);
	energies[3] = EnergyObject();
	energies[3].setXPosition(70.0f); energies[3].setYPosition(map.getHeightAt(70,0)); energies[3].setZPosition(0.0f);
	medikits = std::vector<MediKitObject>(0);

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
	map = PixelBasedFloor(GameData::LEVEL2_TEXTURE_INDEX, "mapa2.png", 0.0f, 0.0f, 2.0f);

	// Enemies
	enemies = std::vector<Enemy>(12);
	
	enemies[0] = Enemy(STATIC_PURSUER);
	enemies[0].setXPosition(-85.0f);enemies[0].setZPosition(90.0f);enemies[0].setYPosition(map.getHeightAt(-85,90));
	enemies[1] = Enemy(STATIC_PURSUER);
	enemies[1].setXPosition(-85.0f);enemies[1].setZPosition(95.0f);enemies[1].setYPosition(map.getHeightAt(-85,95));
	enemies[2] = Enemy(STATIC_PURSUER);
	enemies[2].setXPosition(-70.0f);enemies[2].setZPosition(-90.0f);enemies[2].setYPosition(map.getHeightAt(-70,-90));
	enemies[3] = Enemy(STATIC_PURSUER);
	enemies[3].setXPosition(-70.0f);enemies[3].setZPosition(-95.0f);enemies[3].setYPosition(map.getHeightAt(-70,-95));
	
	std::vector<GuardPathState> *v = new std::vector<GuardPathState>(2);
	enemies[4] = Enemy(PATH);
	enemies[4].setXPosition(-77.0f);enemies[4].setZPosition(45.0f);enemies[4].setYPosition(map.getHeightAt(-77,45));
	v->at(0) = GuardPathState(0.0f, -0.15f, 700);
	v->at(1) = GuardPathState(0.0f, 0.15f, 700);
	enemies[4].setGuardState(*v);

	v = new std::vector<GuardPathState>(2);
	enemies[5] = Enemy(PATH_PURSUER);
	enemies[5].setXPosition(-55.0f);enemies[5].setZPosition(95.0f);enemies[5].setYPosition(map.getHeightAt(-55,95));
	v->at(0) = GuardPathState(0.0f, -0.3f, 600);
	v->at(1) = GuardPathState(0.0f, 0.3f, 600);
	enemies[5].setGuardState(*v);

	
	enemies[6] = Enemy(RANDOM);
	enemies[6].setXPosition(-0.0f);enemies[6].setZPosition(20.0f);enemies[6].setYPosition(map.getHeightAt(0,20));
	enemies[7] = Enemy(RANDOM);
	enemies[7].setXPosition(20.0f);enemies[7].setZPosition(0.0f);enemies[7].setYPosition(map.getHeightAt(20,0));
	enemies[8] = Enemy(RANDOM);
	enemies[8].setXPosition(0.0f);enemies[8].setZPosition(-20.0f);enemies[8].setYPosition(map.getHeightAt(0,-20));
	enemies[9] = Enemy(RANDOM);
	enemies[9].setXPosition(-20.0f);enemies[9].setZPosition(0.0f);enemies[9].setYPosition(map.getHeightAt(-20,0));

	v = new std::vector<GuardPathState>(2);
	enemies[10] = Enemy(PATH_PURSUER);
	enemies[10].setXPosition(90.0f);enemies[10].setZPosition(50.0f);enemies[10].setYPosition(map.getHeightAt(90,50));
	v->at(0) = GuardPathState(0.0f, 0.1f, 300);
	v->at(1) = GuardPathState(0.0f, -0.1f, 300);
	enemies[10].setGuardState(*v);

	v = new std::vector<GuardPathState>(2);
	enemies[11] = Enemy(PATH_PURSUER);
	enemies[11].setXPosition(90.0f);enemies[11].setZPosition(-50.0f);enemies[11].setYPosition(map.getHeightAt(90,-50));
	v->at(0) = GuardPathState(0.0f, -0.1f, 300);
	v->at(1) = GuardPathState(0.0f, 0.1f, 300);
	enemies[11].setGuardState(*v);
	
	// Obstacles
	obstacles = std::vector<Obstacle>(45*2+15*2+5+10);
	
	for(int i = 0; i < 45; i++) {
		obstacles[i] = Obstacle(-85.0, map.getHeightAt(-85, -96+i*4), -96+i*4, 11.0, 2.0, TREE); 
	}
	for(int i = 0; i < 45; i++) {
		obstacles[i+45] = Obstacle(-70.0, map.getHeightAt(-70, 96-i*4), 96-i*4, 11.0, 2.0, TREE); 
	}
	for(int i = 0; i < 15; i++) {
		obstacles[i+90] = Obstacle(80.0, map.getHeightAt(80, 98-i*2), 98-i*2, 5.0, 1.0, BARREL); 
	}
	for(int i = 0; i < 15; i++) {
		obstacles[i+105] = Obstacle(80.0, map.getHeightAt(80, -98+i*2), -98+i*2, 5.0, 1.0, BARREL); 
	}
	// 120
	obstacles[120] = Obstacle(80.0, map.getHeightAt(80, 66), 66, 11.0, 2.0, TREE);
	obstacles[121] = Obstacle(80.0, map.getHeightAt(80, -66), -66, 11.0, 2.0, TREE);
	obstacles[122] = Obstacle(10.0, map.getHeightAt(10, -50), -50, 11.0, 2.0, TREE);
	obstacles[123] = Obstacle(-50.0, map.getHeightAt(-50, 20), 20, 11.0, 2.0, TREE);
	obstacles[124] = Obstacle(15.0, map.getHeightAt(15, 88), 88, 11.0, 2.0, TREE);
	obstacles[125] = Obstacle(2.0, map.getHeightAt(2, 0), 0, 5.0, 1.0, BARREL);
	obstacles[126] = Obstacle(-5.0, map.getHeightAt(-5, 1), 1, 5.0, 1.0, BARREL);
	obstacles[127] = Obstacle(6.0, map.getHeightAt(6, -3), -3, 5.0, 1.0, BARREL);
	obstacles[128] = Obstacle(-10.0, map.getHeightAt(-10, 5), 5, 5.0, 1.0, BARREL);
	obstacles[129] = Obstacle(8.0, map.getHeightAt(8, -5), -5, 5.0, 1.0, BARREL);
	obstacles[130] = Obstacle(0.0, map.getHeightAt(0, -2), -2, 5.0, 1.0, BARREL);
	obstacles[131] = Obstacle(-1.0, map.getHeightAt(0, 10), 10, 5.0, 1.0, BARREL);
	obstacles[132] = Obstacle(-2.0, map.getHeightAt(0, -8), -8, 5.0, 1.0, BARREL);
	obstacles[133] = Obstacle(3.0, map.getHeightAt(0, 7), 7, 5.0, 1.0, BARREL);
	obstacles[134] = Obstacle(5.0, map.getHeightAt(0, -5), -5, 5.0, 1.0, BARREL);
	

	// Items
	energies = std::vector<EnergyObject>(3);
	energies[0] = EnergyObject();
	energies[0].setXPosition(-77.0f); energies[0].setYPosition(map.getHeightAt(-77,-95)); energies[0].setZPosition(-95.0f);
	energies[1] = EnergyObject();
	energies[1].setXPosition(90.0f); energies[1].setYPosition(map.getHeightAt(90,95)); energies[1].setZPosition(95.0f);
	energies[2] = EnergyObject();
	energies[2].setXPosition(0.0f); energies[2].setYPosition(map.getHeightAt(0,0)); energies[2].setZPosition(0.0f);
	medikits = std::vector<MediKitObject>(2);
	medikits[0] = MediKitObject();
	medikits[0].setXPosition(-73.0f); medikits[0].setYPosition(map.getHeightAt(-73,-90)); medikits[0].setZPosition(-90.0f);
	medikits[1] = MediKitObject();
	medikits[1].setXPosition(0.0f); medikits[1].setYPosition(map.getHeightAt(0,90)); medikits[1].setZPosition(90.0f);
	
	// Altars
	altars = std::vector<Altar>(3);
	altars[0].setXPosition(-77.0f); altars[0].setYPosition(map.getHeightAt(-77,95)); altars[0].setZPosition(95.0f);
	altars[1].setXPosition(90.0f); altars[1].setYPosition(map.getHeightAt(90,-93)); altars[1].setZPosition(-93.0f);
	altars[2].setXPosition(70.0f); altars[2].setYPosition(map.getHeightAt(70,-93)); altars[2].setZPosition(-93.0f);
}

void Level::loadThirdLevel()
{
	// Landscape
	landscape = Landscape(GameData::SPACESCAPE_TEXTURE_INDEX);

	// Map
	map = PixelBasedFloor(GameData::LEVEL3_TEXTURE_INDEX, "mapa3.png", 0.0f, 0.0f, 2.0f);

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
	energies = std::vector<EnergyObject>(2);
	energies[0] = EnergyObject();
	energies[0].setXPosition(10.0f); energies[0].setYPosition(map.getHeightAt(10,-10)); energies[0].setZPosition(-10.0f);
	energies[1] = EnergyObject();
	energies[1].setXPosition(-10.0f); energies[1].setYPosition(map.getHeightAt(-10,-10)); energies[1].setZPosition(-10.0f);
	medikits = std::vector<MediKitObject>(1);
	medikits[0] = MediKitObject();
	medikits[0].setXPosition(10.0f); medikits[0].setYPosition(map.getHeightAt(10,10)); medikits[0].setZPosition(10.0f);

	// Altars
	altars = std::vector<Altar>(2);
	altars[0].setXPosition(25.0f); altars[0].setYPosition(map.getHeightAt(25,15)); altars[0].setZPosition(15.0f);
	altars[1].setXPosition(35.0f); altars[1].setYPosition(map.getHeightAt(35,50)); altars[1].setZPosition(50.0f);
}


/* Update */
void Level::update(CameraHandler &camera, Player &player)
{	
	float max_x, min_x, max_z, min_z;
	max_x = map.getDistanceBetweenPixels() * map.getPixelsHeigth() / 2;

	// squared maps
	max_z = max_x;
	min_z = min_x = - max_x;

	// Vector with all the objects 
	std::vector<GameObject*> objects = std::vector<GameObject*>();
	objects.reserve(1 + enemies.size() + obstacles.size() + altars.size() + energies.size() + medikits.size());
	objects.push_back(&player);
	for (unsigned int i = 0; i < enemies.size(); i++) objects.push_back(&enemies[i]);
	for (unsigned int i = 0; i < obstacles.size(); i++) objects.push_back(&obstacles[i]);
	for (unsigned int i = 0; i < altars.size(); i++) objects.push_back(&altars[i]);
	for (unsigned int i = 0; i < energies.size(); i++) {
		if (!energies[i].isPickedUp()) objects.push_back(&energies[i]);
	}
	for (unsigned int i = 0; i < medikits.size(); i++) {
		if (!medikits[i].isPickedUp()) objects.push_back(&medikits[i]);
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
	if (player.getXPosition() > max_x) {
		player.setXPosition(max_x);
	} else if (player.getXPosition() < min_x) {
		player.setXPosition(min_x);
	}
	if (player.getZPosition() > max_z) {
		player.setZPosition(max_z);
	} else if (player.getZPosition() < min_z) {
		player.setZPosition(min_z);
	}
	// Enemies
	for (unsigned int i = 0; i < enemies.size(); i++) {
		if (fusRoDahUsed) {
			enemies[i].fusRoDah(player.getXPosition(), player.getZPosition());
		}
		map.getPerpendicularVector(inclination, enemies[i].getXPosition(), enemies[i].getZPosition());
		enemies[i].update(inclination, objects, player.getXPosition(), player.getZPosition());
		if (!enemies[i].isInFusRoDah()) enemies[i].setYPosition(map.getHeightAt(enemies[i].getXPosition(), enemies[i].getZPosition()));
		else {
			float floor_y = map.getHeightAt(enemies[i].getXPosition(), enemies[i].getZPosition());
			if (enemies[i].getYPosition() < floor_y) enemies[i].setYPosition(floor_y);
		}
		if (enemies[i].getXPosition() > max_x) {
			enemies[i].setXPosition(max_x);
		} else if (player.getXPosition() < min_x) {
			enemies[i].setXPosition(min_x);
		}
		if (enemies[i].getZPosition() > max_z) {
			enemies[i].setZPosition(max_z);
		} else if (enemies[i].getZPosition() < min_z) {
			enemies[i].setZPosition(min_z);
		}
	}

	// Altars
	for (unsigned int i = 0; i < altars.size(); i++) altars[i].update();

	// Items
	for (unsigned int i = 0; i < energies.size(); i++) energies[i].update(camera.getActiveCameraYAngle());
	for (unsigned int i = 0; i < medikits.size(); i++) medikits[i].update();

	// Landscape
	landscape.update();
}


/* Render */
void Level::render(GameData &data)
{
	if (fusRoDahUsed) {
		data.playSound(GameData::FUS_SOUND_INDEX);
		fusRoDahUsed = false;
	}
	map.render(data);
	for (unsigned int i = 0; i < enemies.size(); i++) enemies[i].render(data);
	for (unsigned int i = 0; i < obstacles.size(); i++) obstacles[i].render(data);
	for (unsigned int i = 0; i < altars.size(); i++) altars[i].render(data);
	for (unsigned int i = 0; i < energies.size(); i++) energies[i].render(data);
	for (unsigned int i = 0; i < medikits.size(); i++) medikits[i].render(data);
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

void Level::useFusRoDah(){
	fusRoDahUsed = true;
}