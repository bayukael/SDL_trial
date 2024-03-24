cmake_minimum_required(VERSION 3.21)
project(sdl_trial)

set(SDL2_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules/SDL2-2.28.4/cmake)
set(SDL2_image_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules/SDL2_image-2.8.2/cmake)
# --------- Setup the Executable output Directory -------------
if(NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${PROJECT_NAME}/Bin
    CACHE PATH
    "Single Directory for all Executables."
    )
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(sdl_trial_main src/main.cpp)
target_include_directories(sdl_trial_main PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/modules/SDL2-2.28.4/include
  ${CMAKE_CURRENT_SOURCE_DIR}/modules/SDL2_image-2.8.2/include
  # ${SDL2_INCLUDE_DIRS}
)
target_link_libraries(sdl_trial_main
  ${SDL2_LIBRARIES}
  SDL2_image::SDL2_image
)