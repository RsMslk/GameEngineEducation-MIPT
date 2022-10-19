#include "ScriptProxy.h"

CScriptProxy::CScriptProxy(const std::string& filename)
{
	lua_script.open_libraries(sol::lib::base);
	sol::protected_function target = lua_script.load_file(filename);;
	script = target.dump();
}

void CScriptProxy::run_script()
{
	auto res = lua_script.safe_script(script.as_string_view());

}
sol::state& CScriptProxy::GetState()
{
	return lua_script;
}
