
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


class Enemy : public MobileGameObject
{
public:
	Enemy(void);
	Enemy(EnemyType et);
	~Enemy(void);

	/* Update */
	void update(Vector3D &inclination, std::vector<GameObject*> &objects, float x, float z);

	/* Render */
	void render(GameData &data);

	void setGuardState(std::vector<GuardPathState> &gps);
	void fusRoDah(float x, float z);
	bool isInFusRoDah();

private:
	std::vector<GuardPathState> guard;
	int guardIndex;
	EnemyState state;
	bool pursue;
	float detectionDistance;
	float pursueVelocity;
	int fusRoDahEffect;

protected:
	virtual void tractarColisions(std::vector<GameObject*> &objects);
};

