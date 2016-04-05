// NetMsgASync.cpp : implementation file
//

#include "stdafx.h"
#include "timerApp.h"
#include "NetMsgASync.h"


// NetMsgASync

NetMsgASync::NetMsgASync()
    : m_pSocket(NULL)
    , m_nLength(0)
{
}

NetMsgASync::~NetMsgASync()
{
}


// NetMsgASync member functions


void NetMsgASync::OnAccept(int nErrorCode)
{
    // TODO: Add your specialized code here and/or call the base class
    TRACE("workforce: onAccept()\n");
    NetMsgASync* pSocket = new NetMsgASync();
    if (Accept(*pSocket))
    {
        pSocket->AsyncSelect(FD_READ);
        m_pSocket = pSocket;
    } else {
        delete pSocket;
    }
    CAsyncSocket::OnAccept(nErrorCode);
}


void NetMsgASync::OnConnect(int nErrorCode)
{
    // TODO: Add your specialized code here and/or call the base class

    CAsyncSocket::OnConnect(nErrorCode);
}


void NetMsgASync::OnReceive(int nErrorCode)
{
    // TODO: Add your specialized code here and/or call the base class
    m_nLength = Receive(m_szBuffer, sizeof(m_szBuffer), 0);
    TRACE("NetMsgASync:receive(%s)\n", m_szBuffer);
    memset(m_szBuffer, 0, sizeof(m_szBuffer));
    AsyncSelect(FD_WRITE);

    CAsyncSocket::OnReceive(nErrorCode);
}


void NetMsgASync::OnOutOfBandData(int nErrorCode)
{
    // TODO: Add your specialized code here and/or call the base class

    CAsyncSocket::OnOutOfBandData(nErrorCode);
}


void NetMsgASync::OnSend(int nErrorCode)
{
    // TODO: Add your specialized code here and/or call the base class
    char buffer[1024];
    sprintf_s(buffer, "%s", "Hello World");
    Send(buffer, strlen(buffer), 0);
    TRACE("NetMsgASync:send(%s)\n", buffer);
    m_nLength = 0;
    memset(m_szBuffer, 0, sizeof(m_szBuffer));
    
    AsyncSelect(FD_READ);

    CAsyncSocket::OnSend(nErrorCode);
}


void NetMsgASync::OnClose(int nErrorCode)
{
    // TODO: Add your specialized code here and/or call the base class

    CAsyncSocket::OnClose(nErrorCode);
}
