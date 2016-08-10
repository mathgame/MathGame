#include "IBaseComponent.h"
#include "../Tools/Crc.h"
using namespace MGTools;


///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const unsigned long long& notUsed, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = CRC::crc64("#NDN#_uint64");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const signed long long& notUsed, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = CRC::crc64("#NDN#_int64");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const unsigned long& notUsed, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = CRC::crc64("#NDN#_uint32");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const signed long& notUsed, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = CRC::crc64("#NDN#_int32");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const unsigned short& notUsed, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = CRC::crc64("#NDN#_uint16");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const signed short& notUsed, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = CRC::crc64("#NDN#_int16");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const unsigned char& notUsed, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = CRC::crc64("#NDN#_uint8");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const signed char& notUsed, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = CRC::crc64("#NDN#_int8");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const unsigned& notUsed, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = CRC::crc64("#NDN#_uint");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const signed& notUsed, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = CRC::crc64("#NDN#_int");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const char& notUsed, u_int32_t x, u_int32_t y, u_int32_t d)
{
    // 'unsigned char' and 'char' are two different C types.
    // 'char' is not guaranteed to have only 8 bits.
    u_int64_t typeHash = CRC::crc64("#NDN#_char");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const float& notUsed, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = CRC::crc64("#NDN#_float");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const double& notUsed, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = CRC::crc64("#NDN#_double");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const std::string& notUsed, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = CRC::crc64("#NDN#_std::string");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const bool& notUsed, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = CRC::crc64("#NDN#_bool");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}
