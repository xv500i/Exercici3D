
#include "Enemy.h"
#include <random>
#include "Vector3D.h"
// DEBUG
#include "Globals.h"


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
	type = ENEMY;
	animationTics = 0;
}

Enemy::Enemy(EnemyType et)
	: MobileGameObject()
{
	BoundingCilinder *bc = getBoundingCilinder();
	bc->setHeight(4.5f);
	bc->setRadius(1.3f);
	animationTics = 0;

	type = ENEMY;
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
	// Tics animation
	animationTics++;

	/* IA */
	Vector3D direction;
	int p_forward = 30;
	int p_left = 60;
	int p_right = 90;
	int p_back = 100;
	float fx, fz;
	int res = rand() % 100;
	if (fusRoDahEffect > 0) {
		fx = getXVelocity();
		fz = getZVelocity();
	} else {
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
			// TODO URGENT!!! ALEX SOMS
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
				// ANIMATION
				animationTics = 0;
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
					// TODO URGENT!!! ALEX SOMS
				}
				guard[guardIndex].update();
				direction = Vector3D(guard[guardIndex].getVX(), 0.0f, guard[guardIndex].getVZ());
				setXVelocity(direction.getX());
				setZVelocity(direction.getZ());
			}
			break;
		}
	}
	MobileGameObject::update(inclination, objects);
	if (fusRoDahEffect > 0) {
		setXVelocity(fx);
		setZVelocity(fz);
		fusRoDahEffect--;
	}
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
				MobileGameObject *mgo;
				switch (go->getType()) {	
				case OBJECT:
				
					break;
				case ENEMY:
					// sliding
					mgo = (MobileGameObject *) (go);
					mgo->sliding(this);
					sliding(go);
					break;
				case MOBILEOBJECT:
				
					break;
				case PLAYER:
					// sliding
					sliding(go);
					mgo = (MobileGameObject *) (go);
					mgo->sliding(this);
					break;
				case OBSTACLE:
					// sliding
					sliding(go);
					break;
				case ENERGY:	
					break;
				case MEDIKIT:
					break;
				}
			}
		}
	}
}

void Enemy::fusRoDah(float x, float z){
	Vector3D vel = Vector3D(x - getXPosition(), 0.0f , z - getZPosition());
	float module = vel.getModule();
	if (vel.getModule() > 50.f) return;
	vel.normalize();
	vel *= -1;
	vel *= 1/module*20.0f;
	fusRoDahEffect = 50;
	setXVelocity(vel.getX());
	setYVelocity(2.0f);
	setZVelocity(vel.getZ());
}

bool Enemy::isInFusRoDah(){
	return fusRoDahEffect > 0;
}


void Enemy::render(GameData &data)
{
	int frame;
	if (state == STATIC_STATE) {
		data.setModelAnimation(GameData::RED_ORC_MODEL_INDEX, ANIM_STAND);
		frame = data.getModelAnimationFrame(GameData::RED_ORC_MODEL_INDEX, ANIM_STAND, animationTics/3);
	}
	else {
		data.setModelAnimation(GameData::RED_ORC_MODEL_INDEX, ANIM_RUN);
		frame = data.getModelAnimationFrame(GameData::RED_ORC_MODEL_INDEX, ANIM_RUN, animationTics/3);
	}
	data.renderModel(GameData::RED_ORC_MODEL_INDEX, getXPosition(), getYPosition() + 2.2f, getZPosition(), getYAngle(), 0.0f, 1.5f, frame);
	if (DEBUG) renderBoundingCilinder();
}