
#pragma once

#include "HUDElement.h"


class FusRoDahHUDElement : public HUDElement
{
private:
	const static int MARGIN = 4;

	int fusRoDahTics;

public:
	FusRoDahHUDElement(void);
	FusRoDahHUDElement(int x, int y, int width, int height, int textureIndex);
	virtual ~FusRoDahHUDElement(void);

	/* Update */
	void update(int fusRoDahTics);

	/* Render */
	void render(GameData &data);
};

