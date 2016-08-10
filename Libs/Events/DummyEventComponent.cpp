
// Put your includes above this line
///////////////////////////////////////////////////////////////////
/// !!! DO NOT INCLUDE ANY FILES AFTER THIS LINE !!!
#include "DummyEventComponent.h"
///////////////////////////////////////////////////////////////////////////
using namespace COMPONENT_FACTORY_NAMESPACE;
#include "System/push_warning_level.h"
#include "System/stop_unused_var_warning.h"
IMPLEMENT_COMPONENT_COMMON_METHODS(DUMMYEVENT_COMP_VALUES_ITERATOR_1470408268, DummyEvent, FACTORY_NAMESPACE_STRING)
#include "System/pop_warning_level.h"
/// !!! DO NOT INCLUDE ANY FILES HERE !!!
///////////////////////////////////////////////////////////////////////////
bool DummyEventComponent::Load()
{
    DUMMYEVENT_COMP_VALUES_ITERATOR_1470408268(COMP_IMPLEMENT_REQ_LOADER, COMP_IMPLEMENT_NOT_REQ_LOADER);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool DummyEventComponent::Load(MGTools::iUniStream& inputStream)
{
    COMP_IMPLEMENT_BIN_LOAD(DUMMYEVENT_COMP_VALUES_ITERATOR_1470408268, DummyEvent);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool DummyEventComponent::Serialize(pugi::xml_node& node) const
{
    DUMMYEVENT_COMP_VALUES_ITERATOR_1470408268(COMP_IMPLEMENT_REQ_WRITER, COMP_IMPLEMENT_NOT_REQ_WRITER);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool DummyEventComponent::Serialize(MGTools::oUniStream& outStream) const
{
    COMP_IMPLEMENT_BIN_SERIALIZE(DUMMYEVENT_COMP_VALUES_ITERATOR_1470408268, DummyEvent);
    return true;
}

///////////////////////////////////////////////////////////////////////////
DummyEventComponent::DummyEventComponent()
    : COMP_IMPLEMENT_CONSTRUCTOR_VALUES_INIT(DUMMYEVENT_COMP_VALUES_ITERATOR_1470408268)
{

}

///////////////////////////////////////////////////////////////////////////
DummyEventComponent::~DummyEventComponent()
{

}

///////////////////////////////////////////////////////////////////////////
MGTools::ComponentsResolveResult
DummyEventComponent::Resolve(const DummyEventComponent& c1, const DummyEventComponent& c2, const MGTools::MgrMergeInfo& mergeInfo)
{
    return MGTools::ComponentsResolveResult::NOT_IMPLEMENTED;
}

///////////////////////////////////////////////////////////////////////////
MGTools::IBaseComponentPtr
DummyEventComponent::Combine(const DummyEventComponent& c1, const DummyEventComponent& c2, const MGTools::MgrMergeInfo& mergeInfo)
{
    //DummyEventComponentPtr newCompPtr = DummyEventComponent::CreateNewInstance();

    return nullptr;
}
