
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"


///////////////////////////////////////////////////////////////////////////
template<typename T>
void iUniStream::SafeCast(T& c)
{
    USBits mask(0, US_MASK_BIT_SIZE);
    *this >> mask;
    switch (mask.bits)
    {
    case US_MASK_UINT_8:
    {
        unsigned char cC = 0;
        Receive8(cC);
        c = (T)cC;
    }
    break;
    case US_MASK_SINT_8:
    {
        unsigned char cC = 0;
        Receive8(cC);
        signed char cSigned = reinterpret_cast<signed char&>(cC);
        c = (T)cSigned;
    }
    break;
    case US_MASK_UINT_16:
    {
        unsigned short cC = 0;
        Receive16(cC);
        c = (T)cC;
    }
    break;
    case US_MASK_SINT_16:
    {
        unsigned short cC = 0;
        Receive16(cC);
        signed short cSigned = reinterpret_cast<signed short&>(cC);
        c = (T)cSigned;
    }
    break;
    case US_MASK_UINT_32:
    {
        unsigned long cC = 0;
        Receive32(cC);
        c = (T)cC;
    }
    break;
    case US_MASK_SINT_32:
    {
        unsigned long cC = 0;
        Receive32(cC);
        signed long cSigned = reinterpret_cast<signed long&>(cC);
        c = (T)cSigned;
    }
    break;
    case US_MASK_UINT_64:
    {
        unsigned long long cC = 0;
        Receive64(cC);
        c = (T)cC;
    }
    break;
    case US_MASK_SINT_64:
    {
        unsigned long long cC = 0;
        Receive64(cC);
        signed long long cSigned = reinterpret_cast<signed long long&>(cC);
        c = (T)cSigned;
    }
    break;
    case US_MASK_CHAR_16:
    {
        unsigned short cC = 0;
        Receive16(cC);
        if (sizeof(char16_t) == 2)
        {
            usUint16_t tmp = (usUint16_t)(cC);
            char16_t ch = reinterpret_cast<char16_t&>(tmp);
            c = (T)ch;
        }
        else if(sizeof(char16_t) == 4)
        {
            usUint32_t tmp = (usUint32_t)(cC);
            char32_t ch = reinterpret_cast<char32_t&>(tmp);
            c = (T)ch;
        }
        else
        {
            UNHANDLED_CASE();
        }
    }
    break;
    case US_MASK_CHAR_32:
    {
        unsigned long cC = 0;
        Receive32(cC);
        if(sizeof(char32_t) == 4)
        {
            usUint32_t tmp = (usUint32_t)(cC);
            char32_t ch = reinterpret_cast<char32_t&>(tmp);
            c = (T)ch;
        }
        else if (sizeof(char32_t) == 8)
        {
            usUint64_t tmp = (usUint64_t)(cC);
            char32_t ch = reinterpret_cast<char32_t&>(tmp);
            c = (T)ch;
        }
        else
        {
            UNHANDLED_CASE();
        }
    }
    break;
    case US_MASK_FLOAT_32:
    {
        unsigned long cC = 0;
        CopyNum32(cC);
        if (sizeof(float) == 4)
        {
            usUint32_t tmp = (usUint32_t)(cC);
            float ch = reinterpret_cast<float&>(tmp);
            c = (T)ch;
        }
        else
        {
            UNHANDLED_CASE();
        }
    }
    break;
    case US_MASK_DOUBLE_64:
    {
        unsigned long long cC = 0;
        CopyNum64(cC);
        if (sizeof(long long) == 8)
        {
            usUint64_t tmp = (usUint64_t)(cC);
            double ch = reinterpret_cast<double&>(tmp);
            c = (T)ch;
        }
        else
        {
            UNHANDLED_CASE();
        }
    }
    break;
    case US_MASK_BOOL_1:
    {
        USBits boolMask(1, 1);
        GetStreamData(boolMask);
        bool val = (boolMask.bits == 1);
        c = (T)val;
    }
    break;
    default:
        UNHANDLED_CASE();
    break;
    }
}

