
#include <opwig/json/reader.h>

#include <opwig/md/accessspecifier.h>
#include <opwig/md/function.h>
#include <opwig/json/exceptions.h>

#include <libjson.h>

#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <map>

using std::list;
using std::string;
using std::ifstream;
using opwig::md::Ptr;
using opwig::md::Namespace;
using opwig::md::Scope;
using opwig::md::Class;

namespace opwig {
namespace json {

namespace {

    auto void_type = md::Type::Create("void", false);

    std::map<std::string, md::AccessSpecifier> access_specifier_mapper = {
        { "private", md::AccessSpecifier::PRIVATE },
        { "protected", md::AccessSpecifier::PROTECTED },
        { "public", md::AccessSpecifier::PUBLIC },
    };

    std::pair<Ptr<Scope>, std::string> GetScopeAndName(Ptr<Scope> initial_scope, const std::string& full_name) {
        auto result = initial_scope;
        std::size_t pos = 0, prev_pos = 0;
        while ((pos = full_name.find("::", prev_pos)) != std::string::npos) {
            auto name = full_name.substr(prev_pos, pos - prev_pos);
            Ptr<Scope> next = result->NestedClass(name);
            result = next ? next : result->NestedNamespace(name);
            if (!result) {
                throw MissingScope(name, full_name);
            }
            prev_pos = pos + 2;
        }
        return std::make_pair(result, full_name.substr(prev_pos));
    }

    Ptr<Class> FindClass(Ptr<Scope> initial_scope, const std::string& full_name) {
        Ptr<Scope> scope;
        std::string name;
        std::tie(scope, name) = GetScopeAndName(initial_scope, full_name);
        return scope->NestedClass(name);
    }

    std::string FixTypename(const std::string& json_type) {
        // FIXME: remove 'class', 'struct' words
        return json_type;
    }

    Ptr<md::Function> CreateFunction(const JSONNode& data, bool is_method) {
        std::vector<md::Parameter> parameter_list;
        for (const auto& param : data["params"]) {
            // FIXME: parameter_list.emplace_back(FixTypename(param.as_string()));
            parameter_list.emplace_back(void_type);
        }

        auto func = md::Function::Create(data["name"].as_string(),
                                         void_type, // FIXME: method["return"].as_string(),
                                         parameter_list,
                                         is_method ? data["pure"].as_bool() : false,
                                         is_method ? data["virtual"].as_bool() : false);
        func->set_deleted(data["deleted"].as_bool());
        func->set_access(access_specifier_mapper.at(data["access"].as_string()));
        // FIXME: where is const?
        return func;
    }
}

Reader::Reader(std::istream& in, md::Ptr<md::Namespace> global)
    : global_(global)
{
    in.seekg(0, std::ios::end);
    contents_.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents_[0], contents_.size());
}

Reader::Reader(const std::string& s, md::Ptr<md::Namespace> global)
    : contents_(s)
    , global_(global) {}

bool Reader::parse() {

    auto json_root = libjson::parse(contents_);

    if (json_root.find("namespaces") != json_root.end())
    for (const auto& ns : json_root["namespaces"]) {
        Ptr<Scope> scope;
        std::string name;
        std::tie(scope, name) = GetScopeAndName(global_, ns.as_string());
        scope->AddNestedNamespace(md::Namespace::Create(name));
    }

    if (json_root.find("classes") != json_root.end())
    for (const auto& c : json_root["classes"]) {
        Ptr<Scope> scope;
        std::string name;
        std::tie(scope, name) = GetScopeAndName(global_, c["qualified_name"].as_string());

        std::list<md::BaseSpecifier> base_specifiers;
        if (c.find("base_class") != c.end())
        for (const auto& base : c["base_class"]) {
            base_specifiers.emplace_back(base["name"].as_string(),
                                         false,
                                         access_specifier_mapper.at(base["access"].as_string()));
        }
        Ptr<Class> tc = Class::Create(name, base_specifiers);

        if (c.find("methods") != c.end())
        for (const auto& method : c["methods"]) {
            auto func = CreateFunction(method, true);
            tc->AddNestedFunction(func);
        }

        scope->AddNestedClass(tc);
    }

    if (json_root.find("functions") != json_root.end())
    for (const auto& f : json_root["functions"]) {
        Ptr<Scope> scope;
        std::string name;
        std::tie(scope, name) = GetScopeAndName(global_, f["qualified_name"].as_string());
        scope->AddNestedFunction(CreateFunction(f, false));
    }

    return true;
}

} // namespace gen 
} // namespace opwig
