#pragma once
#include "pch.h"

class SOUNDSYSTEM_API SoundEngine
{
public:
	static SoundEngine* get();
	SoundEngine();
	~SoundEngine();
	irrklang::ISoundEngine* get_sound_engine();
private:
	irrklang::ISoundEngine* engine;
};

class SOUNDSYSTEM_API SoundSystem
{
public:
	SoundSystem();
	void load(std::string filename);
	void play(std::string sound_name);
	//irrklang::ISoundSource* source(std::string);

private:
	std::unordered_map<std::string, irrklang::ISoundSource*> sources;
	SoundEngine* engine;
};