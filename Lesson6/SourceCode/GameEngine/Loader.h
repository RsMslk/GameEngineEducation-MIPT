#pragma once

#include<string>
#include"tinyxml2.h"
#include <vector>
#include <array>


class Loader {
public:
	void LoadXML(std::string file);
	typedef std::vector<std::pair<std::string, std::string>> LevelComponents;
	
	std::vector<LevelComponents> Get_level();

	template <int n>
	static std::array<float, n> GetVal(const std::string& s);
	
private:
	tinyxml2::XMLDocument xml_file;
};

template <int n>
static std::array<float, n> Loader::GetVal(const std::string& s)
{
	//std::vector<float> val(n);
	std::array<float, n> vals = {};
	int counter_vals = 0;
	std::string substr = {};
	for (int i = 0; i < s.size(); i++)
	{
		
		
		if (s[i] == '\n')
		{
			//val.push_back(std::stof(substr));
			vals[i] = std::stof(substr);
			counter_vals++;
			substr.clear();
			break;
		}
		else
		{
			if (s[i] == ' ')
			{
				//val.push_back(std::stof(substr));
				vals[i] = std::stof(substr);
				counter_vals++;
				substr.clear();
			} 
			else
				substr.append(&s[i]);
		}
	}
	
	//std::copy_n(val.begin(), n, vals.begin());
	return vals;
}