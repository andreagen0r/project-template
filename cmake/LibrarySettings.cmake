function(library_build_settings TARGET_NAME)
    if(NOT BUILD_SHARED_LIBS)
        set(STATIC_POSTFIX "-s")
        set_target_properties(${TARGET_NAME} PROPERTIES
            COMPILE_FLAGS -D${TARGET_NAME}_STATIC_DEFINE)
    endif()

    set_target_properties(${TARGET_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
        DEBUG_POSTFIX "${STATIC_POSTFIX}-d"
        RELEASE_POSTFIX "${STATIC_POSTFIX}"
        MINSIZEREL_POSTFIX "${STATIC_POSTFIX}-mr"
        RELWITHDEBINFO_POSTFIX "${STATIC_POSTFIX}-rd"
        )
endfunction()

function(library_install TARGET_NAME)
    install(TARGETS ${TARGET_NAME}
        EXPORT ${TARGET_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        )
endfunction()

function(library_generate_export_header TARGET_NAME)
    include("GenerateExportHeader")
    generate_export_header("${TARGET_NAME}")
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}_export.h" DESTINATION "include")
endfunction()
