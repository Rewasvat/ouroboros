

#include <languages/lua/luawrapper.h>

#include <opa/virtualdata.h>
#include <opa/virtualobj.h>
#include <languages/lua/luadata.h>
#include <languages/lua/bootstrapgear.h>
#include <languages/lua/datagear.h>
#include <languages/lua/modules.h>

#include <opa/scriptmanager.h>

namespace opa {
namespace lua {

using std::string;
using std::vector;

/// Overwritten methods.

bool LuaWrapper::Initialize() {
    if (data_gear_) return true;
    RegisterModules(this);
    BootstrapGear btgear;
    do {
        if (!btgear.Initialize(modules_)) break;
        modules_.clear();
        data_gear_ = btgear.NextGear();
        if (!data_gear_) break;
        return true;
    } while(0);
    btgear.Abort();
    return false;
}

void LuaWrapper::Finalize() {
    delete data_gear_;
    data_gear_ = nullptr;
}

VirtualData::Ptr LuaWrapper::NewData() {
    return VirtualData::Ptr(NewLuaData());
}

void LuaWrapper::ExecuteCode(const std::string& code) {
    LoadChunk(code, DataGear::DoString);
}

VirtualObj LuaWrapper::LoadModule(const string& name) {
	string fullpath = SCRIPT_MANAGER()->scripts_path() + SCRIPT_MANAGER()->ConvertDottedNotationToPath(name) + "." + file_extension();
    return VirtualObj(LoadChunk(fullpath, DataGear::DoFile));
}

/// Other methods.

LuaData* LuaWrapper::NewLuaData() {
    return new LuaData(
        this,
        NewDataID()
    );
}
VirtualData::Ptr LuaWrapper::OperateBuffer(const DataID operand_id,
                                           lua_CFunction op) {
    DataID result_id = NewDataID();
    bool success = data_gear()
        .SafeCall(op)
        .Arg(operand_id)
        .Arg(&buffer_)
        .Arg(result_id)
        .NoResult();
    buffer_.clear();
    if (!success) {
        LuaMsg("was lua data #%d.\n", operand_id);
        DeleteDataID(result_id);
        return VirtualData::Ptr();
        // TODO throw exception!
    }
    return data_gear_->HasValue(result_id)
        ? VirtualData::Ptr(new LuaData(this, result_id))
        : VirtualData::Ptr();
}

DataID LuaWrapper::NewDataID() {
    return data_gear()
        .SafeCall(DataGear::GenerateID)
        .GetResult<DataID>(LUA_NOREF);
}

void LuaWrapper::DeleteDataID(DataID id) {
   data_gear()
       .SafeCall(DataGear::DestroyID)
       .Arg(id)
       .NoResult();
}

VirtualData::Ptr LuaWrapper::LoadChunk(const string& chunk,
                                       lua_CFunction loader) {
    DataID result_id = NewDataID();
    bool success = data_gear()
        .SafeCall(loader)
        .Arg(chunk.c_str())
        .Arg(result_id)
        .NoResult();
    if (!success) {
        DeleteDataID(result_id);
        return VirtualData::Ptr();
    }
    return data_gear_->HasValue(result_id)
        ? VirtualData::Ptr(new LuaData(this, result_id))
        : VirtualData::Ptr();
}

std::string NameConversion(const std::string& name) {
    std::string result = name;
    for(size_t i = 0; i < result.size(); ++i)
        if(result[i] == '_') result[i] = '.';
    return result;
}

} /* namespace lua */
} /* namespace opa */
