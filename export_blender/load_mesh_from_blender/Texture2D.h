//
// Created by TJR on 2025/7/15.
//

#ifndef CPP_GAME_ENGINE_TEXTURE2D_H
#define CPP_GAME_ENGINE_TEXTURE2D_H
#define STB_IMAGE_IMPLEMENTATION

#include <string>
#include <glad/glad.h>
#include <memory>
struct TpcFileHead {
    char type_[3];
    int mipmap_level_;
    int width_;
    int height_;
    int gl_texture_format_;
    int compress_size_;
};

class Texture2D {
public:
    using Texture2D_ptr = std::shared_ptr<Texture2D>;
    static Texture2D_ptr LoadFromFile(std::string &image_file_path);

public:

    int width_;
    int height_;

    GLenum gl_texture_format_;
    GLuint gl_texture_id_;

};


#endif //CPP_GAME_ENGINE_TEXTURE2D_H
