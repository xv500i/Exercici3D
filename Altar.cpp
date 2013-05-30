
#include "Altar.h"
// DEBUG
#include "Globals.h"


Altar::Altar(void) : GameObject() 
{
	type = ALTAR;
	active = false;
	particlesCreated = false;
	ticsActive = 0;
	BoundingCilinder *bc = getBoundingCilinder();
	bc->setHeight(5.5f);
	bc->setRadius(1.3f);
	playSpark = false;
}

Altar::~Altar(void) {}


/* Update */
void Altar::update(float visionYAngle)
{
	if (!particlesCreated && active) {
		// Texture preparation
		std::vector<int> textures = std::vector<int>(4);
		textures[0] = GameData::ALTAR_PARTICLE_1_INDEX;
		textures[1] = GameData::ALTAR_PARTICLE_2_INDEX;
		textures[2] = GameData::ALTAR_PARTICLE_3_INDEX;
		textures[3] = GameData::ALTAR_PARTICLE_4_INDEX;

		// Particle creation 
		aura.createParticleCylinder(1000, getXPosition(), getZPosition(), getYPosition(), getYPosition() + 9.0f, 2.25f, 0.1f, textures);
		particlesCreated = true;
	}
	if (active) {
		ticsActive++;
		aura.updateParticleCylinder(visionYAngle);
	}
}


/* Render */
void Altar::render(GameData &data)
{
	if (active && !playSpark) {
		playSpark = true;
		data.playSound(GameData::SPARK_INDEX);
	}
	data.renderModel(GameData::ALTAR_MODEL_INDEX, getXPosition(), getYPosition() + 1.0f, getZPosition(), getYAngle(), 0.0f, 1.25f);
	if (active) aura.render(data);
	if (DEBUG) renderBoundingCilinder();
}


/* Altar activation */
void Altar::activate()
{
	active = true;
}

bool Altar::isActive()
{
	return active;
}

bool Altar::isActiveAndFinished()
{
	return active && ticsActive >= TICS_ACTIVE_LIMIT;
}