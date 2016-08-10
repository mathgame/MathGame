#include "oUniStream.h"
#include "iUniStream.h"
#include <iostream>
using namespace MGTools;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"

///////////////////////////////////////////////////////////////////////////
oUniInplace::oUniInplace(oUniStream& o_Stream):oStream(o_Stream){}

/////////////////////////////////
//////////////////////////////////////////
oUniStream::oUniStream()
    : m_buffObj(std::vector<unsigned char>())
    , m_buff(&m_buffObj)
    , m_bitsIndex(0)
    , m_bitsUsed(8)
    , m_lastOperationResult(true)
    , m_isEncodingMode(false)
    , m_isLockedForInplace(false)
    , m_isInplaceMode(false)
    , m_inplaceStartIndex(0)
    , m_inplaceSizeStart(0)
    , m_globalOffset(0)
    , m_inplaceBitsIndex(0)
    , m_inplaceBitsUsedIndex(0)
{
    Reset();
}

///////////////////////////////////////////////////////////////////////////
oUniStream::oUniStream(const oUniStream& oStream) // copy
    : m_buffObj(std::vector<unsigned char>())
    , m_buff(&m_buffObj)
    , m_bitsIndex(oStream.m_bitsIndex)
    , m_bitsUsed(oStream.m_bitsUsed)
    , m_lastOperationResult(oStream.m_lastOperationResult)
    , m_isEncodingMode(oStream.m_isEncodingMode)
    , m_isLockedForInplace(oStream.m_isLockedForInplace)
    , m_isInplaceMode(oStream.m_isInplaceMode)
    , m_inplaceStartIndex(oStream.m_inplaceStartIndex)
    , m_inplaceSizeStart(oStream.m_inplaceSizeStart)
    , m_globalOffset(oStream.m_globalOffset)
    , m_inplaceBitsIndex(oStream.m_inplaceBitsIndex)
    , m_inplaceBitsUsedIndex(oStream.m_inplaceBitsUsedIndex)
{
    std::copy((oStream.m_buff)->begin(), (oStream.m_buff)->end(),
                  std::back_inserter(*m_buff));
}

