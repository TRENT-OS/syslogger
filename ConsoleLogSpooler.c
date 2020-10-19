/*
 *  Console Log Spooler
 *
 *  Copyright (C) 2020-2021, HENSOLDT Cyber GmbH
 */

#include "lib_debug/Debug.h"
#include <camkes.h>

//==============================================================================
// CAmkES component
//==============================================================================

//---------------------------------------------------------------------------
// called before any other init function is called. Full runtime support is not
// available, e.g. interfaces cannot be expected to be accessible.
void pre_init(void)
{
    // nothing to be done here at the moment
}

//------------------------------------------------------------------------------
int run()
{
    /// TODO: implement console logger behaviour. A console logger should pick
    // up, print on console and consume a message from the shared FIFO in the
    // dataport when a notification of log available is received from the system
    // logger.
    return 0;
}
