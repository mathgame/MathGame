
///////////////////////////////////////////////////////////////////////////
template<typename InstanceType, typename ResultType, typename ... ArgsTypes>
bool FunctionBinder::Register(const std::string& funcName, InstanceType& instance, ResultType (InstanceType::*func)(ArgsTypes ... args))
{
    if (m_functions.find(funcName) != m_functions.end())
    {
        return false;
    }
    m_functions[funcName] = CreateFunctor(&instance, func);
    return true;
}

///////////////////////////////////////////////////////////////////////////
template<typename RetType, typename ... ArgsTypes>
bool FunctionBinder::RegisterStatic(const std::string& funcName, RetType(*func)(ArgsTypes ... args))
{
    if (m_functions.find(funcName) != m_functions.end())
    {
        return false;
    }
    m_functions[funcName] = CreateStaticFunctor(func);
    return true;
}
