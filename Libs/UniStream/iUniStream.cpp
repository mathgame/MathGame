#include "iUniStream.h"
#include "oUniStream.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"

using namespace MGTools;

///////////////////////////////////////////////////////////////////////////
iUniInplace::iUniInplace(iUniStream& i_Stream):iStream(i_Stream){}

///////////////////////////////////////////////////////////////////////////
iUniStream::iUniStream()
    : m_buffObj(std::vector<unsigned char>())
    , m_buff(&m_buffObj)
    , m_bits(0)
    , m_bitsUsed(8)
    , m_lastOperationResult(true)
    , m_isDecodingMode(false)
    , m_readIndex(0)
    , m_endIndex(0)
{
}

///////////////////////////////////////////////////////////////////////////
iUniStream::iUniStream(std::vector<unsigned char>& buff, bool decodingMode)
    : m_buffObj(std::move(buff))
    , m_buff(&m_buffObj)
    , m_bits(0)
    , m_bitsUsed(8)
    , m_lastOperationResult(true)
    , m_isDecodingMode(decodingMode)
    , m_readIndex(0)
    , m_endIndex(m_buff->size())
{
}

///////////////////////////////////////////////////////////////////////////
iUniStream::iUniStream(oUniStream& oStream)
    : m_buffObj(std::move(oStream.GetBuffer()))
    , m_buff(&m_buffObj)
    , m_bits(0)
    , m_bitsUsed(8)
    , m_lastOperationResult(true)
    , m_isDecodingMode(oStream.IsEncodingMode())
    , m_readIndex(0)
    , m_endIndex(m_buff->size())
{
}

///////////////////////////////////////////////////////////////////////////
iUniStream::iUniStream(const iUniStream& iStream) // copy
    : m_buffObj(*(iStream.m_buff))
    , m_buff(&m_buffObj)
    , m_bits(iStream.m_bits)
    , m_bitsUsed(iStream.m_bitsUsed)
    , m_lastOperationResult(iStream.m_lastOperationResult)
    , m_isDecodingMode(iStream.m_isDecodingMode)
    , m_readIndex(iStream.m_readIndex)
    , m_endIndex(iStream.m_endIndex)
{
}

///////////////////////////////////////////////////////////////////////////
iUniStream::iUniStream(iUniStream&& iStream) // move
    : m_buffObj(std::move(*(iStream.m_buff)))
    , m_buff(&m_buffObj)
    , m_bits(std::move(iStream.m_bits))
    , m_bitsUsed(std::move(iStream.m_bitsUsed))
    , m_lastOperationResult(std::move(iStream.m_lastOperationResult))
    , m_isDecodingMode(std::move(iStream.m_isDecodingMode))
    , m_readIndex(std::move(iStream.m_readIndex))
    , m_endIndex(std::move(iStream.m_endIndex))
{
}


