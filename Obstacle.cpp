#include "Obstacle.h"


Obstacle::Obstacle(void)
	: GameObject()
{

}


Obstacle::~Obstacle(void)
{

}

Obstacle::Obstacle(Point3D &center, float height, float radius, ObstacleType type)
	:height(height), radius(radius), type(type)
{
	setXPosition(center.getX());
	setYPosition(center.getY());
	setZPosition(center.getZ());
}
	
void Obstacle::render() const
{

}

void Obstacle::update()
{

}
