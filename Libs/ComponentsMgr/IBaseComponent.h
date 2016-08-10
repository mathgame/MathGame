#ifndef I_BASE_COMPONENT_H_
#define I_BASE_COMPONENT_H_
#include "ComponentsMgrFwd.h"

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <sstream>

#include "HashConstructor.h"

#include "../pugixml/pugixml.hpp"
#include "../UniStream/iUniStream.h"
#include "../UniStream/oUniStream.h"

//namespace pugi
//{
//    class xml_node;
//};

//

namespace MGTools {

class ComponentMgr;

class IBaseComponent
{
public:
    IBaseComponent() : m_xmlNode(nullptr), m_componentManager(ComponentMgrWeakPtr()) {};
    virtual ~IBaseComponent(){};

    virtual void Update(){};

    bool HasContainer(const std::string& name) const;
    const CompVector& GetContainer(const std::string& name) const;
    const CompVectorContainer& GetContainers() const;

    template<typename T>
    std::vector< std::shared_ptr<T> > GetContainer(const std::string& name) const;

    virtual std::string GetComponentName() const = 0;
    virtual IComponentId GetComponentId() const = 0;
    virtual u_int64_t GetComponentTypeHash() const = 0;
    virtual u_int64_t GetFactoryTypeHash() const = 0;
    virtual std::string GetNamespaceName() const = 0;
    virtual void Clear() = 0;
    virtual bool IsEmpty() const = 0;
    virtual bool IsEqualTo(IBaseComponentPtr compPtr) const = 0;
    virtual void CopyFrom(const IBaseComponent* compPtr) = 0;
    virtual IBaseComponentPtr CreateCopy() const = 0;

    const std::string& GetComponentHint() const { return m_componentHint; };
    void SetComponentHint(const std::string& hint) { m_componentHint = hint; };

    template<class ComponentFactoryType>
    bool BaseLoad(const pugi::xml_node& xmlNode);

    template<class ComponentFactoryType>
    bool BaseLoad(iUniStream& inputStream);

    static bool ReadType(const pugi::xml_node& xmlNode, std::string& result);
    ComponentMgrPtr GetComponentManager() const;
    void SetComponentManager(ComponentMgrPtr componentManager) { m_componentManager = componentManager; };

protected:

    void AddToComponentVector(const std::string& vecName, IBaseComponentPtr compPtr);
    static bool AgregateContainers(IBaseComponent& dstComp, const IBaseComponent& srcComp, std::string containerName = "");

    virtual bool Load() = 0;
    virtual bool Load(iUniStream& inputStream) = 0;
    virtual bool Serialize(pugi::xml_node& node) const = 0;
    virtual bool Serialize(oUniStream& outStream) const = 0;

    template<typename T>
    static bool Read(const pugi::xml_node& xmlNode, const std::string& fieldName, T& result);

    template<typename T>
    bool Read(const std::string& fieldName, T& result);

    template<typename T>
    static bool Write(pugi::xml_node xmlNode, const std::string& fieldName, const T& value);

    template<typename T>
    static  u_int64_t GetFieldHash(const char* fieldName, int fieldPos, bool isRequired);

private:
    static bool IsComponent(const pugi::xml_node& xmlNode);
    bool BaseSerialize(pugi::xml_node& xmlNode) const;
public:
    bool BaseSerialize(oUniStream& outStream) const;
private:
    static bool ExtractContainer(std::stringstream& src, std::stringstream& result);

    ////////////////////////////////////


