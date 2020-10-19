/*
 *  System Logger
 *
 *  Copyright (C) 2020-2021, HENSOLDT Cyber GmbH
 */

#include "OS_Error.h"
#include "lib_debug/Debug.h"

#include "camkes.h"


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
