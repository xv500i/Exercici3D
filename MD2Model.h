
#pragma once

#include "rendermd2.h"
#include "Texture.h"


enum {
    ANIM_STAND,
    ANIM_RUN,
    ANIM_ATTACK,
    ANIM_PAIN_A,
    ANIM_PAIN_B,
    ANIM_PAIN_C,
    ANIM_JUMP,
    ANIM_FLIP,
    ANIM_SALUTE,
    ANIM_FALLBACK,
    ANIM_WAVE,
    ANIM_POINT,
    ANIM_CROUCH_STAND,
    ANIM_CROUCH_WALK,
    ANIM_CROUCH_ATTACK,
    ANIM_CROUCH_PAIN,
    ANIM_CROUCH_DEATH, 
    ANIM_DEATH_FALLBACK,
    ANIM_DEATH_FALLFORWARD,
    ANIM_DEATH_FALLBACKSLOW,
    ANIM_BOOM
};


class MD2Model
{
public:
	MD2Model();
	~MD2Model();

	bool load(char *filename, char *extension);
	void setAnimation(int anim_state);
	int getAnimationStartFrame(int anim_state);
	int getAnimationEndFrame(int anim_state);
	void setColor(float r, float g, float b);

	/* Render */
	void render(float x, float y, float z);
	void render(float x, float y, float z, float yaw, float pitch);
	void render(float x, float y, float z, float yaw, float pitch, float frame, float range, float scale, float speed, float snap, float time_last, float time_base);

private:
	md2 *model;
	vec color;
	int anim, frame;
	Texture tex;
};

