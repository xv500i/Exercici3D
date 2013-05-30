
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

	/* Animation */
	void setAnimation(int animationState);
	int getAnimationFrame(int animationState, int tics);

	/* Render */
	void render(float x, float y, float z, float angleY = 0.0f, float angleX = 0.0f, float scale = 1.0f, int frame = 0);
};