///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
/// FUNCTIONS WITH RETURN TYPE
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template<typename ResultType>
FunctionType
CreateStaticFunctor(ResultType(*func)(void))
{
    auto lambda = [func](iUniStream& stream)->oUniStream {
        if (!stream.IsEmpty())
        {
            throw "Too many parameters";
        }
        ResultType res = (*func)();
        oUniStream oStream;
        oStream << res;

        return (oStream);
    };

    return FunctionType(lambda);
};


///////////////////////////////////////////////////////////////////////////
template<typename ResultType,
         typename ArgType01>
FunctionType
CreateStaticFunctor(
                   ResultType(*func)(ArgType01))
{
    auto lambda = [func](iUniStream& stream)->oUniStream {
        ArgType01 t1;
        stream >> t1;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if (!stream.IsEmpty())
        {
            throw "Too many parameters";
        }
        ResultType res = (*func)(t1);
        oUniStream oStream;
        oStream << res;

        return (oStream);
    };

    return FunctionType(lambda);
};

///////////////////////////////////////////////////////////////////////////
template<typename ResultType,
         typename ArgType01, typename ArgType02>
FunctionType
CreateStaticFunctor(
                   ResultType(*func)(ArgType01, ArgType02))
{
    auto lambda = [func](iUniStream& stream)->oUniStream {
        ArgType01 t1; ArgType02 t2;
        stream >> t1 >> t2;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if (!stream.IsEmpty())
        {
            throw "Too many parameters";
        }
        ResultType res = (*func)(t1, t2);
        oUniStream oStream;
        oStream << res;

        return (oStream);
    };

    return FunctionType(lambda);
};

///////////////////////////////////////////////////////////////////////////
template<typename ResultType,
         typename ArgType01, typename ArgType02, typename ArgType03>
FunctionType
CreateStaticFunctor(
                   ResultType(*func)(ArgType01, ArgType02, ArgType03))
{
    auto lambda = [func](iUniStream& stream)->oUniStream {
        ArgType01 t1; ArgType02 t2; ArgType03 t3;
        stream >> t1 >> t2 >> t3;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if (!stream.IsEmpty())
        {
            throw "Too many parameters";
        }
        ResultType res = (*func)(t1, t2, t3);
        oUniStream oStream;
        oStream << res;

        return (oStream);
    };

    return FunctionType(lambda);
};

///////////////////////////////////////////////////////////////////////////
template<typename ResultType,
         typename ArgType01, typename ArgType02, typename ArgType03, typename ArgType04>
FunctionType
CreateStaticFunctor(
                   ResultType(*func)(ArgType01, ArgType02, ArgType03, ArgType04))
{
    auto lambda = [func](iUniStream& stream)->oUniStream {
        ArgType01 t1; ArgType02 t2; ArgType03 t3; ArgType04 t4;
        stream >> t1 >> t2 >> t3 >> t4;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if (!stream.IsEmpty())
        {
            throw "Too many parameters";
        }
        ResultType res = (*func)(t1, t2, t3, t4);
        oUniStream oStream;
        oStream << res;

        return (oStream);
    };

    return FunctionType(lambda);
};

///////////////////////////////////////////////////////////////////////////
template<typename ResultType,
         typename ArgType01, typename ArgType02, typename ArgType03, typename ArgType04,
         typename ArgType05>
FunctionType
CreateStaticFunctor(
                   ResultType(*func)(ArgType01, ArgType02, ArgType03, ArgType04,
                                     ArgType05))
{
    auto lambda = [func](iUniStream& stream)->oUniStream {
        ArgType01 t1; ArgType02 t2; ArgType03 t3; ArgType04 t4;
        ArgType05 t5;
        stream >> t1 >> t2 >> t3 >> t4 >> t5;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if (!stream.IsEmpty())
        {
            throw "Too many parameters";
        }
        ResultType res = (*func)(t1, t2, t3, t4, t5);
        oUniStream oStream;
        oStream << res;

        return (oStream);
    };

    return FunctionType(lambda);
};

///////////////////////////////////////////////////////////////////////////
template<typename ResultType,
         typename ArgType01, typename ArgType02, typename ArgType03, typename ArgType04,
         typename ArgType05, typename ArgType06>
