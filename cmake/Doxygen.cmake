function(enable_doxygen)

    option(ENABLE_DOXYGEN "Enable doxygen doc builds of source" ON)

    if(ENABLE_DOXYGEN)
        find_package(Doxygen)

        if(DOXYGEN_FOUND)
            set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/doc/Doxyfile.in)
            set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/doc/Doxyfile)

            configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
            message("Doxygen build started")

            add_custom_target(doc ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc
                COMMENT "Generating API documentation with Doxygen"
                VERBATIM
                )
                
            file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/doc/html)

            install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/html DESTINATION share/${PROJECT_NAME}/doc)
                                			
        else(DOXYGEN_FOUND)
            message(FATAL_ERROR "Doxygen is needed to build the documentation.")
        endif(DOXYGEN_FOUND)

    endif()

endfunction()
