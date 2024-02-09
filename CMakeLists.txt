cmake_minimum_required(VERSION 3.22)

project(DnDTool3.0)

# Find the LSDLE library
find_library(LSDLE_LIB NAMES LSDLE PATHS "C:/Users/on3sn/LSDLE/lib")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

# Add library for DnDTool3.0
add_library(DnDTool3.0
    src/Simulator.cpp

    src/Menus/HitpointManaModificationMenu.cpp
    src/Menus/MainSimMenu.cpp
    src/Menus/SettingsMenu.cpp
    src/Menus/StatsOverlayMenu.cpp
)



# Specify the include directories
target_include_directories(DnDTool3.0
    PUBLIC

        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/DnDTool3.0>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/DnDTool3.0/Menus>
        $<BUILD_INTERFACE:C:/Users/on3sn/LSDLE/include/LSDLE>
        $<BUILD_INTERFACE:C:/Users/on3sn/LSDLE/include/LSDLE/MenuTools>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Find required libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Link required libraries
target_link_libraries(DnDTool3.0
    PUBLIC
        SDL2::SDL2
        SDL2_image
        ${LSDLE_LIB}
)

# Create executable
add_executable(Main main.cpp)

# Link executables to required libraries
target_link_libraries(Main ${LSDLE_LIB})
target_link_libraries(Main DnDTool3.0)