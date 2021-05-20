cmake_minimum_required(VERSION 3.1)
project(OcrLiteNcnnWasm)

option(OCR_STATIC "Use Static Librarys For Build" ON)
option(OCR_OPENMP "OcrLite Enable OpenMP" ON)
#set(OCR_STATIC OFF)

set(CMAKE_CXX_STANDARD 11)
add_definitions(-DUNICODE -D_UNICODE)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions("-Wall -g -O0")
else ()
    add_definitions("-Wall")
endif ()

# OpenMP

# NCNN
# include(${CMAKE_CURRENT_SOURCE_DIR}/ncnn-static/NcnnWrapperConfig.cmake)
set(ncnn_DIR "${CMAKE_CURRENT_LIST_DIR}/ncnn-static/webassembly/simd/lib/cmake/ncnn")
set(NCNN_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/ncnn-static/webassembly/simd/include")
include_directories(${NCNN_INCLUDE_DIRS})
find_package(ncnn REQUIRED)
if (ncnn_FOUND)
    message(STATUS "ncnn Found!")
else ()
    message(FATAL_ERROR "ncnn Not Found!")
endif (ncnn_FOUND)

# Wasm
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s FORCE_FILESYSTEM=1 -s INITIAL_MEMORY=256MB -s EXIT_RUNTIME=1")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s FORCE_FILESYSTEM=1 -s INITIAL_MEMORY=256MB -s EXIT_RUNTIME=1")
set(CMAKE_EXECUTBLE_LINKER_FLAGS "${CMAKE_EXECUTBLE_LINKER_FLAGS} -s FORCE_FILESYSTEM=1 -s INITIAL_MEMORY=256MB -s EXIT_RUNTIME=1")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s EXPORTED_FUNCTIONS=['_ocrlite_ncnn'] --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets@.")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXPORTED_FUNCTIONS=['_ocrlite_ncnn'] --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets@.")
set(CMAKE_EXECUTBLE_LINKER_FLAGS "${CMAKE_EXECUTBLE_LINKER_FLAGS} -s EXPORTED_FUNCTIONS=['_ocrlite_ncnn'] --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets@.")

# add_link_options("SHELL:-s ERROR_ON_UNDEFINED_SYMBOLS=0")

# OpenCV
set(OpenCV_DIR "${CMAKE_CURRENT_LIST_DIR}/opencv-static/webassembly/share/OpenCV")
find_package(OpenCV REQUIRED)
if (OpenCV_FOUND)
    message(STATUS "OpenCV Found!")
else ()
    message(FATAL_ERROR "OpenCV Not Found!")
endif (OpenCV_FOUND)

# project include
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# source
file(GLOB OCR_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(OCR_COMPILE_CODE ${OCR_SRC})

add_executable(OcrLiteNcnnWasm ${OCR_COMPILE_CODE})
# add_library(OcrLiteNcnnWasm ${OCR_COMPILE_CODE})
target_link_libraries(OcrLiteNcnnWasm ncnn ${OpenCV_LIBS} ${OpenMP_CXX_LIB_NAMES})

if (OCR_OPENMP)
    target_compile_definitions(OcrLiteNcnnWasm PRIVATE __OPENMP__)
endif ()