///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::operator=(iUniStream&& iStream)
{
    m_buffObj = std::move(*(iStream.m_buff));
    m_buff = &m_buffObj;
    m_bits = std::move(iStream.m_bits);
    m_bitsUsed = std::move(iStream.m_bitsUsed);
    m_lastOperationResult = std::move(iStream.m_lastOperationResult);
    m_isDecodingMode = std::move(iStream.m_isDecodingMode);
    m_readIndex = std::move(iStream.m_readIndex);
    m_endIndex = std::move(iStream.m_endIndex);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
void iUniStream::SetBuffer(std::vector<unsigned char>& buff, bool decodingMode)
{
    if (
            (!m_lastOperationResult) ||
            (m_buffObj.size()) ||
            (m_buff != &m_buffObj)
            )
    {
        throw "Reset buffer of used input stream.";
    }
    SetDecodingMode(decodingMode);
    m_buffObj = std::move(buff);
}

///////////////////////////////////////////////////////////////////////////
bool iUniStream::GetBitsByte()
{
    m_bitsUsed = 0;
    CopyNum8(m_bits);
    return m_lastOperationResult;
}

///////////////////////////////////////////////////////////////////////////
void iUniStream::Reset()
{
    m_buff = &m_buffObj;
    m_bits = 0;
    m_bitsUsed = 8;
    m_lastOperationResult = true;
    m_isDecodingMode = false;
    m_readIndex = 0;
    m_endIndex = 0;
    ClearSTLBuffer();
}


///////////////////////////////////////////////////////////////////////////
void iUniStream::DecodeNum16(unsigned short& c)
{
    // 1/0 inv/org
    // 1    16 bits
    // 01   8 bits
    // 00   4 bits
    USBits bit = USBits(0, 1);

    bool inv = (GetStreamData(bit), bit.bits == 1);
    if ((GetStreamData(bit), bit.bits == 1))
    {
        // Use 16 bits
        CopyNum16(c);
    }
    else if ((GetStreamData(bit), bit.bits == 1))
    {
        // Use 8 bits
        unsigned char cC = 0;
        CopyNum8(cC);
        c = (unsigned short)cC;
    }
    else
    {
        // Use 4 bits
        USBits numBits = USBits(0, 4);
        GetStreamData(numBits);
        c = (unsigned short)numBits.bits;
    }
    if (inv)
        c = ~((usUint16_t)c);
}

///////////////////////////////////////////////////////////////////////////
void iUniStream::DecodeNum32(unsigned long& c)
{
    // 1/0 inv/org
    // 1    32 bits
    // 01   16 bits
    // 001  8 bits
    // 000  4 bits
    USBits bit = USBits(0, 1);
    bool inv = (GetStreamData(bit), bit.bits == 1);

    if ((GetStreamData(bit), bit.bits == 1))
    {
        // Use 32 bits
        CopyNum32(c);
    }
    else if ((GetStreamData(bit), bit.bits == 1))
    {
        // Use 16 bits
        unsigned short cC = 0;
        CopyNum16(cC);
        c = (unsigned long)cC;
    }
    else if ((GetStreamData(bit), bit.bits == 1))
    {
        // Use 8 bits
        unsigned char cC = 0;
        CopyNum8(cC);
        c = (unsigned long)cC;
    }
    else
    {
        // Use 4 bits
        USBits numBits = USBits(0, 4);
        GetStreamData(numBits);
        c = (unsigned long)numBits.bits;
    }
    if (inv)
        c = ~((usUint32_t)c);
}

///////////////////////////////////////////////////////////////////////////
void iUniStream::DecodeNum64(unsigned long long& c)
{
    // 1/0 inv/org
    // 1    64 bits
    // 01   40 bits
    // 001  16 bits
    // 000  8 bits
    USBits bit = USBits(0, 1);
    bool inv = (GetStreamData(bit), bit.bits == 1);
    if ((GetStreamData(bit), bit.bits == 1))
    {
        // Use 64 bits
        CopyNum64(c);
    }
    else if ((GetStreamData(bit), bit.bits == 1))
    {
        // Use 40 bits
        unsigned long cCLong = 0;
        unsigned char cCChar = 0;
        CopyNum32(cCLong);
        CopyNum8(cCChar);
        c  = (unsigned long long)cCLong << 0;
        c |= (unsigned long long)cCChar << 32;
    }
    else if ((GetStreamData(bit), bit.bits == 1))
    {
        // Use 16 bits
        unsigned short cC = 0;
        CopyNum16(cC);
        c  = (unsigned long long)cC;
    }
    else
    {
        // Use 8 bits
        unsigned char cC = 0;
        CopyNum8(cC);
        c  = (unsigned long long)cC;
    }
    if (inv)
        c = ~((usUint64_t)c);
}

///////////////////////////////////////////////////////////////////////////
void iUniStream::CopyNum16(unsigned short& c)
{
    unsigned char cCh = 0;

    c  = (CopyNum8(cCh), (unsigned short)cCh) << 0;
    c |= (CopyNum8(cCh), (unsigned short)cCh) << 8;
}

///////////////////////////////////////////////////////////////////////////
void iUniStream::CopyNum32(unsigned long& c)
{
    unsigned char cCh = 0;

    c  = (CopyNum8(cCh), (unsigned long)cCh) << 0;
    c |= (CopyNum8(cCh), (unsigned long)cCh) << 8;
    c |= (CopyNum8(cCh), (unsigned long)cCh) << 16;
    c |= (CopyNum8(cCh), (unsigned long)cCh) << 24;
}

///////////////////////////////////////////////////////////////////////////
void iUniStream::CopyNum64(unsigned long long& c)
{
    unsigned char cCh = 0;

    c  = (CopyNum8(cCh), (unsigned long long)cCh) << 0;
    c |= (CopyNum8(cCh), (unsigned long long)cCh) << 8;
    c |= (CopyNum8(cCh), (unsigned long long)cCh) << 16;
    c |= (CopyNum8(cCh), (unsigned long long)cCh) << 24;
    c |= (CopyNum8(cCh), (unsigned long long)cCh) << 32;
    c |= (CopyNum8(cCh), (unsigned long long)cCh) << 40;
    c |= (CopyNum8(cCh), (unsigned long long)cCh) << 48;
    c |= (CopyNum8(cCh), (unsigned long long)cCh) << 56;
}

///////////////////////////////////////////////////////////////////////////
void iUniStream::CopyNum8(unsigned char& c)
{
    if (m_readIndex >= m_endIndex)
    {
        m_lastOperationResult = false;
        m_bits = 0;
        return;
    }

    c = (*m_buff)[m_readIndex++];
}

///////////////////////////////////////////////////////////////////////////
void iUniStream::Receive8(unsigned char& c)
{
    CopyNum8(c);
}

///////////////////////////////////////////////////////////////////////////
void iUniStream::Receive16(unsigned short& c)
{
	if (IsDecodingMode())
	{
		DecodeNum16(c);
	}
	else
	{
		CopyNum16(c);
	}
}

///////////////////////////////////////////////////////////////////////////
void iUniStream::Receive32(unsigned long& c)
{
	if (IsDecodingMode())
	{
		DecodeNum32(c);
	}
	else
	{
		CopyNum32(c);
	}
}

///////////////////////////////////////////////////////////////////////////
void iUniStream::Receive64(unsigned long long& c)
{
	if (IsDecodingMode())
	{
		DecodeNum64(c);
	}
	else
	{
		CopyNum64(c);
	}
}


///////////////////////////////////////////////////////////////////////////
void iUniStream::GetStreamSettings(iUniStream& iUs)
{
    USBits bits(0, 1);
    GetStreamData(bits);
    iUs.SetDecodingMode(bits.bits == 1);
    GetStreamData(bits);
    iUs.m_lastOperationResult = (bits.bits == 1);

    // Take the iStream settings
    USSizeType dummySz;
    GetStreamData(dummySz);
    CopyNum8(iUs.m_bitsUsed);
    iUs.m_bits = 0;
    iUs.m_bitsUsed = 8;
}

///////////////////////////////////////////////////////////////////////////
void iUniStream::GetStreamSettings(oUniStream& oUs)
{
    USBits bits(0, 1);
    GetStreamData(bits);
    oUs.SetEncodingMode(bits.bits == 1);
    GetStreamData(bits);
    oUs.m_lastOperationResult = (bits.bits == 1);

    // Take the iStream settings
    GetStreamData(oUs.m_bitsIndex);
    CopyNum8(oUs.m_bitsUsed);
}


///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(oUniStream& oUs)
{
    USSizeType sz;
    GetStreamData(sz);

    oUs.Reset();
    GetStreamSettings(oUs);
    for (USSizeType i = 0; i < sz; ++i)
    {
        unsigned char c = 0;
        CopyNum8(c);
        oUs.PushSTLBack(c);
    }

    return *this;
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(USBits& obj)
{
    if (obj.bitsCount > 8)
    {
        US_LOG << "Incorrect read bits count : " << (int)obj.bitsCount;
        US_ASSERT();
        m_lastOperationResult = false;
        return *this;
    }
    if (m_bitsUsed >= 8)
    {
        if (false == GetBitsByte())
        {
            m_lastOperationResult = false;
            return *this;
        }
    }

    char bitsCount = obj.bitsCount;
    register unsigned char bits = m_bits;
    register unsigned char c = bits >> m_bitsUsed;

    if (m_bitsUsed + bitsCount > 8)
    {
        char overflow = m_bitsUsed + bitsCount - 8;
        char saved = 8 - m_bitsUsed;

        if (false == GetBitsByte())
        {
            m_lastOperationResult = false;
            return *this;
        }
        bits = m_bits << saved;
        c |= bits;

        m_bitsUsed += overflow;
    }
    else
    {
        m_bitsUsed += bitsCount;
    }

    obj.bits = c & FILL_BITS(bitsCount);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(iUniStream& iUs)
{
    USSizeType sz;
    GetStreamData(sz);

    iUs.Reset();
    GetStreamSettings(iUs);
    for (USSizeType i = 0; i < sz; ++i)
    {
        unsigned char c = 0;
        CopyNum8(c);
        iUs.PushSTLBack(c);
    }
    iUs.m_endIndex = iUs.GetSTLBufferSize();

    return *this;
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(const iUniInplace& cRef)
{
    iUniStream& iUs = cRef.iStream;
    USSizeType sz;
    GetStreamData(sz);

    iUs.Reset();
    GetStreamSettings(iUs);

    iUs.m_readIndex = m_readIndex;
    m_readIndex += sz;
    iUs.m_endIndex = m_readIndex;

    iUs.m_buff = m_buff;

    return *this;
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(USSizeType& containerSize)
{
    unsigned long sz = 0;
    USBits bits(0, 1);

    GetStreamData(bits);
    if (1 == bits.bits)
    {
        // 4 bits size
        bits = USBits(0, 4);
        GetStreamData(bits);
        sz = bits.bits;
    }
    else if (1 == (GetStreamData(bits), bits.bits))
    {
        // 8 bits size
        unsigned char c = 0;
        CopyNum8(c);
        sz = c;
    }
    else if (1 == (GetStreamData(bits), bits.bits))
    {
        // 16 bits size
        unsigned short c = 0;
        CopyNum16(c);
        sz = c;
    }
    else
    {
        // 32 bits size
        unsigned long c = 0;
        CopyNum32(c);
        sz = c;
    }

    containerSize = sz;
    return *this;
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(unsigned char& cRef)
{
    SafeCast<unsigned char>(cRef);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(signed char& cRef)
{
    SafeCast<signed char>(cRef);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(unsigned short& cRef)
{
    SafeCast<unsigned short>(cRef);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(signed short& cRef)
{
    SafeCast<signed short>(cRef);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(unsigned long& cRef)
{
    SafeCast<unsigned long>(cRef);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(signed long& cRef)
{
    SafeCast<signed long>(cRef);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(unsigned long long& cRef)
{
    SafeCast<unsigned long long>(cRef);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(signed long long& cRef)
{
    SafeCast<signed long long>(cRef);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(unsigned& cRef)
{
    SafeCast<unsigned>(cRef);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(signed& cRef)
{
    SafeCast<signed>(cRef);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(char& cRef)
{
    SafeCast<char>(cRef);
    return *this;
}


///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(bool& cRef)
{
    SafeCast<bool>(cRef);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(float& cRef)
{
    SafeCast<float>(cRef);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(double& cRef)
{
    SafeCast<double>(cRef);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(wchar_t& cRef)
{
    SafeCast<wchar_t>(cRef);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(char16_t& cRef)
{
    SafeCast<char16_t>(cRef);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(char32_t& cRef)
{
    SafeCast<char32_t>(cRef);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
size_t iUniStream::GetSize() const
{
    return (m_endIndex - m_readIndex);

}

///////////////////////////////////////////////////////////////////////////
iUniStream& iUniStream::GetStreamData(void*& cRef)
{
    void* res = nullptr;
    if (sizeof(void*) == 2)
    {
        unsigned short c;
        SafeCast<unsigned short>(c);
        usUint16_t cC = (usUint16_t)c;
        res = reinterpret_cast<void*&>(cC);
    }
    else if(sizeof(void*) == 4)
    {
        unsigned long c;
        SafeCast<unsigned long>(c);
        usUint32_t cC = (usUint32_t)c;
        res = reinterpret_cast<void*&>(cC);
    }
    else if(sizeof(void*) == 8)
    {
        unsigned long long c;
        SafeCast<unsigned long long>(c);
        usUint64_t cC = (usUint64_t)c;
        res = reinterpret_cast<void*&>(cC);
    }
    else
    {
        UNHANDLED_CASE();
    }
    cRef = res;
    return *this;
}

///////////////////////////////////////////////////////////////////////////
bool iUniStream::IsEmpty() const
{
    return (GetSize() == 0);
}

#pragma GCC diagnostic pop
