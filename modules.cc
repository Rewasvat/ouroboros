/// WHAT WIZARDY IS THIS!?
#define MODULES_LIST(LANG, ACTION) 

#define LANGUAGES_LIST(ACTION)  \
    ACTION(LUA) \
    ACTION(PYTHON)

#include <ouroboros/module.h>
#include <ouroboros/languages/lua/luawrapper.h>
#include <ouroboros/languages/lua/modules.h>
#include <ouroboros/languages/python/pythonwrapper.h>
#include <ouroboros/languages/python/modules.h>

#define MODULE_INIT_DECLARTION(LANG, NAME) extern LANG##_INIT_FUNCTION_SIGNATURE(NAME);

#define DECLARE_MODULE_INITS(LANG) extern "C" { MODULES_LIST(LANG, MODULE_INIT_DECLARTION) }

#define MODULE_ITEM(LANG, name) \
    LANG##_NAMESPACE::AddModule(::ouroboros::Module< LANG##_NAMESPACE::inittype >(LANG##_MODULE_NAME(name), LANG##_INIT_FUNCTION_NAME(name)));

#define DECLARE_MODULES(LANG) \
static int build_##LANG##_MODULES() { \
    MODULES_LIST(LANG, MODULE_ITEM) \
    return 1; \
} \
static int LANG##_MODULES = build_##LANG##_MODULES();

LANGUAGES_LIST(DECLARE_MODULE_INITS)
LANGUAGES_LIST(DECLARE_MODULES)

int UGDK_MODULES_HEARTBEAT = 0;