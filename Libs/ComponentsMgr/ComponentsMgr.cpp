#include "ComponentsMgr.h"
#include "IBaseComponent.h"

#include "../pugixml/pugixml.hpp"
//#include "../MGValidate.h"

#include <memory>

#include "../BaseComponents/System/ComponentsFactory.h"

using namespace MGTools;

const std::string& ComponentMgr::s_strXmlAttrName = "name";
const std::string& ComponentMgr::s_strXmlNodeCompMgr = "compmgr";
const std::string& ComponentMgr::s_strXmlNodeInclude = "include";

const std::string& ComponentMgr::s_strXmlAttrFileName = "filename";
const std::string& ComponentMgr::s_strXmlAttrTagName = "tagname";
const std::string& ComponentMgr::s_strXmlAttrSegment = "segment";

#define exception int

///////////////////////////////////////////////////////////////////////////
ComponentMgr::ComponentMgr()
    : m_name("")
    , m_components(ComponentsContainer())
    , m_factoryHash(0ul)
{

}

///////////////////////////////////////////////////////////////////////////
bool ComponentMgr::IsManager(const pugi::xml_node& xmlNode)
{
    std::string name = xmlNode.name();
    return (s_strXmlNodeCompMgr == name);
}

///////////////////////////////////////////////////////////////////////////
ComponentMgrPtr ComponentMgr::Merge(ComponentMgrPtr mgr1, ComponentMgrPtr mgr2, const std::string& managerName, const MGTools::MgrMergeInfo& mergeInfo)
{
    if (mgr1->GetFactoryHash() != mgr2->GetFactoryHash())
    {
        COMP_LOG << "Merging managers from different factories : " << mgr1->GetName() << ", " << mgr2->GetName();
        COMP_ASSERT("Merging managers from different factories");

        return nullptr;
    }

    ComponentsContainer c;
    ComponentsContainer& c1 = mgr1->m_components;
    ComponentsContainer& c2 = mgr2->m_components;

    // Insert all components that exist only in c1
    for (const auto& p : c1)
    {
        if( c2.find(p.first) == c2.end())
        {
            std::pair<IComponentId, IBaseComponentPtr> pairCopy;
            pairCopy.first = p.first;
            pairCopy.second = p.second->CreateCopy();
            c.insert(pairCopy);
        }
    }
    // Insert all components that exist only in c2
    for (const auto& p : c2)
    {
        if( c1.find(p.first) == c1.end())
        {
            std::pair<IComponentId, IBaseComponentPtr> pairCopy;
            pairCopy.first = p.first;
            pairCopy.second = p.second->CreateCopy();
            c.insert(pairCopy);
        }
    }

    // Merge only conflicted components ( common components for both containers c1 and c2)
    for (const auto& p : c1)
    {
        auto compIterator = c2.find(p.first);
        if (compIterator == c2.end())
        {
            continue;
        }

        const MGTools::IBaseComponentPtr& comp1 = p.second;
        const MGTools::IBaseComponentPtr& comp2 = compIterator->second;
        IComponentId comp1_ID = p.first;
        IComponentId comp2_ID = compIterator->first;

        // Resolve force modes
        switch (mergeInfo.m_type)
        {
        case MgrMergeType::ASSERT_IF_CONFLICT:
        {
            COMP_LOG << "Resolving conflict is not allowed  fail : " << comp1->GetComponentName() << ", " << comp2->GetComponentName();
            COMP_ASSERT("Resolving conflict is not allowed  fail");
            return nullptr;
        }
        break;
        case MgrMergeType::FORCE_FIRST_COMP:
        {
            c[comp1_ID] = comp1->CreateCopy();
        }
        break;
        case MgrMergeType::FORCE_SECOND_COMP:
        {
            c[comp2_ID] = comp2->CreateCopy();
        }
        break;
        default:break;
        }

        auto result = mgr1->m_resolver(comp1, comp2, mergeInfo);

        // Check if combine is needed (create new component instead of the two old components)
        if (ComponentsResolveResult::USE_COMBINER == result)
        {
            auto newCompPtr = mgr1->m_combiner(comp1, comp2, mergeInfo);
            if (nullptr == newCompPtr)
            {
                COMP_LOG << "Combining fail : " << comp1->GetComponentName() << ", " << comp2->GetComponentName();
                return nullptr;
            }
            c[newCompPtr->GetComponentId()] = newCompPtr;
        }
        else
        {
            ProcessManualResolveResult(c, comp1, comp2, result, mergeInfo.m_type);
        }
    }
    auto ptr = std::make_shared< MGTools::ComponentMgr >();
    ptr->m_resolver = mgr1->m_resolver;
    ptr->m_combiner = mgr1->m_combiner;
    ptr->m_factoryHash = mgr1->m_factoryHash;
    ptr->m_name = managerName;
    ptr->m_components = c;

    return ptr;
}

