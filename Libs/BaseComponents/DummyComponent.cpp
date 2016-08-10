
// Put your includes above this line
///////////////////////////////////////////////////////////////////
/// !!! DO NOT INCLUDE ANY FILES AFTER THIS LINE !!!
#include "DummyComponent.h"
///////////////////////////////////////////////////////////////////////////
using namespace COMPONENT_FACTORY_NAMESPACE;
#include "System/push_warning_level.h"
#include "System/stop_unused_var_warning.h"
IMPLEMENT_COMPONENT_COMMON_METHODS(DUMMY_COMP_VALUES_ITERATOR_1470405051, Dummy, FACTORY_NAMESPACE_STRING)
#include "System/pop_warning_level.h"
/// !!! DO NOT INCLUDE ANY FILES HERE !!!
///////////////////////////////////////////////////////////////////////////
bool DummyComponent::Load()
{
    DUMMY_COMP_VALUES_ITERATOR_1470405051(COMP_IMPLEMENT_REQ_LOADER, COMP_IMPLEMENT_NOT_REQ_LOADER);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool DummyComponent::Load(MGTools::iUniStream& inputStream)
{
    COMP_IMPLEMENT_BIN_LOAD(DUMMY_COMP_VALUES_ITERATOR_1470405051, Dummy);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool DummyComponent::Serialize(pugi::xml_node& node) const
{
    DUMMY_COMP_VALUES_ITERATOR_1470405051(COMP_IMPLEMENT_REQ_WRITER, COMP_IMPLEMENT_NOT_REQ_WRITER);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool DummyComponent::Serialize(MGTools::oUniStream& outStream) const
{
    COMP_IMPLEMENT_BIN_SERIALIZE(DUMMY_COMP_VALUES_ITERATOR_1470405051, Dummy);
    return true;
}

///////////////////////////////////////////////////////////////////////////
DummyComponent::DummyComponent()
    : COMP_IMPLEMENT_CONSTRUCTOR_VALUES_INIT(DUMMY_COMP_VALUES_ITERATOR_1470405051)
{

}

///////////////////////////////////////////////////////////////////////////
DummyComponent::~DummyComponent()
{

}

///////////////////////////////////////////////////////////////////////////
MGTools::ComponentsResolveResult
DummyComponent::Resolve(const DummyComponent& c1, const DummyComponent& c2, const MGTools::MgrMergeInfo& mergeInfo)
{
    return MGTools::ComponentsResolveResult::NOT_IMPLEMENTED;
}

///////////////////////////////////////////////////////////////////////////
MGTools::IBaseComponentPtr
DummyComponent::Combine(const DummyComponent& c1, const DummyComponent& c2, const MGTools::MgrMergeInfo& mergeInfo)
{
    //DummyComponentPtr newCompPtr = DummyComponent::CreateNewInstance();

    return nullptr;
}
