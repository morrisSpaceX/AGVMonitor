#pragma once
#define SVR_PORT    (8383)
// NetServer command target

class NetServer : public CObject
{
public:
	NetServer();
	virtual ~NetServer();
    int Run(int param);
};


