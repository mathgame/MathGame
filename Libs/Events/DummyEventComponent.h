/*
 * Author: Nikolay Nedelchev
 *
 * All rights reserved
 *
 */

#ifndef __COMP_DUMMYEVENT_1470408268_
#define __COMP_DUMMYEVENT_1470408268_

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
#define DUMMYEVENT_COMP_VALUES_ITERATOR_1470408268(REQUIRED, NOT_REQUIRED)       \
    /*  USAGE:                                                      */      \
    /*  NOT_REQUIRED(   int,                valueName            )  */      \
    /*  NOT_REQUIRED(   std::vector<int>,   intArray             )  */      \
    /*  REQUIRED(       std::string,        someString, private: )  */      \
    /*                                                              */      \
    NOT_REQUIRED(int, marker)   \
    
// Describe component values above, do not leave empty lines and terminate your lines with line-continuation character'\'
///////////////////////////////////////////////////////////////////
///
class DummyEventComponent;
typedef std::shared_ptr<DummyEventComponent> DummyEventComponentPtr;

class DummyEventComponent : public MGTools::IBaseComponent
{
    MG_COMPONENT_COMMON_DECLARATIONS(DUMMYEVENT_COMP_VALUES_ITERATOR_1470408268, DummyEvent);

public:

protected:

private:

};

};

#endif // __COMP_DUMMYEVENT_1470408268_
