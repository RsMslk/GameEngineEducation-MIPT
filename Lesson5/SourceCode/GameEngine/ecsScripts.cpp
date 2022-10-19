#include "ecsScript.h"
#include "EntitySystem/ecsSystems.h"
#include "EntitySystem/ecsPhys.h"
#include "EntitySystem/ecsControl.h"
#include "EntitySystem/ecsMesh.h"
#include "Input.h"
#include"../ScriptSystem/ScriptSystem.h"
#include "../ScriptSystem/ScriptProxy.h"
#include "../GameEngine/InputHandler.h"


void register_ecs_script_systems(flecs::world& ecs)
{
	static auto scriptSystemQuery = ecs.query<ScriptSystemsPtr>();
	static auto inputHandlerQuery = ecs.query<InputHandlerPtr>();

	ecs.system<Scripts>().each([&](flecs::entity e, Scripts& scripts)
		{
			inputHandlerQuery.each([&](InputHandlerPtr& inputHandler)
				{
					scriptSystemQuery.each([&](ScriptSystemsPtr& scriptSystem)
						{
							for (const auto& script : scripts.names)
							{
								auto scriptProxy = scriptSystem.ptr->CreateProxy(script.c_str());
								init_script_state(ecs, scriptProxy);
								scriptProxy->BindValue("input_handler", std::ref(*inputHandler.ptr));
								scriptProxy->BindValue("entity_id", e.id());
							}
						});
				});
			e.remove<Scripts>();
		});
}

void init_script_state(flecs::world& ecs, std::shared_ptr<CScriptProxy> scriptProxy)
{

    sol::state& state = scriptProxy->GetState();
    state["eIC_GoLeft"] = eIC_GoLeft;
    state["eIC_GoRight"] = eIC_GoRight;
    state["eIC_Jump"] = eIC_Jump;
    state["world"] = std::ref(ecs);
    state.new_usertype<Position>("Position",
        "x", &Position::x,
        "y", &Position::y,
        "z", &Position::z);
    state.new_usertype<Velocity>("Velocity",
        "x", &Velocity::x,
        "y", &Velocity::y,
        "z", &Velocity::z);
    state.new_usertype<JumpSpeed>("JumpSpeed",
        "val", &JumpSpeed::val);
    state.new_usertype<BouncePlane>("BouncePlane",
        "w", &BouncePlane::w,
        "x", &BouncePlane::x,
        "y", &BouncePlane::y,
        "z", &BouncePlane::z);
    state.new_usertype<std::bitset<eIC_Max>>("Bitset",
        "test", &std::bitset<eIC_Max>::test);
    state.new_usertype<InputHandler>("InputHandler",
        "getInputState", &InputHandler::GetInputState);
    state.new_usertype<flecs::world>("World",
        "getEntity", [](flecs::world& world, flecs::entity_t id) { return world.entity(id); });
    state.new_usertype<flecs::entity>("Entity",
        "getPosition", [](flecs::entity e) { return e.get<Position>(); },
        "getVelocity", [](flecs::entity e) { return e.get<Velocity>(); },
        "getJumpSpeed", [](flecs::entity e) { return e.get<JumpSpeed>()->val; },
        "getBouncePlane", [](flecs::entity e) { return e.get<BouncePlane>(); });
}