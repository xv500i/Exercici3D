
#include "ItemObject.h"


ItemObject::ItemObject() : GameObject()
{
	pickedUp = false;
}

ItemObject::~ItemObject(void) {}


/* Pick up */
void ItemObject::pickUp()
{
	pickedUp = true;
}

bool ItemObject::isPickedUp()
{
	return pickedUp;
}