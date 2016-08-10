


///////////////////////////////////////////////////////////////////////////
template<typename ResultType, typename ... ArgsTypes>
ResultType
FunctionCaller::CallFunction(const std::string& funcName, ArgsTypes ... args)
{
    if (false == m_connector->IsConnected())
    {
        throw "Disconnected connector usage.";
    }
    oUniStream argsStream, resStream;
    argsStream.Serialize(args ...);

    m_connector->CallFunction(funcName, argsStream, resStream);
    iUniStream resInpStream(resStream);
    ResultType res;
    resInpStream >> res;
    return res;
}

///////////////////////////////////////////////////////////////////////////
template<typename ... ArgsTypes>
void
FunctionCaller::CallVoidFunction(const std::string& funcName, ArgsTypes ... args)
{
    if (false == m_connector->IsConnected())
    {
        throw "Disconnected connector usage.";
    }
    oUniStream argsStream;
    argsStream.Serialize(args ...);

    m_connector->CallVoidFunction(funcName, argsStream);
}
