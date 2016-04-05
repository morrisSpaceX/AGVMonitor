// NetServer.cpp : implementation file
//

#include "stdafx.h"
#include "timerApp.h"
#include "NetServer.h"
#include "MySocket.h"
#include "NetMsgASync.h"
// NetServer

NetServer::NetServer()
{
}

NetServer::~NetServer()
{
}


// NetServer member functions
extern CMutex g_mux;
extern CMutex g_muxsvr;
int g_flag = 0;

UINT WorkForceClient(LPVOID lpParam)
{
    /*
    * main thread must create socket before working threads
    */

    AfxSocketInit();
    CSocket *pClientSocket = new CSocket();
    TRACE("worker: create()\n");
    if (!pClientSocket->Create()) {
        TRACE("worker: create failed(%d)\n", pClientSocket->GetLastError());
        delete pClientSocket;
        return false;
    }

    extern int g_flag;
    // while (!g_flag) {}

    // CString svrAddr("210.192.105.89");
    // char *ip = "10.166.206.59";
    char *ip = "127.0.0.1";
    CString svrAddr(ip);
    int svrPort = SVR_PORT;
    TRACE("worker:connect(%s)port(%d)\n", ip, SVR_PORT);
    if (!pClientSocket->Connect(svrAddr, svrPort)) {
        TRACE("worker: connect failed(%d)\n", pClientSocket->GetLastError());
        pClientSocket->Close();
        delete pClientSocket;
        return false;
    }

    CString buffer;
    svrAddr.Format(buffer);
    int len = 1024 * 10;
    buffer = "fromnowon";
    TRACE("worker:send()\n");
    pClientSocket->Send(buffer, buffer.GetLength());
    char b[1024];
    memset(b, 0, 1024);
    TRACE("worker:receive()\n");
    len = pClientSocket->Receive(b, 1024);
    TRACE("worker:close()\n");
    pClientSocket->Close();
    TRACE("--------------------IBM.len(%d)(%s)\n", len, b);
    TRACE("worker:delete()\n");
    delete pClientSocket;

    return true;
}



UINT WorkForce(LPVOID lpParam)
{
    g_mux.Lock();
    AfxSocketInit();

    BOOL bOptVal = TRUE;
    int bOptLen = sizeof(BOOL);
    // int nPort = *((int*)lpParam);
    CSocket * pServerSocket = new CSocket();
    CSocket * pReceiveSocket = new CSocket();
    g_mux.Unlock();

    try {
        // pServerSocket->Create(SVR_PORT);
        TRACE("workforce:socket()\n");
#if 0
        pServerSocket->Socket();
        //fix 10048 error
        pServerSocket->SetSockOpt(SO_REUSEADDR, (void *)&bOptVal, bOptLen, SOL_SOCKET);
        TRACE("workforce:bind()\n");
        pServerSocket->Bind(SVR_PORT);
#else
        pServerSocket->Create(SVR_PORT);
#endif
        TRACE("workforce:listen()\n");
        pServerSocket->Listen(10);
        TRACE("workforce:accept()\n");
        pServerSocket->Accept(*pReceiveSocket);
        char buffer[1024];
        memset(buffer, 0, 1024);
        TRACE("workforce:receive()\n");
        pReceiveSocket->Receive(buffer, 1024, 0);
        TRACE("===============workforce:server got(%s)\n", buffer);
        TRACE("workforce:send()\n");
        pReceiveSocket->Send("helloworld", 10, 0);
        TRACE("workforce:close()\n");
        pReceiveSocket->Close();
        pServerSocket->Close();
        TRACE("workforce:delete()\n");
        delete pReceiveSocket;
        delete pServerSocket;
    }
    catch (int n){
        TRACE("workforce:delete(%d)\n", n);
        delete pReceiveSocket;
        delete pServerSocket;
    }
    return 0;
}

int NetServer::Run(int param)
{
    UINT                    WorkForce(LPVOID lpParameter);
    LPVOID                  pParam = NULL;
    int                     nPriority = THREAD_PRIORITY_ABOVE_NORMAL;
    UINT                    nStackSize = 0;
    DWORD                   dwCreateFlags = 0;
    LPSECURITY_ATTRIBUTES   lpSecurityAttrs = NULL;
    // CWinThread *pMyFirstWorker, *pMySecondWorker;
    CWinThread *pMySecondWorker;
    int port = 0;

#if 0
    pMyFirstWorker  = AfxBeginThread(WorkForce, pParam, nPriority, nStackSize,
        dwCreateFlags, lpSecurityAttrs);
#else
    pMySecondWorker = AfxBeginThread(WorkForceClient, (LPVOID)&port);
#endif
    return 0;
}

