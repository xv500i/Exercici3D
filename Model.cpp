
#include "Model.h"


Model::Model(void) {}

Model::~Model(void) {}


/* Loading */
bool Model::load(char *filename, char *ext)
{
	return model.load(filename, ext);
}


/* Animation */
void Model::setAnimation(int animationState)
{
	model.setAnimation(animationState);
}

int Model::getAnimationFrame(int animationState, int tics)
{
	int numFrames = model.getAnimationEndFrame(animationState) - model.getAnimationStartFrame(animationState);
	return model.getAnimationStartFrame(animationState) + tics%numFrames;
}


/* Render */
void Model::render(float x, float y, float z, float angleY, float angleX, float scale, int frame)
{
	model.render(x, y, z, angleY, angleX, frame, 1.0f, scale, 1.0f, 0.0f, 0.0f, 0.0f);
}