///////////////////////////////////////////////////////////////////////////
oUniStream::oUniStream(oUniStream&& oStream) // move
    : m_buffObj(std::move(*(oStream.m_buff)))
    , m_buff(&m_buffObj)
    , m_bitsIndex(std::move(oStream.m_bitsIndex))
    , m_bitsUsed(std::move(oStream.m_bitsUsed))
    , m_lastOperationResult(std::move(oStream.m_lastOperationResult))
    , m_isEncodingMode(std::move(oStream.m_isEncodingMode))
    , m_isLockedForInplace(std::move(oStream.m_isLockedForInplace))
    , m_isInplaceMode(std::move(oStream.m_isInplaceMode))
    , m_inplaceStartIndex(std::move(oStream.m_inplaceStartIndex))
    , m_inplaceSizeStart(std::move(oStream.m_inplaceSizeStart))
    , m_globalOffset(std::move(oStream.m_globalOffset))
    , m_inplaceBitsIndex(std::move(oStream.m_inplaceBitsIndex))
    , m_inplaceBitsUsedIndex(std::move(oStream.m_inplaceBitsUsedIndex))
{
    if (oStream.IsInplaceMode())
    {
        // You cant move inplace stream. Please flush it and use the main stream.
        throw "Inplaced Rvalue stream error(1)!";
    }
    if (oStream.IsLockedForInplace())
    {
        // You cant move stream that is used for inplacing an another stream.
        // Please flush your inplace stream first.
        throw "Please flush inplace mode first(1)!";
    }
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::operator=(oUniStream&& oStream)
{
    if (oStream.IsInplaceMode())
    {
        // You cant move inplace stream. Please flush it and use the main stream.
        throw "Inplaced Rvalue stream error(2)!";
    }
    if (oStream.IsLockedForInplace())
    {
        // You cant move stream that is used for inplacing an another stream.
        // Please flush your inplace stream first.
        throw "Please flush inplace mode first(2)!";
    }

    m_buffObj = std::move(*(oStream.m_buff));
    m_buff = &m_buffObj;
    m_bitsIndex = std::move(oStream.m_bitsIndex);
    m_bitsUsed = std::move(oStream.m_bitsUsed);
    m_lastOperationResult = std::move(oStream.m_lastOperationResult);
    m_isEncodingMode = std::move(oStream.m_isEncodingMode);
    m_isLockedForInplace = std::move(oStream.m_isLockedForInplace);
    m_isInplaceMode = std::move(oStream.m_isInplaceMode);
    m_inplaceStartIndex = std::move(oStream.m_inplaceStartIndex);
    m_inplaceSizeStart = std::move(oStream.m_inplaceSizeStart);
    m_globalOffset = std::move(oStream.m_globalOffset);
    m_inplaceBitsIndex = std::move(oStream.m_inplaceBitsIndex);
    m_inplaceBitsUsedIndex = std::move(oStream.m_inplaceBitsUsedIndex);
    return *this;
}

//oUniStream& operator=(oUniStream&& oStream);

///////////////////////////////////////////////////////////////////////////
void oUniStream::GetBitsByte()
{
    PushBack(0);

    m_bitsUsed = 0;
    m_bitsIndex = GetSTLBufferSize() - 1;
}

///////////////////////////////////////////////////////////////////////////
void oUniStream::PushBack(unsigned char c)
{
    if (IsLockedForInplace())
    {
        m_lastOperationResult = false;
    }

    if (!m_lastOperationResult)
    {
        return;
    }

    PushSTLBack(c);
}

///////////////////////////////////////////////////////////////////////////
void oUniStream::Reset()
{
    if (IsLockedForInplace())
    {
        m_lastOperationResult = false;
        throw "Reset of locked output stream.";
    }
    if (IsInplaceMode())
    {
        m_lastOperationResult = false;
        throw "Reset of inplaced output stream.";
    }

    ClearSTLBuffer();
    m_bitsIndex = 0;
    m_bitsUsed = 8;
    m_lastOperationResult = true;
    m_inplaceBitsIndex = 0;
    m_inplaceBitsUsedIndex = 0;
}

///////////////////////////////////////////////////////////////////////////
void oUniStream::EncodeNum16(unsigned short c)
{
	// 0/1  org/inverse
    // 1    16 bits
    // 01   8 bits
    // 00   4 bits

    unsigned short cInv = ~((usUint16_t)c);
    if (cInv < c)
    {
        StreamData(USBits(1, 1)); //"1"
        c = cInv;
    }
    else
    {
        StreamData(USBits(0, 1)); //"1"
    }

	if (c > FILL_BITS(8))
    {
        // Use 16 bits
        StreamData(USBits(1, 1)); //"1"
        CopyNum16(c);
    }
    else if (c > FILL_BITS(4))
    {
        // Use 8 bits
        StreamData(USBits(2, 2)); //"01"
        unsigned char ch = (unsigned char)(c & FILL_BITS(8));
        CopyNum8(ch);
    }
    else
    {
        // Use 4 bits
        StreamData(USBits(0, 2)); //"00"
        StreamData(USBits((unsigned char)(c & FILL_BITS(4)), 4));
    }
}

///////////////////////////////////////////////////////////////////////////
void oUniStream::EncodeNum32(unsigned long c)
{
    // 0/1  org/inverse
    // 1    32 bits
    // 01   16 bits
    // 001  8 bits
    // 000  4 bits

    unsigned long cInv = ~((usUint32_t)c);
    if (cInv < c)
    {
        StreamData(USBits(1, 1)); //"1"
        c = cInv;
    }
    else
    {
        StreamData(USBits(0, 1)); //"0"
    }

    if (c > FILL_BITS(16))
    {
        // Use 32 bits
        StreamData(USBits(1, 1)); //"1"
        CopyNum32(c);
    }
    else if (c > FILL_BITS(8))
    {
        // Use 16 bits
        StreamData(USBits(2, 2)); //"01"
        unsigned short ch = (unsigned short)(c & FILL_BITS(16));
        CopyNum16(ch);
    }
    else if (c > FILL_BITS(4))
    {
        // Use 8 bits
        StreamData(USBits(4, 3)); //"001"
        unsigned char ch = (unsigned char)(c & FILL_BITS(8));
        CopyNum8(ch);
    }
    else
    {
        // Use 4 bits
        StreamData(USBits(0, 3)); //"000"
        StreamData(USBits((unsigned char)(c & FILL_BITS(4)), 4));
    }
}

///////////////////////////////////////////////////////////////////////////
void oUniStream::EncodeNum64(unsigned long long c)
{
    // 0/1  org/inverse
    // 1    64 bits
    // 01   40 bits
    // 001  16 bits
    // 000  8 bits

    unsigned long long cInv = ~((usUint64_t)c);;
    if (cInv < c)
    {
        StreamData(USBits(1, 1)); //"1"
        c = cInv;
    }
    else
    {
        StreamData(USBits(0, 1)); //"1"
    }

	if (c > FILL_BITS_LONG(40))
    {
        // Use 64 bits
        StreamData(USBits(1, 1)); //"1"
        CopyNum64(c);
    }
    else if (c > FILL_BITS(16))
    {
        // Use 40 bits
        StreamData(USBits(2, 2)); //"01"
        unsigned long chLong = (unsigned long)( c & FILL_BITS_LONG(32) );
        unsigned char chChar = (unsigned char)((c >> 32) & FILL_BITS(8));
        CopyNum32(chLong);
        CopyNum8(chChar);
    }
    else if (c > FILL_BITS(8))
    {
        // Use 16 bits
        StreamData(USBits(4, 3)); //"001"
        unsigned short ch = (unsigned short)(c & FILL_BITS(16));
        CopyNum16(ch);
    }
    else
    {
        // Use 8 bits
        StreamData(USBits(0, 3)); //"000"
        unsigned char ch = (unsigned char)(c & FILL_BITS(8));
        CopyNum8(ch);
    }
}

///////////////////////////////////////////////////////////////////////////
void oUniStream::CopyNum16(unsigned short c)
{
    CopyNum8((unsigned char)((c >> 0) & FILL_BITS(8)));
    CopyNum8((unsigned char)((c >> 8) & FILL_BITS(8)));
}

///////////////////////////////////////////////////////////////////////////
void oUniStream::CopyNum32(unsigned long c)
{
    CopyNum8((unsigned char)((c >> 0) & FILL_BITS(8)));
    CopyNum8((unsigned char)((c >> 8) & FILL_BITS(8)));
    CopyNum8((unsigned char)((c >> 16) & FILL_BITS(8)));
    CopyNum8((unsigned char)((c >> 24) & FILL_BITS(8)));
}

void oUniStream::CopyNum32(unsigned long c, size_t buffIndex)
{
    if (IsLockedForInplace())
    {
        m_lastOperationResult = false;
        throw "Use of locked output stream";
    }

    if (buffIndex + 3 >= GetSTLBufferSize())
    {
        m_lastOperationResult = false;
        throw "Buffer out of range.";
    }
    (*m_buff)[buffIndex++] = (unsigned char)((c >> 0) & FILL_BITS(8));
    (*m_buff)[buffIndex++] = (unsigned char)((c >> 8) & FILL_BITS(8));
    (*m_buff)[buffIndex++] = (unsigned char)((c >> 16) & FILL_BITS(8));
    (*m_buff)[buffIndex++] = (unsigned char)((c >> 24) & FILL_BITS(8));
}

///////////////////////////////////////////////////////////////////////////
void oUniStream::CopyNum64(unsigned long long c)
{
    CopyNum8((unsigned char)((c >> 0) & FILL_BITS(8)));
    CopyNum8((unsigned char)((c >> 8) & FILL_BITS(8)));
    CopyNum8((unsigned char)((c >> 16) & FILL_BITS(8)));
    CopyNum8((unsigned char)((c >> 24) & FILL_BITS(8)));
    CopyNum8((unsigned char)((c >> 32) & FILL_BITS(8)));
    CopyNum8((unsigned char)((c >> 40) & FILL_BITS(8)));
    CopyNum8((unsigned char)((c >> 48) & FILL_BITS(8)));
    CopyNum8((unsigned char)((c >> 56) & FILL_BITS(8)));
}

///////////////////////////////////////////////////////////////////////////
void oUniStream::CopyNum8(unsigned char c, size_t buffIndex)
{
    if (IsLockedForInplace())
    {
        m_lastOperationResult = false;
        throw "Use of locked output stream";
    }

    if (buffIndex >= GetSTLBufferSize())
    {
        m_lastOperationResult = false;
        throw "Buffer out of range.";
    }
    (*m_buff)[buffIndex] = c;
}

///////////////////////////////////////////////////////////////////////////
void oUniStream::CopyNum8(unsigned char c)
{
    PushBack(c);
}

///////////////////////////////////////////////////////////////////////////
void oUniStream::Transmit8(unsigned char c)
{
    CopyNum8(c);
}

///////////////////////////////////////////////////////////////////////////
void oUniStream::Transmit16(unsigned short c)
{
	if (IsEncodingMode())
		EncodeNum16(c); 
	else 
		CopyNum16(c);
}
///////////////////////////////////////////////////////////////////////////
void oUniStream::Transmit32(unsigned long c)
{
	if (IsEncodingMode())
		EncodeNum32(c);
	else
		CopyNum32(c);
}

///////////////////////////////////////////////////////////////////////////
void oUniStream::Transmit64(unsigned long long c)
{
	if (IsEncodingMode())
		EncodeNum64(c);
	else
		CopyNum64(c);
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::StreamData(const USBits& obj)
{
    if (IsLockedForInplace())
    {
        m_lastOperationResult = false;
        return *this;
    }
    if (!m_lastOperationResult)
    {
        return *this;

    }

    if (obj.bitsCount > 8)
    {
        US_LOG << "Incorrect write bits count : " << (int)obj.bitsCount;
        US_ASSERT();
        m_lastOperationResult = false;
        return *this;
    }

    if (m_bitsUsed >= 8)
    {
        GetBitsByte();
        if (!m_lastOperationResult)
        {
            return *this;

        }
    }

    char bitsCount = obj.bitsCount;
    register unsigned char bits = obj.bits & FILL_BITS(bitsCount);
    register unsigned char c = bits << m_bitsUsed;

    (*m_buff)[m_bitsIndex] |= c;
    if (m_bitsUsed + bitsCount > 8)
    {
        char overflow = m_bitsUsed + bitsCount - 8;
        char saved = 8 - m_bitsUsed;
        c = bits >> saved;
        GetBitsByte();
        if (!m_lastOperationResult)
        {
            return *this;

        }
        (*m_buff)[m_bitsIndex] |= c;
        m_bitsUsed += overflow;
    }
    else
    {
        m_bitsUsed += bitsCount;
    }

    return *this;
}

///////////////////////////////////////////////////////////////////////////
void oUniStream::AddStreamSettings(const oUniStream& oUs)
{
    if (oUs.IsInplaceMode())
    {
        m_lastOperationResult = false;
        throw "Streaming of inplaced stream";
    }

    StreamData(USSizeType(oUs.GetSTLBufferSize()));

    StreamData(USBits( (oUs.IsEncodingMode() ? 1 : 0), 1 ));
    StreamData(USBits( (oUs.m_lastOperationResult ? 1 : 0), 1));
	// iStream settings
    StreamData(oUs.m_bitsIndex);
    CopyNum8(m_bitsUsed);
}

///////////////////////////////////////////////////////////////////////////
void oUniStream::AddInplaceStreamSettings(const oUniStream& oUs)
{
    // 32 bits size
    StreamData(USBits(0, 3)); //"000"
    m_inplaceSizeStart = GetSTLBufferSize();
    CopyNum32(0UL);
    StreamData(USBits( (oUs.IsEncodingMode() ? 1 : 0), 1 ));

    // TODO : Update this bit on inplace stream flush !
    StreamData(USBits( (oUs.m_lastOperationResult ? 1 : 0), 1));

    // iStream settings
    // 32 bits size
    StreamData(USBits(0, 3)); //"000"
    m_inplaceBitsIndex = GetSTLBufferSize();
    CopyNum32(0UL);

    m_inplaceBitsUsedIndex = GetSTLBufferSize();
    CopyNum8(m_bitsUsed);
}

///////////////////////////////////////////////////////////////////////////
std::vector<unsigned char>& oUniStream::GetBuffer()
{
    if (IsLockedForInplace())
    {
        throw "GetBuffer() from locked stream.";
    }
    if (IsInplaceMode())
    {
        throw "GetBuffer() from locked inplaced stream.";
    }
    if (!m_lastOperationResult)
    {
        throw "GetBuffer() from failed stream.";
    }
    return *m_buff;
}

///////////////////////////////////////////////////////////////////////////
void oUniStream::SetEncodingMode(bool mode)
{
    if (IsLockedForInplace())
    {
        m_lastOperationResult = false;
        throw "Changing mode of locked stream.";
    }
    if (IsInplaceMode())
    {
        m_lastOperationResult = false;
        throw "Changing mode of inplaced stream.";
    }
    if (GetSTLBufferSize())
    {
        m_lastOperationResult = false;
        throw "Changing mode of non empty stream.";
    }

    m_isEncodingMode = mode;
}


///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::PrepareInplace(const oUniInplace& cRef)
{
    oUniStream& inplace = cRef.oStream;
    if (
            (!m_lastOperationResult) ||
            (!inplace.m_lastOperationResult) ||
            (this->IsLockedForInplace()) ||
            (inplace.GetSize()) ||
            (inplace.IsInplaceMode()) ||
            (false)
       )
    {
        m_lastOperationResult = false;
        inplace.m_lastOperationResult = false;
        return *this;
    }

    // this stream
    this->AddInplaceStreamSettings(inplace);
    this->LockForInplace();
    this->m_inplaceStartIndex = GetSTLBufferSize();

    // inplace strem
    inplace.m_bitsIndex = 0;
    inplace.m_bitsUsed = 8;
    inplace.m_lastOperationResult = true;
    inplace.m_buff = this->m_buff;
    inplace.SetInplaceMode(true);
    inplace.m_globalOffset = inplace.GetSTLBufferSize();

    return *this;
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::FlushInplaceStreaming(oUniStream& oUs)
{
    if (false == oUs.IsInplaceMode())
    {
        m_lastOperationResult = false;
        return *this;
    }
    oUs.m_buff = &(oUs.m_buffObj);
    oUs.m_lastOperationResult = false;
    this->UnlockFromInplace();

    // We dond want to trust inplace.GetSize() here.
    size_t inplaceSz = GetSTLBufferSize() - m_inplaceStartIndex;
    size_t bitsIndex = oUs.m_bitsIndex - m_inplaceStartIndex;


    this->CopyNum32((unsigned long)inplaceSz, m_inplaceSizeStart);
    this->CopyNum32((unsigned long)bitsIndex, m_inplaceBitsIndex);
    this->CopyNum8((unsigned long)oUs.m_bitsUsed, m_inplaceBitsUsedIndex);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::StreamData(oUniStream& oUs)
{
    if ((!oUs.m_lastOperationResult) || (!m_lastOperationResult))
    {
        oUs.m_lastOperationResult = false;
        m_lastOperationResult = false;
        return *this;
    }

    if (IsLockedForInplace())
    {
        return FlushInplaceStreaming(oUs);
    }

    AddStreamSettings(oUs);
    for (unsigned char c : *(oUs.m_buff))
    {
        CopyNum8(c);
    }
    return *this;
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::StreamData(const USSizeType& containerSize)
{
    // 1    4 bits
    // 01   8 bits
    // 001  16 bits
    // 000  32 bits
    unsigned long sz = (unsigned long)containerSize;
    if (sz <= FILL_BITS(4))
    {
        // 4 bits size
        StreamData(USBits(1, 1)); // "1"
        StreamData(USBits((unsigned char)(sz & FILL_BITS(4)), 4));
    }
    else if (sz <= FILL_BITS(8))
    {
        // 8 bits size
        StreamData(USBits(2, 2)); //"01"
        unsigned char szChar = (unsigned char)(sz & FILL_BITS(8));
        CopyNum8(szChar);
    }
    else if (sz <= FILL_BITS(16))
    {
        // 16 bits size
        StreamData(USBits(4, 3)); //"001"
        unsigned short szShort = (unsigned short)(sz & FILL_BITS(16));
        CopyNum16(szShort);
    }
    else
    {
        // 32 bits size
        StreamData(USBits(0, 3)); //"000"
        CopyNum32(sz);
    }

    return *this;
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::StreamData(const unsigned char& cRef)
{
    StreamData(USBits(US_MASK_UINT_8, US_MASK_BIT_SIZE));
    Transmit8(cRef);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::StreamData(const signed char& cRef)
{
    signed char c = cRef;
    unsigned char cUnsigned = reinterpret_cast<unsigned char&>(c);
    StreamData(USBits(US_MASK_SINT_8, US_MASK_BIT_SIZE));
    Transmit8(cUnsigned);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::StreamData(const unsigned short& cRef)
{
    unsigned short c = cRef;
    if (2 == sizeof(short))
    {
        StreamData(USBits(US_MASK_UINT_16, US_MASK_BIT_SIZE));
        Transmit16(c);
        return *this;
    }
    // 'short' is AT LEAST 16 bits
    else if (4 == sizeof(short))
    {
        StreamData(USBits(US_MASK_UINT_32, US_MASK_BIT_SIZE));
        Transmit32((unsigned long)c);
        return *this;
    }
    UNHANDLED_CASE();
    return *this;
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::StreamData(const signed short& cRef)
{
    signed short c = cRef;
    unsigned short cUnsigned = reinterpret_cast<signed short&>(c);
    if (2 == sizeof(short))
    {
        StreamData(USBits(US_MASK_SINT_16, US_MASK_BIT_SIZE));
        Transmit16(cUnsigned);
        return *this;
    }
    // 'short' is AT LEAST 16 bits
    else if (4 == sizeof(short))
    {
        StreamData(USBits(US_MASK_SINT_32, US_MASK_BIT_SIZE));
        Transmit32((unsigned long)(cUnsigned));
        return *this;
    }
    UNHANDLED_CASE();
    return *this;
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::StreamData(const unsigned long& cRef)
{
    unsigned long c = cRef;
    if (4 == sizeof(long))
    {
        StreamData(USBits(US_MASK_UINT_32, US_MASK_BIT_SIZE));
        Transmit32(c);
        return *this;
    }
    // 'long' is AT LEAST 32 bits
    else if (8 == sizeof(long))
    {
        StreamData(USBits(US_MASK_UINT_64, US_MASK_BIT_SIZE));
        Transmit64((unsigned long long)c);
        return *this;
    }
    UNHANDLED_CASE();
    return *this;
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::StreamData(const signed long& cRef)
{
    signed long c = cRef;
    unsigned long cUnsigned = reinterpret_cast<unsigned long&>(c);
    if (4 == sizeof(long))
    {
        StreamData(USBits(US_MASK_SINT_32, US_MASK_BIT_SIZE));
        Transmit32(cUnsigned);
        return *this;
    }
    // 'long' is AT LEAST 32 bits
    else if (8 == sizeof(long))
    {
        StreamData(USBits(US_MASK_SINT_64, US_MASK_BIT_SIZE));
        Transmit64((unsigned long long)(cUnsigned));
        return *this;
    }
    UNHANDLED_CASE();
    return *this;
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::StreamData(const unsigned long long& cRef)
{
    unsigned long long c = cRef;
    // 'long long' is AT LEAST 64 bits
    if (8 == sizeof(long long))
    {
        StreamData(USBits(US_MASK_UINT_64, US_MASK_BIT_SIZE));
        Transmit64(c);
        return *this;
    }
    UNHANDLED_CASE();
    return *this;
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::StreamData(const signed long long& cRef)
{
    signed long long c = cRef;
    unsigned long long cUnsigned = reinterpret_cast<unsigned long long&>(c);
    // 'long long' is AT LEAST 64 bits
    if (8 == sizeof(long long))
    {
        StreamData(USBits(US_MASK_SINT_64, US_MASK_BIT_SIZE));
        Transmit64(cUnsigned);
        return *this;
    }
    UNHANDLED_CASE();
    return *this;
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::StreamData(const unsigned& cRef)
{
    unsigned c = cRef;
    // 'int' is AT LEAST 16 bis
    if (2 == sizeof(int))
    {
        StreamData(USBits(US_MASK_UINT_16, US_MASK_BIT_SIZE));
        Transmit16((unsigned short)c);
        return *this;
    }
    else if (4 == sizeof(int))
    {
        StreamData(USBits(US_MASK_UINT_32, US_MASK_BIT_SIZE));
        Transmit32((unsigned long)c);
        return *this;
    }
    else if (8 == sizeof(int))
    {
        StreamData(USBits(US_MASK_UINT_64, US_MASK_BIT_SIZE));
        Transmit64((unsigned long long)c);
        return *this;
    }
    UNHANDLED_CASE();
    return *this;
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::StreamData(const signed& cRef)
{
    signed c = cRef;
    unsigned cUnsigned = reinterpret_cast<unsigned&>(c);
    // 'int' is AT LEAST 16 bis
    if (2 == sizeof(int))
    {
        StreamData(USBits(US_MASK_SINT_16, US_MASK_BIT_SIZE));
        Transmit16((unsigned short)(cUnsigned));
        return *this;
    }
    else if (4 == sizeof(int))
    {
        StreamData(USBits(US_MASK_SINT_32, US_MASK_BIT_SIZE));
        Transmit32((unsigned long)(cUnsigned));
        return *this;
    }
    else if (8 == sizeof(int))
    {
        StreamData(USBits(US_MASK_SINT_64, US_MASK_BIT_SIZE));
        Transmit64((unsigned long long)(cUnsigned));
        return *this;
    }
    UNHANDLED_CASE();
    return *this;
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::StreamData(const char& cRef)
{
    unsigned char cC = (unsigned char)cRef;
    StreamData(cC);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::StreamData(const bool& cRef)
{
    StreamData(USBits(US_MASK_BOOL_1, US_MASK_BIT_SIZE));
    if (cRef)
    {
        StreamData(USBits(1, 1));
    }
    else
    {
        StreamData(USBits(0, 1));
    }
    return *this;
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::StreamData(const float& cRef)
{
    float c = cRef;

    if (4 == sizeof(float))
    {
        StreamData(USBits(US_MASK_FLOAT_32, US_MASK_BIT_SIZE));
        usUint32_t cC = reinterpret_cast<usUint32_t&>(c);
        CopyNum32((unsigned long)cC);
    }
    else
    {
        UNHANDLED_CASE();
    }
    return *this;
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::StreamData(const double& cRef)
{
    double c = cRef;
    if (8 == sizeof(double))
    {
        StreamData(USBits(US_MASK_DOUBLE_64, US_MASK_BIT_SIZE));
        usUint64_t cC = reinterpret_cast<usUint64_t&>(c);
        CopyNum64((unsigned long long)cC);
    }
    else
    {
        UNHANDLED_CASE();
    }
    return *this;
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::StreamData(const wchar_t& cRef)
{
    wchar_t c = cRef;
    if (sizeof(wchar_t) == 2)
    {
        StreamData(USBits(US_MASK_CHAR_16, US_MASK_BIT_SIZE));
        usUint16_t cC = reinterpret_cast<usUint16_t&>(c);
        Transmit16((unsigned short)cC);
    }
    else if(sizeof(wchar_t) == 4)
    {
        StreamData(USBits(US_MASK_CHAR_32, US_MASK_BIT_SIZE));
        usUint32_t cC = reinterpret_cast<usUint32_t&>(c);
        Transmit32((unsigned long)cC);
    }
    else
    {
        UNHANDLED_CASE();
    }
    return *this;
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::StreamData(const char16_t& cRef)
{
    char16_t c = cRef;
    StreamData(USBits(US_MASK_CHAR_16, US_MASK_BIT_SIZE));

    if (sizeof(char16_t) == 2)
    {
        usUint16_t cC = reinterpret_cast<usUint16_t&>(c);
        Transmit16((unsigned short)cC);
    }
    else if(sizeof(char16_t) == 4)
    {
        usUint32_t cC = reinterpret_cast<usUint32_t&>(c);
        Transmit16((unsigned short)cC);
    }
    else
    {
        UNHANDLED_CASE();
    }
    return *this;
}

///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::StreamData(const char32_t& cRef)
{
    char32_t c = cRef;
    StreamData(USBits(US_MASK_CHAR_32, US_MASK_BIT_SIZE));

    if (sizeof(char32_t) == 4)
    {
        usUint32_t cC = reinterpret_cast<usUint32_t&>(c);
        Transmit32((unsigned long)cC);
    }
    else if(sizeof(char32_t) == 8)
    {
        usUint64_t cC = reinterpret_cast<usUint64_t&>(c);
        Transmit32((unsigned long)cC);
    }
    else
    {
        UNHANDLED_CASE();
    }
    return *this;
}

///////////////////////////////////////////////////////////////////////////
size_t oUniStream::GetSize() const
{
    if (IsInplaceMode())
    {
        return GetSTLBufferSize() - m_globalOffset;
    }
    return GetSTLBufferSize();
}


///////////////////////////////////////////////////////////////////////////
oUniStream& oUniStream::StreamData(void * const &cRef)
{
    void* c = cRef;
    if (sizeof(void*) == 2)
    {
        usUint16_t cC = reinterpret_cast<usUint16_t&>(c);
        StreamData((unsigned short)cC);
    }
    else if(sizeof(void*) == 4)
    {
        usUint32_t cC = reinterpret_cast<usUint32_t&>(c);
        StreamData((unsigned long)cC);
    }
    else if(sizeof(void*) == 8)
    {
        usUint64_t cC = reinterpret_cast<usUint64_t&>(c);
        StreamData((unsigned long long)cC);
    }
    else
    {
        UNHANDLED_CASE();
    }
    return *this;
}

#pragma GCC diagnostic pop
