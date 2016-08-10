#include "IBaseComponent.h"
#include <sstream>
#include "../pugixml/pugixml.hpp"
#include "../BaseComponents/System/ComponentsFactory.h"
#include "../XmlParsers/XmlTools.h"

using namespace MGTools;

#define exception int
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteToStream(std::stringstream& dst, const unsigned long long& value)
{
    try
    {
        bool parseResult = (dst << value) ? true : false;
        return parseResult;
    }
    catch(exception& e)
    {
        return false;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteToStream(std::stringstream& dst, const signed long long& value)
{
    try
    {
        bool parseResult = (dst << value) ? true : false;
        return parseResult;
    }
    catch(exception& e)
    {
        return false;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteToStream(std::stringstream& dst, const unsigned long& value)
{
    try
    {
        bool parseResult = (dst << value) ? true : false;
        return parseResult;
    }
    catch(exception& e)
    {
        return false;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteToStream(std::stringstream& dst, const signed long& value)
{
    try
    {
        bool parseResult = (dst << value) ? true : false;
        return parseResult;
    }
    catch(exception& e)
    {
        return false;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteToStream(std::stringstream& dst, const unsigned short& value)
{
    unsigned long val = (unsigned long)value;
    bool success = WriteToStream(dst, val);
    return success;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteToStream(std::stringstream& dst, const signed short& value)
{
    signed long val = (signed long)value;
    bool success = WriteToStream(dst, val);
    return success;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteToStream(std::stringstream& dst, const unsigned char& value)
{
    unsigned long val = (unsigned long)value;
    bool success = WriteToStream(dst, val);
    return success;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteToStream(std::stringstream& dst, const signed char& value)
{
    signed long val = (signed long)value;
    bool success = WriteToStream(dst, val);
    return success;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteToStream(std::stringstream& dst, const unsigned& value)
{
    unsigned long val = (unsigned long)value;
    bool success = WriteToStream(dst, val);
    return success;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteToStream(std::stringstream& dst, const signed& value)
{
    signed long val = (signed long)value;
    bool success = WriteToStream(dst, val);
    return success;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteToStream(std::stringstream& dst, const char& value)
{
    // 'unsigned char' and 'char' are two different C types.
    // 'char' is not guaranteed to have only 8 bits.
    unsigned long val = (unsigned long)value;
    bool success = WriteToStream(dst, val);
    return success;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteToStream(std::stringstream& dst, const float& value)
{
    try
    {
        bool parseResult = (dst << value) ? true : false;
        return parseResult;
    }
    catch(exception& e)
    {
        return false;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteToStream(std::stringstream& dst, const double& value)
{
    try
    {
        bool parseResult = (dst << value) ? true : false;
        return parseResult;
    }
    catch(exception& e)
    {
        return false;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteToStream(std::stringstream& dst, const std::string& value)
{
    try
    {
        bool parseResult = (dst << value) ? true: false;
        return parseResult;
    }
    catch(exception& e)
    {
        return false;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteToStream(std::stringstream& dst, const bool& value)
{
    try
    {
        std::string valueStr = (value) ? std::string("true") : std::string("false");
        bool parseResult = (dst << valueStr) ? true: false;
        return parseResult;
    }
    catch(exception& e)
    {
        return false;
    }

    return false;
}
