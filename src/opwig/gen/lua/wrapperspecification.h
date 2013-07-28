
#ifndef OPWIG_GEN_LUA_WRAPPERSPECIFICATION_H_
#define OPWIG_GEN_LUA_WRAPPERSPECIFICATION_H_

#include <opwig/gen/wrapperspecification.h>
#include <list>
#include <string>

namespace opwig {
namespace gen {
namespace lua {

class WrapperSpecification final : public ::opwig::gen::WrapperSpecification {

  public:

    WrapperSpecification (const std::string& the_input_file);

    std::string wrapper_name () const;

    std::string FileHeader() const;

    std::string FinishFile() const;

    std::string WrapFunction(const md::Ptr<const md::Function>& obj);
    std::string WrapVariable(const md::Ptr<const md::Variable>& obj);
    std::string WrapClass(const md::Ptr<const md::Class>& obj);
    std::string WrapNamespace(const md::Ptr<const md::Namespace>& obj);
    std::string WrapEnum(const md::Ptr<const md::Enum>& obj);

    std::string LoadFuncSignature() const;
    std::string LoadFuncName() const;
    
  private:

    std::list<std::string>  wrapped_functions_;
    std::string             intput_file_;

};

inline WrapperSpecification::WrapperSpecification (const std::string& the_input_file)
    : intput_file_(the_input_file) {}

inline std::string WrapperSpecification::wrapper_name () const {
    return "Lua";
}

inline std::string WrapperSpecification::LoadFuncSignature () const {
    return "int(*)(lua_State*)";
}

inline std::string WrapperSpecification::LoadFuncName () const {
    return "luaopen_"+module_name();
}

} // namespace lua
} // namespace gen
} // namespace opwig

#endif // OPWIG_GEN_LUA_WRAPPERSPECIFICATION_H_

