#pragma once
#include <cstdint>

#define US_LOG std::cout
#define US_ASSERT() while(1);

namespace MGTools {
	typedef uint8_t usUint8_t;
	typedef int8_t usSint8_t;
	typedef uint16_t usUint16_t;
	typedef int16_t usSint16_t;
	typedef uint32_t usUint32_t;
	typedef int32_t usSint32_t;
	typedef uint64_t usUint64_t;
	typedef int64_t usSint64_t;
};
