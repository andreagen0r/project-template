macro(run_conan)
    if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")

        file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
    endif()

    include(${CMAKE_BINARY_DIR}/conan.cmake)

    conan_add_remote(NAME bincrafters URL
        https://api.bintray.com/conan/bincrafters/public-conan)

    conan_cmake_run(
        REQUIRES
        catch2/2.13.4
        spdlog/1.8.2
        nlohmann_json/3.9.1
        OPTIONS
        BASIC_SETUP
        CMAKE_TARGETS # individual targets to link to
        BUILD
        missing
        )
endmacro()