    // UNSIGNED INT_64
    static bool ReadFromStream(std::stringstream& src, unsigned long long& result);
    static bool WriteToStream(std::stringstream& dst, const unsigned long long& value);
    static u_int64_t GetTypeHash(const unsigned long long& notUsed, u_int32_t x, u_int32_t y, u_int32_t d);
    // SIGNED INT_64
    static bool ReadFromStream(std::stringstream& src, signed long long& result);
    static bool WriteToStream(std::stringstream& dst, const signed long long& value);
    static u_int64_t GetTypeHash(const signed long long& notUsed, u_int32_t x, u_int32_t y, u_int32_t d);
    // UNSIGNED INT_32
    static bool ReadFromStream(std::stringstream& src, unsigned long& result);
    static bool WriteToStream(std::stringstream& dst, const unsigned long& value);
    static u_int64_t GetTypeHash(const unsigned long& notUsed, u_int32_t x, u_int32_t y, u_int32_t d);
    // SIGNED INT_32
    static bool ReadFromStream(std::stringstream& src, signed long& result);
    static bool WriteToStream(std::stringstream& dst, const signed long& value);
    static u_int64_t GetTypeHash(const signed long& notUsed, u_int32_t x, u_int32_t y, u_int32_t d);
    // UNSIGNED INT_16
    static bool ReadFromStream(std::stringstream& src, unsigned short& result);
    static bool WriteToStream(std::stringstream& dst, const unsigned short& value);
    static u_int64_t GetTypeHash(const unsigned short& notUsed, u_int32_t x, u_int32_t y, u_int32_t d);
    // SIGNED INT_16
    static bool ReadFromStream(std::stringstream& src, signed short& result);
    static bool WriteToStream(std::stringstream& dst, const signed short& value);
    static u_int64_t GetTypeHash(const signed short& notUsed, u_int32_t x, u_int32_t y, u_int32_t d);
    // UNSIGNED INT_8
    static bool ReadFromStream(std::stringstream& src, unsigned char& result);
    static bool WriteToStream(std::stringstream& dst, const unsigned char& value);
    static u_int64_t GetTypeHash(const unsigned char& notUsed, u_int32_t x, u_int32_t y, u_int32_t d);
    // SIGNED INT_8
    static bool ReadFromStream(std::stringstream& src, signed char& result);
    static bool WriteToStream(std::stringstream& dst, const signed char& value);
    static u_int64_t GetTypeHash(const signed char& notUsed, u_int32_t x, u_int32_t y, u_int32_t d);
    // UNSIGNED INT
    static bool ReadFromStream(std::stringstream& src, unsigned& result);
    static bool WriteToStream(std::stringstream& dst, const unsigned& value);
    static u_int64_t GetTypeHash(const unsigned& notUsed, u_int32_t x, u_int32_t y, u_int32_t d);
    // SIGNED INT
    static bool ReadFromStream(std::stringstream& src, signed& result);
    static bool WriteToStream(std::stringstream& dst, const signed& value);
    static u_int64_t GetTypeHash(const signed& notUsed, u_int32_t x, u_int32_t y, u_int32_t d);
    // CHAR
    static bool ReadFromStream(std::stringstream& src, char& result);
    static bool WriteToStream(std::stringstream& dst, const char& value);
    static u_int64_t GetTypeHash(const char& notUsed, u_int32_t x, u_int32_t y, u_int32_t d);
    // FLOAT
    static bool ReadFromStream(std::stringstream& src, float& result);
    static bool WriteToStream(std::stringstream& dst, const float& value);
    static u_int64_t GetTypeHash(const float& notUsed, u_int32_t x, u_int32_t y, u_int32_t d);
    // DOUBLE
    static bool ReadFromStream(std::stringstream& src, double& result);
    static bool WriteToStream(std::stringstream& dst, const double& value);
    static u_int64_t GetTypeHash(const double& notUsed, u_int32_t x, u_int32_t y, u_int32_t d);
    // STRING
    static bool ReadFromStream(std::stringstream& src, std::string& result);
    static bool WriteToStream(std::stringstream& dst, const std::string& value);
    static u_int64_t GetTypeHash(const std::string& notUsed, u_int32_t x, u_int32_t y, u_int32_t d);
    // BOOL
    static bool ReadFromStream(std::stringstream& src, bool& result);
    static bool WriteToStream(std::stringstream& dst, const bool& value);
    static u_int64_t GetTypeHash(const bool& notUsed, u_int32_t x, u_int32_t y, u_int32_t d);
    ////////////////////////////////////
    // PAIR
    template<typename T1, typename T2>
    static bool ReadFromStream(std::stringstream& src, std::pair<T1, T2>& result);
    template<typename T1, typename T2>
    static bool WriteToStream(std::stringstream& dst, const std::pair<T1, T2>& value);
    template<typename T1, typename T2>
    static u_int64_t GetTypeHash(const std::pair<T1, T2>& notUsed, u_int32_t x, u_int32_t y, u_int32_t d);
    // VECTOR
    template<typename T>
    static bool ReadFromStream(std::stringstream& src, std::vector<T>& result);
    template<typename T>
    static bool WriteToStream(std::stringstream& dst, const std::vector<T>& value);
    template<typename T>
    static u_int64_t GetTypeHash(const std::vector<T>& notUsed, u_int32_t x, u_int32_t y, u_int32_t d);
    // MAP
    template<typename KeyT, typename ValT>
    static bool ReadFromStream(std::stringstream& src, std::map<KeyT, ValT>& result);
    template<typename KeyT, typename ValT>
    static bool WriteToStream(std::stringstream& dst, const std::map<KeyT, ValT>& value);
    template<typename KeyT, typename ValT>
    static u_int64_t GetTypeHash(const std::map<KeyT, ValT>& notUsed, u_int32_t x, u_int32_t y, u_int32_t d);
    ////////////////////////////////////

    template<class ComponentFactoryType>
    bool ReadContainers();
    template<class ComponentFactoryType>
    bool ReadContainers(iUniStream& inputStream);


    template<class ComponentFactoryType>
    bool ReadVector(const pugi::xml_node& containerNode);
    template<class ComponentFactoryType>
    bool ReadVector(iUniStream& containerStream);

    bool WriteContainers(pugi::xml_node& xmlNode) const;
    bool WriteVector(pugi::xml_node& xmlNode, const CompVector& vec, const std::string& vecName) const;

    bool WriteContainers(oUniStream& outStream) const;
    bool WriteVector(oUniStream& outStream, const CompVector& vec, const std::string& vecName) const;

protected:
    const pugi::xml_node*   m_xmlNode;
private:
    std::string             m_ComponentType;
    CompVectorContainer     m_vectorContainer;
    ComponentMgrWeakPtr     m_componentManager;
    std::string             m_componentHint; // some description, MUST BE USED ONLY WITH DEBUG PURPOSE

    static CompVector       m_emptyCompVector;
    static const std::string& s_strXmlNodeName;
    static const std::string& s_strXmlNodeType;
    static const std::string& s_strXmlNodeClass;
    static const std::string& s_strXmlNodeKey;
    static const std::string& s_strXmlNodeCompName;
    static const std::string& s_strXmlNodeCompContainer;
    static const std::string& s_strXmlNodeCompMgrName;
    static const std::string& s_strXmlNodeIncludeName;

    friend class ComponentMgr;
};


#include "IBaseComponent.hpp"

} // namespace MGTools

#endif // I_BASE_COMPONENT_
