cmake_minimum_required (VERSION 3.8)

cmake_policy (SET CMP0091 NEW)
set (CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project ("PacsTest")

set (DCMTK_SOURCE_DIR "${PROJECT_SOURCE_DIR}/../../DCMTK/dcmtk")
set (DCMTK_BINARY_DIR "${DCMTK_SOURCE_DIR}-msvc19")

list (APPEND DCMTK_INCLUDE_DIRS "${DCMTK_BINARY_DIR}/config/include")
list (APPEND DCMTK_INCLUDE_DIRS "${DCMTK_SOURCE_DIR}/dcmnet/include")
list (APPEND DCMTK_INCLUDE_DIRS "${DCMTK_SOURCE_DIR}/dcmdata/include")
list (APPEND DCMTK_INCLUDE_DIRS "${DCMTK_SOURCE_DIR}/dcmjpeg/include")
list (APPEND DCMTK_INCLUDE_DIRS "${DCMTK_SOURCE_DIR}/dcmjpls/include")
list (APPEND DCMTK_INCLUDE_DIRS "${DCMTK_SOURCE_DIR}/dcmimgle/include")
list (APPEND DCMTK_INCLUDE_DIRS "${DCMTK_SOURCE_DIR}/oflog/include")
list (APPEND DCMTK_INCLUDE_DIRS "${DCMTK_SOURCE_DIR}/ofstd/include")
include_directories ("${DCMTK_INCLUDE_DIRS}")

link_directories ("${DCMTK_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}")

add_subdirectory ("PacsTest")
add_subdirectory ("DicomScu")
