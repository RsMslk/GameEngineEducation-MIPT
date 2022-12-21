#pragma once

#include "flecs.h"
#include "RenderEngine.h"
#include "../InputHandler.h"
#include "../SoundSystem/soundsystem.h"	

class EntitySystem
{
public:
	EntitySystem() = delete;
	EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler, SoundSystem* soundsystem);

	void Update();
private:
	flecs::world ecs;
};

