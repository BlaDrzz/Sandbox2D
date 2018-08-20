target_sources(libSandbox2D PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/EntryState.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/GlobalState.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/LocalSpaceState.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/PlayerController.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Ship.cpp"
)

#include("${CMAKE_CURRENT_LIST_DIR}/Templates/CMakeLists.txt")
