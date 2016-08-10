#include "ComponentsFactory.h"

///////////////////////////////////////////////////////////////////////////
using namespace COMPONENT_FACTORY_NAMESPACE;

CUSTOM_COMPONENTS_ITERATOR(IMPLEMENT_COMPONENT_ID_GETTERS);

const std::map<std::string, COMPONENT_FACTORY_NAMESPACE::EComponentId> COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::s_componentsNameToIdMap =
{
    CUSTOM_COMPONENTS_ITERATOR(ADD_COMPONENT_NAME_TO_ID_TO_MAP)
};

const std::map<COMPONENT_FACTORY_NAMESPACE::EComponentId, std::string> COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::s_componentsIdToNameMap =
{
    CUSTOM_COMPONENTS_ITERATOR(ADD_COMPONENT_ID_TO_NAME_TO_MAP)
};

///////////////////////////////////////////////////////////////////////////
bool COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::Init()
{
    return true;
}

///////////////////////////////////////////////////////////////////////////
MGTools::IBaseComponentPtr
COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::CreateComponent(const pugi::xml_node& inputData)
{
    std::string compTypeStr;
    if (false == MGTools::IBaseComponent::ReadType(inputData, compTypeStr))
    {
        return MGTools::IBaseComponentPtr();
    }

    auto iterator = s_componentsNameToIdMap.find( compTypeStr );
    if (iterator == s_componentsNameToIdMap.end())
    {
        return MGTools::IBaseComponentPtr(nullptr);
    }

    auto componentId = iterator->second;
    switch(componentId)
    {
        CUSTOM_COMPONENTS_ITERATOR(IMPLEMENT_COMPONENT_LOADER);

        default:
        {
        }
        break;
    }

    return MGTools::IBaseComponentPtr(nullptr);
}

MGTools::IBaseComponentPtr
COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::CreateComponent(MGTools::iUniStream& inputData)
{
    u_int32_t componentIntId;
    if (!(inputData >> componentIntId))
    {
        return MGTools::IBaseComponentPtr(nullptr);
    }
    EComponentId componentId = (EComponentId)componentIntId;

    switch(componentId)
    {
        CUSTOM_COMPONENTS_ITERATOR(IMPLEMENT_COMPONENT_LOADER);

        default:
        {
        }
        break;
    }

    return MGTools::IBaseComponentPtr(nullptr);
}

///////////////////////////////////////////////////////////////////////////
MGTools::ComponentsResolveResult
COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::Resolve(const MGTools::IBaseComponentPtr& c1, const MGTools::IBaseComponentPtr& c2, const MGTools::MgrMergeInfo& mergeInfo)
{
    if (c1->GetComponentId() != c2->GetComponentId())
    {
        return MGTools::ComponentsResolveResult::FAIL;
    }

    switch(COMPONENT_FACTORY_NAMESPACE::EComponentId(c1->GetComponentId()))
    {
        CUSTOM_COMPONENTS_ITERATOR(COMP_RESOLVER_SWITCH_REGISTER);
    default:
        break;
    }

    return MGTools::ComponentsResolveResult::USE_COMBINER;
}

///////////////////////////////////////////////////////////////////////////
MGTools::IBaseComponentPtr
COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::Combine(const MGTools::IBaseComponentPtr& c1, const MGTools::IBaseComponentPtr& c2, const MGTools::MgrMergeInfo& mergeInfo)
{
    if (c1->GetComponentId() != c2->GetComponentId())
    {
        return nullptr;
    }

    switch(COMPONENT_FACTORY_NAMESPACE::EComponentId(c1->GetComponentId()))
    {
        CUSTOM_COMPONENTS_ITERATOR(COMP_COMBINER_SWITCH_REGISTER);
    default:
        break;
    }

    return nullptr;
}

///////////////////////////////////////////////////////////////////////////
u_int64_t
COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::GetFactoryHash()
{
    static u_int64_t hash = 0;
    static bool hashReady = false;

    if (false == hashReady)
    {
        std::vector<u_int64_t> hashes;
        CUSTOM_COMPONENTS_ITERATOR(COMP_FACTORY_HASH_CALC);
        hashes.push_back(MGTools::HashConstructor::ConstructHash(FACTORY_NAMESPACE_STRING));
        hash = MGTools::HashConstructor::ConstructHash(hashes);
        hashReady = true;
    }

    return hash;
}
