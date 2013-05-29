
#include "Altar.h"
// DEBUG
#include "Globals.h"


Altar::Altar(void) : GameObject() 
{
	type = ALTAR;
	active = false;
	particlesCreated = false;
	BoundingCilinder *bc = getBoundingCilinder();
	bc->setHeight(5.0f);
	bc->setRadius(1.3f);
}

Altar::~Altar(void) {}


/* Update */
void Altar::update(float visionYAngle)
{
	if (!particlesCreated && active) {
		// Texture preparation
		std::vector<int> textures = std::vector<int>(4);
		textures[0] = GameData::ENERGY_PARTICLE_1_INDEX;
		textures[1] = GameData::ENERGY_PARTICLE_2_INDEX;
		textures[2] = GameData::ENERGY_PARTICLE_3_INDEX;
		textures[3] = GameData::ENERGY_PARTICLE_4_INDEX;

		// Particle creation 
		aura.createParticleCylinder(500, getXPosition(), getZPosition(), getYPosition(), getYPosition() + 9.0f, 2.25f, 0.1f, textures);
		particlesCreated = true;
	}
	if (active) aura.updateParticleCylinder(visionYAngle);
}


/* Render */
void Altar::render(GameData &data)
{
	data.renderModel(GameData::ALTAR_MODEL_INDEX, getXPosition(), getYPosition(), getZPosition(), getYAngle(), 0.0f, 1.25f);
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