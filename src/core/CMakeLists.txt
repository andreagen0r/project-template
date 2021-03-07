project(Core)

add_library(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/core.cpp
    )

add_library(Foo::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set(SUBDIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/entities
    ${CMAKE_CURRENT_SOURCE_DIR}/usecases
    ${CMAKE_CURRENT_SOURCE_DIR}/controllers
    ${CMAKE_CURRENT_SOURCE_DIR}/repositories
    )

foreach(SUB_DIR ${SUBDIRECTORIES})
    add_subdirectory(${SUB_DIR})
endforeach()

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}> #PROJECT_NAME_export.h headers
    $<INSTALL_INTERFACE:include>
    )

target_link_libraries(${PROJECT_NAME}
    CONAN_PKG::spdlog
    )

library_build_settings(${PROJECT_NAME})

library_generate_export_header(${PROJECT_NAME})

library_install(${PROJECT_NAME})
