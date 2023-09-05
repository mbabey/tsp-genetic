cmake_minimum_required(VERSION 3.20)
project(lab1template)

set(SANITIZE TRUE) # Whether sanitizers will run.

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_STANDARD 20)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SOURCE_LIST
        ${SOURCE_DIR}/City.cpp
        ${SOURCE_DIR}/main.cpp
        ${SOURCE_DIR}/Population.cpp
        ${SOURCE_DIR}/GeneticTSM.cpp
        ${SOURCE_DIR}/Tour.cpp
        )
set(HEADER_LIST
        ${INCLUDE_DIR}/City.hpp
        ${INCLUDE_DIR}/Population.hpp
        ${INCLUDE_DIR}/settings.hpp
        ${INCLUDE_DIR}/GeneticTSM.hpp
        ${INCLUDE_DIR}/Tour.hpp
        )

if (${SANITIZE})
    add_compile_options("-fsanitize=address")
    add_compile_options("-fsanitize=undefined")
    add_compile_options("-fsanitize-address-use-after-scope")
    add_compile_options("-fstack-protector-all")
    add_compile_options("-fdelete-null-pointer-checks")
    add_compile_options("-fno-omit-frame-pointer")

    if (NOT APPLE)
        add_compile_options("-fsanitize=leak")
    endif ()

    add_link_options("-fsanitize=address")
    add_link_options("-fsanitize=bounds")
endif ()


add_executable(assignment2template ${SOURCE_LIST})
