cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

project(
   Foo
   VERSION 1.0.0
   DESCRIPTION "Description"
   HOMEPAGE_URL "http://www.foo.com"
   LANGUAGES CXX
   )

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

find_package(Qt6 COMPONENTS
    Core
    Qml
    Quick
    QuickControls2
    Network
    LinguistTools
    REQUIRED
    )

include(cmake/StandardProjectSettings.cmake)
include(cmake/CompilerWarnings.cmake)
include(cmake/StaticAnalyzers.cmake)
include(cmake/Sanitizers.cmake)
include(cmake/Doxygen.cmake)
include(cmake/Conan.cmake)
include(cmake/Git.cmake)
include(cmake/LibrarySettings.cmake)

option(ENABLE_TESTING "Enable Test Builds" ON)
option(BUILD_SHARED_LIBS "True when building a shared library" True)

# Git integration version
configure_file(
  ${CMAKE_SOURCE_DIR}/src/app/version.h.in
  ${CMAKE_BINARY_DIR}/include/version.h
)
include_directories(${CMAKE_BINARY_DIR}/include)


# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)
if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
   option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
   if (ENABLE_BUILD_WITH_TIME_TRACE)
      add_compile_definitions(project_options INTERFACE -ftime-trace)
   endif()
endif()

run_conan()
enable_sanitizers(project_options)
enable_doxygen()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)
set_project_warnings(project_warnings)


add_subdirectory(src)

if(ENABLE_TESTING)
   enable_testing()
   message("Building Tests.")
   add_subdirectory(test)
endif()

if(ENABLE_FUZZING)
   message("Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html")
   add_subdirectory(fuzz_test)
endif()

include(CMakePackageConfigHelpers)

include(FeatureSummary)
feature_summary(WHAT ENABLED_FEATURES DISABLED_FEATURES PACKAGES_FOUND)
feature_summary(FILENAME ${CMAKE_CURRENT_BINARY_DIR}/features.log WHAT ALL)
