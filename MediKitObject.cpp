
#include "MediKitObject.h"


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
	data.renderModel(GameData::MEDIKIT_MODEL_INDEX, getXPosition(), getYPosition(), getZPosition());
}