//
// Created by TJR on 2025/7/15.
//

#ifndef CPP_GAME_ENGINE_TEXTURE2D_H
#define CPP_GAME_ENGINE_TEXTURE2D_H
#define STB_IMAGE_IMPLEMENTATION

#include <string>
#include <glad/glad.h>

class Texture2D {
public:
    static Texture2D* LoadFromFile(std::string& image_file_path);
private:
    int width_;
    int height_;

    GLenum gl_texture_format_;//纹理ID

};


#endif //CPP_GAME_ENGINE_TEXTURE2D_H
