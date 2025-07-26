cmake_minimum_required(VERSION 3.28)
project(test_rttr)

set(CMAKE_CXX_STANDARD 17)

set(RTTR_DIR D:/Program/rttr-0.9.5-src/rttr-0.9.5-win64-gcc14.2/cmake)
find_package(RTTR CONFIG REQUIRED Core)

add_executable(${PROJECT_NAME} main.cpp )
target_link_libraries(${PROJECT_NAME} RTTR::Core)

# 编译后自动复制 DLL
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "D:/Program/rttr-0.9.5-src/rttr-0.9.5-win64-gcc14.2/lib/librttr_core.dll"
        "$<TARGET_FILE_DIR:test_rttr>"
        COMMENT "Copying librttr_core.dll to output directory"
)

