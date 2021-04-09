#
# SysLogger client library
#
# Copyright (C) 2020-2021, HENSOLDT Cyber GmbH
#

cmake_minimum_required(VERSION 3.17)

# enable new behavior introduced in CMake 3.13, where relative paths will be
# converted into absolute paths in target_sources(INTERFACE ....)
cmake_policy(SET CMP0076 NEW)


#-------------------------------------------------------------------------------
# client lib
project(syslogger_client C)

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME}
    INTERFACE
        src/SysLoggerClient.c
)

target_compile_definitions(${PROJECT_NAME}
    INTERFACE
        # affects these header files:
        #    os_core_api/include/SysLogger/SysLoggerClient.h
        #    libs/lib_debug/include/lib_debug/Debug.h
        Debug_Config_PRINT_TO_LOG_SERVER
        Debug_Config_LOG_SERVER_H="SysLoggerClient.h"
)

if (OS_Logger_CONFIG_H_FILE)
    target_compile_definitions(${PROJECT_NAME}
        INTERFACE
            "SysLogger_CONFIG_H_FILE=${OS_Logger_CONFIG_H_FILE}"
    )
endif()

target_link_libraries(${PROJECT_NAME}
    INTERFACE
        os_core_api
        syslogger
)

target_include_directories(${PROJECT_NAME}
        INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/include
    )
