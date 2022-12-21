#ifndef PCH_H
#define PCH_H

#pragma once
#include "framework.h"
#include <irrKlang.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <array>
#endif //PCH_H


#ifdef SOUNDSYSTEM_EXPORTS
#define SOUNDSYSTEM_API __declspec(dllexport)
#else
#define SOUNDSYSTEM_API __declspec(dllimport)
#endif