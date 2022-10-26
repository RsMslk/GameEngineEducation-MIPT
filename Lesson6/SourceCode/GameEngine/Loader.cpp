#include "Loader.h"

tinyxml2::XMLDocument Loader::LoadXML(std::string file) {
	tinyxml2::XMLDocument level_xml{};
	level_xml.LoadFile(file.data());
	return{};
}