#include "sdlFiles.h"
#include <iostream>
#include "defs.h"
#include "sound.h"
Mix_Chunk *pushBlock;
bool channelArray[MAX_CHANNELS];
bool levelMusicLoaded[MAX_LEVEL] = { 0 };
char *musicNames[] = { "Dystopic-Factory.mp3", "Puzzle-Game-5.mp3" };
int numSongs = sizeof(musicNames) / sizeof(musicNames[0]);
Mix_Music *levelMusic[sizeof(musicNames) / sizeof(musicNames[0])] = { 0 };
extern std::string appPath;
std::string musicPath;
Mix_Chunk *snd_explode = NULL;
Mix_Chunk *snd_switch = NULL;
Mix_Chunk *snd_teleport = NULL;
Mix_Chunk *snd_spring = NULL;
Mix_Chunk *snd_splash = NULL;
Mix_Chunk *snd_zap = NULL;
Mix_Chunk *snd_smash = NULL;
Mix_Music *titleMusic = NULL;
Mix_Music *levelSelectMusic = NULL;
bool audioEnabled = true;
/*SDL WII bug avoidance*/
void setPanning(unsigned int channel, unsigned int right)
{
	//Fix the reversed panning on the wii
#ifdef GEKKO
	Mix_SetPanning(channel, right, 254-right);
#else
	Mix_SetPanning(channel,254-right,right);
#endif
}
//Initializes the music
void musicInit()
{
	numSongs = sizeof(musicNames) / sizeof(musicNames[0]);
	musicPath.assign("music/");
	if (Mix_OpenAudio( 22050*2, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		audioEnabled = false;
		return;
	}
	snd_explode = Mix_LoadWAV("sound/explode.wav");
	snd_switch = Mix_LoadWAV("sound/switch.wav");
	snd_teleport = Mix_LoadWAV("sound/teleport.wav");
	snd_spring = Mix_LoadWAV("sound/spring.wav");
	snd_splash = Mix_LoadWAV("sound/splash.wav");
	snd_zap = Mix_LoadWAV("sound/zap.wav");
	snd_smash = Mix_LoadWAV("sound/smash.wav");
	titleMusic = Mix_LoadMUS("music/Sculpture-Garden.mp3");
	levelSelectMusic = Mix_LoadMUS("music/Techno-Gameplay.mp3");
}
void freeMusic(int levelNum)
{
	if (!audioEnabled)
		return;
	if (levelNum < 0 || levelNum > MAX_LEVEL || levelMusic[levelNum-1] == NULL)
		return;
	Mix_HaltMusic();
	Mix_FreeMusic(levelMusic[levelNum - 1]);
	levelMusic[levelNum - 1] = NULL;
	levelMusicLoaded[levelNum - 1] = false;
}
void playMusic(Mix_Music *music)
{
	if (!audioEnabled)
		return;
	Mix_PlayMusic(music, -1);
}
void playMusic(int levelNum)
{
	Mix_Volume(-1, 128);
	if (!audioEnabled)
		return;
	if (levelNum < 0 || levelNum > MAX_LEVEL)
		return;
	char *fileName = musicNames[(levelNum-1) % numSongs];
	char buffer[80];
	if (levelMusic[(levelNum - 1) % numSongs] == NULL)
	{
		sprintf(buffer, "%s%s", musicPath.c_str(), fileName);
		levelMusic[(levelNum - 1) % numSongs] = Mix_LoadMUS(buffer);
	}
	Mix_PlayMusic(levelMusic[(levelNum-1) % numSongs], -1);
}
bool playSound(Mix_Chunk *input)
{
	Mix_Volume(-1, 128);
	if (!audioEnabled)
		return false;
	if (input == NULL)
		return false;
	if (Mix_PlayChannel( 0, input, 0 ) == -1)
		return false;
	else
		return true;
}