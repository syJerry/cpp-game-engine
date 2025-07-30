//
// Created by TJR on 2025/7/27.
//

#include "Transform.h"

#include <rttr/registration>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

RTTR_REGISTRATION//注册反射
{
    rttr::registration::class_<Transform>("Transform")
            .constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
            .property("position", &Transform::position, &Transform::set_position)
            .property("rotation", &Transform::rotation, &Transform::set_rotation)
            .property("scale", &Transform::scale, &Transform::set_scale)
            .property("model",&Transform::model, static_cast<void (Transform::*)(glm::mat4)>(nullptr));
}

glm::mat4 Transform::model() {
    glm::mat4 trans_mat = glm::translate(position_); //不移动顶点坐标;

    glm::mat4 rotation_mat = glm::eulerAngleYXZ(glm::radians(rotation_.y),
                                            glm::radians(rotation_.x),
                                            glm::radians(rotation_.z));
    glm::mat4 scale_mat = glm::scale(scale_); //缩放;
    model_ = trans_mat * scale_mat * rotation_mat;
//    glm::mat4 trans = glm::translate(glm::vec3(0, 0, 0)); //不移动顶点坐标;
//    static float rotate_eulerAngle = 0.f;
//    rotate_eulerAngle += 0.01;
//    glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(rotate_eulerAngle),
//                                            glm::radians(rotate_eulerAngle),
//                                            glm::radians(rotate_eulerAngle));
//    glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f)); //缩放;
//    model_ = trans * scale * rotation;
    return model_;
}
