/*
 * Author: Nikolay Nedelchev
 *
 * All rights reserved
 *
 */

#ifndef __COMP_DUMMY_1470405051_
#define __COMP_DUMMY_1470405051_

#include <string>

// Put your includes above this line
///////////////////////////////////////////////////////////////////
/// !!! DO NOT INCLUDE ANY FILES AFTER THIS LINE !!!
#include "Settings/Defines.h"
#include "Settings/Includes.h"
/// !!! DO NOT INCLUDE ANY FILES HERE !!!
namespace COMPONENT_FACTORY_NAMESPACE {
// Put your typedefs here:


///////////////////////////////////////////////////////////////////
#define DUMMY_COMP_VALUES_ITERATOR_1470405051(REQUIRED, NOT_REQUIRED)       \
    /*  USAGE:                                                      */      \
    /*  NOT_REQUIRED(   int,                valueName            )  */      \
    /*  NOT_REQUIRED(   std::vector<int>,   intArray             )  */      \
    /*  REQUIRED(       std::string,        someString, private: )  */      \
    /*                                                              */      \

    
// Describe component values above, do not leave empty lines and terminate your lines with line-continuation character'\'
///////////////////////////////////////////////////////////////////
///
class DummyComponent;
typedef std::shared_ptr<DummyComponent> DummyComponentPtr;

class DummyComponent : public MGTools::IBaseComponent
{
    MG_COMPONENT_COMMON_DECLARATIONS(DUMMY_COMP_VALUES_ITERATOR_1470405051, Dummy);

public:

protected:

private:

};

};

#endif // __COMP_DUMMY_1470405051_
