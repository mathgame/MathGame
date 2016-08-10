#ifndef _CRC_H
#define _CRC_H

#include <cstddef>
namespace CRC
{

#define Z_NULL  0
#define POLYNOMIAL 0xedb88320
#define POLY 0x1021

unsigned long crc32( unsigned crc, const char *buf, size_t len);
signed long crc32N( const void *buf, int len);
unsigned short crc16(const char *data_p, unsigned short length);

unsigned long long crc64(const char *dataPtr, int sz);
unsigned long long crc64(const char *dataPtr);
}
#endif
