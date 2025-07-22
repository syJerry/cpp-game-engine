cmake_minimum_required(VERSION 3.28)
project(cpp_game_engine)

add_subdirectory(hello_world)
add_subdirectory(draw_polygon/draw_triangle)
add_subdirectory(draw_polygon/draw_quad)
add_subdirectory(draw_polygon/draw_cube)

#add_subdirectory(test/test_freeiamge)
add_subdirectory(texture/load_imge)
add_subdirectory(texture/draw_cube_texture)
add_subdirectory(texture/export_compressed_texture)
add_subdirectory(texture/draw_cube_compress_texture)