///////////////////////////////////////////////////////////////////////////
bool ComponentMgr::ProcessManualResolveResult(ComponentsContainer& container, const MGTools::IBaseComponentPtr& comp1, const MGTools::IBaseComponentPtr comp2, ComponentsResolveResult resolverResult, MgrMergeType mergeType)
{
    IComponentId comp1_ID = comp1->GetComponentId();
    IComponentId comp2_ID = comp2->GetComponentId();

    if (comp1_ID != comp2_ID)
    {
        COMP_LOG << "Different components merging fail : " << comp1->GetComponentName() << ", " << comp2->GetComponentName();
        COMP_ASSERT("Different components merging fail");
        return false;
    }

    switch (resolverResult) {
    case ComponentsResolveResult::FAIL:
    {
        COMP_LOG << "Resolving fail : " << comp1->GetComponentName() << ", " << comp2->GetComponentName();
        COMP_ASSERT("Resolving fail");

        return false;
    }
    case ComponentsResolveResult::NO_ONE:
        break;
    case ComponentsResolveResult::TAKE_FIRST:
    {
        container[comp1_ID] = comp1->CreateCopy();
    }
    break;
    case ComponentsResolveResult::TAKE_SECOND:
    {
        container[comp2_ID] = comp2->CreateCopy();
    }
    break;
    case ComponentsResolveResult::NOT_IMPLEMENTED:
    {
        switch (mergeType) {
        case MgrMergeType::USE_FIRST_IF_NOT_IMPLEMENTED:
        {
            container[comp1_ID] = comp1->CreateCopy();
        }
        break;
        case MgrMergeType::USE_SECOND_IF_NOT_IMPLEMENTED:
        {
            container[comp2_ID] = comp2->CreateCopy();
        }
        break;
        default:
            COMP_LOG << "Not implemented resolving fail : " << comp1->GetComponentName() << ", " << comp2->GetComponentName();
            COMP_ASSERT("Not implemented resolving fail");
            return false;
        }
    }
    break;
    default:
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
ComponentMgrPtr ComponentMgr::CreateFromFile (const std::string& fileName, const std::string& mgrName)
{
    return CreateFromFile<BaseComponents::ComponentsFactory>(fileName, mgrName);
}

///////////////////////////////////////////////////////////////////////////
bool ComponentMgr::Serialize(pugi::xml_node& node) const
{
    node.set_name(s_strXmlNodeCompMgr.c_str());
    pugi::xml_attribute mgrNameAttr = node.append_attribute(s_strXmlAttrName.c_str());
    mgrNameAttr.set_value(GetName().c_str());

    for (const auto& comp : m_components)
    {
        pugi::xml_node compNode = node.append_child("");
        if (false == comp.second->BaseSerialize(compNode))
        {
            // ASSERT
            COMP_LOG << "Error serializing node";
            return false;
        }
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool ComponentMgr::Serialize(oUniStream& outStream) const
{
    oUniStream mgrStream;
    outStream >> oUniInplace(mgrStream);

    if (!(mgrStream << GetName()))
    {
        // ASSERT
        COMP_LOG << "Error serializing manager name" << GetName();
        return false;
    }

    oUniStream componentsStream;
    mgrStream >> oUniInplace(componentsStream);

    for (const auto& comp : m_components)
    {
        if (false == comp.second->BaseSerialize(componentsStream))
        {
            // ASSERT
            COMP_LOG << "Error serializing node";
            return false;
        }
    }
    mgrStream << componentsStream;
    outStream << mgrStream;

    return true;
}

///////////////////////////////////////////////////////////////////////////
bool ComponentMgr::Serialize(const std::string& fileName) const
{
    pugi::xml_document document;
    auto node = document.append_child(s_strXmlNodeCompMgr.c_str());
    bool result = Serialize(node);

    if (result)
    {
        result = document.save_file(fileName.c_str());
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////
void ComponentMgr::AddComponent(IBaseComponentPtr compPtr)
{
    if (nullptr == compPtr)
    {
        COMP_LOG << "Add nullptr component in manager : " << GetName();
        return;
    }
    if( m_components.find(compPtr->GetComponentId()) == m_components.end())
    {
        m_components[compPtr->GetComponentId()] = compPtr;
    }
    else
    {
        COMP_LOG << "Add duplicate component in manager : " << GetName() << ", " << compPtr->GetComponentName();
    }
}

///////////////////////////////////////////////////////////////////////////
void ComponentMgr::IntroduceManagerToAllComponents(ComponentMgrPtr mgr)
{
    for (const auto& compPair : mgr->m_components)
    {
        compPair.second->SetComponentManager(mgr);
    }
}

///////////////////////////////////////////////////////////////////////////
void ComponentMgr::RegisterManager(const std::string& key, ComponentMgrPtr mgrPtr)
{
    if (nullptr == mgrPtr)
    {
        COMP_LOG << "Registering NULL manager: " << GetName() << ", " << ", " << key;
        COMP_ASSERT("Registering NULL manager.");
        return;
    }
    if (nullptr != GetRegisteredManager(key))
    {
        COMP_LOG << "Registering already registered manager: " << GetName() << ", " << mgrPtr->GetName() << ", " << key;
        COMP_ASSERT("Registering already registered manager.");
        return;
    }
    m_managers[key] = mgrPtr; // overwriting old manager if any
}

///////////////////////////////////////////////////////////////////////////
ComponentMgrPtr ComponentMgr::GetRegisteredManager(const std::string& key)
{
    auto mgrIter = m_managers.find(key);
    if (mgrIter == m_managers.end())
    {
        return nullptr;
    }

    if (ComponentMgrPtr mgrSharedPtr = (*mgrIter).second.lock())  // Has to be copied into a shared_ptr before usage
    {
        return mgrSharedPtr;
    }

    UnregisterManager(key);
    return nullptr;
}

///////////////////////////////////////////////////////////////////////////
void ComponentMgr::UnregisterManager(const std::string& key)
{
    m_managers.erase(key);
}

///////////////////////////////////////////////////////////////////////////
IBaseComponentPtr ComponentMgr::GetComponent(IComponentId componentId) const
{
    auto compIterator = m_components.find( componentId );
    if( compIterator == m_components.end())
    {
        return nullptr;
    }
    return compIterator->second;
}

///////////////////////////////////////////////////////////////////////////
bool ComponentMgr::Contain(IComponentId componentId) const
{
    auto compIterator = m_components.find( componentId );
    return (compIterator != m_components.end());
}
