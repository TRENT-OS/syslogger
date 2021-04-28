#
# System Logger
#
# Copyright (C) 2020-2021, HENSOLDT Cyber GmbH
#

cmake_minimum_required(VERSION 3.17)

project(syslogger C)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}
)

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/client")

CAmkESAddImportPath(camkes)

#-------------------------------------------------------------------------------
#
# Declare SysLog CAmkES Component
#
# Parameters:
#
#   <name>
#       component instance name

#   <system_config_lib>
#       system config library
#
function(DeclareCAmkESComponent_SysLogger
    name
    system_config_lib
)
    if (OS_Logger_CONFIG_H_FILE)
        set(SysLogger_CONFIG_H_FILE ${OS_Logger_CONFIG_H_FILE})
    endif()

    DeclareCAmkESComponent(
        ${name}
        INCLUDES
            "${CMAKE_CURRENT_FUNCTION_LIST_DIR}"
        SOURCES
            ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/SysLogger.c
        C_FLAGS
            -Wall
            -Werror
            -DSysLogger_CONFIG_H_FILE=${SysLogger_CONFIG_H_FILE}
        LIBS
            ${system_config_lib}
            os_core_api
            lib_debug
    )

endfunction()

#-------------------------------------------------------------------------------
#
# Declare Console Spooler CAmkES Component
#
# Parameters:
#
#   <name>
#       component instance name
#
#   <system_config_lib>
#       system config library
#
function(DeclareCAmkESComponent_ConsoleLogSpooler
    name
    system_config_lib
)

    DeclareCAmkESComponent(
        ${name}
        SOURCES
            ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/ConsoleLogSpooler.c
        C_FLAGS
            -Wall
            -Werror
        LIBS
            ${system_config_lib}
            os_core_api
            os_libs
    )

endfunction()
