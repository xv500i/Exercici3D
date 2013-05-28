
#include "MediKitObject.h"


MediKitObject::MediKitObject(void) : ItemObject() 
{
	type = MEDIKIT;
}

MediKitObject::~MediKitObject(void) {}


/* Update */
void MediKitObject::update()
{

}


/* Render */
void MediKitObject::render(GameData &data)
{
	data.renderModel(GameData::MEDIKIT_MODEL_INDEX, getXPosition(), getYPosition(), getZPosition());
}