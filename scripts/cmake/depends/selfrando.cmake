# TODO: header

if (ENABLE_SELFRANDO OR ENABLE_CODE_LAYOUT_RANDO)
    message(STATUS "Including dependency: selfrando")

    download_dependency(
        selfrando
        GIT_REPOSITORY "git@github.com:immunant/selfrando-bareflank.git"
        GIT_TAG "include-symbol-sizes"
    )

    if (ENABLE_BUILD_VMM OR ENABLE_BUILD_TEST)
        list(APPEND SELFRANDO_VMM_CONFIGURE_FLAGS
            -DBAREFLANK_DIR=${CMAKE_SOURCE_DIR}
            # TODO: in debug mode, build TrapDump too
	    -DSR_BUILD_MODULES=TrapLinker|TrapLibs
            -DBUILD_SHARED_LIBS=OFF
            -DTRAPLINKER_INSTALL_LD=OFF
            -DTRAPINFO_INSTALL_HEADERS=ON
            -DSR_FORCE_INPLACE=ON
            -DSR_DEBUG_LEVEL=env
        )

        add_dependency(
            selfrando vmm
            LIST_SEPARATOR |
            CMAKE_ARGS  ${SELFRANDO_VMM_CONFIGURE_FLAGS}
        )
    endif()

    list(APPEND SELFRANDO_HEADERS_CONFIGURE_FLAGS
        # TODO: in debug mode, build TrapDump too
        -DSR_BUILD_MODULES=""
        -DTRAPLINKER_INSTALL_LD=OFF
        -DTRAPINFO_INSTALL_HEADERS=ON
    )

endif()
