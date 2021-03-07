# Set a default build type if none was specified
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
    set(CMAKE_BUILD_TYPE
        RelWithDebInfo
        CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui, ccmake
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
        "MinSizeRel" "RelWithDebInfo")
endif()

find_program(CCACHE ccache)
if (CCACHE)
    message(STATUS, "using ccache")
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
else()
    message(WARNING, "ccache not found cannot use")
endif()

# Generate compile_commands.json to make it easier to work with clang based tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_IPO "Enable Interprocedural Optimization, aka Link Time Optimization (LTO)" OFF)
if (ENABLE_IPO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT result OUTPUT output)
    if(result)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    else()
        message(SEND_ERROR "IPO is not supported: ${output}")
    endif()
endif()

# Enable Qt macros to not implicitly convert to and from QString
if (CMAKE_BUILD_TYPE STREQUAL "Debug" OR "RelWithDebInfo")
    message("Disables automatic conversions from 8-bit strings (char *) to Unicode QStrings, as well as from 8-bit
        char types (char and unsigned char) to QChar.")
    add_compile_definitions(QT_NO_CAST_FROM_ASCII)

    message("Disables automatic conversion from QString to 8-bit strings (char *).")
    add_compile_definitions(QT_NO_CAST_TO_ASCII)
endif ()

option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if (ENABLE_PCH)
  # This sets a global PCH parameter, each project will build its own PCH, which
  target_precompile_headers(project_options
      INTERFACE
      <vector>
      <string>
      <map>
      <utility>
      )
endif()
