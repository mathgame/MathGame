#pragma once
#include "../../UniStream/UniStream.h"
#include "FunctionConnector.h"
#include <functional>
#include <string>
#include <memory>

namespace MGTools {

class FunctionBinder;

class RemoteFunctionConnector : public FunctionConnector
{

public:

    void Connect(FunctionBinder& binderPtr);
    void Disconnect();

    virtual bool FunctionExist(const std::string& funcName);
    virtual bool CallFunction(const std::string& funcName, oUniStream& argsStream, oUniStream& resultStream);
    virtual bool CallVoidFunction(const std::string& funcName, oUniStream& argsStream);
    virtual bool IsConnected() const { return (m_binder != nullptr); };

    void BufferReceived(std::vector<unsigned char> buff);

    virtual void SendBuffer(const std::vector<unsigned char> buff) const = 0;
protected:

private:
    FunctionBinder* m_binder;
};

};
