#pragma once
#include "../../UniStream/UniStream.h"

#include <functional>
#include <string>
#include <map>

namespace MGTools {

class FunctionBinder
{
typedef std::function<oUniStream(iUniStream&)> FunctionType;
public:
    FunctionBinder();
    virtual ~FunctionBinder();

    template<typename InstanceType, typename ResultType, typename ... ArgsTypes>
    bool Register(const std::string& funcName, InstanceType& instance, ResultType (InstanceType::*func)(ArgsTypes ... args));

    template<typename RetType, typename ... ArgsTypes>
    bool RegisterStatic(const std::string& funcName, RetType(*func)(ArgsTypes ... args));

    bool CallFunction(const std::string& funcName, iUniStream& funcArgs, oUniStream& funcResult);

    bool FunctionExist(const std::string funcName);
protected:

private:
#include "FunctionBinderFunctors.hpp"
#include "FunctionBinderStaticFunctors.hpp"

    std::map<std::string, FunctionType> m_functions;
};

#include "FunctionBinder.hpp"

};
