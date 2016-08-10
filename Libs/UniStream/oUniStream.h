#pragma once
#include "ioUniStream.h"

namespace MGTools {

class oUniStream
{
private:
    oUniStream(const oUniStream& oStream); // copy
public:
    oUniStream();
    oUniStream(oUniStream&& oStream); // move
    oUniStream& operator=(oUniStream&& oStream);

    oUniStream& operator<<(const USBits& obj);
    oUniStream& operator<<(oUniStream& Bbs);
    oUniStream& operator<<(const USSizeType& containerSize);

    oUniStream& operator<<(const unsigned char& cRef);

    oUniStream& operator<<(const signed char& cRef);
    oUniStream& operator<<(const unsigned short& cRef);
    oUniStream& operator<<(const signed short& cRef);
    oUniStream& operator<<(const unsigned long& cRef);
    oUniStream& operator<<(const signed long& cRef);
    oUniStream& operator<<(const unsigned long long& cRef);
    oUniStream& operator<<(const signed long long& cRef);
    oUniStream& operator<<(const unsigned& cRef);
    oUniStream& operator<<(const signed& cRef);
    oUniStream& operator<<(const char& cRef);
    oUniStream& operator<<(bool& cRef);

    oUniStream& operator<<(const float& cRef);
    oUniStream& operator<<(const double& cRef);

    oUniStream& operator<<(const wchar_t& cRef);
    oUniStream& operator<<(const char16_t& cRef);
    oUniStream& operator<<(const char32_t& cRef);

    oUniStream& operator>>(const oUniInplace& cRef);

    ///////////////////////////////////////////////////////////////////////////

    oUniStream& Serialize() { return *this; };

    template<typename T>
    oUniStream& Serialize(T t1);

    template<typename T, typename ... Types>
    oUniStream& Serialize(T t1, Types ...  args);

    template<typename T>
    oUniStream& operator<<(T* const & cRef);
    template<typename T>
    oUniStream& operator<<(const std::vector<T>& cRef);
	template<typename T>
    oUniStream& operator<<(const std::basic_string<T>& cRef);
	template<typename T, typename KeyT>
    oUniStream& operator<<(const std::pair<KeyT, T>& cRef);
	template<typename T>
    oUniStream& operator<<(const std::list<T>& cRef);
	template<typename T>
    oUniStream& operator<<(const std::set<T>& cRef);
	template<typename T, typename KeyT>
    oUniStream& operator<<(const std::map<KeyT, T>& cRef);
	template<typename T>
    oUniStream& operator<<(const std::shared_ptr<T>& cRef);
	///////////////////////////////////////////////////////////////////////////

	template<typename T, size_t size>
    oUniStream& operator<<(const T(&arr)[size]);

    bool IsEncodingMode() const { return m_isEncodingMode; };
    bool IsInplaceMode() const { return m_isInplaceMode; };
    bool IsLockedForInplace() const { return m_isLockedForInplace; };

    void SetEncodingMode(bool mode = true);
    explicit operator bool() const{return m_lastOperationResult;};
    size_t GetSize() const;
    std::vector<unsigned char> &GetBuffer();
    void Reset();
private:
    void ClearSTLBuffer();
    size_t GetSTLBufferSize() const;
    void PushSTLBack(unsigned char c);

    void LockForInplace() { m_isLockedForInplace = true; };
    void UnlockFromInplace() { m_isLockedForInplace = false; };
    void SetInplaceMode(bool isInplace) { m_isInplaceMode = isInplace; };
    void AddInplaceStreamSettings(const oUniStream& oUs);
    void AddStreamSettings(const oUniStream& oUs);


    oUniStream& StreamData(const USBits& obj);
    oUniStream& StreamData(oUniStream& Bbs);
    oUniStream& StreamData(const USSizeType& containerSize);
    oUniStream& StreamData(const unsigned char& cRef);
    oUniStream& StreamData(const signed char& cRef);
    oUniStream& StreamData(const unsigned short& cRef);
    oUniStream& StreamData(const signed short& cRef);
    oUniStream& StreamData(const unsigned long& cRef);
    oUniStream& StreamData(const signed long& cRef);
    oUniStream& StreamData(const unsigned long long& cRef);
    oUniStream& StreamData(const signed long long& cRef);
    oUniStream& StreamData(const unsigned& cRef);
    oUniStream& StreamData(const signed& cRef);
    oUniStream& StreamData(const char& cRef);
    oUniStream& StreamData(const bool& cRef);
    oUniStream& StreamData(const float& cRef);
    oUniStream& StreamData(const double& cRef);
    oUniStream& StreamData(const wchar_t& cRef);
    oUniStream& StreamData(const char16_t& cRef);
    oUniStream& StreamData(const char32_t& cRef);

    oUniStream& StreamData(void* const & cRef);

    oUniStream& PrepareInplace(const oUniInplace& cRef);
    oUniStream& FlushInplaceStreaming(oUniStream& oUs);

    void Transmit8(unsigned char c);
	void Transmit16(unsigned short c);
	void Transmit32(unsigned long c);
	void Transmit64(unsigned long long c);

    void EncodeNum16(unsigned short c);
    void EncodeNum32(unsigned long c);
    void EncodeNum64(unsigned long long c);

    void CopyNum16(unsigned short c);
    void CopyNum32(unsigned long c);
    void CopyNum32(unsigned long c, size_t buffIndex);
    void CopyNum64(unsigned long long c);
    void CopyNum8(unsigned char c);
    void CopyNum8(unsigned char c, size_t buffIndex);

    void GetBitsByte();
    void PushBack(unsigned char c);
    std::vector<unsigned char>   m_buffObj;
    std::vector<unsigned char>*  m_buff;
    USSizeType		m_bitsIndex;
    unsigned char   m_bitsUsed;
    bool            m_lastOperationResult;
    bool            m_isEncodingMode;
    bool            m_isLockedForInplace;
    bool            m_isInplaceMode;
    size_t          m_inplaceStartIndex;
    size_t          m_inplaceSizeStart;
    size_t          m_globalOffset;
    size_t          m_inplaceBitsIndex;
    size_t          m_inplaceBitsUsedIndex;

    friend class iUniStream;
};
#include "oUniStreamSTL.hpp"

}
