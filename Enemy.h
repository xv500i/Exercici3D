#pragma once
#include "GuardPathState.h"
#include <vector>
#include "MobileGameObject.h"

enum EnemyState {
	GUARD_STATE,
	RANDOM_PATH_STATE,
	STATIC_STATE,
	PURSUE_STATE
};

enum EnemyType {
	STATIC_PURSUER,
	PATH,
	RANDOM,
	PATH_PURSUER
};

class Enemy : 
	public MobileGameObject
{
public:
	Enemy(void);
	Enemy(EnemyType et);
	~Enemy(void);
	void update(Vector3D &inclination, std::vector<GameObject*> &objects, float x, float z);
	void setGuardState(std::vector<GuardPathState> &gps);

private:
	std::vector<GuardPathState> guard;
	int guardIndex;
	EnemyState state;
	bool pursue;
	float detectionDistance;
	float pursueVelocity;

protected:
	virtual void tractarColisions(std::vector<GameObject*> &objects);
};

