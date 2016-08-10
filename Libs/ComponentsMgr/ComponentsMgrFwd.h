#ifndef COMPONENTSMGRINTERFACE_H
#define COMPONENTSMGRINTERFACE_H


#include <vector>
#include <memory>
#include <cassert>
#include <map>

namespace MGTools {

class IBaseComponent;
class ComponentMgr;

typedef unsigned int IComponentId;

typedef std::shared_ptr<IBaseComponent> IBaseComponentPtr;
typedef std::weak_ptr<IBaseComponent> IBaseComponentWeakPtr;
typedef std::shared_ptr<ComponentMgr> ComponentMgrPtr;
typedef std::weak_ptr<ComponentMgr> ComponentMgrWeakPtr;
typedef std::map<IComponentId, IBaseComponentPtr> ComponentsContainer;
typedef std::vector<IBaseComponentPtr> CompVector;
typedef std::map<std::string, CompVector> CompVectorContainer;

#define COMP_LOG std::cout
#define COMP_ASSERT(msg) assert(false && msg);

enum class ComponentsResolveResult
{
    FAIL,           // Resolving fail
    NOT_IMPLEMENTED,// No proper resolver for this component type
    NO_ONE,         // Resoving is OK but dont use neither of the two components
    TAKE_FIRST,     // Take the first one
    TAKE_SECOND,    // Take the second one
    USE_COMBINER    // Resolver is OK, but it needs you to use component combiner to produce a new component from both old
};

enum class MgrMergeType
{
    MANUAL,
    FORCE_FIRST_COMP,
    FORCE_SECOND_COMP,
    USE_FIRST_IF_NOT_IMPLEMENTED,
    USE_SECOND_IF_NOT_IMPLEMENTED,
    ASSERT_IF_CONFLICT,
};

class MgrMergeInfo
{
public:
    MgrMergeInfo() : m_type(MgrMergeType::MANUAL), m_object(nullptr){};
    MgrMergeInfo(void* objectPtr) : m_type(MgrMergeType::MANUAL), m_object(objectPtr){};
    MgrMergeInfo(MgrMergeType type, void* objectPtr = nullptr) : m_type(type), m_object(objectPtr){};

    MgrMergeType    m_type;
    void*           m_object;
};

typedef MGTools::ComponentsResolveResult (*ComponentsResolverFunc)(const MGTools::IBaseComponentPtr& c1, const MGTools::IBaseComponentPtr& c2, const MGTools::MgrMergeInfo& mergeInfo);
typedef MGTools::IBaseComponentPtr (*ComponentsCombinerFunc)(const MGTools::IBaseComponentPtr& c1, const MGTools::IBaseComponentPtr& c2, const MGTools::MgrMergeInfo& mergeInfo);

};


#endif // COMPONENTSMGRINTERFACE_H
