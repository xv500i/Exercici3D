
#include "EnergyObject.h"
// DEBUG
#include "Globals.h"


const float EnergyObject::VELOCITY_Y = 0.05f;
const float EnergyObject::MIN_OFFSET_Y = 0.0f;
const float EnergyObject::MAX_OFFSET_Y = 2.0f;


EnergyObject::EnergyObject(void) : ItemObject() 
{
	type = ENERGY;
	offsetY = 0.0f;
	goingUp = true;
	particlesCreated = false;

	// New bounding cylinder
	BoundingCilinder *bc = getBoundingCilinder();
	bc->setRadius(0.7f);
}

EnergyObject::~EnergyObject(void) {}


/* Update */
void EnergyObject::update(float visionYAngle)
{
	if (!particlesCreated) {
		// Texture preparation
		std::vector<int> textures = std::vector<int>(4);
		textures[0] = GameData::ENERGY_PARTICLE_1_INDEX;
		textures[1] = GameData::ENERGY_PARTICLE_2_INDEX;
		textures[2] = GameData::ENERGY_PARTICLE_3_INDEX;
		textures[3] = GameData::ENERGY_PARTICLE_4_INDEX;

		// Particle creation 
		aura.createParticleCylinder(100, getXPosition(), getZPosition(), getYPosition() - 1.0f, getYPosition() + 9.0f, 1.0f, 0.2f, textures);
		particlesCreated = true;
	}

	// Height
	if (goingUp) {
		offsetY += VELOCITY_Y;
		if (offsetY >= MAX_OFFSET_Y) goingUp = false;
	}
	else {
		offsetY -= VELOCITY_Y;
		if (offsetY <= MIN_OFFSET_Y) goingUp = true;
	}

	// Aura particles
	aura.update(visionYAngle);
}


/* Render */
void EnergyObject::render(GameData &data)
{
	if (isPickedUp()) return;
	Point3D pos = getPosition();

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, data.getTextureID(GameData::ENERGY_TEXTURE_INDEX));
		glTranslatef(pos.getX(), pos.getY() + 1.0f + offsetY, pos.getZ());
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		GLUquadricObj *q = gluNewQuadric();
		gluQuadricOrientation(q, GLU_OUTSIDE);
		gluQuadricTexture(q, GL_TRUE);
		gluSphere(q, 0.5, 16, 16);
		gluDeleteQuadric(q);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	if (particlesCreated) aura.render(data);

	if (DEBUG) renderBoundingCilinder();
}
