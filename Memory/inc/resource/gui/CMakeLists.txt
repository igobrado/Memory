include(${CMAKE_CURRENT_LIST_DIR}/components/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/impl/CMakeLists.txt)

list(APPEND MEMORY_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/ComponentFactory.hpp
        ${CMAKE_CURRENT_LIST_DIR}/GUILoader.hpp
        )