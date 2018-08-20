target_sources(libSandbox2D PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/Graphics.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/IniFile.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/InputManager.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/PrecisionTimer.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/Sandbox2D.cpp"
)

include("${CMAKE_CURRENT_LIST_DIR}/Physics/CMakeLists.txt")
