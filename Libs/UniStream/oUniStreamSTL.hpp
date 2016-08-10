///////////////////////////////////////////////////////////////////////////
template<typename T>
oUniStream& oUniStream::operator<<(const std::vector<T>& cRef)
{
	*this << USSizeType(cRef.size());
	for (const T& e : cRef)
	{
        if (!(*this << e))
        {
            return *this;
        }
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
template<typename T>
oUniStream& oUniStream::operator<<(const std::basic_string<T>& cRef)
{
	*this << USSizeType(cRef.size());
	for (const T& e : cRef)
	{
        if (!(*this << e))
        {
            return *this;
        }
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
template<typename T, typename KeyT>
oUniStream& oUniStream::operator<<(const std::pair<KeyT, T>& cRef)
{
    if ((*this << (cRef.first)))
    {
        *this << (cRef.second);
    }
	return *this;
}

///////////////////////////////////////////////////////////////////////////
template<typename T>
oUniStream& oUniStream::operator<<(const std::list<T>& cRef)
{
    if (!(*this << USSizeType(cRef.size())))
    {
        return *this;
    }
	for (const T& e : cRef)
	{
        if (!(*this << e))
        {
            return *this;
        }
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
template<typename T>
oUniStream& oUniStream::operator<<(const std::set<T>& cRef)
{
    if (!(*this << USSizeType(cRef.size())))
    {
        return *this;
    }

	for (const T& e : cRef)
	{
        if (!(*this << e))
        {
            return *this;
        }
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
template<typename T, typename KeyT>
oUniStream& oUniStream::operator<<(const std::map<KeyT, T>& cRef)
{
    if (!(*this << USSizeType(cRef.size())))
    {
        return *this;
    }
	for (const auto& e : cRef)
	{
        if (!(*this << (e.first) << (e.second)))
        {
            return *this;
        }
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
template<typename T>
oUniStream& oUniStream::operator<<(const std::shared_ptr<T>& cRef)
{
	*this << (*cRef);
	return *this;
}

///////////////////////////////////////////////////////////////////////////
template<typename T, size_t size>
oUniStream& oUniStream::operator<<(const T(&arr)[size])
{
    if (!(*this << USSizeType(size)))
    {
        return *this;
    }
	for (size_t i = 0; i < size; i++)
	{
        if (!(*this << arr[i]))
        {
            return *this;
        }
	}
	return *this;
};

///////////////////////////////////////////////////////////////////////////
template<typename T>
oUniStream& oUniStream::operator<<(T* const & cRef)
{
    void* c = (void*)cRef;
    return StreamData(c);
}

///////////////////////////////////////////////////////////////////////////
template<typename T>
oUniStream& oUniStream::Serialize(T t1)
{
    (*this) << t1;
    return *this;
}

///////////////////////////////////////////////////////////////////////////
template<typename T, typename ... Types>
oUniStream& oUniStream::Serialize(T t1, Types ...  args)
{
    (*this) << t1;
    (*this).Serialize(args...);
    return *this;
}
