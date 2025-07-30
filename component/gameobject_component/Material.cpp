//
// Created by TJR on 2025/7/24.
//

#include "Material.h"
#include "Application.h"
#include "Texture2D.h"
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <iostream>
#include <rttr/registration>

RTTR_REGISTRATION
{
    rttr::registration::class_<Material>("Material")
            .constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
            .property("shader",&Material::shader,static_cast<void (Material::*)(Shader::Shader_ptr)>(nullptr));
}

void Material::Parse(const std::string &material_path) {
    //解析xml
    rapidxml::file<> xml_file((Application::data_path() + material_path).c_str());
    if (xml_file.size() == 0) {
        std::cerr << "failed open " << material_path << std::endl;
    }
    rapidxml::xml_document<> document;
    document.parse<0>(xml_file.data());
    //根节点
    rapidxml::xml_node<> *material_node = document.first_node("material");
    if (material_node == nullptr) {
        return;
    }
    rapidxml::xml_attribute<> *material_shader_attribute = material_node->first_attribute("shader");
    if (material_shader_attribute == nullptr) {
        return;
    }

    shader_ = Shader::Find(Application::data_path() + material_shader_attribute->value());
    //解析Texture
    rapidxml::xml_node<> *material_texture_node = material_node->first_node("texture");
    while (material_texture_node != nullptr) {
        rapidxml::xml_attribute<> *texture_name_attribute = material_texture_node->first_attribute("name");
        if (texture_name_attribute == nullptr) {
            std::cerr << "Material name not found!"<<std::endl;
            return;
        }
        rapidxml::xml_attribute<> *texture_image_attribute = material_texture_node->first_attribute("image");
        if (texture_image_attribute == nullptr) {
            std::cerr << "Material image not found!"<<std::endl;
            return;
        }
        std::string shader_property_name = texture_name_attribute->value();
        std::string image_path = Application::data_path() + texture_image_attribute->value();
//        std::cout << image_path << std::endl;
        textures_.push_back(std::make_pair(texture_name_attribute->value(), Texture2D::LoadFromFile(image_path)));
        material_texture_node = material_texture_node->next_sibling("texture");
    }
}
