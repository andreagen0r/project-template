project(Entities)

add_library(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/user.cpp
    )

add_library(Foo::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_link_libraries(
    ${PROJECT_NAME}
    CONAN_PKG::spdlog
    )

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}> #PROJECT_NAME_export.h headers
    $<INSTALL_INTERFACE:include>
    )

library_build_settings(${PROJECT_NAME})

library_generate_export_header(${PROJECT_NAME})

library_install(${PROJECT_NAME})
