#ifndef MSGMGR_H
#define MSGMGR_H

#include <memory>
#include <list>
#include "../ComponentsMgr/ComponentsMgrFwd.h"

namespace MGTools
{
class MsgMgr;

class MsgReceiver
{
public:
    ~MsgReceiver();

    void RegisterToMsgMgr(MsgMgr& msgMgr);
    virtual void ReceiveMsg( IBaseComponentPtr msg ) = 0;
private:
    std::vector<MsgMgr*> m_myMsgManagers;
};

class MsgMgr
{
public:
    MsgMgr();
    void Update();
    void RegisterReceiver(MsgReceiver* receiver);
    void DeregisterReceiver(MsgReceiver* receiver);

    void PushMsgAsync(IBaseComponentPtr msg);
    void SendMsgSync(IBaseComponentPtr msg);

private:
    bool CheckForReceiver(MsgReceiver* receiver) const;

    std::list<MsgReceiver*>             m_msgReceivers;
    std::vector<IBaseComponentPtr>      m_messages;
};

};

#endif // MSGMGR_H
