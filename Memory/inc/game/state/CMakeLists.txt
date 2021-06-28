include(${CMAKE_CURRENT_LIST_DIR}/impl/CMakeLists.txt)

list(APPEND MEMORY_HEADERS
        ${CMAKE_CURRENT_LIST_DIR}/State.hpp
        ${CMAKE_CURRENT_LIST_DIR}/StateMachine.hpp
        )