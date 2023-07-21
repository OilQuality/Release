#include "threadcmd.h"

ThreadCmd::ThreadCmd()
{

}

void ThreadCmd::run()
{
    //qDebug("------------ ThreadCmd:: run() ----------- thread id: %d", (int)QThread::currentThreadId());
    while(true)
    {
        sleep(10);
    }
}

void ThreadCmd::OnCmd()
{
    //qDebug("------------ ThreadCmd::OnCmd() ----------- thread id: %d", (int)QThread::currentThreadId());
}
