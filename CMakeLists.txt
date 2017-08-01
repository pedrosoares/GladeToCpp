cmake_minimum_required(VERSION 3.7)
project(GladeToCpp)

set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig)
pkg_check_modules(PKG REQUIRED gtkmm-3.0)
include_directories(${PKG_INCLUDE_DIRS})
link_libraries(${PKG_LIBRARIES})
link_directories(${PKG_LIBRARY_DIRS})

find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})
link_libraries(${LIBXML2_LIBRARIES})
link_directories(${LIBXML2_LIBRARY_DIRS})

add_subdirectory("vendor/Tigre")
include_directories("vendor")
link_libraries(String)


set(SOURCE_FILES main.cpp GtkMap.cpp Parse.cpp)
add_executable(GladeToCpp ${SOURCE_FILES})
