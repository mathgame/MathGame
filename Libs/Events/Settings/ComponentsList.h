//////////////////////////
#include "../FirstEventComponent.h"
#include "../DummyEventComponent.h"
// DO NOT DELETE THIS AND DO NOT PUT EMPTY LINE, THIS IS CREATE COMPONENT SCRIPT INCLUDE MARKER
//


///////////////////////////////////////////////////////////////////////////
// Add include file and add new line with your component name in ther macro iterator
#undef CUSTOM_COMPONENTS_ITERATOR
#define CUSTOM_COMPONENTS_ITERATOR(CUSTOM_COMPONENT_MACRO)\
    CUSTOM_COMPONENT_MACRO(FirstEvent, foo)\
    CUSTOM_COMPONENT_MACRO(DummyEvent, foo)\
// DO NOT DELETE THIS AND DO NOT PUT EMPTY LINE, THIS IS CREATE COMPONENT SCRIPT REGISTER MARKER
//
