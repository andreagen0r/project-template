project(Utils)

add_library(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/math.hpp
    )

add_library(Foo::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}> #PROJECT_NAME_export.h headers
    $<INSTALL_INTERFACE:include>
    )

target_link_libraries(${PROJECT_NAME} PRIVATE "")

library_build_settings(${PROJECT_NAME})

library_generate_export_header(${PROJECT_NAME})

library_install(${PROJECT_NAME})
