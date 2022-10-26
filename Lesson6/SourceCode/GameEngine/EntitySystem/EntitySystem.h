#pragma once

#include "flecs.h"
#include "RenderEngine.h"
#include "../InputHandler.h"

class IScriptSystem;
class EntitySystem
{
public:
	EntitySystem() = delete;
	EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler, IScriptSystem* scriptSystem, std::string xml_path);
	void Update();
private:
	flecs::world ecs;
};

