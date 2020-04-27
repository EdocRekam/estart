cmake_minimum_required (VERSION 2.6)

# ************************************************************************************************************
# Project variables
# ************************************************************************************************************
set (PRJ_NAME estart)
set (COMPUTERNAME "$ENV{COMPUTERNAME}" CACHE STRING "")

# ************************************************************************************************************
# Suggested settings show in cmake-gui
# ************************************************************************************************************
set (CMAKE_C_STANDARD_LIBRARIES "kernel32.lib shell32.lib advapi32.lib shlwapi.lib" CACHE STRING "")
set (CMAKE_C_FLAGS "/DWIN32 /D_WINDOWS /W4 /DUNICODE /D_UNICODE" CACHE STRING "")
set (CMAKE_C_FLAGS_RELEASE "/MT /O2 /Ob2 /DNDEBUG" CACHE STRING "")
set (CMAKE_C_FLAGS_DEBUG "/MTd /Zi /Ob0 /Od /RTC1" CACHE STRING "")
set (CMAKE_CONFIGURATION_TYPES x64-Release CACHE STRING "")
set (CMAKE_BUILD_TYPE CACHE STRING Release)

#
# Add WIN32 executable
#
project (${PRJ_NAME})
file(GLOB sources *.c *.h)
add_executable(${PRJ_NAME} WIN32 ${sources})

#
# Define COMPUTERNAME.H header name
#
target_compile_options(${PRJ_NAME} PUBLIC "-DCOMPUTERNAME_H=\"${COMPUTERNAME}.h\"")
