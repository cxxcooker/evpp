cmake_minimum_required (VERSION 2.8)

project (safe-evpp C CXX)

if (UNIX)
    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Release")
    endif()

    set (CXX_FLAGS
         -g
         -fPIC
         -Wall
		 -D__STDC_FORMAT_MACROS
         -Wno-unused-parameter
         -Wno-unused-function
         -Wunused-variable
         -Wunused-value
         -Wcast-qual
         -Wcast-align
         -Wwrite-strings
         -Wsign-compare
         -Winvalid-pch
         -fms-extensions
         -Wfloat-equal
         -Wextra
         -std=c++11
    )
    include_directories (${PROJECT_SOURCE_DIR}
                         ${PROJECT_SOURCE_DIR}/3rdparty)
else (UNIX)
set (CXX_FLAGS -DWIN32 -D_WIN32 -EHsc)
    set(VcpkgRoot ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET})
    include_directories(${VcpkgRoot}/include
                        ${PROJECT_SOURCE_DIR}
                        ${PROJECT_SOURCE_DIR}/3rdparty/wininclude)

    # On windows, Debug mode
    link_directories(${VcpkgRoot}/debug/lib ${VcpkgRoot}/debug/lib/manual-link)

    # On Windows, Release mode
    # link_directories(${VcpkgRoot}/lib ${VcpkgRoot}/lib/manual-link)
endif (UNIX)

string (REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

if (UNIX)
    SET(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g -ggdb -D_DEBUG -DGOOGLE_STRIP_LOG=0")
    SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -g -ggdb -DNDEBUG -DGOOGLE_STRIP_LOG=1")
    SET(DEPENDENT_LIBRARIES event glog pthread)
else (UNIX)
    SET(DEPENDENT_LIBRARIES event glog)
endif (UNIX)

# Set to true if https support is needed.
# Note that this needs openssl
# SET(HTTPS True)
if (HTTPS)
    list(APPEND DEPENDENT_LIBRARIES ssl crypto event_openssl)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEVPP_HTTP_CLIENT_SUPPORTS_SSL")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEVPP_HTTP_SERVER_SUPPORTS_SSL")
endif (HTTPS)


if (CMAKE_BENCHMARK_TESTING)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DH_BENCHMARK_TESTING=1")
endif (CMAKE_BENCHMARK_TESTING)

set(BOOST_ROOT /home/niuqiang/projects/speech-util/boost_1_72_0_dist/)
include_directories(
        /home/niuqiang/projects/speech-util/boost_1_72_0_dist/include
    /home/niuqiang/projects/speech-util/glog-master-dist/include
    /home/niuqiang/projects/speech-util/libevent-2.1.11-dist/include
    /home/niuqiang/projects/speech-util/gflags-2.2.2-dist/include
)
link_directories(
        /home/niuqiang/projects/speech-util/boost_1_72_0_dist/lib
    /home/niuqiang/projects/speech-util/glog-master-dist/lib
    /home/niuqiang/projects/speech-util/libevent-2.1.11-dist/lib
    /home/niuqiang/projects/speech-util/gflags-2.2.2-dist/lib
)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#set (MACOSX_RPATH ${LIBRARY_OUTPUT_PATH})
set (CMAKE_MACOSX_RPATH 0)

find_program(THRIFT_COMPILER thrift)
find_path(THRIFT_INCLUDE_DIR thrift)
find_library(THRIFT_LIBRARY NAMES thrift)

message (STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
message (STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})
message (STATUS "CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS})
message (STATUS "EXECUTABLE_OUTPUT_PATH " ${EXECUTABLE_OUTPUT_PATH})
message (STATUS "LIBRARY_OUTPUT_PATH " ${LIBRARY_OUTPUT_PATH})
message (STATUS "THRIFT_COMPILER " ${THRIFT_COMPILER})
message (STATUS "THRIFT_INCLUDE_DIR " ${THRIFT_INCLUDE_DIR})
message (STATUS "THRIFT_LIBRARY " ${THRIFT_LIBRARY})

add_subdirectory (evpp)
add_subdirectory (apps)
add_subdirectory (labs)

if (NOT EVPP_VCPKG_BUILD)
    add_subdirectory (examples)
endif ()

set (CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include (utils)
include (packages)

include (CPack)
include (CTest)
