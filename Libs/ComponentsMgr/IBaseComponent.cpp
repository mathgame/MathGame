#include "IBaseComponent.h"
#include <sstream>
#include "../pugixml/pugixml.hpp"
//#include "../MGValidate.h"
#include "../BaseComponents/System/ComponentsFactory.h"
//#include "../XmlParsers/XmlTools.h"

using namespace MGTools;


///////////////////////////////////////////////////////////////////////////
const std::string& IBaseComponent::s_strXmlNodeName = "name";
const std::string& IBaseComponent::s_strXmlNodeType = "type";
const std::string& IBaseComponent::s_strXmlNodeClass = "class";
const std::string& IBaseComponent::s_strXmlNodeKey = "key";
const std::string& IBaseComponent::s_strXmlNodeCompName = "component";
const std::string& IBaseComponent::s_strXmlNodeCompContainer = "compcontainer";
const std::string& IBaseComponent::s_strXmlNodeCompMgrName = "compmgr";
const std::string& IBaseComponent::s_strXmlNodeIncludeName = "include";

CompVector IBaseComponent::m_emptyCompVector;

#define exception int
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
const CompVector& IBaseComponent::GetContainer(const std::string& name) const
{
    const auto& ptr = m_vectorContainer.find(name);
    if (ptr == m_vectorContainer.end())
    {
        return m_emptyCompVector;
    }
    return ptr->second;
}

///////////////////////////////////////////////////////////////////////////
const CompVectorContainer& IBaseComponent::GetContainers() const
{
    return m_vectorContainer;
}

