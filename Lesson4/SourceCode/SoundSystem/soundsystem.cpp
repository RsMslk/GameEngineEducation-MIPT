#include "soundsystem.h"
#include <assert.h>


SoundEngine* SoundEngine::get()
{
	static SoundEngine* snd_eng = new SoundEngine();
	return snd_eng;
}

irrklang::ISoundEngine* SoundEngine::get_sound_engine()
{
	return this->engine;
}


SoundEngine::SoundEngine()
{
	engine = irrklang::createIrrKlangDevice();
	if (!engine)
	{
		printf("Could not startup engine\n"); // error starting up the engine
	}
}

SoundEngine::~SoundEngine() {
	engine->drop();
}

SoundSystem::SoundSystem()
{
	engine = SoundEngine::get();
}
void SoundSystem::load(std::string filename)
{

	irrklang::ISoundSource* Sound = SoundSystem::engine->get_sound_engine()->addSoundSourceFromFile("sound.wav");
	sources.insert(std::pair<std::string, irrklang::ISoundSource*>("Sound", Sound));
}

void SoundSystem::play(std::string sound_name)
{
	engine->get_sound_engine()->play2D(sources.find(sound_name)->second);
}