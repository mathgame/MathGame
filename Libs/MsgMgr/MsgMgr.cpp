#include "MsgMgr.h"
//#include "../ComponentsMgr/IBaseComponent.h"
#include <algorithm>
using namespace MGTools;

///////////////////////////////////////////////////////////////////////////
void MsgReceiver::RegisterToMsgMgr(MsgMgr& msgMgr)
{
    msgMgr.RegisterReceiver(this);
    m_myMsgManagers.push_back(&msgMgr);
}

///////////////////////////////////////////////////////////////////////////
MsgReceiver::~MsgReceiver()
{
    for (MsgMgr* msgMgrPtr : m_myMsgManagers)
    {
        msgMgrPtr->DeregisterReceiver(this);
    }
}

///////////////////////////////////////////////////////////////////////////
MsgMgr::MsgMgr()
{
}

///////////////////////////////////////////////////////////////////////////
void MsgMgr::Update()
{
    for (IBaseComponentPtr msgPtr : m_messages)
    {
        SendMsgSync(msgPtr);
    }
    m_messages.clear();
}

///////////////////////////////////////////////////////////////////////////
bool MsgMgr::CheckForReceiver(MsgReceiver* receiver) const
{
    auto iter = std::find(m_msgReceivers.begin(), m_msgReceivers.end(), receiver);
    return (iter != m_msgReceivers.end());
}

///////////////////////////////////////////////////////////////////////////
void MsgMgr::RegisterReceiver(MsgReceiver* receiver)
{
    if (CheckForReceiver(receiver))
    {
        assert(false && "Duplicate receiver.");
        return;
    }
    m_msgReceivers.push_front(receiver);
}

///////////////////////////////////////////////////////////////////////////
void MsgMgr::DeregisterReceiver(MsgReceiver *receiver)
{
    auto iter = std::find(m_msgReceivers.begin(), m_msgReceivers.end(), receiver);
    if (iter != m_msgReceivers.end())
    {
        m_msgReceivers.erase(iter);
    }
}

///////////////////////////////////////////////////////////////////////////
void MsgMgr::PushMsgAsync(IBaseComponentPtr msg)
{
    m_messages.push_back(msg);
}

///////////////////////////////////////////////////////////////////////////
void MsgMgr::SendMsgSync(IBaseComponentPtr msg)
{
    for (MsgReceiver* rcver : m_msgReceivers)
    {
        rcver->ReceiveMsg(msg);
    }
}
