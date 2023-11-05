cmake_minimum_required(VERSION 3.21)
project(sdl_trial)

set(SDL2_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules/SDL2-2.28.4/cmake)
# --------- Setup the Executable output Directory -------------
if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_NAME}/Bin
    CACHE PATH
    "Single Directory for all Executables."
    )
endif()

find_package(SDL2 REQUIRED)

add_executable(sdl_trial_main src/main.cpp)
target_include_directories(sdl_trial_main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/modules/SDL2-2.28.4/include)
target_link_libraries(sdl_trial_main ${SDL2_LIBRARIES})