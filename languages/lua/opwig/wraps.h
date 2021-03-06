
#ifndef OPWIG_GEN_LUA_WRAPS_H_
#define OPWIG_GEN_LUA_WRAPS_H_

#include <opwig/md/ptr.h>

#include <string>
#include <list>

namespace opa {
namespace lua {

struct DataWrap {
    std::string name;
    std::string nesting;
};

struct ModuleWrap : public std::enable_shared_from_this<ModuleWrap> {

    ModuleWrap(const ModuleWrap&) = delete;
    ModuleWrap& operator=(const ModuleWrap&) = delete;

    std::string                     name, path, nesting;
    std::list<DataWrap>             functions;
    std::list<DataWrap>             getters;
    std::list<DataWrap>             setters;
    std::list<DataWrap>             member_getters;
    std::list<DataWrap>             member_setters;
    std::list<DataWrap>             member_functions;

    /// Tells if the module represents a class.
    /** @return bool Wheter the module is a class.
     */
    bool is_class () const;

    /// Tells if the module has any wraps in it.
    /** @return bool Whether there are any wrap.
     */
    bool has_wraps () const;

    /// Tells if the module has any sub-modules in it.
    /** @return Whether there are children modules.
     */
    bool has_children () const;

    /// Gives a read-only access to the module's submodules.
    /** @return const std::list<md::Ptr<ModuleWrap>>&
     **         A read-only reference to the list of child modules.
     */
    const std::list<opwig::md::Ptr<ModuleWrap>>& children () const;

    /// Gives the module's supermodule.
    /** @return md::Ptr<ModuleWrap> The parent module.
     */
    opwig::md::Ptr<ModuleWrap> parent () const;

    /// Adds a submodule to the module.
    /** @param the_child The new child module.
     */
    void AddChild (const opwig::md::Ptr<ModuleWrap>& the_child);

  private:

    friend class WrapperState;

    std::list<opwig::md::Ptr<ModuleWrap>>  children_;
    opwig::md::WeakPtr<ModuleWrap>         parent_;
    bool                            is_class_;
    size_t                          nonclass_children_num_;

    ModuleWrap (bool is_class_flag = false)
        : is_class_(is_class_flag), nonclass_children_num_(0) {}

};

inline bool ModuleWrap::is_class () const {
    return is_class_;
}

inline bool ModuleWrap::has_wraps () const {
    return !functions.empty() || !getters.empty() || !setters.empty();
}

inline bool ModuleWrap::has_children () const {
    return !children_.empty(); // nonclass_children_num_ > 0;
}

inline const std::list<opwig::md::Ptr<ModuleWrap>>& ModuleWrap::children () const {
    return children_;
}

inline opwig::md::Ptr<ModuleWrap> ModuleWrap::parent () const {
    return parent_.lock();
}

inline void ModuleWrap::AddChild (const opwig::md::Ptr<ModuleWrap>& the_child) {
    children_.push_back(the_child);
    the_child->parent_ = shared_from_this();
    if (!the_child->is_class()) nonclass_children_num_++;
}

} // namespace lua
} // namespace opa

#endif

