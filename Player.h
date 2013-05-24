#pragma once
#include "MobileGameObject.h"
#include "GameData.h"

class Player :
	public MobileGameObject
{
public:
	Player(void);
	~Player(void);

	void render(GameData &data) const;
	bool isDead();
	void update(Vector3D &inclination, std::vector<GameObject*> &objects);
	void resetRot();
protected:
	virtual void tractarColisions(std::vector<GameObject*> &objects);

private:
	float rotX;
	float rotZ;
	float rotY;
};

