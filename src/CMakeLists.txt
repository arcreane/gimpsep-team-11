cmake_minimum_required(VERSION 3.0)

set(OpenCV_DIR C:/opencv-4.5.2-mingw/)
find_package( OpenCV REQUIRED )

message(STATUS "OpenCV library status:")
message(STATUS "    versions: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "    source: ${CMAKE_CURRENT_SOURCE_DIR}")

set( SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src )
set( SOURCE # project source files
    ${SRC_DIR}/Image.cpp
    ${SRC_DIR}/ImageEditor.cpp
    ${SRC_DIR}/ImageManager.cpp
    ${SRC_DIR}/Menu.cpp
)

#added include directories
include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${SCR_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

set (CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES  *.cpp)

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${SOURCE}
)
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS})