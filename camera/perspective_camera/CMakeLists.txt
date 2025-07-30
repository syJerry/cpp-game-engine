cmake_minimum_required(VERSION 3.28)
project(perspective_camera)

set(CMAKE_CXX_STANDARD 17)
set(RTTR_DIR D:/Program/rttr-0.9.5-src/rttr-0.9.5-win64-gcc14.2/cmake)
find_package(RTTR CONFIG REQUIRED Core)

include_directories(D:\\Program\\glfw-3.4.bin.WIN64\\include
        D:\\Program\\glad\\include
        D:\\Program\\glm-0.9.9.8
        D:\\Program\\stb
        D:\\Program\\rapidxml-1.13)

set(GLAD_SRC "D:/Program/glad/src/glad.c"
        Texture2D.cpp
        Texture2D.h
        MeshFilter.cpp
        MeshFilter.h
        Shader.cpp
        Shader.h
        Material.cpp
        Material.h
        Application.cpp
        Application.h
        MeshRenderer.cpp
        MeshRenderer.h
        GameObject.cpp
        GameObject.h
        Component.cpp
        Component.h
        Transform.cpp
        Transform.h
        Camera.cpp
        Camera.h)
add_executable(${PROJECT_NAME} main.cpp ${GLAD_SRC})

target_link_libraries(${PROJECT_NAME} D:\\Program\\glfw-3.4.bin.WIN64\\lib-mingw-w64\\libglfw3.a)
target_link_libraries(${PROJECT_NAME} RTTR::Core)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "D:/Program/rttr-0.9.5-src/rttr-0.9.5-win64-gcc14.2/lib/librttr_core.dll"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        COMMENT "Copying librttr_core.dll to output directory"
)