
#ifndef OUROBOROS_SCRIPT_LUA_LUAWRAPPER_H_
#define OUROBOROS_SCRIPT_LUA_LUAWRAPPER_H_

#include <string>
#include <list>
#include <vector>

#include <languages/lua/defs.h>
#include <OPA/langwrapper.h>

namespace ouroboros {
namespace lua {

class DataGear;
class LuaData;
typedef ouroboros::InheritableLangWrapper<lua_CFunction> LuaWrapperBase;

class LuaWrapper: public LuaWrapperBase {

  public:

    LuaWrapper() :
        LuaWrapperBase("lua",LANG(Lua), "Lua"),
        data_gear_(nullptr) {}
    ~LuaWrapper() {
        if (data_gear_) Finalize();
    }

    /// Overwritten methods.

    bool Initialize();

    void Finalize();

    VirtualData::Ptr NewData();

    LuaData* NewLuaData();

    void ExecuteCode(const std::string& code);

    VirtualObj LoadModule(const std::string& name);

    /// Other methods.

    VirtualData::Ptr OperateBuffer(const DataID operand_id, lua_CFunction op);

    DataGear& data_gear() { return *data_gear_; }

    void Share(DataGear* gear) {
        data_gear_ = gear;
    }

    DataGear* shared_gear() {
        return data_gear_;
    }

    void AddToBuffer(DataID id) {
        buffer_.push_back(id);
    }

    void CleanBuffer() {
        buffer_.clear();
    }

  private:

    DataGear*   data_gear_;
    DataBuffer  buffer_;

    DataID NewDataID();

    void DeleteDataID(DataID id);

    VirtualData::Ptr LoadChunk(const std::string& chunk, lua_CFunction loader);

};

std::string NameConversion(const std::string& name);

} /* namespace lua */
} /* namespace ouroboros */

#endif /* OUROBOROS_SCRIPT_LUA_LUAWRAPPER_H_ */
