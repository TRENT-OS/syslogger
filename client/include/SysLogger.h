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

// The following limit is calculated starting from an empirical measurement of
// the available amount of bytes for a message in the log() RPC.
// seL4_IPCBufferSizeBits determines the size of the IPC buffer expressed in
// bits (for example, for the empirical test that has been done, in that 32 bit
// architecture, it was 9, that means 2⁹ = 512 bytes for the IPC buffer).
// It was found, by dichotomic re-attempts, that the remaining bytes for a
// message in the log() RPC were 480. Instead of defining SysLogger_MAX_MSG_SIZE
// simply as 480 it is preferred to keep the proportion as it it would increase
// (double) when for example switching to a 64 bits architecture.
// 480 is 120 memory words therefore we shall consider this datum and multiply
// it by a coefficient that is the amount of bytes in a memory word.
#define SysLogger_MAX_MSG_SIZE   (120 * WORD_BIT/CHAR_BIT)

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
