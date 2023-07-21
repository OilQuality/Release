#include "threadcheckstate.h"

ThreadCheckState::ThreadCheckState()
{

}

void ThreadCheckState::run()
{
    sleep( 2 );
    emit sigCheck();
    //qDebug("ThreadCheckState::run()");
}
