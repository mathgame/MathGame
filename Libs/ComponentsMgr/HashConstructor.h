#ifndef HASHCONSTRUCTOR_H
#define HASHCONSTRUCTOR_H
#include <cstdint>
#include <vector>

namespace MGTools {
class HashConstructor
{
public:
    static uint64_t ConstructHash(const std::vector<uint64_t>& hashes);
    static uint64_t ConstructHash(const char* str);
    static uint64_t ConstructHash(uint64_t typeHash, uint32_t x, uint32_t y, uint32_t d);
    static uint64_t ConstructHash(uint64_t type_1_Hash, uint64_t type_2_Hash);
    static uint64_t ConstructHash(uint64_t typeHash, const char* fieldName, uint32_t fieldPos, bool isRequired);

private:
    HashConstructor();
};
};
#endif // HASHCONSTRUCTOR_H