///////////////////////////////////////////////////////////////////////////
template<typename T>
iUniStream& iUniStream::operator >> (std::vector<T>& cRef)
{
	USSizeType len;

    if (!(*this >> len))
    {
        return *this;
    }
	cRef.clear();
	for (size_t i = 0; i < len; i++)
	{
		cRef.push_back(T());

        if (!(*this >> (cRef.back())))
        {
            return *this;
        }
	}
	return *this;
}

template<typename T>
iUniStream& iUniStream::operator >> (std::basic_string<T>& cRef)
{
	USSizeType len;

    if (!(*this >> len))
    {
        return *this;
    }
	cRef.clear();
	for (size_t i = 0; i < len; i++)
	{
		cRef.push_back(T());
        if (!(*this >> (cRef.back())))
        {
            return *this;
        }
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
template<typename T, typename KeyT>
iUniStream& iUniStream::operator >> (std::pair<KeyT, T>& cRef)
{
    if ((*this >> (cRef.first)))
        *this >> (cRef.second);
	return *this;
}

///////////////////////////////////////////////////////////////////////////
template<typename T>
iUniStream& iUniStream::operator >> (std::list<T>& cRef)
{
	USSizeType len;

    if (!(*this >> len))
    {
        return *this;
    }
	cRef.clear();
	for (size_t i = 0; i < len; i++)
	{
		cRef.push_back(T());
        if (!(*this >> (cRef.back())))
        {
            return *this;
        }
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
template<typename T>
iUniStream& iUniStream::operator >> (std::set<T>& cRef)
{
	USSizeType len;

    if (!(*this >> len))
    {
        return *this;
    }
	cRef.clear();
	for (size_t i = 0; i < len; i++)
	{
		T newE = T();
        if (!(*this >> newE))
        {
            return *this;
        }
		cRef.insert(newE);
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
template<typename T, typename KeyT>
iUniStream& iUniStream::operator >> (std::map<KeyT, T>& cRef)
{
	USSizeType len;

    if (!(*this >> len))
    {
        return *this;
    }
	cRef.clear();
	for (size_t i = 0; i < len; i++)
	{
		KeyT k;
        if (!(*this >> k))
        {
            return *this;
        }
		auto it = cRef.insert(std::pair<KeyT, T>(k, T()));
        if (!(*this >> (it.first->second)))
        {
            return *this;
        }
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
template<typename T>
iUniStream& iUniStream::operator >> (std::shared_ptr<T>& cRef)
{
	cRef = std::make_shared<T>();
    if (!(*this >> (*cRef)))
    {
        return *this;
    }
	return *this;
}

///////////////////////////////////////////////////////////////////////////
template<typename T, size_t size>
iUniStream& iUniStream::operator >> (T(&arr)[size])
{
    USSizeType len;
    if (!(*this >> len))
    {
        return *this;
    }
    if (size != len)
    {
        m_lastOperationResult = false;
        throw "Reading array with different size.";
        return *this;
    }

	for (size_t i = 0; i < size; i++)
	{
        if (!(*this >> arr[i]))
        {
            return *this;
        }
	}

	return *this;
};

///////////////////////////////////////////////////////////////////////////
template<typename T>
iUniStream& iUniStream::operator >> (T*& cRef)
{
    void* tmpPtr;
    GetStreamData(tmpPtr);
    cRef = (T*)tmpPtr;
    return *this;
}

///////////////////////////////////////////////////////////////////////////
template<typename T>
iUniStream& iUniStream::Deserialize(T& t1)
{
    (*this) >> t1;
    return *this;
}

///////////////////////////////////////////////////////////////////////////
template<typename T, typename ... Types>
iUniStream& iUniStream::Deserialize(T& t1, Types& ...  args)
{
    (*this) >> t1;
    (*this).Deserialize(args...);
    return *this;
}
#pragma GCC diagnostic pop
