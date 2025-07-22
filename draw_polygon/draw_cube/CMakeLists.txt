cmake_minimum_required(VERSION 3.28)
project(draw_cube)

set(CMAKE_CXX_STANDARD 17)

include_directories(D:\\Program\\glfw-3.4.bin.WIN64\\include
                    D:\\Program\\glad\\include
                    D:\\Program\\glm-0.9.9.8\\)

set(GLAD_SRC "D:/Program/glad/src/glad.c")
add_executable(${PROJECT_NAME} main.cpp ${GLAD_SRC})

target_link_libraries(${PROJECT_NAME} D:\\Program\\glfw-3.4.bin.WIN64\\lib-mingw-w64\\libglfw3.a)
