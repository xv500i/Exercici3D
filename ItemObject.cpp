
#include "ItemObject.h"
// DEBUG
#include "Globals.h"


ItemObject::ItemObject() : GameObject() {}

ItemObject::ItemObject(bool energy) : GameObject()
{
	if (energy) type = ENERGY;
	else type = MEDIKIT;
	pickedUp = false;
	particlesCreated = false;
}

ItemObject::~ItemObject(void) {}


/* Update */
void ItemObject::update()
{
	if (type == ENERGY) {
		if (!particlesCreated) {
			// Texture preparation
			std::vector<int> textures = std::vector<int>(4);
			textures[0] = GameData::ENERGY_PARTICLE_1_INDEX;
			textures[1] = GameData::ENERGY_PARTICLE_2_INDEX;
			textures[2] = GameData::ENERGY_PARTICLE_3_INDEX;
			textures[3] = GameData::ENERGY_PARTICLE_4_INDEX;
			std::vector<int> masks = std::vector<int>(4);
			masks[0] = GameData::ENERGY_PARTICLE_MASK_1_INDEX;
			masks[1] = GameData::ENERGY_PARTICLE_MASK_2_INDEX;
			masks[2] = GameData::ENERGY_PARTICLE_MASK_3_INDEX;
			masks[3] = GameData::ENERGY_PARTICLE_MASK_4_INDEX;

			// Particle creation 
			particles.createParticleCylinder(getXPosition(), getZPosition(), getYPosition() - 1.0f, 1.0f, textures, masks);
			particlesCreated = true;
		}
		particles.update();
	}
}


/* Render */
void ItemObject::render(GameData &data)
{
	if (pickedUp) return;
	Point3D pos = getPosition();
	glPushMatrix();
		if (type == MEDIKIT) glColor3f(0.0f, 1.0f, 0.0f);
		else if (type == ENERGY) glColor3f(0.0f, 0.0f, 1.0f);
		glTranslatef(pos.getX(), pos.getY() + 1.0f, pos.getZ());
		GLUquadricObj *q = gluNewQuadric();
		gluSphere(q, 0.5, 16, 16);
		gluDeleteQuadric(q);

		glColor3f(1.0f,1.0f,1.0f);
	glPopMatrix();

	if (type == ENERGY) particles.render();

	if (DEBUG) renderBoundingCilinder();
}


/* Pick up */
void ItemObject::pickUp()
{
	pickedUp = true;
}

bool ItemObject::isPickedUp()
{
	return pickedUp;
}