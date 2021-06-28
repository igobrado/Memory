cmake_minimum_required(VERSION 3.12)
set(ProjectName "Memory")
project(${ProjectName})
include(${CMAKE_CURRENT_LIST_DIR}/cmake/ProjectSetup.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/CopyDLL.cmake)
project_setup()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

find_package(SFML 2.5.1
        COMPONENTS
        REQUIRED
        system
        window
        graphics
        audio)

if (SFML_FOUND)
    include(${CMAKE_CURRENT_LIST_DIR}/Memory/CMakeLists.txt)

    list(APPEND MEMORY_SOURCES
            ${CMAKE_CURRENT_LIST_DIR}/Dependencies/tinyxml2/tinyxml2.h
            )

    list(APPEND MEMORY_HEADERS
            ${CMAKE_CURRENT_LIST_DIR}/Dependencies/tinyxml2/tinyxml2.cpp
            )

    add_executable(
            ${ProjectName}
            ${MEMORY_HEADERS}
            ${MEMORY_SOURCES})

    target_include_directories(
            ${ProjectName}
            PRIVATE
            ${SFML_INCLUDE_DIR}
            ${CMAKE_CURRENT_LIST_DIR}/Dependencies/tinyxml2
            ${CMAKE_CURRENT_LIST_DIR}/Memory/inc/
    )

    target_link_libraries(
            ${ProjectName}
            ${SFML_DEPENDENCIES} ${SFML_LIBRARIES})

    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CHAPTER_NAME})

    install(DIRECTORY ${CHAPTER_DIR}/Media
            DESTINATION ${PROJECT_NAME}
            PATTERN "CMakeLists.txt" EXCLUDE)
    if (UNIX)
        copy_dll(linux)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        copy_dll(msvc)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        copy_dll(mingw)
    endif()


else ()
    message(FATAL "Unable to find SFML.")
endif ()