FunctionType
CreateStaticFunctor(
                   ResultType(*func)(ArgType01, ArgType02, ArgType03, ArgType04,
                                     ArgType05, ArgType06))
{
    auto lambda = [func](iUniStream& stream)->oUniStream {
        ArgType01 t1; ArgType02 t2; ArgType03 t3; ArgType04 t4;
        ArgType05 t5; ArgType06 t6;
        stream >> t1 >> t2 >> t3 >> t4 >> t5 >> t6;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if (!stream.IsEmpty())
        {
            throw "Too many parameters";
        }
        ResultType res = (*func)(t1, t2, t3, t4, t5, t6);
        oUniStream oStream;
        oStream << res;

        return (oStream);
    };

    return FunctionType(lambda);
};

///////////////////////////////////////////////////////////////////////////
template<typename ResultType,
         typename ArgType01, typename ArgType02, typename ArgType03, typename ArgType04,
         typename ArgType05, typename ArgType06, typename ArgType07>
FunctionType
CreateStaticFunctor(
                   ResultType(*func)(ArgType01, ArgType02, ArgType03, ArgType04,
                                     ArgType05, ArgType06, ArgType07))
{
    auto lambda = [func](iUniStream& stream)->oUniStream {
        ArgType01 t1; ArgType02 t2; ArgType03 t3; ArgType04 t4;
        ArgType05 t5; ArgType06 t6; ArgType07 t7;
        stream >> t1 >> t2 >> t3 >> t4 >> t5 >> t6 >> t7;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if (!stream.IsEmpty())
        {
            throw "Too many parameters";
        }
        ResultType res = (*func)(t1, t2, t3, t4, t5, t6, t7);
        oUniStream oStream;
        oStream << res;

        return (oStream);
    };

    return FunctionType(lambda);
};

///////////////////////////////////////////////////////////////////////////
template<typename ResultType,
         typename ArgType01, typename ArgType02, typename ArgType03, typename ArgType04,
         typename ArgType05, typename ArgType06, typename ArgType07, typename ArgType08>
FunctionType
CreateStaticFunctor(
                   ResultType(*func)(ArgType01, ArgType02, ArgType03, ArgType04,
                                     ArgType05, ArgType06, ArgType07, ArgType08))
{
    auto lambda = [func](iUniStream& stream)->oUniStream {
        ArgType01 t1; ArgType02 t2; ArgType03 t3; ArgType04 t4;
        ArgType05 t5; ArgType06 t6; ArgType07 t7; ArgType08 t8;
        stream >> t1 >> t2 >> t3 >> t4 >> t5 >> t6 >> t7 >> t8;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if (!stream.IsEmpty())
        {
            throw "Too many parameters";
        }
        ResultType res = (*func)(t1, t2, t3, t4, t5, t6, t7, t8);
        oUniStream oStream;
        oStream << res;

        return (oStream);
    };

    return FunctionType(lambda);
};

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
/// VOID FUNCTIONS
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
FunctionType
CreateStaticFunctor(void(*func)(void))
{
    auto lambda = [func](iUniStream& stream)->oUniStream {
        if (!stream.IsEmpty())
        {
            throw "Too many parameters";
        }
        (*func)();

        return (oUniStream());
    };

    return FunctionType(lambda);
};

///////////////////////////////////////////////////////////////////////////
template<typename ArgType01>
FunctionType
CreateStaticFunctor(
                   void(*func)(ArgType01))
{
    auto lambda = [func](iUniStream& stream)->oUniStream {
        ArgType01 t1;
        stream >> t1;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if (!stream.IsEmpty())
        {
            throw "Too many parameters";
        }
        (*func)(t1);

        return (oUniStream());
    };

    return FunctionType(lambda);
};

///////////////////////////////////////////////////////////////////////////
template<typename ArgType01, typename ArgType02>
FunctionType
CreateStaticFunctor(
                   void(*func)(ArgType01, ArgType02))
{
    auto lambda = [func](iUniStream& stream)->oUniStream {
        ArgType01 t1; ArgType02 t2;
        stream >> t1 >> t2;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if (!stream.IsEmpty())
        {
            throw "Too many parameters";
        }
        (*func)(t1, t2);

        return (oUniStream());
    };

    return FunctionType(lambda);
};

///////////////////////////////////////////////////////////////////////////
template<typename ArgType01, typename ArgType02, typename ArgType03>
FunctionType
CreateStaticFunctor(
                   void(*func)(ArgType01, ArgType02, ArgType03))
{
    auto lambda = [func](iUniStream& stream)->oUniStream {
        ArgType01 t1; ArgType02 t2; ArgType03 t3;
        stream >> t1 >> t2 >> t3;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if (!stream.IsEmpty())
        {
            throw "Too many parameters";
        }
        (*func)(t1, t2, t3);

        return (oUniStream());
    };

    return FunctionType(lambda);
};

