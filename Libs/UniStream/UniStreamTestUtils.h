#pragma once

#include <vector>
#include <string>
#include <cstring>


/*

namespace MGTools
{

void fill_numbers(MGTools::iUniStream& bs)
{
    for (int t = 0; t < 256; t++)
    {
	  unsigned char i = (unsigned char)t;
	  char c_char = i; bs << c_char;
	  unsigned char c_unsigned_char = i; bs << c_unsigned_char;
	  signed char c_signed_char = reinterpret_cast<signed char&>(i); bs << c_signed_char;

	  unsigned short c_unsigned_short_1 = i; bs << c_unsigned_short_1;
	  unsigned short c_unsigned_short_2 = 256 + i; bs << c_unsigned_short_2;
	  unsigned short c_unsigned_short_3 = 65535 - i; bs << c_unsigned_short_3;

	  signed short c_signed_short_1 = reinterpret_cast<signed short&>(c_unsigned_short_1); bs << c_signed_short_1;
	  signed short c_signed_short_2 = reinterpret_cast<signed short&>(c_unsigned_short_2); bs << c_signed_short_2;
	  signed short c_signed_short_3 = reinterpret_cast<signed short&>(c_unsigned_short_3); bs << c_signed_short_3;

	  unsigned long c_unsigned_long_1 = i; bs << c_unsigned_long_1;
	  unsigned long c_unsigned_long_2 = 256 + i; bs << c_unsigned_long_2;
	  unsigned long c_unsigned_long_3 = 65535 + i; bs << c_unsigned_long_3;
	  unsigned long c_unsigned_long_4 = 0;
	  c_unsigned_long_4 = ~c_unsigned_long_4;
	  c_unsigned_long_4 -= i;

	  bs << c_unsigned_long_4;

	  signed long c_signed_long_1 = reinterpret_cast<signed long&>(c_unsigned_long_1); bs << c_signed_long_1;
	  signed long c_signed_long_2 = reinterpret_cast<signed long&>(c_unsigned_long_2); bs << c_signed_long_2;
	  signed long c_signed_long_3 = reinterpret_cast<signed long&>(c_unsigned_long_3); bs << c_signed_long_3;
	  signed long c_signed_long_4 = reinterpret_cast<signed long&>(c_unsigned_long_4); bs << c_signed_long_4;

	  unsigned long long c_unsigned_long_long_1 = i; bs << c_unsigned_long_long_1;
	  unsigned long long c_unsigned_long_long_2 = 256 + i; bs << c_unsigned_long_long_2;
	  unsigned long long c_unsigned_long_long_3 = 65535 + i; bs << c_unsigned_long_long_3;
	  unsigned long long c_unsigned_long_long_4 = (1ULL << 32) + i; bs << c_unsigned_long_long_4;
	  unsigned long long c_unsigned_long_long_5 = ~0 - i; bs << c_unsigned_long_long_5;

	  signed long long c_signed_long_long_1 = reinterpret_cast<signed long long&>(c_unsigned_long_long_1); bs << c_signed_long_long_1;
	  signed long long c_signed_long_long_2 = reinterpret_cast<signed long long&>(c_unsigned_long_long_2); bs << c_signed_long_long_2;
	  signed long long c_signed_long_long_3 = reinterpret_cast<signed long long&>(c_unsigned_long_long_3); bs << c_signed_long_long_3;
	  signed long long c_signed_long_long_4 = reinterpret_cast<signed long long&>(c_unsigned_long_long_4); bs << c_signed_long_long_4;
	  signed long long c_signed_long_long_5 = reinterpret_cast<signed long long&>(c_unsigned_long_long_5); bs << c_signed_long_long_5;

	  unsigned c_unsigned_1 = i; bs << c_unsigned_1;
	  unsigned c_unsigned_2 = 256 + i; bs << c_unsigned_2;
	  unsigned c_unsigned_3 = 65535 + i; bs << c_unsigned_3;
	  unsigned c_unsigned_4 = ~0UL - i; bs << c_unsigned_4;

	  signed c_signed_1 = reinterpret_cast<signed&>(c_unsigned_1); bs << c_signed_1;
	  signed c_signed_2 = reinterpret_cast<signed&>(c_unsigned_2); bs << c_signed_2;
	  signed c_signed_3 = reinterpret_cast<signed&>(c_unsigned_3); bs << c_signed_3;
	  signed c_signed_4 = reinterpret_cast<signed&>(c_unsigned_4); bs << c_signed_4;
    }
}

bool check_numbers(MGTools::iUniStream& bs)
{
    for (int t = 0; t < 256; t++)
    {
		unsigned char i = (unsigned char)t;
		char c_char = i, c_char2; bs >> c_char2;
		unsigned char c_unsigned_char = i, c_unsigned_char2; bs >> c_unsigned_char2;
		signed char c_signed_char = reinterpret_cast<signed char&>(i), c_signed_char2; bs >> c_signed_char2;

		if (c_char != c_char2)
		{
			return false;
		}
		if (c_unsigned_char != c_unsigned_char2)
		{
			return false;
		}
		if (c_signed_char != c_signed_char2)
		{
			return false;
		}

		unsigned short c_unsigned_short_1 = i;
		unsigned short c_unsigned_short_2 = 256 + i;
		unsigned short c_unsigned_short_3 = 65535 - i;

		unsigned short c_unsigned_short_12; bs >> c_unsigned_short_12;
		unsigned short c_unsigned_short_22; bs >> c_unsigned_short_22;
		unsigned short c_unsigned_short_32; bs >> c_unsigned_short_32;

		if (c_unsigned_short_12 != c_unsigned_short_1)
		{
			return false;
		}

		if (c_unsigned_short_22 != c_unsigned_short_2)
		{
			return false;
		}

		if (c_unsigned_short_32 != c_unsigned_short_3)
		{
			return false;
		}

		signed short c_signed_short_1 = reinterpret_cast<signed short&>(c_unsigned_short_1);
		signed short c_signed_short_2 = reinterpret_cast<signed short&>(c_unsigned_short_2);
		signed short c_signed_short_3 = reinterpret_cast<signed short&>(c_unsigned_short_3);

		signed short c_signed_short_12; bs >> c_signed_short_12;
		signed short c_signed_short_22; bs >> c_signed_short_22;
		signed short c_signed_short_32; bs >> c_signed_short_32;

		if (c_signed_short_12 != c_signed_short_1)
		{
			return false;
		}

		if (c_signed_short_22 != c_signed_short_2)
		{
			return false;
		}

		if (c_signed_short_32 != c_signed_short_3)
		{
			return false;
		}

		unsigned long c_unsigned_long_1 = i;
		unsigned long c_unsigned_long_2 = 256 + i;
		unsigned long c_unsigned_long_3 = 65535 + i;
		unsigned long c_unsigned_long_4 = ~0 - (unsigned long)i;

		unsigned long c_unsigned_long_12; bs >> c_unsigned_long_12;
		unsigned long c_unsigned_long_22; bs >> c_unsigned_long_22;
		unsigned long c_unsigned_long_32; bs >> c_unsigned_long_32;
		unsigned long c_unsigned_long_42;
		bs >> c_unsigned_long_42;

		if (c_unsigned_long_12 != c_unsigned_long_1)
		{
			return false;
		}

		if (c_unsigned_long_22 != c_unsigned_long_2)
		{
			return false;
		}

		if (c_unsigned_long_32 != c_unsigned_long_3)
		{
			return false;
		}

		if (c_unsigned_long_42 != c_unsigned_long_4)
		{
			return false;
		}

		signed long c_signed_long_1 = reinterpret_cast<signed long&>(c_unsigned_long_1);
		signed long c_signed_long_2 = reinterpret_cast<signed long&>(c_unsigned_long_2);
		signed long c_signed_long_3 = reinterpret_cast<signed long&>(c_unsigned_long_3);
		signed long c_signed_long_4 = reinterpret_cast<signed long&>(c_unsigned_long_4);

		signed long c_signed_long_12; bs >> c_signed_long_12;
		signed long c_signed_long_22; bs >> c_signed_long_22;
		signed long c_signed_long_32; bs >> c_signed_long_32;
		signed long c_signed_long_42; bs >> c_signed_long_42;

		if (c_signed_long_12 != c_signed_long_1)
		{
			return false;
		}

		if (c_signed_long_22 != c_signed_long_2)
		{
			return false;
		}

		if (c_signed_long_32 != c_signed_long_3)
		{
			return false;
		}

		if (c_signed_long_42 != c_signed_long_4)
		{
			return false;
		}

		unsigned long long c_unsigned_long_long_1 = i;
		unsigned long long c_unsigned_long_long_2 = 256 + i;
		unsigned long long c_unsigned_long_long_3 = 65535 + i;
		unsigned long long c_unsigned_long_long_4 = (1ULL << 32) + i;
		unsigned long long c_unsigned_long_long_5 = ~0ULL - i;

		unsigned long long c_unsigned_long_long_12; bs >> c_unsigned_long_long_12;
		unsigned long long c_unsigned_long_long_22; bs >> c_unsigned_long_long_22;
		unsigned long long c_unsigned_long_long_32; bs >> c_unsigned_long_long_32;
		unsigned long long c_unsigned_long_long_42; bs >> c_unsigned_long_long_42;
		unsigned long long c_unsigned_long_long_52; bs >> c_unsigned_long_long_52;

		if (c_unsigned_long_long_12 != c_unsigned_long_long_1)
		{
			return false;
		}

		if (c_unsigned_long_long_22 != c_unsigned_long_long_2)
		{
			return false;
		}

		if (c_unsigned_long_long_32 != c_unsigned_long_long_3)
		{
			return false;
		}

		if (c_unsigned_long_long_42 != c_unsigned_long_long_4)
		{
			return false;
		}

		if (c_unsigned_long_long_52 != c_unsigned_long_long_5)
		{
			return false;
		}

		signed long long c_signed_long_long_1 = reinterpret_cast<signed long long&>(c_unsigned_long_long_1);
		signed long long c_signed_long_long_2 = reinterpret_cast<signed long long&>(c_unsigned_long_long_2);
		signed long long c_signed_long_long_3 = reinterpret_cast<signed long long&>(c_unsigned_long_long_3);
		signed long long c_signed_long_long_4 = reinterpret_cast<signed long long&>(c_unsigned_long_long_4);
		signed long long c_signed_long_long_5 = reinterpret_cast<signed long long&>(c_unsigned_long_long_5);

		signed long long c_signed_long_long_12; bs >> c_signed_long_long_12;
		signed long long c_signed_long_long_22; bs >> c_signed_long_long_22;
		signed long long c_signed_long_long_32; bs >> c_signed_long_long_32;
		signed long long c_signed_long_long_42; bs >> c_signed_long_long_42;
		signed long long c_signed_long_long_52; bs >> c_signed_long_long_52;

		if (c_signed_long_long_12 != c_signed_long_long_1)
		{
			return false;
		}

		if (c_signed_long_long_22 != c_signed_long_long_2)
		{
			return false;
		}

		if (c_signed_long_long_32 != c_signed_long_long_3)
		{
			return false;
		}

		if (c_signed_long_long_42 != c_signed_long_long_4)
		{
			return false;
		}

		if (c_signed_long_long_52 != c_signed_long_long_5)
		{
			return false;
		}

		unsigned c_unsigned_1 = i;
		unsigned c_unsigned_2 = 256 + i;
		unsigned c_unsigned_3 = 65535 + i;
		unsigned c_unsigned_4 = ~0UL - i;

		unsigned c_unsigned_12; bs >> c_unsigned_12;
		unsigned c_unsigned_22; bs >> c_unsigned_22;
		unsigned c_unsigned_32; bs >> c_unsigned_32;
		unsigned c_unsigned_42; bs >> c_unsigned_42;

		if (c_unsigned_12 !=c_unsigned_1 )
		{
			return false;
		}

		if (c_unsigned_22 !=c_unsigned_2 )
		{
			return false;
		}

		if (c_unsigned_32 !=c_unsigned_3 )
		{
			return false;
		}

		if (c_unsigned_42 !=c_unsigned_4 )
		{
			return false;
		}

		signed c_signed_1 = reinterpret_cast<signed&>(c_unsigned_1);
		signed c_signed_2 = reinterpret_cast<signed&>(c_unsigned_2);
		signed c_signed_3 = reinterpret_cast<signed&>(c_unsigned_3);
		signed c_signed_4 = reinterpret_cast<signed&>(c_unsigned_4);

		signed c_signed_12; bs >> c_signed_12;
		signed c_signed_22; bs >> c_signed_22;
		signed c_signed_32; bs >> c_signed_32;
		signed c_signed_42; bs >> c_signed_42;

		if (c_signed_12 != c_signed_1)
		{
			return false;
		}

		if (c_signed_22 != c_signed_2)
		{
			return false;
		}

		if (c_signed_32 != c_signed_3)
		{
			return false;
		}

		if (c_signed_42 != c_signed_4)
		{
			return false;
		}
	}

	return true;
}

void fill_1(MGTools::iUniStream& bs)
{
    MGTools::USBits b = MGTools::USBits(255, 1);

	for (int i = 1; i < 9; i++)
	{
		for (int j = 0; j < (1 << i); j++)
		{
            b = MGTools::USBits(j, i);
			bs << b;
		}
		for (int z = 0; z < i; z++)
		{
			bs << (unsigned char)z;
		}
	}

	oUniStream bsInplace;
	bsInplace.SetEncodingMode(bs.IsEncodingMode());
	bs >> oUniInplace(bsInplace);

	fill_numbers(bsInplace);
	bs << bsInplace;
}

bool check_1(MGTools::iUniStream& bs)
{
    MGTools::USBits b = MGTools::USBits(255, 1);

	for (int i = 1; i < 9; i++)
	{
		for (int j = 0; j < (1 << i); j++)
		{
            b = MGTools::USBits(0, i);
			bs >> b;
			if (b.bits != j)
			{
				return false;
			}
		}
		for (int z = 0; z < i; z++)
		{
			unsigned char c = 0;
			bs >> c;
			if (c != z)
			{
				return false;
			}
		}
	}

	iUniStream bsInplace;
	bs >> iUniInplace(bsInplace);

	return check_numbers(bsInplace);
}

void fill_2(MGTools::iUniStream& bs)
{
    MGTools::USBits b = MGTools::USBits(255, 1);

	for (int i = 1; i < 9; i++)
	{
		for (int z = 0; z < i; z++)
		{
			bs << (unsigned char)z;
		}
		for (int j = 0; j < (1 << i); j++)
		{
            b = MGTools::USBits(j, i);
			bs << b;
		}
	}
}

bool check_2(MGTools::iUniStream& bs)
{
    MGTools::USBits b = MGTools::USBits(255, 1);

	for (int i = 1; i < 9; i++)
	{
		for (int z = 0; z < i; z++)
		{
			unsigned char c = 0;
			bs >> c;
			if (c != z)
			{
				return false;
			}
		}
		for (int j = 0; j < (1 << i); j++)
		{
            b = MGTools::USBits(0, i);
			bs >> b;
			if (b.bits != j)
			{
				return false;
			}
		}
	}

	return true;
}

void fillMiddle(MGTools::iUniStream& bs)
{
    MGTools::iUniStream bs1, bs2;
	bs1.SetEncodingMode(bs.IsEncodingMode());
	bs2.SetEncodingMode(bs.IsEncodingMode());

	fill_1(bs1);
	bs << bs1;

	bs >> oUniInplace(bs2);
	fill_2(bs2);
	bs << bs2;
	fill_1(bs);
}

bool checkMiddle(MGTools::iUniStream& bs)
{
    MGTools::iUniStream bs1, bs2;

	bs1.SetDecodingMode(bs.IsDecodingMode());
	bs2.SetDecodingMode(bs.IsDecodingMode());

	bs >> iUniInplace(bs1);
	if (!check_1(bs1))
	{
		return false;
	}

	bs >> bs2;
	if (!check_2(bs2))
	{
		return false;
	}

	if (!check_1(bs))
	{
		return false;
	}

	return true;
}

void mainFill(MGTools::iUniStream& bs)
{
	fill_1(bs);
    MGTools::iUniStream bs1, bs2;

	bs1.SetEncodingMode(bs.IsEncodingMode());
	bs2.SetEncodingMode(bs.IsEncodingMode());

	fillMiddle(bs1);
	bs << bs1;
	fillMiddle(bs2);
	bs << bs2;
}

bool checkMain(MGTools::iUniStream& bs)
{
    MGTools::iUniStream bs1, bs2;

	bs1.SetDecodingMode(bs.IsDecodingMode());
	bs2.SetDecodingMode(bs.IsDecodingMode());

	if (!check_1(bs))
	{
		return false;
	}

	bs >> bs1;
	if (!checkMiddle(bs1))
	{
		return false;
	}

	bs >> bs2;
	if (!checkMiddle(bs2))
	{
		return false;
	}

	return true;
}

class StreamedClass
{
public:
	StreamedClass() {}
	StreamedClass(uint32_t i, std::string name, std::vector<double> doubles)
	: Int(i)
	, Name(name)
	, vDoubles(doubles)
	{
	}
	
    friend MGTools::iUniStream& operator << (MGTools::iUniStream& out, const StreamedClass& myClass)
	{
		out << myClass.Int << myClass.Name << myClass.vDoubles;
		return out;
	}
	
    friend MGTools::iUniStream& operator >> (MGTools::iUniStream& in, StreamedClass& myClass)
	{
		in >> myClass.Int >> myClass.Name >> myClass.vDoubles;
		return in;
	}
	
	bool operator == (const StreamedClass& rhs)
	{
		if (this->Int == rhs.Int && 
			this->Name == rhs.Name &&
			this->vDoubles == rhs.vDoubles)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	uint32_t Int;
	std::string Name;
	std::vector<double> vDoubles;
};

std::vector<double> GetVectorOfNums()
{
	std::vector<double> outV;
	outV.push_back(-3.24);
	outV.push_back(12.2784);
	outV.push_back(-97.23454114);
	outV.push_back(0.12341);
	outV.push_back(-0.04964);
	
	return outV;
}

}
*/
