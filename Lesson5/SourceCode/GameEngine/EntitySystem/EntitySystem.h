#pragma once

#include "flecs.h"
#include "RenderEngine.h"
#include "../InputHandler.h"
#include "SoundSystem.h"

class IScriptSystem;
class EntitySystem
{
public:
	EntitySystem() = delete;
	EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler, IScriptSystem* scriptSystem, SoundSystem* soundsystem);
	void Update();
private:
	flecs::world ecs;
};

