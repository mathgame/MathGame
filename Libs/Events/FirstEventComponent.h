/*
 * Author: Nikolay Nedelchev
 *
 * All rights reserved
 *
 */

#ifndef __COMP_FIRSTEVENT_1470408262_
#define __COMP_FIRSTEVENT_1470408262_

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
#define FIRSTEVENT_COMP_VALUES_ITERATOR_1470408262(REQUIRED, NOT_REQUIRED)       \
    /*  USAGE:                                                      */      \
    /*  NOT_REQUIRED(   int,                valueName            )  */      \
    /*  NOT_REQUIRED(   std::vector<int>,   intArray             )  */      \
    /*  REQUIRED(       std::string,        someString, private: )  */      \
    /*                                                              */      \
    NOT_REQUIRED(int, alabala)  \
    
// Describe component values above, do not leave empty lines and terminate your lines with line-continuation character'\'
///////////////////////////////////////////////////////////////////
///
class FirstEventComponent;
typedef std::shared_ptr<FirstEventComponent> FirstEventComponentPtr;

class FirstEventComponent : public MGTools::IBaseComponent
{
    MG_COMPONENT_COMMON_DECLARATIONS(FIRSTEVENT_COMP_VALUES_ITERATOR_1470408262, FirstEvent);

public:

protected:

private:

};

};

#endif // __COMP_FIRSTEVENT_1470408262_
