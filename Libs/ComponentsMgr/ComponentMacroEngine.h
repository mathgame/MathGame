#ifndef COMPONENTMACROENGINE_H
#define COMPONENTMACROENGINE_H

//
// Declaration of components required values
#define COMP_DECLARE_REQ_VALUE(type, valName, ...)  \
private:                                            \
    type    m_##valName;                            \
    bool    m_has_##valName;                        \

//
// Declaration of components NOT required values
#define COMP_DECLARE_NOT_REQ_VALUE(type, valName, ...)   \
private:                                            \
    type    m_##valName;                            \
    bool    m_has_##valName;                        \

//
// Implementation of required values loader
#define COMP_IMPLEMENT_REQ_LOADER(type, valName, ...)    \
    m_has_##valName = Read(#valName, m_##valName);  \
    if (false == m_has_##valName)                   \
    {                                               \
        COMP_LOG << "REQUIRED value not set error : " << #valName << " in " << GetComponentName();    \
        COMP_ASSERT("");                                    \
        return false;                               \
    }                                               \

//
// Implementation of NOT required values loader
#define COMP_IMPLEMENT_NOT_REQ_LOADER(type, valName, ...)\
    m_has_##valName = Read(#valName, m_##valName);  \

//
// Implementation of required values bin loader
#define COMP_IMPLEMENT_REQ_BIN_LOADER(type, valName, ...)                                                   \
    if ((!(compFields >> m_has_##valName)) || (!m_has_##valName))                                           \
    {                                                                                                       \
        COMP_LOG << "REQUIRED value not set error reading : " << #valName << " in " << GetComponentName();  \
        COMP_ASSERT("");                                                                                    \
        return false;                                                                                       \
    }                                                                                                       \
    if (!(compFields >> m_##valName))                                                                       \
    {                                                                                                       \
        COMP_LOG << "Error reading value : " << #valName << " in " << GetComponentName();                   \
        COMP_ASSERT("");                                                                                    \
        return false;                                                                                       \
    }                                                                                                       \

//
// Implementation of NOT required values bin loader
#define COMP_IMPLEMENT_NOT_REQ_BIN_LOADER(type, valName, ...)                                       \
    if (!(compFields >> m_has_##valName))                                                           \
    {                                                                                               \
        COMP_LOG << "Cant read 'has' field error : " << #valName << " in " << GetComponentName();   \
        COMP_ASSERT("");                                                                            \
        return false;                                                                               \
    }                                                                                               \
    if ((Has_##valName()) && (!(compFields >> m_##valName)))                                        \
    {                                                                                               \
        COMP_LOG << "Cant read field error : " << #valName << " in " << GetComponentName();         \
        COMP_ASSERT("");                                                                            \
        return false;                                                                               \
    }                                                                                               \

//
// Implementation of binary loader
#define COMP_IMPLEMENT_BIN_LOAD(VAL_ITERATOR, compName)                             \
    MGTools::iUniStream compFields;                                                     \
    inputStream >> MGTools::iUniInplace(compFields);                                    \
    VAL_ITERATOR(COMP_IMPLEMENT_REQ_BIN_LOADER, COMP_IMPLEMENT_NOT_REQ_BIN_LOADER)      \

//
// Implementation of required values hash calculator
#define COMP_IMPLEMENT_REQ_HASH(type, valName, ...)    \
        hashes.push_back(GetFieldHash< type >(#valName, fieldPos++, true) );    \

//
// Implementation of not required values hash calculator
#define COMP_IMPLEMENT_NOT_REQ_HASH(type, valName, ...)    \
        hashes.push_back(GetFieldHash< type >(#valName, fieldPos++, false) );    \

//
// Implementation of required values writer
#define COMP_IMPLEMENT_REQ_WRITER(type, valName, ...)                        \
    if (Has_##valName() == false)                                       \
    {                                                                   \
        COMP_LOG << "REQUIRED value not set error before saving : " << #valName << " in " << GetComponentName();    \
        COMP_ASSERT("");                                                \
        return false;                                                   \
    }                                                                   \
    if (false == IBaseComponent::Write(node, #valName, m_##valName))    \
    {                                                                   \
        COMP_LOG << "Cant save field " << #valName;                     \
        return false;                                                   \
    }                                                                   \

//
// Implementation of NOT required values writer
#define COMP_IMPLEMENT_NOT_REQ_WRITER(type, valName, ...)            \
    if ((Has_##valName()) && (false == IBaseComponent::Write(node, #valName, m_##valName))) \
    {                                                                                       \
        COMP_LOG << "Cant save field " << #valName;                                         \
        return false;                                                                       \
    }                                                                                       \

//
// Implementation of required values binary writer
#define COMP_IMPLEMENT_REQ_BIN_WRITER(type, valName, ...)   \
    if (Has_##valName() == false)                                       \
    {                                                                   \
        COMP_LOG << "REQUIRED value not set error before saving : " << #valName << " in " << GetComponentName();    \
        COMP_ASSERT("");                                                \
        return false;                                                   \
    }                                                                   \
    if (!(compFields << true << m_##valName))                           \
    {                                                                   \
        COMP_LOG << "Cant save field " << #valName;                     \
        return false;                                                   \
    }                                                                   \

//
// Implementation of NOT required values writer
#define COMP_IMPLEMENT_NOT_REQ_BIN_WRITER(type, valName, ...)                                   \
    if (Has_##valName())                                                                        \
    {                                                                                           \
        if (!(compFields << true << m_##valName))                                               \
        {                                                                                       \
            COMP_LOG << "Cant save field " << #valName;                                         \
            return false;                                                                       \
        }                                                                                       \
    } else                                                                                      \
    {                                                                                           \
        if (!(compFields << true))                                                              \
        {                                                                                       \
            COMP_LOG << "Cant save 'has' field " << #valName;                                   \
            return false;                                                                       \
        }                                                                                       \
    };                                                                                          \

//
// Take all fields that are empty and that exist in the argument component 'c'
// and store them in 'this' component
#define COMP_IMPLEMENT_TAKE_EMPTY_FIELDS_FROM(type, valName, ...)           \
    if ( (false == this->Has_##valName()) && (true == c.Has_##valName()))   \
    {                                                                       \
        this->Set_##valName(c.Get_##valName());                             \
        anyChange = true;                                                   \
    }                                                                       \

//
// Implementation of binary serialization
#define COMP_IMPLEMENT_BIN_SERIALIZE(VAL_ITERATOR, compName)                        \
    MGTools::oUniStream compFields;                                                     \
    compFields.SetEncodingMode(outStream.IsEncodingMode());                         \
    outStream >> MGTools::oUniInplace(compFields);                                      \
    VAL_ITERATOR(COMP_IMPLEMENT_REQ_BIN_WRITER, COMP_IMPLEMENT_NOT_REQ_BIN_WRITER)  \
    outStream << compFields;                                                        \

//
// Implementation of required values getter
#define COMP_IMPLEMENT_REQ_GETTERS(type, valName, ...)                  \
public:                                                                 \
    bool Has_##valName() const { return m_has_##valName; };             \
__VA_ARGS__                                                             \
    const type& Get_##valName() const                                   \
    {                                                                   \
        if(false == Has_##valName())                                    \
        {                                                               \
            COMP_LOG << "Not initialized REQUIRED variable usage : "    \
                << #valName << " in " << GetComponentName();            \
            COMP_ASSERT("");                                            \
        }                                                               \
        return m_##valName;                                             \
    };                                                                  \
    void Set_##valName(const type& newVal)                              \
        { m_##valName = newVal; m_has_##valName = true; };              \
    void Clear_##valName()                                              \
        { m_has_##valName = false; m_##valName = type (); };            \
//
#define COMP_DECLARE_COMP_FIELDS_ENUM(type, valName, ...)    valName,

//
// Implementation of NOT required values getters
#define COMP_IMPLEMENT_NOT_REQ_GETTERS(type, valName, ...)      \
public:                                                         \
    bool Has_##valName() const                                  \
        {return m_has_##valName;};                              \
__VA_ARGS__                                                     \
    const type& Get_##valName() const                           \
    {                                                           \
        if(false == Has_##valName())                            \
        {                                                       \
            COMP_LOG << "Not initialized variable usage : "     \
                << #valName << " in " << GetComponentName();    \
            COMP_ASSERT("");                                    \
        }                                                       \
        return m_##valName;                                     \
    };                                                          \
    void Set_##valName(const type& newVal)                      \
        { m_##valName = newVal; m_has_##valName = true; };      \
    void Clear_##valName()                                      \
        { m_has_##valName = false; m_##valName = type (); };    \

#define IMPLEMENT_COMPONENTS_ENUM(compName, foo)    \
    COMP_ID_##compName,

///////////////////////////////////////////////////////////////////////////
#define IMPLEMENT_COMPONENT_LOADER(compName, foo)               \
    case EComponentId::COMP_ID_##compName:                      \
    {                                                           \
        auto ptr = compName##Component::CreateNewInstance();    \
        if (ptr->BaseLoad<ComponentsFactory>(inputData))          \
        {                                                       \
            return ptr;                                         \
        }                                                       \
        return MGTools::IBaseComponentPtr(nullptr);                 \
    }                                                           \
    break;                                                      \

//

#define MG_COMPONENT_COMMON_DECLARATIONS(VAL_ITERATOR, compName)                 \
public:                                                             \
enum class Fields           \
{                           \
    EMPTY,                  \
    VAL_ITERATOR(COMP_DECLARE_COMP_FIELDS_ENUM, COMP_DECLARE_COMP_FIELDS_ENUM)  \
};          \
VAL_ITERATOR(COMP_IMPLEMENT_REQ_GETTERS, COMP_IMPLEMENT_NOT_REQ_GETTERS);  \
public:                                                             \
compName##Component();                                              \
~compName##Component();                                             \
                                                                    \
virtual MGTools::IComponentId GetComponentId() const;                   \
virtual std::string GetComponentName() const;                       \
virtual u_int64_t GetComponentTypeHash() const;                     \
virtual std::string GetNamespaceName() const;                       \
virtual u_int64_t GetFactoryTypeHash() const;                       \
virtual void Clear();                                               \
virtual bool IsEmpty() const;                                       \
virtual bool IsEqualTo(MGTools::IBaseComponentPtr compPtr) const;       \
virtual void CopyFrom(const MGTools::IBaseComponent* compPtr);              \
virtual MGTools::IBaseComponentPtr CreateCopy() const;                  \
                                                                    \
bool FillEmptyFieldsFrom(const compName##Component& c);             \
static MGTools::IComponentId GetComponentIdStatic();                    \
static std::string GetComponentNameStatic();                        \
static std::shared_ptr<compName##Component> CreateNewInstance(std::string hint = std::string());    \
static MGTools::ComponentsResolveResult Resolve(const compName##Component& c1, const compName##Component& c2, const MGTools::MgrMergeInfo& mergeInfo);  \
static MGTools::IBaseComponentPtr Combine(const compName##Component& c1, const compName##Component& c2, const MGTools::MgrMergeInfo& mergeInfo);        \
static u_int64_t GetComponentTypeHashStatic();                      \
static u_int64_t GetFactoryTypeHashStatic();                        \
static compName##ComponentPtr SafeCast(std::shared_ptr<IBaseComponent> compPtr);    \
static const compName##Component* SafeCastRawPtr(const MGTools::IBaseComponent* compPtr);              \
static std::string GetNamespaceNameStatic();                        \
                                                                    \
template<class ManagerType>                                                     \
static bool Contain(std::shared_ptr<ManagerType> mgrPtr)                        \
{                                                                               \
    if (nullptr == mgrPtr)                                                      \
    {                                                                           \
        COMP_LOG    << "Looking for component in null manager : "               \
                    << compName##Component::GetComponentNameStatic();           \
        COMP_ASSERT("mrg nullptr.");                                            \
        return false;                                                           \
    }                                                                           \
    return mgrPtr->Contain(compName##Component::GetComponentIdStatic());        \
}                                                                               \
                                                                                \
template<class ManagerType>                                                     \
static compName##ComponentPtr SafeGet(std::shared_ptr<ManagerType> mgrPtr)      \
{                                                                               \
    if (nullptr == mgrPtr)                                                      \
    {                                                                           \
        COMP_LOG    << "Looking for component in null manager : "               \
                    << compName##Component::GetComponentNameStatic();           \
        COMP_ASSERT("mrg nullptr.");                                            \
        return compName##Component::CreateNewInstance();                        \
    }                                                                           \
    MGTools::IBaseComponentPtr basePtr = mgrPtr->GetComponent                       \
                                (compName##Component::GetComponentIdStatic());  \
    if (nullptr == basePtr)                                                     \
    {                                                                           \
        COMP_LOG    << "Missing component in manager : " << mgrPtr->GetName()   \
                    << ", " << compName##Component::GetComponentNameStatic();   \
        COMP_ASSERT("Missing component.");                                      \
        return compName##Component::CreateNewInstance();                        \
    }                                                                           \
    compName##ComponentPtr comp = compName##Component::SafeCast(basePtr);       \
    if (nullptr == comp)                                                        \
    {                                                                           \
        COMP_LOG    << "Component cast error: " << mgrPtr->GetName()            \
                    << ", " << basePtr->GetComponentName() << ", "              \
                    << compName##Component::GetComponentNameStatic();           \
        COMP_ASSERT("Component cast error");                                    \
        return compName##Component::CreateNewInstance();                        \
    }                                                                           \
    return comp;                                                                \
};                                                                              \
                                                                    \
protected:                                                          \
virtual bool Load();                                                \
virtual bool Load(MGTools::iUniStream& inputStream);                    \
virtual bool Serialize(pugi::xml_node& node) const;                 \
virtual bool Serialize(MGTools::oUniStream& outStream) const;           \
                                                                    \
VAL_ITERATOR(COMP_DECLARE_REQ_VALUE, COMP_DECLARE_NOT_REQ_VALUE);   \
                                                                    \
private:                                                            \
static u_int64_t s_structureHash;                                   \
static bool s_structureHashCalced;                                  \

//
#define IMPLEMENT_COMPONENT_ID_GETTERS(compName, foo)               \
    MGTools::IComponentId compName##Component::GetComponentId() const   \
    {                                                               \
        return (MGTools::IComponentId)EComponentId::COMP_ID_##compName; \
    };                                                              \
    MGTools::IComponentId compName##Component::GetComponentIdStatic()   \
    {                                                               \
        return (MGTools::IComponentId)EComponentId::COMP_ID_##compName; \
    };                                                              \
    u_int64_t compName##Component::GetFactoryTypeHash() const       \
    {                                                               \
        return GetFactoryTypeHashStatic();                          \
    };                                                              \
    u_int64_t compName##Component::GetFactoryTypeHashStatic()       \
    {                                                               \
        return ComponentsFactory::GetFactoryHash();                 \
    };                                                              \

//
#define IMPLEMENT_COMPONENT_COMMON_METHODS(VAL_ITERATOR, compName, nmSpace)                         \
std::string compName##Component::GetComponentName() const                                           \
{                                                                                                   \
    return #compName;                                                                               \
};                                                                                                  \
std::string compName##Component::GetComponentNameStatic()                                           \
{                                                                                                   \
    return #compName;                                                                               \
};                                                                                                  \
std::shared_ptr<compName##Component> compName##Component::CreateNewInstance(std::string hint)       \
{                                                                                                   \
    auto newInst = std::make_shared< compName##Component >();                                       \
    newInst->SetComponentHint(hint);                                                                \
    return newInst;                                                                                 \
}                                                                                                   \
u_int64_t compName##Component::s_structureHash = 0;                                                 \
bool compName##Component::s_structureHashCalced = false;                                            \
u_int64_t compName##Component::GetComponentTypeHash() const                                         \
{                                                                                                   \
    return GetComponentTypeHashStatic();                                                            \
}                                                                                                   \
u_int64_t compName##Component::GetComponentTypeHashStatic()                                         \
{                                                                                                   \
    if (false == s_structureHashCalced)                                                             \
    {                                                                                               \
        std::vector<u_int64_t> hashes;                                                              \
        int fieldPos = 1;                                                                           \
        VAL_ITERATOR(COMP_IMPLEMENT_REQ_HASH, COMP_IMPLEMENT_NOT_REQ_HASH);                         \
        hashes.push_back(MGTools::HashConstructor::ConstructHash(#compName));                           \
        hashes.push_back(MGTools::HashConstructor::ConstructHash(GetNamespaceNameStatic().c_str()));    \
        s_structureHash = MGTools::HashConstructor::ConstructHash(hashes);                              \
        s_structureHashCalced = true;                                                               \
    }                                                                                               \
    return s_structureHash;                                                                         \
}                                                                                                   \
compName##ComponentPtr compName##Component::SafeCast(std::shared_ptr<MGTools::IBaseComponent> compPtr)       \
{                                                                                                   \
    if (nullptr == compPtr)                                                                         \
    {                                                                                               \
        return nullptr;                                                                             \
    }                                                                                               \
    if (compPtr->GetComponentId() != compName##Component::GetComponentIdStatic())                   \
    {                                                                                               \
        return nullptr;                                                                             \
    }                                                                                               \
    if (compPtr->GetComponentTypeHash() != compName##Component::GetComponentTypeHashStatic())       \
    {                                                                                               \
        return nullptr;                                                                             \
    }                                                                                               \
    if (compPtr->GetFactoryTypeHash() != compName##Component::GetFactoryTypeHashStatic())           \
    {                                                                                               \
        return nullptr;                                                                             \
    }                                                                                               \
    compName##ComponentPtr ptr = std::dynamic_pointer_cast<compName##Component>(compPtr);           \
    return ptr;                                                                                     \
}                                                                                                   \
const compName##Component* compName##Component::SafeCastRawPtr(const MGTools::IBaseComponent* compPtr)                 \
{                                                                                                   \
    if (nullptr == compPtr)                                                                         \
    {                                                                                               \
        return nullptr;                                                                             \
    }                                                                                               \
    if (compPtr->GetComponentId() != compName##Component::GetComponentIdStatic())                   \
    {                                                                                               \
        return nullptr;                                                                             \
    }                                                                                               \
    if (compPtr->GetComponentTypeHash() != compName##Component::GetComponentTypeHashStatic())       \
    {                                                                                               \
        return nullptr;                                                                             \
    }                                                                                               \
    if (compPtr->GetFactoryTypeHash() != compName##Component::GetFactoryTypeHashStatic())           \
    {                                                                                               \
        return nullptr;                                                                             \
    }                                                                                               \
    const compName##Component* ptr = static_cast<const compName##Component*>(compPtr);              \
    return ptr;                                                                                     \
}                                                                                                   \
std::string compName##Component::GetNamespaceNameStatic()                                           \
{                                                                                                   \
    return std::string( FACTORY_NAMESPACE_STRING );                                                 \
}                                                                                                   \
std::string compName##Component::GetNamespaceName() const                                           \
{                                                                                                   \
    return GetNamespaceNameStatic();                                                                \
}                                                                                                   \
bool compName##Component::FillEmptyFieldsFrom(const compName##Component& c)                         \
{                                                                                                   \
    bool anyChange = false;                                                                         \
    VAL_ITERATOR(COMP_IMPLEMENT_TAKE_EMPTY_FIELDS_FROM, COMP_IMPLEMENT_TAKE_EMPTY_FIELDS_FROM);     \
    return anyChange;                                                                               \
}                                                                                                   \
void compName##Component::Clear()                                                                   \
{                                                                                                   \
    VAL_ITERATOR(COMP_CLEAR_VALUE, COMP_CLEAR_VALUE);                                               \
}                                                                                                   \
bool compName##Component::IsEmpty() const                                                           \
{                                                                                                   \
    VAL_ITERATOR(COMP_CHECK_IS_EMPTY_VALUE, COMP_CHECK_IS_EMPTY_VALUE);                             \
    return true;                                                                                    \
}                                                                                                   \
bool compName##Component::IsEqualTo(MGTools::IBaseComponentPtr compPtr) const                           \
{                                                                                                   \
    compName##ComponentPtr myTypePtr = compName##Component::SafeCast(compPtr);                      \
    if (nullptr == myTypePtr) return false;                                                         \
    VAL_ITERATOR(COMP_CHECK_IS_EQUAL_VALUE, COMP_CHECK_IS_EQUAL_VALUE);                             \
    return true;                                                                                    \
}                                                                                                   \
void compName##Component::CopyFrom(const MGTools::IBaseComponent* compPtr)                              \
{                                                                                                   \
    const compName##Component* myTypePtr = compName##Component::SafeCastRawPtr(compPtr);            \
    if (nullptr == myTypePtr)                                                                       \
    {                                                                                               \
        COMP_LOG << "Trying to copy from different component type.";                                \
        COMP_ASSERT("Copy from different component type error.");                                   \
        return;                                                                                     \
    }                                                                                               \
    std::string hint = this->GetComponentHint() + " , copy from : " + myTypePtr->GetComponentHint();\
    this->SetComponentHint(hint);                                                                   \
    VAL_ITERATOR(COMP_COPY_FROM_VALUE, COMP_COPY_FROM_VALUE);                                       \
}                                                                                                   \
MGTools::IBaseComponentPtr compName##Component::CreateCopy() const                                      \
{                                                                                                   \
    compName##ComponentPtr myTypePtr = CreateNewInstance();                                         \
    myTypePtr->CopyFrom(this);                                                                      \
    return myTypePtr;                                                                               \
}                                                                                                   \

//

#define ADD_COMPONENT_NAME_TO_ID_TO_MAP(compName, foo)      \
    {#compName, EComponentId::COMP_ID_##compName},          \

//

#define ADD_COMPONENT_ID_TO_NAME_TO_MAP(compName, foo)      \
    {EComponentId::COMP_ID_##compName, #compName},          \

//

///////////////////////////////////////////////////////////////////////////
#define COMP_RESOLVER_SWITCH_REGISTER(compName, foo)                                \
    case COMPONENT_FACTORY_NAMESPACE::EComponentId::COMP_ID_##compName:             \
    {                                                                               \
        return compName##Component::Resolve(*static_cast< compName##Component*>     \
            (c1.get()), *static_cast< compName##Component*>(c2.get()), mergeInfo);  \
    }                                                                               \

///////////////////////////////////////////////////////////////////////////
#define COMP_COMBINER_SWITCH_REGISTER(compName, foo)                                \
    case COMPONENT_FACTORY_NAMESPACE::EComponentId::COMP_ID_##compName:             \
    {                                                                               \
        return compName##Component::Combine(*static_cast< compName##Component*>     \
            (c1.get()), *static_cast< compName##Component*>(c2.get()), mergeInfo);  \
    }                                                                               \


///////////////////////////////////////////////////////////////////////////
#define COMP_FACTORY_HASH_CALC(compName, foo)                               \
    hashes.push_back(compName##Component::GetComponentTypeHashStatic());    \


///////////////////////////////////////////////////////////////////////////
#define COMP_DECLARE_HIDDEN_FUNCTIONS(valIterator, compName) \


///////////////////////////////////////////////////////////////////////////
#define COMP_IMPLEMENT_HIDDEN_FUNCTIONS(compName, foo) \

///////////////////////////////////////////////////////////////////////////
#define COMP_CONSTRUCTOR_VALUE_INIT(type, valName, ...)    \
    , m_##valName(type())       \
    , m_has_##valName(false)    \

///////////////////////////////////////////////////////////////////////////
#define COMP_IMPLEMENT_CONSTRUCTOR_VALUES_INIT(VAL_ITERATOR)                    \
    MGTools::IBaseComponent()                                                       \
    VAL_ITERATOR(COMP_CONSTRUCTOR_VALUE_INIT, COMP_CONSTRUCTOR_VALUE_INIT)      \

///////////////////////////////////////////////////////////////////////////
#define COMP_CLEAR_VALUE(type, valName, ...)    \
    Clear_##valName();                          \

///////////////////////////////////////////////////////////////////////////
#define COMP_CHECK_IS_EMPTY_VALUE(type, valName, ...)       \
    if (Has_##valName()) return false;                      \

///////////////////////////////////////////////////////////////////////////
#define COMP_CHECK_IS_EQUAL_VALUE(type, valName, ...)                               \
    if (this->Has_##valName() != myTypePtr->Has_##valName()) return false;          \
    if ((this->Has_##valName()) && (this->Get_##valName() != myTypePtr->Get_##valName()))   \
        return false;                                                               \

///////////////////////////////////////////////////////////////////////////
#define COMP_COPY_FROM_VALUE(type, valName, ...)                                    \
    if (myTypePtr->Has_##valName()) this->Set_##valName(myTypePtr->Get_##valName());\
    else this->Clear_##valName();                                                   \

#endif // COMPONENTMACROENGINE_H
