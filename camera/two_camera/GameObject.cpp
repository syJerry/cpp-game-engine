//
// Created by TJR on 2025/7/27.
//

#include <iostream>
#include "GameObject.h"


Component::Component_ptr GameObject::AddComponent(const std::string& component_type_name) {
    rttr::type t = rttr::type::get_by_name(component_type_name.c_str());
    if(!t.is_valid())
    {
        std::cerr << component_type_name << "register failed!！"<<std::endl;
    }
    rttr::variant var = t.create();    // 创建实例
    auto component=var.get_value<Component::Component_ptr>();
    if(component == nullptr)
    {
        return nullptr;
    }
    component->set_game_object(shared_from_this());
    if(component_type_instance_map_.find(component_type_name)==component_type_instance_map_.end()){
        std::vector<Component::Component_ptr> component_vec;
        component_vec.push_back(component);
        component_type_instance_map_[component_type_name]=component_vec;
    }else{
        component_type_instance_map_[component_type_name].push_back(component);
    }
    return component;
}

Component::Component_ptr GameObject::GetComponent(const std::string& component_type_name) {
    if(component_type_instance_map_.find(component_type_name) == component_type_instance_map_.end())
    {
        return nullptr;
    }
    if (component_type_instance_map_[component_type_name].empty())
    {
        return nullptr;
    }
    return component_type_instance_map_[component_type_name][0];
}

std::vector<Component::Component_ptr> &GameObject::GetComponents(const std::string& component_type_name) {
    return component_type_instance_map_[component_type_name];
}
