cmake_minimum_required(VERSION 3.28)
project(test_freeimage)

set(CMAKE_CXX_STANDARD 17)

include_directories("D:/Program/FreeImage")
add_executable(${PROJECT_NAME} main.cpp )

link_directories("D:/Program/FreeImage/build/lib")
target_compile_definitions(test_freeimage PRIVATE FREEIMAGE_LIB)
set(EXTRA_LIBS
        "D:/Program/FreeImage/build/lib/libfreeimage.a"
        "D:/Program/FreeImage/build/lib/libjpeg.a"
        "D:/Program/FreeImage/build/lib/libmng.a"
        "D:/Program/FreeImage/build/lib/librawlite.a"
        "D:/Program/FreeImage/build/lib/libtiff.a"
        "D:/Program/FreeImage/build/lib/libopenexr.a"
        "D:/Program/FreeImage/build/lib/libopenjpeg.a"
        "D:/Program/FreeImage/build/lib/libpng.a"
        "D:/Program/FreeImage/build/lib/libz.a"  # 注意是 libz.a，不是 libzlib.a
        ws2_32
)
target_link_libraries(${PROJECT_NAME} ${EXTRA_LIBS})
