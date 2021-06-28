include_guard(GLOBAL)
function(PROJECT_SETUP)

    set(MEMORY_SOURCES)
    set(MEMORY_HEADERS)

    # Specify default build type if none provided (before project() command)
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
    endif()

endfunction()
