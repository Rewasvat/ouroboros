
include (src/opwig/parser/generate.cmake)

SET(OUROBOROS_SRC 
    ./src/opa/script.h 
    ./src/opa/baseproxy.h 
    ./src/opa/converter.h
    ./src/opa/defs.h
    ./src/opa/exceptions.h
    ./src/opa/initscripts.cxx 
    ./src/opa/virtualmachine.h 
    ./src/opa/module.h 
    ./src/opa/scriptmanager.cxx 
    ./src/opa/scriptmanager.h 
    ./src/opa/type.h 
    ./src/opa/virtualdata.h 
    ./src/opa/virtualobj.cxx 
    ./src/opa/virtualobj.h 
    ./src/opa/virtualprimitive.h 
    ./src/opa/utils/idgenerator.cxx 
    ./src/opa/utils/idgenerator.h 
    ./src/opa/utils/uncopyable.h 

    ./src/opwig/opwig.h
    ./src/opwig/opwig.cxx
    ./src/opwig/md/accessspecifier.h
    ./src/opwig/md/metadataobject.h
    ./src/opwig/md/metadataobject.cxx
    ./src/opwig/md/container.h
    ./src/opwig/md/scope.h
    ./src/opwig/md/scope.cxx
    ./src/opwig/md/ptr.h
    ./src/opwig/md/type.h
    ./src/opwig/md/namespace.h
    ./src/opwig/md/variable.h
    ./src/opwig/md/class.h
    ./src/opwig/md/class.cxx
    ./src/opwig/md/semanticerror.h
    ./src/opwig/md/function.h
    ./src/opwig/md/enum.h
    ./src/opwig/md/parameter.h
    ./src/opwig/md/nestednamespecifier.h
    ./src/opwig/md/nestednamespecifier.cxx
    ./src/opwig/gen/proxygenerator.h
    ./src/opwig/gen/proxygenerator.cxx
    ./src/opwig/gen/proxycodeprovider.h
    ./src/opwig/gen/wrappergenerator.h
    ./src/opwig/gen/wrappergenerator.cxx
    ./src/opwig/gen/wrapperspecification.h

    ${OPWIG_MDPARSER_SRC}
    ${OPWIG_MDSCANNER_SRC}
)
