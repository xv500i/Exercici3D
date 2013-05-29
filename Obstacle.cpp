
#include "Obstacle.h"
#include <gl\glut.h>
// DEBUG
#include "Globals.h"


Obstacle::Obstacle(void)
	: GameObject()
{
	type = OBSTACLE;
}


Obstacle::~Obstacle(void)
{

}

Obstacle::Obstacle(float x, float y, float z, ObstacleType obsType)
	: GameObject(), obsType(obsType)
{
	type = OBSTACLE;
	setXPosition(x);
	setYPosition(y);
	setZPosition(z);
	BoundingCilinder *bc = getBoundingCilinder();
	if (obsType == COLUMN) {
		bc->setHeight(12.5f);
		bc->setRadius(2.0f);
	}
	else if (obsType == BARREL) {
		bc->setHeight(2.5f);
		bc->setRadius(1.2f);
	}
}
	
void Obstacle::render(GameData &data)
{
	if (obsType == COLUMN) 
		data.renderModel(GameData::COLUMN_MODEL_INDEX, getXPosition(), getYPosition(), getZPosition(), 0.0f, 0.0f, 2.0f);
	else if (obsType == BARREL)
		data.renderModel(GameData::BARREL_MODEL_INDEX, getXPosition(), getYPosition(), getZPosition(), 0.0f, 0.0f, 2.0f);
	if (DEBUG) renderBoundingCilinder();
}
