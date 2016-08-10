#include "FunctionBinder.h"
#include <iostream>
using namespace MGTools;

///////////////////////////////////////////////////////////////////////////
FunctionBinder::FunctionBinder()
{

}

///////////////////////////////////////////////////////////////////////////
FunctionBinder::~FunctionBinder()
{

}

///////////////////////////////////////////////////////////////////////////
bool FunctionBinder::CallFunction(const std::string& funcName, iUniStream& funcArgs,oUniStream& funcResult)
{
    auto p = m_functions.find(funcName);
    if (p == m_functions.end())
    {
        funcResult = oUniStream();
        return false;
    }
    funcResult = p->second(funcArgs);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool FunctionBinder::FunctionExist(const std::string funcName)
{
    return (m_functions.find(funcName) != m_functions.end());
}
