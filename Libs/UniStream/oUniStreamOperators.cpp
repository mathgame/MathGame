#include "oUniStream.h"
#include "iUniStream.h"
#include <iostream>
using namespace MGTools;


///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator<<(const USBits& obj)
{
    if (IsLockedForInplace())
    {
        m_lastOperationResult = false;
        throw "Use of locked output stream.";
    }
    if (!m_lastOperationResult)
    {
        throw "Use of broken output stream.";
    }

    return StreamData(obj);
}


///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator<<(oUniStream& oUs)
{
    if (!m_lastOperationResult)
    {
        throw "Use of broken output stream.";
    }
    if (!oUs.m_lastOperationResult)
    {
        throw "Use of broken output stream.";
    }

    if ((IsLockedForInplace()) && (false == oUs.IsInplaceMode()))
    {
        throw "Finishing inplacing with non inplace stream.";
    }

    return StreamData(oUs);
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator<<(const USSizeType& containerSize)
{
    if (!m_lastOperationResult)
    {
        throw "Use of broken output stream.";
    }
    return StreamData(containerSize);
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator<<(const unsigned char& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Use of broken output stream.";
    }
    return StreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator<<(const signed char& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Use of broken output stream.";
    }
    return StreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator<<(const unsigned short& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Use of broken output stream.";
    }
    return StreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator<<(const signed short& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Use of broken output stream.";
    }
    return StreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator<<(const unsigned long& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Use of broken output stream.";
    }
    return StreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator<<(const signed long& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Use of broken output stream.";
    }
    return StreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator<<(const unsigned long long& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Use of broken output stream.";
    }
    return StreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator<<(const signed long long& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Use of broken output stream.";
    }
    return StreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator<<(const unsigned& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Use of broken output stream.";
    }
    return StreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator<<(const signed& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Use of broken output stream.";
    }
    return StreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator<<(const char& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Use of broken output stream.";
    }
    return StreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator<<(bool& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Use of broken output stream.";
    }
    return StreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator<<(const float& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Use of broken output stream.";
    }
    return StreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator<<(const double& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Use of broken output stream.";
    }
    return StreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator<<(const wchar_t& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Use of broken output stream.";
    }
    return StreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator<<(const char16_t& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Use of broken output stream.";
    }
    return StreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator<<(const char32_t& cRef)
{
    if (!m_lastOperationResult)
    {
        throw "Use of broken output stream.";
    }
    return StreamData(cRef);
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator>>(const oUniInplace& cRef)
{
    oUniStream& inplace = cRef.oStream;

    if (!m_lastOperationResult)
    {
        throw "Use of broken dst output stream.";
    }
    if (!cRef.oStream.m_lastOperationResult)
    {
        throw "Use of broken src output stream.";
    }
    if (this->IsLockedForInplace())
    {
        m_lastOperationResult = false;
        throw "Inplacing stream before the previous inplace is finished.";
    }
    if (inplace.GetSize())
    {
        m_lastOperationResult = false;
        inplace.m_lastOperationResult = false;
        throw "Inplacing not empty stream.";
    }
    if (inplace.IsInplaceMode())
    {
        m_lastOperationResult = false;
        inplace.m_lastOperationResult = false;
        throw "Inplacing an already inplaced stream.";
    }

    return PrepareInplace(cRef);
}

