//
// Created by TJR on 2025/7/27.
//

#ifndef CPP_GAME_ENGINE_TRANSFORM_H
#define CPP_GAME_ENGINE_TRANSFORM_H

#include "Component.h"
#include <glm/glm.hpp>
class Transform : public Component{
public:
    glm::vec3 position(){return position_;}
    glm::vec3 rotation(){return rotation_;}
    glm::vec3 scale(){return scale_;}
    glm::mat4 model();

    void set_position(glm::vec3 position){position_=position;}
    void set_rotation(glm::vec3 rotation){rotation_=rotation;}
    void set_scale(glm::vec3 scale){scale_=scale;}
private:
    glm::vec3 position_;
    glm::vec3 rotation_;
    glm::vec3 scale_;
    glm::mat4 model_;
};


#endif //CPP_GAME_ENGINE_TRANSFORM_H
