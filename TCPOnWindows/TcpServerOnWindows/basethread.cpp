#include "basethread.h"

BaseThread::BaseThread()
{
    mThreadId = 0;
}

BaseThread::~BaseThread()
{

}

void BaseThread::start()
{
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadProc, (LPVOID)this, 0, &mThreadId);
}

void BaseThread::run()
{

}

DWORD BaseThread::threadProc(LPVOID lpParam)
{
    BaseThread *pThread = static_cast<BaseThread*>(lpParam);
    if (!pThread)
        return -1;

    pThread->run();

    return 0;
}

