
#include "Model.h"


Model::Model(void) {}

Model::~Model(void) {}


/* Loading */
bool Model::load(char *filename, char *ext)
{
	return model.load(filename, ext);
}


/* Render */
void Model::render(float x, float y, float z, float angleY, float angleX, float scale)
{
	model.render(x, y, z, angleY, angleX, 0.0f, 1.0f, scale, 10.0f, 0.0f, 0.0f, 0.0f);
}
