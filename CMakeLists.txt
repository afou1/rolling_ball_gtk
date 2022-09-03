cmake_minimum_required(VERSION 3.16)
set(CMAKE_C_STANDARD 11)


project(rolling_ball_gtk C)

find_package(PkgConfig REQUIRED)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)


add_executable(rolling_ball_gtk main.c game.h game.c)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})


