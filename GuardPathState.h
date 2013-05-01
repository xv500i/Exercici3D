#pragma once

#ifndef STATE_G_H
#define STATE_G_H

class GuardPathState
{
public:
	GuardPathState(void);
	GuardPathState(float vx, float vz, int ticksMax);
	~GuardPathState(void);
	bool isFinished();
	void update();
	void initialize();
	int getTicksLeft();
	float getVX();
	float getVZ();

private:
	int ticksLeft;
	int ticksMax;
	float vx;
	float vz;
};

#endif