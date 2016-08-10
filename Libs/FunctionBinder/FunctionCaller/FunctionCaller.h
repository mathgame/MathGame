#pragma once
#include "../../UniStream/UniStream.h"

#include <functional>
#include <string>
#include <map>
#include <memory>
#include "../FunctionConnector/FunctionConnector.h"

namespace MGTools {

class FunctionCaller
{
public:
    FunctionCaller();
    virtual ~FunctionCaller();

    bool Connect( FunctionConnector& connectorPtr );
    void Disconnect();

    bool FunctionExist(const std::string& funcName);
    bool IsConnected() const { return m_isConnected; };

    template<typename ResultType, typename ... ArgsTypes>
    ResultType CallFunction(const std::string& funcName, ArgsTypes ... args);

    template<typename ... ArgsTypes>
    void CallVoidFunction(const std::string& funcName, ArgsTypes ... args);

protected:

private:
    bool m_isConnected;
    FunctionConnector* m_connector;
};

#include "FunctionCaller.hpp"

};
