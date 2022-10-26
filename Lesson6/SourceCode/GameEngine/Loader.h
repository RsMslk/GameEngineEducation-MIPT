#pragma once

#include<string>
#include"tinyxml2.h"

class Loader {
public:
	static tinyxml2::XMLDocument LoadXML(std::string file);
};