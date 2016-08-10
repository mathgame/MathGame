#pragma once

#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <memory>
#include "UniStreamConfig.h"


// 2^6
#define FILL_BITS(p) ((1UL << (p)) - 1)
#define FILL_BITS_LONG(p) ((1ULL << (p)) - 1)

#define UNHANDLED_CASE()

#define US_MASK_UINT_8      ((unsigned char)(0))
#define US_MASK_SINT_8      ((unsigned char)(1))
#define US_MASK_UINT_16     ((unsigned char)(2))
#define US_MASK_SINT_16     ((unsigned char)(3))
#define US_MASK_UINT_32     ((unsigned char)(4))
#define US_MASK_SINT_32     ((unsigned char)(5))
#define US_MASK_UINT_64     ((unsigned char)(6))
#define US_MASK_SINT_64     ((unsigned char)(7))
#define US_MASK_CHAR_16     ((unsigned char)(8))
#define US_MASK_CHAR_32     ((unsigned char)(9))
#define US_MASK_FLOAT_32    ((unsigned char)(10))
#define US_MASK_DOUBLE_64   ((unsigned char)(11))
#define US_MASK_BOOL_1      ((unsigned char)(12))
#define US_MASK_BIT_SIZE (4)

namespace MGTools {

class iUniStream;
class oUniStream;

class USSizeType
{
public:
    USSizeType()
		: m_size(0) {}
    USSizeType(size_t sz)
        : m_size(sz){}

    operator size_t() const { return m_size; };
    bool operator>	(size_t sz)	{return m_size >  sz;};
    bool operator<=	(size_t sz)	{return m_size <= sz;};
    bool operator<	(size_t sz)	{return m_size <  sz;};
    bool operator>=	(size_t sz)	{return m_size >= sz;};
    bool operator==	(size_t sz)	{return m_size == sz;};
    bool operator!=	(size_t sz)	{return m_size != sz;};
    USSizeType	operator+	(const size_t sz)		{return USSizeType(m_size + sz);};
    USSizeType	operator-	(const size_t sz)		{return USSizeType(m_size - sz);};
    USSizeType&	operator+=	(const size_t sz)		{m_size += sz; return *this;};
    USSizeType&	operator-=	(const size_t sz)		{m_size -= sz; return *this;};

    USSizeType & operator++() // ++s
    {
        ++m_size;
        return *this ;
    }

    USSizeType operator++(int) // s++
    {
       USSizeType temp = *this ;
       temp.m_size++;
       return temp ;
    }

private:
	size_t m_size;
};

class USBits
{
public:
    unsigned char bits;
    unsigned char bitsCount;
    USBits():bits(0),bitsCount(0){};
    USBits(const char* bitsString)
    {
        unsigned char bitsVal = 0;
        int i = 0;
        while(bitsString[i])
        {
            unsigned char mask = (bitsString[i] == '1') ? 1 : 0;
            mask <<= i;
            bitsVal |= mask;
            i++;
        }
        bits = bitsVal;
        bitsCount = i;
    }

    USBits(unsigned char bitsVal, unsigned char count)
        : bits(bitsVal), bitsCount(count) {};
};

class iUniInplace
{
public:
    iUniInplace(iUniStream& i_Stream);
    iUniStream& iStream;
private:
    iUniInplace();
};
class oUniInplace
{
public:
    oUniInplace(oUniStream& o_Stream);
    oUniStream& oStream;
private:
    oUniInplace();
};
};
