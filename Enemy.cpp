#include "Enemy.h"
#include <random>

Enemy::Enemy(void)
	: MobileGameObject()
{
	/* initialize first guard! */
	guard = std::vector<GuardPathState>();
	guardIndex = 0;
	state = STATIC_STATE;
	pursue = true;
	detectionDistance = 15.0f;
	pursueVelocity = 0.25f;
	type = 'e';
}

Enemy::Enemy(EnemyType et)
	: MobileGameObject()
{
	switch (et) {
	case STATIC_PURSUER:
		/* initialize first guard! */
		guard = std::vector<GuardPathState>();
		guardIndex = 0;
		state = STATIC_STATE;
		pursue = true;
		detectionDistance = 15.0f;
		pursueVelocity = 0.25f;
		break;
	case PATH:
		/* initialize first guard! */
		guard = std::vector<GuardPathState>();
		guardIndex = 0;
		state = GUARD_STATE;
		pursue = false;
		detectionDistance = 15.0f;
		pursueVelocity = 0.25f;
		break;
	case RANDOM:
		/* initialize first guard! */
		guard = std::vector<GuardPathState>();
		guardIndex = 0;
		state = RANDOM_PATH_STATE;
		pursue = true;
		detectionDistance = 15.0f;
		pursueVelocity = 0.25f;
		break;
	case PATH_PURSUER:
		/* initialize first guard! */
		guard = std::vector<GuardPathState>();
		guardIndex = 0;
		state = GUARD_STATE;
		pursue = true;
		detectionDistance = 15.0f;
		pursueVelocity = 0.25f;
		break;
	}
}

Enemy::~Enemy(void)
{
}

void Enemy::update(Vector3D &inclination, std::vector<GameObject*> &objects, float x, float z)
{
	/* IA */
	Vector3D direction;
	int p_forward = 30;
	int p_left = 60;
	int p_right = 90;
	int p_back = 100;
	int res = rand() % 100;
	switch (state) {
	case RANDOM_PATH_STATE:
		direction = Vector3D(x - getXPosition(), 0.0f, z - getZPosition());
		if (pursue && direction.getModule() <= detectionDistance) {
			state = PURSUE_STATE;
		} else {
			/* 30% forward, 30% left, 30% right, 10% backwards */
			if (res < p_forward) {
				moveForward();
			} else if (res < p_left) {
				turnLeft();
				turnLeft();
				turnLeft();
			} else if (res < p_right) {
				turnRight();
				turnRight();
				turnRight();
			} else {
				moveBackwards();
			}
		}
		break;
	case PURSUE_STATE:
		direction = Vector3D(x - getXPosition(), 0.0f, z - getZPosition());
		/* orient to player */
		// FIXME
		/* pursue player */
		direction.normalize();
		direction*=pursueVelocity;
		setXVelocity(direction.getX());
		setZVelocity(direction.getZ());
		break;
	case STATIC_STATE:
		direction = Vector3D(x - getXPosition(), 0.0f, z - getZPosition());
		if (pursue && direction.getModule() <= detectionDistance) {
			state = PURSUE_STATE;
		}
		break;
	case GUARD_STATE:
		direction = Vector3D(x - getXPosition(), 0.0f, z - getZPosition());
		if (pursue && direction.getModule() <= detectionDistance) {
			state = PURSUE_STATE;
		} else if (guard.size() > 0) {
			/* guard finished? */
			if (guard[guardIndex].isFinished()) {
				guardIndex = (++guardIndex)%guard.size();
				guard[guardIndex].initialize();
				/* orient to path */
				//TODO
			}
			guard[guardIndex].update();
			direction = Vector3D(guard[guardIndex].getVX(), 0.0f, guard[guardIndex].getVZ());
			setXVelocity(direction.getX());
			setZVelocity(direction.getZ());
		}
		break;
	}
	MobileGameObject::update(inclination, objects);
}

void Enemy::setGuardState(std::vector<GuardPathState> &gps)
{
	guard = gps;
	guardIndex = 0;
	guard[guardIndex].initialize();
}

void Enemy::tractarColisions(std::vector<GameObject*> &objects)
{
	for(std::vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		GameObject* go = *it;
		// different object
		if (getId() != go->getId()) {
			if (go->getBoundingCilinder()->isCollisioningWith(*getBoundingCilinder())) {
			
				switch (go->getType()) {	
				case 'g':
				
					break;
				case 'e':
					// sliding
					sliding(go);
					break;
				case 'm':
				
					break;
				case 'p':
					// TODO restar vida i fer invulnerable el player
					// sliding
					sliding(go);
					break;
				case 'o':
					// sliding
					sliding(go);
					break;
				case 'i':
					// TODO recollir i fer desapareixer
					break;
				}
			}
		}
	}
}
