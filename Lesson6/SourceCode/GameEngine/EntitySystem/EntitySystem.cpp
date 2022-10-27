#include "EntitySystem.h"
#include "ecsSystems.h"
#include "ecsMesh.h"
#include "ecsControl.h"
#include "ecsPhys.h"
#include "../GameEngine/ecsScript.h"
#include "../GameEngine/Loader.h"
#include <functional>
#include <array>
#include <fstream>
#include <stdio.h>

EntitySystem::EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler, IScriptSystem* scriptSystem, std::string xml_path)
{
    //Loader::LoadXML(xml_path);
    
    ecs.entity("inputHandler")
        .set(InputHandlerPtr{ inputHandler });
    ecs.entity("renderEngine")
        .set(RenderEnginePtr{ renderEngine });
    ecs.entity("scriptSystem")
        .set(ScriptSystemsPtr {scriptSystem});
    register_ecs_mesh_systems(ecs);
    register_ecs_control_systems(ecs);
    register_ecs_phys_systems(ecs);
    register_ecs_script_systems(ecs);

    /*auto cubeControl = ecs.entity()
        .set(Position{ 0.f, 0.f, 0.f })
        .set(Velocity{ 1.f, 0.f, 0.f })
        .set(FrictionAmount{ 0.f })
        .set(JumpSpeed{ 10.f })
        .set(Speed{ 10.f })
        .set(Gravity{ 0.f, -9.8065f, 0.f })
        .set(BouncePlane{ 0.f, 1.f, 0.f, 0.f })
        .set(Bounciness{ 0.5f })
        .set(Scripts(
            "../../../Assets/Scripts/movable.lua"))
        .add<Controllable>()

        .add<CubeMesh>();*/

    Create_player(xml_path);

    auto cubeMoving = ecs.entity()
        .set(Position{ 0.f, 0.f, 0.f })
        .set(Velocity{ 0.f, 3.f, 0.f })
        .set(Gravity{ 0.f, -9.8065f, 0.f })
        .set(BouncePlane{ 0.f, 1.f, 0.f, 5.f })
        .set(Bounciness{ 1.f })
        .add<CubeMesh>();
}

void EntitySystem::Update()
{
    ecs.progress();
}

void EntitySystem::Create_player(std::string xml_path) {
    Loader loader = Loader();
    loader.LoadXML(xml_path);
    auto level = loader.Get_level();
    std::unordered_map<std::string, std::function<void(flecs::entity, std::string)>> entity_dict = {
        {
            "position", [](flecs::entity e, const std::string& val) {
                auto vec = Loader::GetVal<3>(val);
                e.set(Position{ vec[0], vec[1], vec[2] });
            }
        },
        {
            "velocity", [](flecs::entity e, const std::string& val) {
                auto vec = Loader::GetVal<3>(val);
                e.set(Velocity{ vec[0], vec[1], vec[2] });
            }
        },
        {
            "cube_mesh", [](flecs::entity e, const std::string& val) {
                e.add<CubeMesh>();
            }
        }
    };
    
   /* FILE* file_1;
    file_1 = fopen("map_out.txt", "a");
    fprintf(file_1, " map_ SIZE: %d get_lvl_size %d", (int)entity_dict.size(),level.size() );
    fclose(file_1);*/
    for (auto& entity : level)
    {
        flecs::entity e = ecs.entity();
        
        for (auto& component : entity)
        {
            //file_1 = fopen("map_out.txt", "a");
            entity_dict[component.first](e, component.second);
            /*fprintf(file_1, " Map SIZE: %s", component.first);
            fprintf(file_1, " Map SIZE: %d", (int) entity_dict.size());
            fclose(file_1);*/
        }
    }
    
}