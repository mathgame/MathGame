#pragma once
#include "ioUniStream.h"

namespace MGTools {

class iUniStream
{
private:
    iUniStream(const iUniStream& iStream); // copy
public:
    iUniStream();
    iUniStream(std::vector<unsigned char> &buff, bool decodingMode = false);
    iUniStream(oUniStream &iStream);
    iUniStream(iUniStream&& iStream); // move
    iUniStream& operator=(iUniStream&& iStream);

    void SetBuffer(std::vector<unsigned char>& buff, bool decodingMode = false);

    iUniStream& operator>>(USBits& obj);
    iUniStream& operator>>(iUniStream& Bbs);
    iUniStream& operator>> (oUniStream& Bbs);
    iUniStream& operator>>(USSizeType& Bbs);
    iUniStream& operator>>(unsigned char& cRef);
    iUniStream& operator>>(signed char& cRef);
    iUniStream& operator>>(unsigned short& cRef);
    iUniStream& operator>>(signed short& cRef);
    iUniStream& operator>>(unsigned long& cRef);
    iUniStream& operator>>(signed long& cRef);
    iUniStream& operator>>(unsigned long long& cRef);
    iUniStream& operator>>(signed long long& cRef);
    iUniStream& operator>>(unsigned& cRef);
    iUniStream& operator>>(signed& cRef);
    iUniStream& operator>>(char& cRef);
    iUniStream& operator>> (bool& cRef);
    iUniStream& operator>> (float& cRef);
    iUniStream& operator>> (double& cRef);
    iUniStream& operator>> (wchar_t& cRef);
    iUniStream& operator>> (char16_t& cRef);
    iUniStream& operator>> (char32_t& cRef);

    iUniStream& operator>> (const iUniInplace& cRef);




    ///////////////////////////////////////////////////////////////////////////

    template<typename T>
    iUniStream& Deserialize(T& t1);

    template<typename T, typename ... Types>
    iUniStream& Deserialize(T& t1, Types& ...  args);

    template<typename T>
    iUniStream& operator >> (T*& cRef);
	template<typename T>
	iUniStream& operator >> (std::vector<T>& cRef);
	template<typename T>
	iUniStream& operator >> (std::basic_string<T>& cRef);
	template<typename T, typename KeyT>
	iUniStream& operator >> (std::pair<KeyT, T>& cRef);
	template<typename T>
	iUniStream& operator >> (std::list<T>& cRef);
	template<typename T>
	iUniStream& operator >> (std::set<T>& cRef);
	template<typename T, typename KeyT>
	iUniStream& operator >> (std::map<KeyT, T>& cRef);
	template<typename T>
	iUniStream& operator >> (std::shared_ptr<T>& cRef);
	///////////////////////////////////////////////////////////////////////////

	template<typename T, size_t size>
	iUniStream& operator>>(T(&arr)[size]);

    bool IsDecodingMode() const { return m_isDecodingMode; };
    void SetDecodingMode(bool mode = true) { if(m_buff->size()) return;  m_isDecodingMode = mode; };
    explicit operator bool() const{return m_lastOperationResult;};
    void Reset();
    size_t GetSize() const;// { return m_buff->size(); };
    bool IsEmpty() const;// { return m_buff->empty(); };
private:
    template<typename T>
    void SafeCast(T& c);

    void ClearSTLBuffer();
    size_t GetSTLBufferSize() const;
    void PushSTLBack(unsigned char c);
    //void PopSTLFront(unsigned char& c);

	void GetStreamSettings(iUniStream& Bbs);
	void GetStreamSettings(oUniStream& Bbs);

    void Receive8(unsigned char& c);
	void Receive16(unsigned short& c);
	void Receive32(unsigned long& c);
	void Receive64(unsigned long long& c);

    void DecodeNum16(unsigned short& c);
    void DecodeNum32(unsigned long& c);
    void DecodeNum64(unsigned long long& c);


    void CopyNum16(unsigned short& c);
    void CopyNum32(unsigned long& c);
    void CopyNum64(unsigned long long& c);
    void CopyNum8(unsigned char& c);

    bool GetBitsByte();

    iUniStream& GetStreamData(USBits& obj);
    iUniStream& GetStreamData(iUniStream& Bbs);
    iUniStream& GetStreamData(oUniStream& Bbs);
    iUniStream& GetStreamData(USSizeType& Bbs);
    iUniStream& GetStreamData(unsigned char& cRef);
    iUniStream& GetStreamData(signed char& cRef);
    iUniStream& GetStreamData(unsigned short& cRef);
    iUniStream& GetStreamData(signed short& cRef);
    iUniStream& GetStreamData(unsigned long& cRef);
    iUniStream& GetStreamData(signed long& cRef);
    iUniStream& GetStreamData(unsigned long long& cRef);
    iUniStream& GetStreamData(signed long long& cRef);
    iUniStream& GetStreamData(unsigned& cRef);
    iUniStream& GetStreamData(signed& cRef);
    iUniStream& GetStreamData(char& cRef);
    iUniStream& GetStreamData(bool& cRef);
    iUniStream& GetStreamData(float& cRef);
    iUniStream& GetStreamData(double& cRef);
    iUniStream& GetStreamData(wchar_t& cRef);
    iUniStream& GetStreamData(char16_t& cRef);
    iUniStream& GetStreamData(char32_t& cRef);
    iUniStream& GetStreamData(const iUniInplace& cRef);
    iUniStream& GetStreamData(void*& cRef);

    std::vector<unsigned char>   m_buffObj;
    std::vector<unsigned char>*  m_buff;
    unsigned char   m_bits;
    unsigned char   m_bitsUsed;
    bool            m_lastOperationResult;
    bool            m_isDecodingMode;

    size_t          m_readIndex;
    size_t          m_endIndex;

	friend class oUniStream;
};

#include "iUniStreamSTL.hpp"

};

