/*
 *  System Logger Client
 *
 *  Copyright (C) 2021, HENSOLDT Cyber GmbH
 */

// The following is to avoid recursion. You can't send messages from SysLogger
// to SysLogger. It would be a a dog chasing its tail. SysLogger has to just
// simply print its messages
#undef Debug_Config_PRINT_TO_LOG_SERVER

#include "lib_debug/Debug.h"
#include "SysLoggerClient.h"

#include "OS_Error.h"
#include "OS_Types.h"

#include "camkes.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

typedef struct
{
    SysLogger_LogFunc_t logFunc;
}
SysLoggerClient;

static SysLoggerClient  theOne;
static SysLoggerClient* self = NULL;

OS_Error_t
SysLoggerClient_init(SysLogger_LogFunc_t logFunc)
{
    if (NULL == logFunc)
    {
        return OS_ERROR_INVALID_PARAMETER;
    }
    theOne.logFunc  = logFunc;
    self = &theOne;

    return OS_SUCCESS;
}

void
SysLoggerClient_free()
{
    return;
}

OS_Error_t
SysLoggerClient_log(unsigned logLevel, const char* format, ...)
{
    if (NULL == self)
    {
        return OS_ERROR_INVALID_STATE;
    }
    if (NULL == format)
    {
        return OS_ERROR_INVALID_PARAMETER;
    }

    va_list args;
    va_start(args, format);

    char msg[SysLogger_Config_MSG_SIZE] = { 0 };

#if !defined(SysLogger_Config_COMPONENT_NAME_COLUMNS)
#define SysLogger_Config_COMPONENT_NAME_COLUMNS 0
#endif
    Debug_STATIC_ASSERT(SysLogger_Config_COMPONENT_NAME_COLUMNS >= 0);
    Debug_STATIC_ASSERT(
        SysLogger_Config_COMPONENT_NAME_COLUMNS < SysLogger_Config_MSG_SIZE);

#if (SysLogger_Config_COMPONENT_NAME_COLUMNS > 0)
    Debug_STATIC_ASSERT(
        SysLogger_Config_COMPONENT_NAME_COLUMNS <
        SysLogger_Config_MSG_SIZE);

    snprintf(msg, sizeof(msg), "[%s] ", get_instance_name());
    int namePrefixLen = strlen(msg);

    int numTrailingSpaces   =
        SysLogger_Config_COMPONENT_NAME_COLUMNS - namePrefixLen;
    if (numTrailingSpaces > 0)
    {
        memset(&msg[namePrefixLen], ' ', numTrailingSpaces);
    }
#endif
    const int err = vsnprintf(
                        &msg[SysLogger_Config_COMPONENT_NAME_COLUMNS],
                        SysLogger_Config_MSG_SIZE -
                        SysLogger_Config_COMPONENT_NAME_COLUMNS,
                        format,
                        args);
    va_end(args);

    if (err < 0)
    {
        Debug_LOG_ERROR("%s: vsnprintf() returned %d", __func__, err);
        Debug_PRINT(logLevel, "%s: vsnprintf() returned %d, message was:\n    '%s'\n",
                    __func__, err, msg);
        return OS_ERROR_ABORTED;
    }
    if (err >= SysLogger_Config_MSG_SIZE)
    {
        Debug_LOG_ERROR("%s: could not format the message correctly because of buffer too small (%d vs %zu)",
                        __func__, err, (size_t)SysLogger_Config_MSG_SIZE);
        Debug_PRINT(logLevel,
                    "%s: could not format the message correctly because of buffer too small (%d vs %zu), message was:\n    '%s'\n",
                    __func__, err, (size_t)SysLogger_Config_MSG_SIZE, msg);
        return OS_ERROR_BUFFER_TOO_SMALL;
    }
    self->logFunc(logLevel, msg);
    return OS_SUCCESS;
}
