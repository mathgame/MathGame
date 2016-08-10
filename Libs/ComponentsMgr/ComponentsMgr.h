#ifndef _COMPONENTS_MGR_H_
#define _COMPONENTS_MGR_H_

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <sstream>

#include "ComponentsMgrFwd.h"

#include "IBaseComponent.h"

#include <algorithm>
#include <cctype>

namespace pugi
{
    class xml_node;
};

namespace MGTools {

class iUniStream;
class oUniStream;

class ComponentMgr
{
public:
    ComponentMgr();

    ~ComponentMgr(){};
    static ComponentMgrPtr CreateMgr() { return std::make_shared< ComponentMgr >(); };
    static ComponentMgrPtr CreateMgr(const std::string& mgrName) { ComponentMgrPtr ptr = std::make_shared< ComponentMgr >(); ptr->m_name = mgrName; return ptr; };

    template<class ComponentFactoryType>
    static ComponentMgrPtr CreateEmptyMgr(const std::string& mgrName);

    template<class ComponentFactoryType>
    bool InitMgr();


    static ComponentMgrPtr CreateFromFile (const std::string& fileName, const std::string& mgrName = "");

    template<class ComponentFactoryType>
    static ComponentMgrPtr CreateFromFile (const std::string& fileName, const std::string& mgrName = "");

    template<class ComponentFactoryType>
    static ComponentMgrPtr CreateFromStream (iUniStream& inpStream);

    template<class ComponentFactoryType>
    bool LoadFromFile (const std::string& fileName);

    bool Serialize(const std::string& fileName) const;
    bool Serialize(pugi::xml_node& node) const;
    bool Serialize(oUniStream& outStream) const;

    template <typename T>
    std::shared_ptr<T> GetComponent() const;
    IBaseComponentPtr GetComponent(IComponentId componentId) const;
    bool Contain(IComponentId componentId) const;

    template<class ComponentFactoryType>
    bool LoadFromXmlNode(const pugi::xml_node& xmlNode, std::string hint = std::string() );

    template<class ComponentFactoryType>
    bool AddXmlNode(const pugi::xml_node& xmlNode, const std::string& hint);

    template<class ComponentFactoryType>
    bool AddComponent(const pugi::xml_node& xmlNode, const std::string& hint);
    void AddComponent(IBaseComponentPtr compPtr);

    template<class ComponentFactoryType>
    bool AddIncludeFile(const pugi::xml_node& xmlNode);

    const std::string& GetName() const { return m_name; };
    u_int64_t GetFactoryHash() const { return m_factoryHash; };

    static bool IsManager(const pugi::xml_node& xmlNode);

    static ComponentMgrPtr Merge(ComponentMgrPtr mgr1, ComponentMgrPtr mgr2, const std::string& managerName = "", const MgrMergeInfo& mergeInfo = MgrMergeInfo(MgrMergeType::MANUAL));

    static void IntroduceManagerToAllComponents(ComponentMgrPtr mgr);
    void RegisterManager(const std::string& key, ComponentMgrPtr mgrPtr);
    void UnregisterManager(const std::string& key);
    ComponentMgrPtr GetRegisteredManager(const std::string& key);
protected:
    void SetName(const std::string& name) {m_name = name;};
private:
    static bool ProcessManualResolveResult(ComponentsContainer& container, const MGTools::IBaseComponentPtr& comp1, const MGTools::IBaseComponentPtr comp2, ComponentsResolveResult resolverResult, MgrMergeType mergeType);

    static const std::string& s_strXmlAttrName;
    static const std::string& s_strXmlNodeCompMgr;
    static const std::string& s_strXmlNodeInclude;

    static const std::string& s_strXmlAttrFileName;
    static const std::string& s_strXmlAttrTagName;
    static const std::string& s_strXmlAttrSegment;

    ComponentsResolverFunc                      m_resolver;
    ComponentsCombinerFunc                      m_combiner;
    std::string                                 m_name;
    ComponentsContainer                         m_components;
    u_int64_t                                   m_factoryHash;
    std::map<std::string, ComponentMgrWeakPtr>  m_managers;
};

#include "ComponentsMgr.hpp"

} // namespace MGTools

#endif // _COMPONENTS_MGR_H_
