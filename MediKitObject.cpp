
#include "MediKitObject.h"
// DEBUG
#include "Globals.h"


const float MediKitObject::INCREMENT_Y_ANGLE = 5.0f;


MediKitObject::MediKitObject(void) : ItemObject() 
{
	type = MEDIKIT;
	yAngle = 0.0f;
}

MediKitObject::~MediKitObject(void) {}


/* Update */
void MediKitObject::update()
{
	yAngle += INCREMENT_Y_ANGLE;
}


/* Render */
void MediKitObject::render(GameData &data)
{
	if (isPickedUp()) return;
	data.renderModel(GameData::MEDIKIT_MODEL_INDEX, getXPosition(), getYPosition() + 1.0f, getZPosition(), yAngle, 5.0f);
	if (DEBUG) renderBoundingCilinder();
}