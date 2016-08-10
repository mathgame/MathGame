#include "HashConstructor.h"
#include "../Tools/Crc.h"

using namespace MGTools;

///////////////////////////////////////////////////////////////////////////
uint64_t HashConstructor::ConstructHash(uint64_t typeHash, uint32_t x, uint32_t y, uint32_t d)
{
    char buff[8 + 4 + 4 + 4];

    int buffI = 0;

    for (int i = 0; i < 8; i++)
    {
        buff[buffI++] = (char)( (typeHash >> (i * 8)) & 255ULL );
    }

    for (int i = 0; i < 4; i++)
    {
        buff[buffI++] = (char)( (x >> (i * 8)) & 255UL );
    }
    for (int i = 0; i < 4; i++)
    {
        buff[buffI++] = (char)( (y >> (i * 8)) & 255UL );
    }
    for (int i = 0; i < 4; i++)
    {
        buff[buffI++] = (char)( (d >> (i * 8)) & 255UL );
    }

    return CRC::crc64(buff, buffI);
}

///////////////////////////////////////////////////////////////////////////
uint64_t HashConstructor::ConstructHash(uint64_t type_1_Hash, uint64_t type_2_Hash)
{
    char buff[8 + 8];

    int buffI = 0;

    for (int i = 0; i < 8; i++)
    {
        buff[buffI++] = (char)( (type_1_Hash >> (i * 8)) & 255ULL );
    }
    for (int i = 0; i < 8; i++)
    {
        buff[buffI++] = (char)( (type_2_Hash >> (i * 8)) & 255ULL );
    }

    return CRC::crc64(buff, buffI);
}

///////////////////////////////////////////////////////////////////////////
uint64_t HashConstructor::ConstructHash(uint64_t typeHash, const char* fieldName, uint32_t fieldPos, bool isRequired)
{
    char buff[8 + 8 + 4 + 1];
    uint64_t nameHash = CRC::crc64(fieldName);

    int buffI = 0;
    for (int i = 0; i < 8; i++)
    {
        buff[buffI++] = (char)( (typeHash >> (i * 8)) & 255ULL );
    }
    for (int i = 0; i < 8; i++)
    {
        buff[buffI++] = (char)( (nameHash >> (i * 8)) & 255ULL );
    }
    for (int i = 0; i < 4; i++)
    {
        buff[buffI++] = (char)( (fieldPos >> (i * 8)) & 255UL );
    }

    buff[buffI++] = isRequired ? 'T' : 'F';

    return CRC::crc64(buff, buffI);
}

///////////////////////////////////////////////////////////////////////////
uint64_t HashConstructor::ConstructHash(const std::vector<uint64_t>& hashes)
{
    unsigned int sz = hashes.size() * sizeof(hashes[0]);
    uint64_t hash = CRC::crc64((char*)(&(hashes[0])), sz);
    return hash;
}

///////////////////////////////////////////////////////////////////////////
uint64_t HashConstructor::ConstructHash(const char* str)
{
    uint64_t hash = CRC::crc64(str);
    return hash;
}
