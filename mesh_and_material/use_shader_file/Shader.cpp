//
// Created by TJR on 2025/7/23.
//

#include <fstream>
#include <iostream>

#include "Shader.h"

std::unordered_map<std::string, Shader::Shader_ptr> Shader::kShaderMap;

void Shader::Parse(const std::string& shader_dir, const std::string& shader_name) {
    shader_name_ = shader_name;
    //组装完整文件路径
    std::string vertex_shader_file_path = shader_dir +"\\"+ shader_name + ".vs";
    std::string fragment_shader_file_path = shader_dir +"\\"+ shader_name + ".fs";
    //读取顶点Shader代码
    std::ifstream vertex_shader_input_file_stream(vertex_shader_file_path);
    if(!vertex_shader_input_file_stream.is_open())
    {
        std::cerr<< "Failed open "<<vertex_shader_file_path<<std::endl;
        exit(-1);
    }
    std::string vertex_shader_source((std::istreambuf_iterator<char>(vertex_shader_input_file_stream)),
                                     std::istreambuf_iterator<char>());
    //读取片段Shader代码
    std::ifstream fragment_shader_input_file_stream(fragment_shader_file_path);
    if(!fragment_shader_input_file_stream.is_open())
    {
        std::cerr<< "Failed open "<<fragment_shader_file_path<<std::endl;
    }
    std::string fragment_shader_source((std::istreambuf_iterator<char>(fragment_shader_input_file_stream)),
                                       std::istreambuf_iterator<char>());
    CreateGPUProgram(vertex_shader_source.c_str(), fragment_shader_source.c_str());
}

void Shader::CreateGPUProgram(const char *vertex_shader_text, const char *fragment_shader_text) {
    //创建顶点Shader
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    //指定Shader源码
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    //编译Shader
    glCompileShader(vertex_shader);

    //创建片段Shader
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    //指定Shader源码
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    //编译Shader
    glCompileShader(fragment_shader);

    //创建GPU程序
    program = glCreateProgram();
    //附加Shader
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    //Link
    glLinkProgram(program);
}

Shader::Shader_ptr Shader::Find(const std::string& shader_dir, const std::string& shader_name) {
    auto iter=kShaderMap.find(shader_name);
    if(iter!=kShaderMap.end()) {
        return iter->second;
    }
    Shader_ptr shader=std::make_shared<Shader>();
    shader->Parse(shader_dir,shader_name);
    kShaderMap.insert(std::pair<std::string,Shader_ptr>(shader_dir+shader_name,shader));
    return shader;
}


