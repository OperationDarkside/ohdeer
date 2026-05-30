cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_C_COMPILER "$ENV{HOME}/gcc-trunk/bin/gcc")
set(CMAKE_CXX_COMPILER "$ENV{HOME}/gcc-trunk/bin/g++")

project(ohdeer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-std=c++26 -freflection -Wall -Wextra)

set(CMAKE_BUILD_TYPE Debug)

find_package(Boost REQUIRED COMPONENTS system thread url)

add_library(boing INTERFACE)
target_include_directories(boing INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/boing
)

add_executable(ohdeer main.cpp
    ohdeer_session.cpp
    component.cpp
    main_view.cpp
    button.cpp
    label.cpp
    event.cpp)
target_link_options(ohdeer PRIVATE -static-libstdc++ -static-libgcc)

target_link_libraries(ohdeer 
    PRIVATE 
    Boost::system 
    Boost::thread
    Boost::url
    Threads::Threads
    boing
)

# Useful compiler warnings
if(MSVC)
    target_compile_options(ohdeer PRIVATE /W4)
else()
    target_compile_options(ohdeer PRIVATE -Wall -Wextra -Wpedantic)
endif()