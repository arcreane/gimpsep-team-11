cmake_minimum_required(VERSION 3.27)
project(gimpsep_team_11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(gimpsep_team_11
        src/src/ImageEditor.cpp
        src/include/ImageEditor.h
        src/src/Menu.cpp
        src/include/Menu.h
        src/src/Image.cpp
        src/include/Image.h
        src/src/ImageManager.cpp
        src/include/ImageManager.h
        src/main.cpp
)

# Link OpenCV libraries
target_link_libraries(gimpsep_team_11 ${OpenCV_LIBS})
