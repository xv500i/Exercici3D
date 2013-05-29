
#pragma once

#include <vector>
#include "Texture.h"
#include "Model.h"
#include "Sound.h"


class GameData
{
private:
	/* Textures */
	const static int NUM_TEXTURES = 34;		// TOCHANGE: modificar depenent del numero de textures carregades
	const static char* TEXTURE_EXT;
	
	/* Models */
	const static int NUM_MODELS = 4;		// TOCHANGE: modificar depenent del numero de models carregats

	/* Sounds */
	const static int NUM_SOUNDS = 15;		// TOCHANGE: modificar depenent del numero de sons carregats
	const static char* SOUND_EXT;

	std::vector<Texture> textures;		/* All loaded textures */
	std::vector<Model> models;			/* All loaded models */
	std::vector<Sound> sounds;			/* All loaded sounds */

public:
	/* Texture indexes */		// TOCHANGE: afegir indexs de totes les textures carregades
	const static int TITLE_INDEX = 0;
	const static int INSTRUCTIONS_INDEX = 1;
	const static int PAUSE_INDEX = 2;
	const static int GAMEOVER_INDEX = 3;
	const static int QUIT_INDEX = 4;
	const static int START_INDEX = 5;
	const static int HELP_TEX_INDEX = 6;
	const static int RESTART_INDEX = 7;
	const static int RETURN_INDEX = 8;
	const static int CURSOR_INDEX = 9;
	const static int LANTERN_INDEX = 10;
	const static int MANUAL_INDEX = 11;
	const static int CONGRATS_INDEX = 12;
	const static int NEXT_LEVEL_INDEX = 13;
	const static int LEVEL_COMPLETED_INDEX = 14;
	const static int PLAYER_TEXTURE_INDEX = 15;
	const static int LEVEL1_TEXTURE_INDEX = 16;
	const static int LANDSCAPE_TEXTURE_INDEX = 17;
	const static int LIFEFULL_HUD_TEXTURE_INDEX = 18;
	const static int LIFEEMPTY_HUD_TEXTURE_INDEX = 19;
	const static int SPACESCAPE_TEXTURE_INDEX = 20;
	const static int ICESCAPE_TEXTURE_INDEX = 21;
	const static int ENERGY_HUD_TEXTURE_INDEX = 22;
	const static int ENERGY_PARTICLE_1_INDEX = 23;
	const static int ENERGY_PARTICLE_2_INDEX = 24;
	const static int ENERGY_PARTICLE_3_INDEX = 25;
	const static int ENERGY_PARTICLE_4_INDEX = 26;
	const static int ENERGY_TEXTURE_INDEX = 27;
	const static int LEVEL2_TEXTURE_INDEX = 28;
	const static int LEVEL3_TEXTURE_INDEX = 29;
	const static int FUSRODAH_PARTICLE_1_INDEX = 30;
	const static int FUSRODAH_PARTICLE_2_INDEX = 31;
	const static int FUSRODAH_PARTICLE_3_INDEX = 32;
	const static int FUSRODAH_PARTICLE_4_INDEX = 33;
	
	/* Model indexes */			// TOCHANGE: afegir indexs de tots els models carregats
	const static int COLUMN_MODEL_INDEX = 0;
	const static int MEDIKIT_MODEL_INDEX = 1;
	const static int BARREL_MODEL_INDEX = 2;
	const static int ALTAR_MODEL_INDEX = 3;

	/* Sounds indexes */		// TOCHANGE: afegir indexs de tots els sounds carregats
	const static int JUNGLE_THEME_INDEX = 0;
	const static int BOSS_THEME_INDEX = 1;
	const static int INTRO_THEME_INDEX = 2;
	const static int GAME_OVER_INDEX = 3;
	const static int GUN_SOUND_INDEX = 4;
	const static int FUS_SOUND_INDEX = 5;
	const static int STAGE_CLEAR_INDEX = 6;
	const static int ENDING_THEME_INDEX = 7;
	const static int ROAR_INDEX = 8;
	const static int ENEMY_OUCH_INDEX = 9;
	const static int PLAYER_OUCH_INDEX = 10;
	const static int PLAYER_SCREAM_INDEX = 11;
	const static int SPARK_INDEX = 12;
	const static int JUMP_SOUND_INDEX = 13;
	const static int SNOW_FIELD_THEME = 14;


	GameData(void);
	~GameData(void);

	/* Textures */
	bool loadTextures();
	int getTextureID(int textureIndex);
	void getTextureSizeInPixels(int textureIndex, int *width, int *height);

	/* Models */
	bool loadModels();
	void renderModel(int modelIndex, float x, float y, float z, float angleY = 0.0f, float angleX = 0.0f, float scale = 1.0f);

	/* Sounds */
	bool loadSounds();
	void playSound(int soundIndex);
	void stopSound(int soundIndex);
	void stopAllSounds();
	bool isSoundPlaying(int soundIndex);
};