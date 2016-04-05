#pragma once

// NetMsgASync command target

class NetMsgASync : public CAsyncSocket
{
public:
	NetMsgASync();
	virtual ~NetMsgASync();
    virtual void OnAccept(int nErrorCode);
    NetMsgASync* m_pSocket;
    virtual void OnConnect(int nErrorCode);
    virtual void OnReceive(int nErrorCode);
    virtual void OnOutOfBandData(int nErrorCode);
    virtual void OnSend(int nErrorCode);
    virtual void OnClose(int nErrorCode);
    char m_szBuffer[1024];
    int m_nLength;
};