///////////////////////////////////////////////////////////////////////////
void IBaseComponent::AddToComponentVector(const std::string& vecName, IBaseComponentPtr compPtr)
{
    const auto& ptr = m_vectorContainer.find(vecName);
    if (ptr == m_vectorContainer.end())
    {
        CompVector v;
        v.push_back(compPtr);
        m_vectorContainer[vecName] = v;
    }
    else
    {
        ptr->second.push_back(compPtr);
    }
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::ReadType(const pugi::xml_node& xmlNode, std::string& result)
{
    // REMOVE ME
    const auto& attr = xmlNode.attribute(s_strXmlNodeClass.c_str());
    if (false == attr.empty())
    {
        return Read(xmlNode, s_strXmlNodeClass, result);
    }
    ////
    result = xmlNode.name();
    if (result.size() <= 0)
    {
        return false;
    }
    bool startWithSmallLetter = ((result[0] >= 'a') && (result[0] <= 'z'));
    bool startWithCapLetter = ((result[0] >= 'A') && (result[0] <= 'Z'));
    bool startWithLetter = (startWithSmallLetter || startWithCapLetter);

    return (startWithLetter);
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::IsComponent(const pugi::xml_node& xmlNode)
{
    if ((s_strXmlNodeCompMgrName == xmlNode.name()) || (s_strXmlNodeIncludeName == xmlNode.name()))
    {
        // PATCH, CHANGE IT !!!
        // IF IT IS COMP MANAGER OR INCLUDE NODE RETURN FALSE
        return false;
    }
    // CHECK FOR SKIP ATTRIBUTE
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::HasContainer(const std::string& name) const
{
    const auto& ptr = m_vectorContainer.find(name);
    bool result = (ptr != m_vectorContainer.end());

    return result;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::ExtractContainer(std::stringstream& src, std::stringstream& result)
{
    int c;

    while (((c = src.get()) != EOF) && (c != '{'));

    int count = 0;
    while((c = src.get()) != EOF)
    {
        if (c == '{')
        {
            count++;
        }
        else if (c == '}')
        {
            if (0 == count)
            {
                return true;
            }
            count--;
        }
        result << (char)c;
    }

    return false;
}


///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::AgregateContainers(IBaseComponent& dstComp, const IBaseComponent& srcComp, std::string containerName)
{
    std::vector<std::string> containersNames;
    if (containerName == "")
    {
        for (const auto& vectorPair : srcComp.m_vectorContainer)
        {
            containersNames.push_back(vectorPair.first);
        }
    }
    else
    {
        containersNames.push_back(containerName);
    }

    for (const auto& vecName : containersNames)
    {
        if (false == srcComp.HasContainer(vecName))
        {
            continue;
        }

        const auto& srcVec = srcComp.GetContainer(vecName);
        if (false == dstComp.HasContainer(vecName))
        {
            dstComp.m_vectorContainer[vecName] = srcVec;
        }
        else
        {
            auto ptr = dstComp.m_vectorContainer.find(vecName);
            if (dstComp.m_vectorContainer.end() == ptr)
            {
                // ASSERT
                continue;
            }
            for (const auto& compPtr : srcVec)
            {
                ptr->second.push_back(compPtr);
            }
        }
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::BaseSerialize(pugi::xml_node& xmlNode) const
{
    if( false == xmlNode.set_name(m_ComponentType.c_str()) )
    {
        COMP_LOG << "Cant set component xml node name.";
        return false;
    }

    if (false == WriteContainers(xmlNode))
    {
        COMP_LOG << "Cant save component containers.";
        return false;
    }

    if (false == Serialize(xmlNode))
    {
        COMP_LOG << "Error component serializing.";
        return false;
    }

    return true;
}

bool IBaseComponent::BaseSerialize(oUniStream& outStream) const
{
    if (!(outStream << (u_int32_t)GetComponentId()))
    {
        COMP_LOG << "Cant set component ID.";
        return false;
    }
    if (!(outStream << GetComponentHint()))
    {
        COMP_LOG << "Cant set component hint.";
        return false;
    }
    if (false == WriteContainers(outStream))
    {
        COMP_LOG << "Cant save component containers.";
        return false;
    }

    if (false == Serialize(outStream))
    {
        COMP_LOG << "Error component serializing.";
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteContainers(oUniStream& outStream) const
{
    oUniStream allVectors;
    allVectors.SetEncodingMode(outStream.IsEncodingMode());
    outStream >> oUniInplace(allVectors); // Start in-place

    for (const auto& vecPair : m_vectorContainer)
    {
        //auto vecNode = xmlNode.append_child(vecPair.first.c_str());
        oUniStream vectorStream;
        vectorStream.SetEncodingMode(allVectors.IsEncodingMode());
        allVectors >> oUniInplace(vectorStream); // Start in-place
        if (false == WriteVector(vectorStream, vecPair.second, vecPair.first))
        {
            COMP_LOG << "Error saving vector.";
            return false;
        }
        if (!(allVectors << vectorStream)) // Flush in-place
        {
            return false;
        }
    }

    if (outStream << allVectors) // Flush in-place
    {
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteVector(oUniStream& outStream, const CompVector& vec, const std::string& vecName) const
{
    if (!(outStream << vecName))
    {
        COMP_LOG << "Cant set vec node name.";
        return false;
    }

    for (const auto& compPtr : vec)
    {
        if (false == compPtr->BaseSerialize(outStream))
        {
            COMP_LOG << "Error component serializing.";
            return false;
        }
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteContainers(pugi::xml_node& xmlNode) const
{
    for (const auto& vecPair : m_vectorContainer)
    {
        auto vecNode = xmlNode.append_child(vecPair.first.c_str());
        if (false == WriteVector(vecNode, vecPair.second, vecPair.first))
        {
            COMP_LOG << "Error saving vector.";
            return false;
        }
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteVector(pugi::xml_node& xmlNode, const CompVector& vec, const std::string& vecName) const
{
    if (false == xmlNode.set_name(vecName.c_str()))
    {
        COMP_LOG << "Cant set vec node name.";
        return false;
    }

    for (const auto& compPtr : vec)
    {
        auto compNode = xmlNode.append_child();
        if (false == compPtr->BaseSerialize(compNode))
        {
            COMP_LOG << "Error component serializing.";
            return false;
        }
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
ComponentMgrPtr IBaseComponent::GetComponentManager() const
{
    if (auto mgrPtr = m_componentManager.lock())
    {
        return mgrPtr;
    }
    return nullptr;
}
