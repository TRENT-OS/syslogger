/*
 * Copyright (C) 2020-2021, HENSOLDT Cyber GmbH
 */

/**
 * @file
 * @addtogroup SysLogger API
 * @{
 * @brief OS System Logger definitions
 */

#pragma once

#include "OS_Error.h"
#include "lib_debug/Debug.h"

#include "sel4/types.h"
#include "sel4/constants.h"

#if !defined(SysLogger_CONFIG_H_FILE)
#   error a configuration file must be provided!
#else
#   define SysLogger_XSTR(d)    SysLogger_STR(d)
#   define SysLogger_STR(d)     #d
#   include SysLogger_XSTR(SysLogger_CONFIG_H_FILE)
#endif

// CAmkES RPC functions use the seL4 kernel's IPC buffer to pass parameters, in
// our case a string. The available IPC buffer size is determined by the kernel
// constant seL4_MsgMaxLength in memory words (currently 120), that means that
// the total amount of bytes available would be:
// seL4_MsgMaxLength * sizeof(seL4_Word) = 480 bytes. In case of 64-bit
// architecture would be therefore 960 bytes.
#define SysLogger_MAX_MSG_SIZE   (seL4_MsgMaxLength * sizeof(seL4_Word))

/**
 * @brief log function type
 *
 * @param level log level
 * @param message log message
 *
 * @return OS_SUCCESS if success
 */
typedef OS_Error_t (*SysLogger_LogFunc_t)(
    const unsigned int level,
    char const message[SysLogger_Config_MSG_SIZE]);

/** @} */
