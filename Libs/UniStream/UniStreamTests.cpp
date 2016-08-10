#include "iUniStream.h"
#include "oUniStream.h" 
#include "UniStreamTestUtils.h"

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <cstring>

/*
bool TestNumbersPackUnpack()
{
	MGTools::iUniStream outStream;
	MGTools::fill_numbers(outStream);
	
	MGTools::iUniStream inStream(outStream);
	return MGTools::check_numbers(inStream);
}

bool TestMixedPackUnpack()
{
	MGTools::iUniStream outStream;

	int outI = -23;
	std::string outStr = "alabala";
	
	const unsigned int arrLen = 4;
	double dOutArr[arrLen][arrLen] =
	{ 	{ 0, 	1,	2,	3	},
		{ 4, 	5,	6,	7	},
		{ 8, 	9,	10,	11	},
		{ 12,	13,	15,	16	}
	};
	std::vector<std::pair<int, std::string>> vOutV;

	vOutV.push_back(std::pair<int, std::string>(8, "abc"));
	vOutV.push_back(std::pair<int, std::string>(9, "cde"));
	vOutV.push_back(std::pair<int, std::string>(10, "efg"));

	bool bOutBool = true;
	
	outStream << outI << outStr << dOutArr << vOutV << bOutBool;

    auto& buffer = outStream.GetBuffer();
	
	int inI;
	std::string inStr;
	double dInArr[arrLen][arrLen];
	std::vector<std::pair<int, std::string>> vInV;
	bool bInBool;

	MGTools::iUniStream inStream(buffer);
	
	inStream >> inI >> inStr >> dInArr >> vInV >> bInBool;
	
	bool bResults[5] = {false, false, true, false, false};
	
	if (outI == inI)
		bResults[0] = true;
	
	if (outStr == inStr)
		bResults[1] = true;	
	
	for (unsigned i=0; i<arrLen; ++i)
	{
		for (unsigned j=0; j<arrLen; ++j)
		{
			if (dOutArr[i][j] != dInArr[i][j])
			{
				bResults[2] = false;
				break;
			}
		}
	}

	if (vOutV == vInV)
		bResults[3] = true;
	
	if (bOutBool == bInBool)
		bResults[4] = true;
	
	if (bResults[0] && bResults[1] && bResults[2] && bResults[3] && bResults[4])
		return true;
	else
		return false;
		
	
}

bool TestIntImplicitCoversion()
{
	MGTools::iUniStream outStream;
	
	const unsigned int arrLen = 4;
	double outArr[arrLen] = { 3.14, 6.8, 2.3, 1024.1};
	
	outStream << outArr;
	
	MGTools::iUniStream inStream(outStream);
	int inArr[arrLen];
	
	inStream >> inArr;
	
	for (unsigned int i=0; i< arrLen; ++i)
	{
		if ((int)outArr[i] != inArr[i])
		{
			return false;
		}
	}

	return true;
}

bool TestClassStreaming()
{
	MGTools::iUniStream outStream;
	
	MGTools::StreamedClass outClass(1337, std::string("John"), MGTools::GetVectorOfNums());
	outStream << outClass;
	
	MGTools::iUniStream inStream(outStream.GetBuffer());
	MGTools::StreamedClass inClass;
	inStream >> inClass;
	
	return inClass == outClass;
}

bool TestStreamInWhileCycle()
{
	MGTools::iUniStream outStream;
	outStream << 5 << 4 << 3 << 2 << 1 << -5;
	
	MGTools::iUniStream inStream(outStream.GetBuffer());
	
	std::vector<int> inV;
	int element;
	
	while (inStream >> element)
		inV.push_back(element);
	
	return true;
}

bool TestNestedStreams()
{
    MGTools::iUniStream outMainStream;
    outMainStream.SetEncodingMode(true);
    MGTools::mainFill(outMainStream);

    MGTools::iUniStream inMainStream(outMainStream);
    
	return MGTools::checkMain(inMainStream);
}

bool TestDataEncoding()
{
	const unsigned int NUM_TEST_STREAMS = 4;
	const unsigned int NUM_TEST_VALUES = 8;
	
	
	int32_t outArr[NUM_TEST_STREAMS][NUM_TEST_VALUES] = {
		{ 3, 		4, 			5,			6,			9, 			3, 			9, 			14		}, // 8 ints (32 bytes)
		{ 230, 		129, 		65, 		-98, 		211, 		-199, 		231, 		75 		}, // 8 ints (32 bytes)
		{ 232230, 	1343429, 	23265, 		-3208, 		112232211,	-2323199, 	374376, 	7634 	}, // 8 ints (32 bytes)
		{ 6371280, 	24574226, 	32323615, 	-1443298, 	13282532, 	-23232389, 	3743764, 	734634 	}  // 8 ints (32 bytes)
	};
	
	int32_t inArr[NUM_TEST_STREAMS][NUM_TEST_VALUES];
	
	MGTools::iUniStream outEncStream[NUM_TEST_STREAMS];
	
	for (unsigned int i=0; i<NUM_TEST_STREAMS; ++i)
	{
		outEncStream[i].SetEncodingMode(true);
		for(unsigned int j=0; j<NUM_TEST_VALUES; ++j)
		{
			outEncStream[i] << outArr[i][j];
		}
	}
	
	for (unsigned int i=0; i<NUM_TEST_STREAMS; ++i)
	{
		MGTools::iUniStream inEncStream;
		inEncStream.SetBuffer(outEncStream[i].GetBuffer(), true);
		
		for(unsigned int j=0; j<NUM_TEST_VALUES; ++j)
		{
			inEncStream >> inArr[i][j];
		}
	}

	for (unsigned int i=0; i<NUM_TEST_STREAMS; ++i)
	{
		for(unsigned int j=0; j<NUM_TEST_VALUES; ++j)
		{
			if (outArr[i][j] != inArr[i][j])
				return false;
		}
	}

	return true;
}

bool PrintTestResults(std::string testName, bool result)
{
	if (result)
	{
		std::cout << "The test " <<  testName << " has completed successfully!" << std::endl;
	}
	else
	{
		std::cout << "The test " <<  testName <<  " has failed!" << std::endl;
	}
	
	return result;
}

#if 0
int main(int argc, char *argv[])
{
    if (!PrintTestResults("Mixed Pack Unpack", TestMixedPackUnpack())
	|| !PrintTestResults("Implicit Int Conversion", TestIntImplicitCoversion())
	|| !PrintTestResults("Class Streaming", TestClassStreaming())
	|| !PrintTestResults("Stream in while cycle", TestStreamInWhileCycle())
	|| !PrintTestResults("Test Data encoding", TestDataEncoding())
	|| !PrintTestResults("Nested streams", TestNestedStreams())
	|| !PrintTestResults("Numbers pack/unpack", TestNumbersPackUnpack())
	)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}
#endif
*/