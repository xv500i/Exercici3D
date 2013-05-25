
#pragma once

#include "GameObject.h"


class Altar :
	public GameObject
{
private:
	bool active;

public:
	Altar(void);
	virtual ~Altar(void);

	/* Render */
	void render(GameData &data);

	/* Altar activation */
	void activate();
	bool isActive();
};