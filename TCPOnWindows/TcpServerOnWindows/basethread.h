#ifndef BASETHREAD_H
#define BASETHREAD_H

#include <WinSock2.h>
#include <stdio.h>

class BaseThread
{
public:
    BaseThread();
    virtual ~BaseThread();

    void start();

protected:
    virtual void run();
    static DWORD WINAPI threadProc(LPVOID lpParam);

private:
    DWORD mThreadId;
};

#endif // BASETHREAD_H
