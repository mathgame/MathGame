#include "iUniStream.h"
#include "oUniStream.h"

using namespace MGTools;


///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(USBits& obj)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }
    return GetStreamData(obj);
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(iUniStream& iUs)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }

    return GetStreamData(iUs);
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(const iUniInplace& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }
    if (!cRef.iStream.m_lastOperationResult)
    {
        throw "Inplacing broken input stream.";
    }

    return GetStreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(oUniStream& oUs)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }
    if (!oUs.m_lastOperationResult)
    {
        throw "Extracting to broken input stream.";
    }
    if (oUs.m_isInplaceMode)
    {
        throw "Extracting to inplaced input stream.";
    }

    return GetStreamData(oUs);
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(USSizeType& containerSize)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }

    return GetStreamData(containerSize);
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(unsigned char& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }

    return GetStreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(signed char& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }
    return GetStreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(unsigned short& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }
    return GetStreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(signed short& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }
    return GetStreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(unsigned long& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }
    return GetStreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(signed long& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }
    return GetStreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(unsigned long long& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }
    return GetStreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(signed long long& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }
    return GetStreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(unsigned& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }
    return GetStreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(signed& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }
    return GetStreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(char& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }
    return GetStreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(bool& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }
    return GetStreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(float& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }
    return GetStreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(double& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }
    return GetStreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(wchar_t& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }
    return GetStreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(char16_t& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }
    return GetStreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator>>(char32_t& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Reading from broken stream.";
    }
    return GetStreamData(cRef);
}
