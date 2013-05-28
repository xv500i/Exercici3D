
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

Obstacle::Obstacle(float x, float y, float z, float height, float radius, ObstacleType obsType)
	: GameObject(), obsType(obsType)
{
	setXPosition(x);
	setYPosition(y);
	setZPosition(z);
	BoundingCilinder *bc = getBoundingCilinder();
	bc->setHeight(height);
	bc->setRadius(radius);
	type = OBSTACLE;
}
	
void Obstacle::render(GameData &data)
{
	data.renderModel(GameData::COLUMN_MODEL_INDEX, getXPosition(), getYPosition(), getZPosition());
}
