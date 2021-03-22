/*
 * Copyright (C) 2020, HENSOLDT Cyber GmbH
 */

/**
 * @file
 * @addtogroup SysLogger
 * @{
 * @brief System Logger client interface
 */

#pragma once

#include "SysLogger.h"
#include "OS_Types.h"

// The following definition is to work in coordination with lib_debug by
// defining the underlying Debug_PRINT__() required macro. In this way we obtain
// the behaviour of having all the modules that are independent from a logger
// but dependent on lib_debug to work transparently with the system logger.
#if defined(Debug_Config_PRINT_TO_LOG_SERVER)
#define Debug_PRINT__(LEVEL, ...)\
{\
    OS_Error_t err = OS_ERROR_GENERIC;\
    err = SysLoggerClient_log(LEVEL, __VA_ARGS__);\
    if (OS_SUCCESS != err)\
    {\
        printf("SysLoggerClient_log failed with error code %d\n", err);\
    }\
}
#endif

/**
 * @brief Initialize the system logger client
 *
 * @param logFunc the camkes provided rpc log function to the system logger
 * component
 *
 * @retval OS_SUCCESS if operation succeeded
 */
OS_Error_t
SysLoggerClient_init(SysLogger_LogFunc_t logFunc);

/**
 * @brief Free the system logger client
 */
void
SysLoggerClient_free();

/**
 * @brief Log function to send a formatted message to the system logger
 * component
 *
 * @param logLevel the log level
 * @param format the formatted string as for printf()
 * @param ... variable arguments list of the formatted string
 *
 * @retval OS_SUCCESS if operation succeeded
 */
OS_Error_t
SysLoggerClient_log(unsigned logLevel, const char* format, ...);

/** @} */
