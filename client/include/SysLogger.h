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

#include <limits.h>

#if !defined(SysLogger_CONFIG_H_FILE)
#   error a configuration file must be provided!
#else
#   define SysLogger_XSTR(d)    SysLogger_STR(d)
#   define SysLogger_STR(d)     #d
#   include SysLogger_XSTR(SysLogger_CONFIG_H_FILE)
#endif

// CAmkES RPC functions use the seL4 kernel's IPC buffer to pass parameters, in
// our case a string. The IPC buffer size is determined by the kernel constant
// 'seL4_IPCBufferSizeBits'. On 32-bit architectures it is 9, so the IPC buffer
// is 512 (= 2^9) byte and the usable size of the buffer in this case would be
// 480 byte.
#if !defined(CHAR_BIT) || CHAR_BIT == 0
// in this case we assume 32-bit architecture (the smallest supported)
#   define SysLogger_MAX_MSG_SIZE   480
#else
#   define SysLogger_MAX_MSG_SIZE   (120 * WORD_BIT/CHAR_BIT)
#endif

#if !defined(SysLogger_Config_MSG_SIZE)
#   error "SysLogger_Config_MSG_SIZE must be defined"
#elif SysLogger_Config_MSG_SIZE > SysLogger_MAX_MSG_SIZE
#   error "SysLogger_Config_MSG_SIZE exceeds RPC call limits"
#endif

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
