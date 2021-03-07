set(SUBDIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/app
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/preferences
    )

foreach(SUB_DIR ${SUBDIRECTORIES})
    add_subdirectory(${SUB_DIR})
endforeach()
