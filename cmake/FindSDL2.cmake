if(WIN32)
    include(FindPackageHandleStandardArgs)

    # Search for SDL2 CMake build in SDL/lib
    find_path(SDL2_ROOT "include/SDL.h" PATHS "${CMAKE_CURRENT_LIST_DIR}/../SDL" NO_DEFAULT_PATH)
    if(SDL2_ROOT)
        if (EXISTS "${SDL2_ROOT}/lib/SDL2.lib")
            set(SDL2_INCLUDE_DIRS "${SDL2_ROOT}/include")
            set(SDL2_LIBS "${SDL2_ROOT}/lib/SDL2.lib" "${SDL2_ROOT}/lib/SDL2main.lib")
            set(SDL2_DLLS "${SDL2_ROOT}/lib/SDL2.dll")
        endif()
    endif()

    mark_as_advanced(SDL2_ROOT)
    find_package_handle_standard_args(SDL2 DEFAULT_MSG SDL2_INCLUDE_DIRS SDL2_LIBS SDL2_DLLS)
endif()
