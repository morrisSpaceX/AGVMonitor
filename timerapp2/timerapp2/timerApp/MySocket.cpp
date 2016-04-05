// MySocket.cpp : implementation file
//

#include "stdafx.h"
#include "timerApp.h"
#include "MySocket.h"


// CMySocket

CMySocket::CMySocket()
{
    Create(823);
    Listen(5);
}

CMySocket::~CMySocket()
{
}


// CMySocket member functions
