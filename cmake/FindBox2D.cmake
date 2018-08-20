if(WIN32)
    include(FindPackageHandleStandardArgs)

    # Search for BOX2D CMake build in Box2D/lib
    find_path(BOX2D_ROOT "include/Box2D/Box2D.h" PATHS "${CMAKE_CURRENT_LIST_DIR}/../Box2D" NO_DEFAULT_PATH)
    if(BOX2D_ROOT)
        if (EXISTS "${BOX2D_ROOT}/lib/Box2DDebug.lib")
            set(BOX2D_INCLUDE_DIRS "${Box2D_ROOT}/include/Box2D")
            set(BOX2D_LIBS "${Box2D_ROOT}/lib/Box2DDebug.lib")
        endif()
    endif()

    mark_as_advanced(BOX2D_ROOT)
    find_package_handle_standard_args(BOX2D DEFAULT_MSG Box2D_INCLUDE_DIRS BOX2D_LIBS BOX2D_DLLS)
endif()
