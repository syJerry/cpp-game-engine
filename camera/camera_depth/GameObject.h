//
// Created by TJR on 2025/7/27.
//

#ifndef CPP_GAME_ENGINE_GAMEOBJECT_H
#define CPP_GAME_ENGINE_GAMEOBJECT_H

#include "Component.h"
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>
#include <rttr/type>

class GameObject : public std::enable_shared_from_this<GameObject> {
public:
    using GameObject_ptr = std::shared_ptr<GameObject>;
    GameObject(): layer_(0x01){};
    explicit GameObject(std::string name):layer_(0x01){ SetName(std::move(name));}
    void SetName(std::string name){name_ = std::move(name);}
    unsigned char Layer() const
    {
        return layer_;
    }

    template<class T>
    std::shared_ptr<T> AddComponent() {
        Component::Component_ptr component = std::make_shared<Component>();
        rttr::type t=rttr::type::get(*component);
        std::string component_type_name=t.get_name();
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

    Component::Component_ptr AddComponent(const std::string& component_type_name);

    Component::Component_ptr GetComponent(const std::string& component_type_name);
    std::vector<Component::Component_ptr>& GetComponents(const std::string& component_type_name);

private:
    std::string name_;
    std::unordered_map<std::string, std::vector<Component::Component_ptr>>
            component_type_instance_map_{};
    unsigned char layer_;
};


#endif //CPP_GAME_ENGINE_GAMEOBJECT_H
