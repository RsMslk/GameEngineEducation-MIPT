#include "ecsControl.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "flecs.h"
#include "../InputHandler.h"
#include "SoundSystem.h"

void register_ecs_control_systems(flecs::world &ecs)
{
	static auto sound = ecs.query<SoundSystemPtr>();
}

