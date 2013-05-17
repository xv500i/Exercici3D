#pragma once
#include "MobileGameObject.h"
#include "GameData.h"

class Player :
	public MobileGameObject
{
public:
	Player(void);
	~Player(void);

	void render(GameData *data) const;
	bool isDead();

protected:
	virtual void tractarColisions(std::vector<GameObject*> &objects);
};

