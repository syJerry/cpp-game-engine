//
// Created by TJR on 2025/7/27.
//

#ifndef CPP_GAME_ENGINE_COMPONENT_H
#define CPP_GAME_ENGINE_COMPONENT_H


//#include "GameObject.h"
#include <memory>
#include <utility>

class GameObject;
using GameObject_ptr = std::shared_ptr<GameObject>;

class Component {
public:
    using Component_ptr = std::shared_ptr<Component>;
    virtual ~Component() = default;
    GameObject_ptr game_object(){return game_object_.lock();}
    void set_game_object(const GameObject_ptr& game_object){game_object_=game_object;}
private:
    std::weak_ptr<GameObject> game_object_;
};


#endif //CPP_GAME_ENGINE_COMPONENT_H
