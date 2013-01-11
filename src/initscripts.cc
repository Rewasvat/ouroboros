#include <script.h>

#include <config.h>
#include <scriptmanager.h>
#include <languages/lua/luawrapper.h>
#include <languages/python/pythonwrapper.h>

void force_link_function_ouroboros_internal(void) { 
    extern int OUROBOROS_MODULES_HEARTBEAT; 
    OUROBOROS_MODULES_HEARTBEAT = 1;
}

namespace ouroboros {

void InitScripts() {
#ifdef OUROBOROS_LUA_ENABLED
    SCRIPT_MANAGER()->Register(new ouroboros::lua::LuaWrapper());
#endif
#ifdef OUROBOROS_PYTHON_ENABLED
    SCRIPT_MANAGER()->Register(new ouroboros::python::PythonWrapper());
#endif
}

} // namespace ouroboros
