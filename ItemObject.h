
#pragma once

#include "GameObject.h"
#include "GameData.h"


class ItemObject : public GameObject
{
private:
	bool pickedUp;

public:
	ItemObject();
	virtual ~ItemObject(void);

	/* Pick up */
	void pickUp();
	bool isPickedUp();
};