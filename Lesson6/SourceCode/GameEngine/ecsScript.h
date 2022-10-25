#pragma once
#include"flecs.h"
#include<memory>
#include<vector>
#include <string>

class CScriptProxy;

struct Scripts
{
	template <typename... Args>
	Scripts(Args... args) : names{ args... } {}
	std::vector<std::string> names;
};

void init_script_state(flecs::world& ecs, std::shared_ptr<CScriptProxy> scriptProxy);
void register_ecs_script_systems(flecs::world& ecs);