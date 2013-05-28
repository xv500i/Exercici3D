
#include "GameData.h"


const char* GameData::TEXTURE_EXT = ".png";
const char* GameData::SOUND_EXT = ".mp3";

GameData::GameData(void) 
{
	textures = std::vector<Texture>(NUM_TEXTURES);
	models = std::vector<Model>(NUM_MODELS);
	sounds = std::vector<Sound>(NUM_SOUNDS);
}

GameData::~GameData(void) {}


/* Textures */
bool GameData::loadTextures()
{
	const char* filenames[NUM_TEXTURES] = {"title", "instructions", "pause", "gameover", "button_quit", "button_start", 
										   "button_help", "button_restart", "button_mainmenu", "cursor", "lantern", "manual", 
										   "congrats", "button_next_level", "level_completed", "BallTexture", "hecatomb", 
										   "landscape", "LifeFull", "LifeEmpty", "spacescape", "icescape", "Energy",
										   "EnergyParticle1", "EnergyParticle2", "EnergyParticle3", "EnergyParticle4",
										   "EnergyTexture"};
	for (unsigned int i = 0; i < textures.size(); i++) {
		bool b = textures[i].load(filenames[i], TEXTURE_EXT);
		if (!b) return false;
	}
	return true;
}

int GameData::getTextureID(int textureIndex)
{
	return textures[textureIndex].getID();
}

void GameData::getTextureSizeInPixels(int textureIndex, int *width, int *height)
{
	textures[textureIndex].getSizeInPixels(width, height);
}


/* Models */
bool GameData::loadModels()
{
	char* filenames[NUM_MODELS] = {"Column"};
	char* extensions[NUM_MODELS] = {".png"};

	for (int i = 0; i < NUM_MODELS; i++) {
		bool b = models[i].load(filenames[i], extensions[i]);
		if (!b) return false;
	}
}

void GameData::renderModel(int modelIndex, int x, int y, int z)
{
	models[modelIndex].render(x, y, z);
}


/* Sounds */
bool GameData::loadSounds()
{
	const char* filenames[NUM_SOUNDS] = {"Jungle_Theme", "Boss_Battle", "Title_Theme", "Game_Over", "gun", "fus", 
										 "Stage_Clear", "Ending_Theme", "roar", "enemy_hit", "player_hit", "scream", 
										 "spark", "jump", "Snow_Field"};
	const bool loop[NUM_SOUNDS] = {true, true, false, false, false, false, false, false, false, false, false, false, false, false, true};
	const float volumes[NUM_SOUNDS] = {1.0f, 1.0f, 1.0f, 1.0f, 0.3f, 1.0f, 1.0f, 1.0f, 0.8f, 1.5f, 1.0f, 1.0f, 1.5f, 1.0f, 1.0f};
	for (unsigned int i = 0; i < sounds.size(); i++) {
		bool b = sounds[i].load(filenames[i], SOUND_EXT, loop[i], volumes[i]);
		if (!b) return false;
	}
	return true;
}

void GameData::playSound(int soundIndex)
{
	sounds[soundIndex].play();
}

void GameData::stopSound(int soundIndex)
{
	if (sounds[soundIndex].isPlaying()) sounds[soundIndex].stop();
}

void GameData::stopAllSounds()
{
	for (unsigned int i = 0; i < sounds.size(); i++) {
		if (sounds[i].isPlaying()) sounds[i].stop();
	}
}

bool GameData::isSoundPlaying(int soundIndex)
{
	return sounds[soundIndex].isPlaying();
}