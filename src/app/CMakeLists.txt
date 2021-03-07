project(FooApp)

qt6_add_translation(TS_FILES
    Foo_en_US.ts
    Foo_pt_BR.ts
    )

set_source_files_properties(${TS_FILES} PROPERTIES ${CMAKE_BINARY_DIR} "l10n")

qt6_create_translation(QM_FILES
    ${CMAKE_SOURCE_DIR}
    ${TS_FILES}
    )

qt6_add_resources(QRC_FILES
    fonts.qrc
    qml.qrc
    )

qt6_add_executable(${PROJECT_NAME}
    ${TS_FILES}
    ${QRC_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/version.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/registercomponents.cpp
    )

#set_target_properties(${PROJECT_NAME} PROPERTIES
#    QT_QML_MODULE_VERSION 1.0
#    QT_QML_MODULE_URI "Foo"
#    )
#qt6_qml_type_registration(${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
    )

target_include_directories(${PROJECT_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:include>
    )

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Core
    Qt::Quick
    Qt::QuickControls2
    Qt::Qml
    Qt::Network
    CONAN_PKG::spdlog
    Foo::Core
    Foo::Entities
    Foo::Utils
    Foo::Preferences
    )

library_install(${PROJECT_NAME})