///////////////////////////////////////////////////////////////////////////
template<typename ArgType01, typename ArgType02, typename ArgType03, typename ArgType04>
FunctionType
CreateStaticFunctor(
                   void(*func)(ArgType01, ArgType02, ArgType03, ArgType04))
{
    auto lambda = [func](iUniStream& stream)->oUniStream {
        ArgType01 t1; ArgType02 t2; ArgType03 t3; ArgType04 t4;
        stream >> t1 >> t2 >> t3 >> t4;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if (!stream.IsEmpty())
        {
            throw "Too many parameters";
        }
        (*func)(t1, t2, t3, t4);

        return (oUniStream());
    };

    return FunctionType(lambda);
};

///////////////////////////////////////////////////////////////////////////
template<typename ArgType01, typename ArgType02, typename ArgType03, typename ArgType04,
         typename ArgType05>
FunctionType
CreateStaticFunctor(
                   void(*func)(ArgType01, ArgType02, ArgType03, ArgType04,
                               ArgType05))
{
    auto lambda = [func](iUniStream& stream)->oUniStream {
        ArgType01 t1; ArgType02 t2; ArgType03 t3; ArgType04 t4;
        ArgType05 t5;
        stream >> t1 >> t2 >> t3 >> t4 >> t5;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if (!stream.IsEmpty())
        {
            throw "Too many parameters";
        }
        (*func)(t1, t2, t3, t4, t5);

        return (oUniStream());
    };

    return FunctionType(lambda);
};

///////////////////////////////////////////////////////////////////////////
template<typename ArgType01, typename ArgType02, typename ArgType03, typename ArgType04,
         typename ArgType05, typename ArgType06>
FunctionType
CreateStaticFunctor(
                   void(*func)(ArgType01, ArgType02, ArgType03, ArgType04,
                               ArgType05, ArgType06))
{
    auto lambda = [func](iUniStream& stream)->oUniStream {
        ArgType01 t1; ArgType02 t2; ArgType03 t3; ArgType04 t4;
        ArgType05 t5; ArgType06 t6;
        stream >> t1 >> t2 >> t3 >> t4 >> t5 >> t6;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if (!stream.IsEmpty())
        {
            throw "Too many parameters";
        }
        (*func)(t1, t2, t3, t4, t5, t6);

        return (oUniStream());
    };

    return FunctionType(lambda);
};

///////////////////////////////////////////////////////////////////////////
template<typename ArgType01, typename ArgType02, typename ArgType03, typename ArgType04,
         typename ArgType05, typename ArgType06, typename ArgType07>
FunctionType
CreateStaticFunctor(
                   void(*func)(ArgType01, ArgType02, ArgType03, ArgType04,
                               ArgType05, ArgType06, ArgType07))
{
    auto lambda = [func](iUniStream& stream)->oUniStream {
        ArgType01 t1; ArgType02 t2; ArgType03 t3; ArgType04 t4;
        ArgType05 t5; ArgType06 t6; ArgType07 t7;
        stream >> t1 >> t2 >> t3 >> t4 >> t5 >> t6 >> t7;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if (!stream.IsEmpty())
        {
            throw "Too many parameters";
        }
        (*func)(t1, t2, t3, t4, t5, t6, t7);

        return (oUniStream());
    };

    return FunctionType(lambda);
};


///////////////////////////////////////////////////////////////////////////
template<typename ArgType01, typename ArgType02, typename ArgType03, typename ArgType04,
         typename ArgType05, typename ArgType06, typename ArgType07, typename ArgType08>
FunctionType
CreateStaticFunctor(
                   void(*func)(ArgType01, ArgType02, ArgType03, ArgType04,
                               ArgType05, ArgType06, ArgType07, ArgType08))
{
    auto lambda = [func](iUniStream& stream)->oUniStream {
        ArgType01 t1; ArgType02 t2; ArgType03 t3; ArgType04 t4;
        ArgType05 t5; ArgType06 t6; ArgType07 t7; ArgType08 t8;
        stream >> t1 >> t2 >> t3 >> t4 >> t5 >> t6 >> t7 >> t8;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if (!stream.IsEmpty())
        {
            throw "Too many parameters";
        }
        (*func)(t1, t2, t3, t4, t5, t6, t7, t8);

        return (oUniStream());
    };

    return FunctionType(lambda);
};
