#include "GuardPathState.h"


GuardPathState::GuardPathState(void)
{
}

GuardPathState::GuardPathState(float vx, float vz , int ticksMax) : vx(vx), vz(vz), ticksMax(ticksMax)
{

}

GuardPathState::~GuardPathState(void)
{
}

bool GuardPathState::isFinished()
{
	return ticksLeft <= 0;
}

void GuardPathState::initialize()
{
	ticksLeft = ticksMax;
}

int GuardPathState::getTicksLeft()
{
	return ticksLeft;
}

float GuardPathState::getVX()
{
	return vx;
}

float GuardPathState::getVZ()
{
	return vz;
}

void GuardPathState::update()
{
	ticksLeft--;
}
