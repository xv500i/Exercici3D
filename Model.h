
#pragma once
#pragma comment(lib, "MD2Model")

#include "MD2Model.h"


class Model
{
private:
	MD2Model model;

public:
	Model(void);
	virtual ~Model(void);

	/* Loading */
	bool load(char *filename, char *ext);

	/* Render */
	void render(float x, float y, float z, float angleY = 0.0f, float angleX = 0.0f);
};