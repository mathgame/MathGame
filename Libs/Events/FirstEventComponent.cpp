
// Put your includes above this line
///////////////////////////////////////////////////////////////////
/// !!! DO NOT INCLUDE ANY FILES AFTER THIS LINE !!!
#include "FirstEventComponent.h"
///////////////////////////////////////////////////////////////////////////
using namespace COMPONENT_FACTORY_NAMESPACE;
#include "System/push_warning_level.h"
#include "System/stop_unused_var_warning.h"
IMPLEMENT_COMPONENT_COMMON_METHODS(FIRSTEVENT_COMP_VALUES_ITERATOR_1470408262, FirstEvent, FACTORY_NAMESPACE_STRING)
#include "System/pop_warning_level.h"
/// !!! DO NOT INCLUDE ANY FILES HERE !!!
///////////////////////////////////////////////////////////////////////////
bool FirstEventComponent::Load()
{
    FIRSTEVENT_COMP_VALUES_ITERATOR_1470408262(COMP_IMPLEMENT_REQ_LOADER, COMP_IMPLEMENT_NOT_REQ_LOADER);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool FirstEventComponent::Load(MGTools::iUniStream& inputStream)
{
    COMP_IMPLEMENT_BIN_LOAD(FIRSTEVENT_COMP_VALUES_ITERATOR_1470408262, FirstEvent);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool FirstEventComponent::Serialize(pugi::xml_node& node) const
{
    FIRSTEVENT_COMP_VALUES_ITERATOR_1470408262(COMP_IMPLEMENT_REQ_WRITER, COMP_IMPLEMENT_NOT_REQ_WRITER);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool FirstEventComponent::Serialize(MGTools::oUniStream& outStream) const
{
    COMP_IMPLEMENT_BIN_SERIALIZE(FIRSTEVENT_COMP_VALUES_ITERATOR_1470408262, FirstEvent);
    return true;
}

///////////////////////////////////////////////////////////////////////////
FirstEventComponent::FirstEventComponent()
    : COMP_IMPLEMENT_CONSTRUCTOR_VALUES_INIT(FIRSTEVENT_COMP_VALUES_ITERATOR_1470408262)
{

}

///////////////////////////////////////////////////////////////////////////
FirstEventComponent::~FirstEventComponent()
{

}

///////////////////////////////////////////////////////////////////////////
MGTools::ComponentsResolveResult
FirstEventComponent::Resolve(const FirstEventComponent& c1, const FirstEventComponent& c2, const MGTools::MgrMergeInfo& mergeInfo)
{
    return MGTools::ComponentsResolveResult::NOT_IMPLEMENTED;
}

///////////////////////////////////////////////////////////////////////////
MGTools::IBaseComponentPtr
FirstEventComponent::Combine(const FirstEventComponent& c1, const FirstEventComponent& c2, const MGTools::MgrMergeInfo& mergeInfo)
{
    //FirstEventComponentPtr newCompPtr = FirstEventComponent::CreateNewInstance();

    return nullptr;
}
