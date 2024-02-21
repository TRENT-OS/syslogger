/*
 *  System Logger
 *
 * Copyright (C) 2020-2024, HENSOLDT Cyber GmbH
 * 
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * For commercial licensing, contact: info.cyber@hensoldt.net
 */

#include "OS_Error.h"
#include "lib_debug/Debug.h"

#include "SysLogger.h"

#include "camkes.h"

// Ensure that the configuration is compatible with the limits.
Debug_STATIC_ASSERT(SysLogger_Config_MSG_SIZE <= SysLogger_MAX_MSG_SIZE);

//==============================================================================
// CAmkES component
//==============================================================================

OS_Error_t
SysLoggerRpc_log(unsigned int level, char const* msg)
{
    // At the moment the system logger is a dummy printf serializer, in future
    // we may still keep this behavior when no configuration is specified (no
    // logger chain, no spoolers)
    Debug_PRINT(level, msg);
    return OS_SUCCESS;
}

//---------------------------------------------------------------------------
// called before any other init function is called. Full runtime support is not
// available, e.g. interfaces cannot be expected to be accessible.
void pre_init(void)
{
    // nothing to be done here at the moment
}
