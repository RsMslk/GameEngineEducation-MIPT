#pragma once

#pragma warning(disable:4251)

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <cassert>
#include <wrl.h>
#include <string>
#include <memory>

#ifdef RENDERENGINE_EXPORTS
#define SOUNDSYSTEM_API __declspec(dllexport)
#else
#define SOUNDSYSTEM_API __declspec(dllimport)
#endif