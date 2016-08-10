#ifndef _COMPFACTORY_1470397872
#define _COMPFACTORY_1470397872

#include "../Settings/Includes.h"
#include "../Settings/Defines.h"
#include "../Settings/ComponentsList.h"
///////////////////////////////////
#include <memory>
#include <map>
#include <string>
///////////////////////////////////
//

//
///////////////////////////////////
namespace pugi
{
    class xml_node;
};
namespace MGTools
{
    class iUniStream;
}


namespace COMPONENT_FACTORY_NAMESPACE {



enum class EComponentId
{
    CUSTOM_COMPONENTS_ITERATOR(IMPLEMENT_COMPONENTS_ENUM)
};

class ComponentsFactory
{

public:
    static bool Init();
    static MGTools::IBaseComponentPtr CreateComponent(const pugi::xml_node& inputData);
    static MGTools::IBaseComponentPtr CreateComponent(MGTools::iUniStream& inputData);

    static u_int64_t GetFactoryHash();

    static MGTools::ComponentsResolveResult Resolve(const MGTools::IBaseComponentPtr& c1, const MGTools::IBaseComponentPtr& c2, const MGTools::MgrMergeInfo& mergeInfo);
    static MGTools::IBaseComponentPtr Combine(const MGTools::IBaseComponentPtr& c1, const MGTools::IBaseComponentPtr& c2, const MGTools::MgrMergeInfo& mergeInfo);

private:
    ComponentsFactory();

    static  const std::map<std::string, EComponentId> s_componentsNameToIdMap;
    static  const std::map<EComponentId, std::string> s_componentsIdToNameMap;
};

} // namespace MGTools

#endif // _COMPFACTORY_1470397872
