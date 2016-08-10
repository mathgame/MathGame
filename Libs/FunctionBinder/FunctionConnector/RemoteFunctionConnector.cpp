#include "RemoteFunctionConnector.h"

#include "../FunctionBinder/FunctionBinder.h"
#include <iostream>
using namespace MGTools;

///////////////////////////////////////////////////////////////////////////
bool RemoteFunctionConnector::FunctionExist(const std::string& funcName)
{
    return (false == funcName.empty());
}

///////////////////////////////////////////////////////////////////////////
bool RemoteFunctionConnector::CallFunction(const std::string& funcName, oUniStream& argsStream, oUniStream& resultStream)
{
    return false;
}

///////////////////////////////////////////////////////////////////////////
bool RemoteFunctionConnector::CallVoidFunction(const std::string& funcName, oUniStream& argsStream)
{
    oUniStream buffStream;
    buffStream << funcName << argsStream;
    SendBuffer(buffStream.GetBuffer());
    return true;
}

///////////////////////////////////////////////////////////////////////////
void RemoteFunctionConnector::BufferReceived(std::vector<unsigned char> buff)
{
    iUniStream buffStream(buff), argsStream;
    std::string name;

    oUniStream dummyResult;

    buffStream >> name >> argsStream;
    bool res = m_binder->CallFunction(name, argsStream, dummyResult);
    if (false == res)
    {

    }
}

///////////////////////////////////////////////////////////////////////////
void RemoteFunctionConnector::Connect(FunctionBinder& binderPtr)
{
    m_binder = &binderPtr;
}

void RemoteFunctionConnector::Disconnect()
{
    m_binder = nullptr;
}
