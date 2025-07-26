//
// Created by TJR on 2025/7/24.
//

#ifndef CPP_GAME_ENGINE_MATERIAL_H
#define CPP_GAME_ENGINE_MATERIAL_H


#include "Shader.h"
#include "Texture2D.h"
#include <string>
#include <vector>

class Material {
public:
    using Material_ptr = std::shared_ptr<Material>;
    void Parse(const std::string& material_path);
    Shader::Shader_ptr shader(){return shader_;}
    std::vector<std::pair<std::string,Texture2D::Texture2D_ptr>> &
        textures(){return textures_;};
private:
    Shader::Shader_ptr shader_;
    std::vector<std::pair<std::string,Texture2D::Texture2D_ptr>> textures_;
};


#endif //CPP_GAME_ENGINE_MATERIAL_H
