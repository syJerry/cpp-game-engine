//
// Created by TJR on 2025/7/23.
//

#ifndef CPP_GAME_ENGINE_SHADER_H
#define CPP_GAME_ENGINE_SHADER_H


#include <string>
#include <glad/glad.h>
#include <unordered_map>
#include <memory>



class Shader {
public:
    using Shader_ptr = std::shared_ptr<Shader>;

    void Parse(const std::string& shader_dir, const std::string& shader_name);
    static Shader_ptr Find(const std::string& shader_dir, const std::string& shader_name);
    [[nodiscard]] GLuint getProgram() const{return program;}

protected:
    void CreateGPUProgram(const char* vertex_shader_text, const char* fragment_shader_text);

private:
    std::string shader_name_;
    GLuint program;

    static std::unordered_map<std::string,Shader_ptr> kShaderMap;
};


#endif //CPP_GAME_ENGINE_SHADER_H
