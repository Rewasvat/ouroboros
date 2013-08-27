#include <opwig/gen/python/pythonspecification.h>
#include <opwig/gen/python/wrapscope.h>
#include <opwig/gen/python/utilities.h>
#include <opwig/md/function.h>
#include <opwig/md/variable.h>
#include <opwig/md/namespace.h>
#include <opwig/md/type.h>

#include <sstream>

namespace opwig {
namespace gen {
namespace python {

using std::string;
using md::Ptr;
using std::stringstream;
using std::endl;

PythonSpecification::PythonSpecification() {
    root_module_ = Ptr<WrapScope>(new WrapScope(""));
    current_ = root_module_;
}

// HEADER BLOCK
string PythonSpecification::FileHeader() const {
    root_module_->set_name(module_name_);
    return
        "// FILE GENERATED BY OPWIG - OUROBOROS PROJECT.\n\n"
        "#include <Python.h>\n"
        "#include <languages/python/pythonwrapper.h>\n"
        "#include <languages/python/pythonconverter.h>\n"
        "#include <languages/python/wrapperbase.h>\n"
        "#include <opa/scriptmanager.h>\n"
        "#include <opa/module.h>\n"
        "#include <iostream>\n"
        "#include <string>\n"
        "\n"
        "using std::string;\n"
        "using std::cout;\n"
        "using std::endl;\n"
        "using opa::Module;\n"
        "using opa::python::PythonWrapper;\n"
        "using opa::python::PythonConverter;\n"
        "\n";
}

string PythonSpecification::MiddleBlock() const {
    return
        "namespace {\n\n"
        "bool NumArgsOk(PyObject* args, int num) {\n"
        "    if (static_cast<int>(PyTuple_Size(args)) != num) {\n"
        "        string msg = \"expected \"+std::to_string(num)+\" parameters, but received \"+std::to_string(PyTuple_Size(args))+\".\";\n"
        "        PyErr_SetString(PyExc_RuntimeError, msg.c_str());\n"
        "        return false;\n"
        "    }\n"
        "    return true;\n"
        "}\n\n"
        "void AddToParentModule(PyObject* mChild, const string& childName, const string& fullParentName) {\n"
        "    PyObject* mParent = PyImport_ImportModule(fullParentName.c_str()); //newref\n"
        "    if (mParent == nullptr) {\n"
        "        string msg = \"Initializing '\"+childName+\"', could not import '\"+fullParentName+\"'\";\n"
        "        PyErr_SetString(PyExc_RuntimeError, msg.c_str());\n"
        "    }\n"
        "    else {\n"
        "        Py_INCREF(mChild);\n"
        "        if (PyModule_AddObject(mParent, childName.c_str(), mChild) == -1) {\n"
        "            string msg = \"could not add submodule '\"+childName+\"' to module '\"+fullParentName+\"'\";\n"
        "            PyErr_SetString(PyExc_RuntimeError, msg.c_str());\n"
        "        }\n"
        "        Py_DECREF(mParent);\n"
        "    }\n"
        "}\n\n"
        "PyObject* FuncErrorHandling(const std::exception& e) {\n"
        "    cout << \"[ERROR IN C++]\" << e.what() << endl;\n"
        "    if (PyErr_Occurred()==nullptr)   PyErr_SetString(PyExc_RuntimeError, e.what());\n"
        "    return nullptr;\n"
        "}\n"
        "} // unnamed namespace\n\n"
        "namespace "+BASE_NSPACE+" {\n\n";
}

// FINISH BLOCK
void HandleModuleMethodTables(stringstream& block, const Ptr<WrapScope>& module) {
    block << "//module " << module->name() << " method table" << endl;
    block << module->GenerateMethodTable(BASE_NSPACE) << endl;
    for (auto subm : module->sub_modules() )
        if (!subm->is_class())
            HandleModuleMethodTables(block, subm);
}

void HandleWrapScopeForInitFunc(stringstream& block, const Ptr<WrapScope>& module) {
    block << "PyMODINIT_FUNC" << endl;
    block << GetInitFuncNameForModule(module->name()) << "(void) {" << endl;
    block << TAB;
    if (module->parent())
        block << "PyObject* " << module->name() << "_mod = ";
    block << "Py_InitModule(\"" << module->full_dotted_name() << "\", " << module->GetMethodTableName() << ");" << endl;

    if (module->parent()) {
        block << TAB << "AddToParentModule(" << module->name() << "_mod, \"" << module->name();
        block << "\", \"" << module->parent()->full_dotted_name() << "\");" << endl;
    }
    for (auto subm : module->sub_modules() ) {
        if (subm->is_class()) {
            string typeName = BASE_NSPACE + "::" + subm->full_dotted_name("::") + "::" + GetTypeNameForClass(subm->name());
            block << TAB << "if (PyType_Ready(&" << typeName << ") < 0)" << endl;
            block << TAB << TAB << "return;" << endl;
        }
    }
    block << "}" << endl;

    for (auto subm : module->sub_modules() )
        if (!subm->is_class())
            HandleWrapScopeForInitFunc(block, subm);
}

string PythonSpecification::FinishFile() const {
    stringstream block;
    block << endl << "} //namespace " << BASE_NSPACE << endl << endl;
    HandleModuleMethodTables(block, root_module_);
    HandleWrapScopeForInitFunc(block, root_module_);
    return block.str();
}

// WRAP FUNCION
string PythonSpecification::WrapFunction(const Ptr<const md::Function>& obj) {
    current_->AddFunction(obj);
        
    stringstream func;
    string self_type = "PyObject";
    if (current_->is_class()) {
        self_type = GetTypeObjNameForClass(current_->name());
    }
    func << "PyObject* " << FUNC_PREFIX << obj->name() << "(" << self_type << "* py_self, PyObject* args)" << endl;
    func << "try {" << endl;
    if (obj->num_parameters() > 0)
        func << TAB << "if (!NumArgsOk(args, " << obj->num_parameters() << ")) return nullptr;" << endl;
    func << TAB << "PythonConverter converter (true);" << std::endl;
    stringstream args ("");
    for (unsigned i=0; i<obj->num_parameters(); i++) {
        func << TAB << obj->parameter_type(i)->full_type() <<" fArg"<< i;
        func << " = converter.PyArgToType<"<< obj->parameter_type(i)->full_type() <<">(args, " << i << ");" << endl;
        if (i > 0)
            args << ", ";
        args << "fArg" << i;
    }
    string func_call = obj->nested_name();
    if (current_->is_class()) {
        func << TAB << "typename py_self->type* cpp_self = static_cast<py_self->type*>(py_self->obj);" << endl;
        func_call = "cpp_self->" + obj->name();
    }

    if (obj->return_type()->full_type() == "void") {
        func << TAB << func_call << "("<< args.str() << ");" << endl;
        func << TAB << "Py_RETURN_NONE;" << endl;
    }
    else {
        func << TAB << obj->return_type()->full_type() << " fValue = " << func_call << "("<< args.str() << ");" << endl;
        func << TAB << "return converter.TypeToScript<"<< obj->return_type()->full_type() <<">(fValue);" << endl;
    }
    func << "}" << endl;
    func << "catch (std::exception& e) { return FuncErrorHandling(e); }" << endl;
    return func.str();
}

// WRAP VARIABLE
string PythonSpecification::WrapVariable(const Ptr<const md::Variable>& obj) {
    current_->AddVariable(obj);
    stringstream func;
    if (!current_->is_class()) {
        func << "PyObject* " << FUNC_PREFIX << obj->name() << "(PyObject* self, PyObject* args)" << std::endl;
        func << "try {" << endl;
        func << TAB << "PythonConverter converter (true);" << std::endl;
        func << TAB << obj->type()->full_type() << " oldValue = " << obj->nested_name() << ";" << endl;
        if (!obj->type()->is_const()) {
            func << TAB << "if (static_cast<int>(PyTuple_Size(args)) == 1) {" << endl;
            func << TAB << TAB << obj->nested_name() << " = ";
            func << "converter.PyArgToType<"<< obj->type()->full_type() <<">(args, 0);" << endl;
            func << TAB << "}" << endl;
            func << TAB << "else if (!NumArgsOk(args, 0)) return nullptr;" << endl;
        }
        func << TAB << "return converter.TypeToScript<" << obj->type()->full_type() <<">(oldValue);" << endl;
        func << "}" << endl;
        func << "catch (std::exception& e) { return FuncErrorHandling(e); }" << endl;
    }
    else {
        func << "PyObject* " << FUNC_PREFIX << obj->name() << "_getter(" << GetTypeObjNameForClass(current_->name());
        func << "* py_self, void *closure)" << endl;
        func << "try {" << endl;
        func << TAB << "PythonConverter converter (true);" << endl;
        func << TAB << "typename py_self->type* cpp_self = static_cast<py_self->type*>(py_self->obj);" << endl;
        func << TAB << "return converter.TypeToScript<" << obj->type()->full_type() <<">(cpp_self->" << obj->name() << ");" << endl;
        func << "}" << endl;
        func << "catch (std::exception& e) { return FuncErrorHandling(e); }" << endl << endl;

        func << "int " << FUNC_PREFIX << obj->name() << "_setter(" << GetTypeObjNameForClass(current_->name());
        func << "* py_self, PyObject *value, void *closure)" << endl;
        if (!obj->type()->is_const()) {
            func << "try {" << endl;
            func << TAB << "if (value == NULL) {" << endl;
            func << TAB << TAB << "PyErr_SetString(PyExc_TypeError, \"[OPWIG] Cannot delete attribute from wrapped C++ class\");" << endl;
            func << TAB << TAB << "return -1;" << endl;
            func << TAB << "}" << endl;
            func << TAB << "PythonConverter converter (true);" << endl;
            func << TAB << obj->type()->full_type() <<" newValue = converter.ScriptToType<" << obj->type()->full_type() <<">(value);" << endl;
            //TODO: check if this is accurate - passing type checking to converter
            func << TAB << "typename py_self->type* cpp_self = static_cast<py_self->type*>(py_self->obj);" << endl;
            func << TAB << "cpp_self->" << obj->name() << " = newValue;" << endl;
            func << TAB << "return 0;" << endl;
            func << "}" << endl;
            func << "catch (std::exception& e) { return FuncErrorHandling(e); }" << endl;
        }
        else {
            func << "{" << endl;
            func << TAB << "PyErr_SetString(PyExc_TypeError, \"[OPWIG] tried to set value of a const (read-only) variable.\");" << endl;
            func << TAB << "return -1;" << endl;
            func << "}" << endl;
        }
    }
    return func.str();
}

// WRAP ENUM
string PythonSpecification::WrapEnum(const Ptr<const md::Enum>& obj) {
    return "";
}

// OPEN CLASS
string PythonSpecification::OpenClass(const Ptr<const md::Class>& obj) {
    PushScope(obj->name(), true);
    stringstream ocb; //open class block

    ocb << "namespace " << obj->name() << " { //entering CLASS namespace " << obj->name() << endl;
    ocb << "typedef struct _" << GetTypeObjNameForClass(obj->name()) << " {" << endl;
    ocb << TAB << "PyObject_HEAD" << endl;
    ocb << TAB << "void* obj;" << endl;
    ocb << TAB << "typedef " << obj->nested_name() << " type;" << endl;
    ocb << TAB << "void construct(PyObject* args, PyObject* kwds) {" << endl;
    ocb << TAB << TAB << "COISAS" << endl; //TODO: IMPLEMENT COISAS
    ocb << TAB << "}" << endl;
    ocb << "} " << GetTypeObjNameForClass(obj->name()) << ";" << endl;
    
    return ocb.str();
}

// CLOSE CLASS
string PythonSpecification::CloseClass(const Ptr<const md::Class>& obj) {
    stringstream ccb; //close class block
    ccb << current_->GenerateMethodTable(BASE_NSPACE) << endl;
    ccb << current_->GenerateGetSetTable(BASE_NSPACE) << endl << endl;
    ccb << "static PyTypeObject " << GetTypeNameForClass(obj->name()) << " = {" << endl;
    ccb << TAB << "PyObject_HEAD_INIT(NULL)" << endl;
    ccb << TAB << "0," << endl;
    ccb << TAB << "\"" << obj->nested_name(".", false) << "\"," << endl;
    ccb << TAB << "sizeof(" << GetTypeObjNameForClass(obj->name()) << ")," << endl;
    ccb << TAB << "0," << endl;
    ccb << TAB << "(destructor)opa::python::wrapper::GenericDealloc<" << obj->nested_name() << ">," << endl;
    ccb << TAB << "0, 0, 0, 0," << endl;
    ccb << TAB << "(reprfunc)opa::python::wrapper::GenericRepr<" << obj->nested_name() << ">," << endl;
    ccb << TAB << "0, 0, 0, 0, 0, 0, 0, 0, 0," << endl;
    ccb << TAB << "Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE," << endl;
    ccb << TAB << "\"wrapped C++ type\"," << endl;
    ccb << TAB << "0, 0, 0, 0, 0, 0," << endl;
    ccb << TAB << current_->GetMethodTableName() << ", /* tp_methods */" << endl;
    ccb << TAB << "0,    /* tp_members */" << endl;
    ccb << TAB << current_->GetGetSetTableName() << ", /* tp_getset */" << endl;
    ccb << TAB << "0, 0, 0, 0, 0, 0, 0," << endl;
    ccb << TAB << "opa::python::wrapper::GenericNew<" << obj->nested_name() << ">," << endl;
    ccb << "};" << endl;
    ccb << "} //closing CLASS namespace " << obj->name() << endl;

    PopScope();
    return ccb.str();
}

// OPEN NAMESPACE
string PythonSpecification::OpenNamespace(const Ptr<const md::Namespace>& obj) {
    PushScope(obj->name(), false);
    return "namespace "+obj->name()+" { //entering namespace "+obj->name()+"\n";
}

// CLOSE NAMESPACE
string PythonSpecification::CloseNamespace(const Ptr<const md::Namespace>& obj) {
    PopScope();
    return "} //closing namespace "+obj->name()+"\n";
}

// AUXILIARY METHODS
void PythonSpecification::PushScope(const std::string& name, bool is_class) {
    Ptr<WrapScope> newm = Ptr<WrapScope>(new WrapScope(name, is_class, current_));
    current_->AddSubModule(newm);
    current_ = newm;
}

void PythonSpecification::PopScope() {
    current_ = current_->parent();
}

std::list<ScriptModule> PythonSpecification::GetGeneratedModules () const {
    return root_module_->ConvertTreeToScriptModuleList();
}

} // namespace python
} // namespace gen
} // namespace opwig
