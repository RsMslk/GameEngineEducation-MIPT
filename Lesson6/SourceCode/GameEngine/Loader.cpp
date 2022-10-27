#include "Loader.h"
#include <cassert>

void Loader::LoadXML(std::string file) {
	tinyxml2::XMLDocument level_xml{};
	level_xml.LoadFile(file.data());
	assert(!level_xml.Error());
}

std::vector<Loader::LevelComponents> Loader::Get_level() {
	std::vector<Loader::LevelComponents> entities;
	auto entity_elements = xml_file.FirstChildElement("entities");
	if (entity_elements)
	{
		auto entity_element = entity_elements->FirstChildElement("entity");
		while (entity_element)
		{
			auto& entity = entities.emplace_back();
			auto component = entity_element->FirstChildElement();
			while (component)
			{
				auto comp_val = component->GetText();
				if (!comp_val)
				{
					entity.emplace_back(component->Name(), "");
				}
				else
				{
					entity.emplace_back(component->Name(), comp_val);
				}
				component = component->NextSiblingElement();
			}
			entity_element = entity_element->NextSiblingElement("entity");
		}
	}
	return entities;
}