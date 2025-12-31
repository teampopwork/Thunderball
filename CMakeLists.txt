cmake_minimum_required(VERSION 3.18)
project(ThunderballDecomp)

math(EXPR bits "8 * ${CMAKE_SIZEOF_VOID_P}")
message(STATUS "Building ${bits}-bit Peggle")
if (NOT bits EQUAL 32)
  message(WARNING "Only 32-bit executables are supported")
endif()

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    message(STATUS "MSVC Version: ${MSVC_VERSION}")
    if (MSVC_VERSION EQUAL 1400)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GF /EHsc /GS /Gy /GR /W3 /c /Wp64 /Z7 /TP")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Og /Ob1 /Oi /Ot /Oy-")
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
    else()
        add_definitions(-DNOMINMAX)

        if(CMAKE_CXX_FLAGS MATCHES "sanitize=address")
            message(STATUS "ASAN detected, switching to non-debug runtime library.")
            set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
        endif()
    endif()

    add_definitions(-D_USE_MATH_DEFINES)
endif()

add_subdirectory(source/ImageLib)
add_subdirectory(source/PakLib)
add_subdirectory(source/SexyAppFramework)
set(SEXYAPP_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/source)
add_subdirectory(source/Thunderball)

include(cmake/reccmp.cmake)
reccmp_add_target(popcapgame1 ID POPCAPGAME1)
reccmp_configure()