
#include "Model.h"


Model::Model(void) {}

Model::~Model(void) {}


/* Loading */
bool Model::load(char *filename, char *ext)
{
	return model.load(filename, ext);
}


/* Render */
void Model::render(float x, float y, float z)
{
	model.render(x, y, z);
}
