//
// Created by TJR on 2025/7/30.
//

#include "Camera.h"

#include <rttr/registration>

RTTR_REGISTRATION
{
    rttr::registration::class_<Camera>("Camera")
            .constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
            .property("view_mat4",
                      &Camera::view_mat4,
                      static_cast<void (Camera::*)(glm::mat4)>(&Camera::setView))
            .property("projection_mat4",
                      &Camera::projection_mat4,
                      static_cast<void (Camera::*)(glm::mat4)>(&Camera::setProjection));
}


/*
 * 构建一个视图矩阵，模拟摄像机的位置
 * eye：摄像机在世界空间中的位置（vec3）。
    center：摄像机对准的目标点（vec3）。
    up：摄像机的“向上”方向（通常是世界空间的Y轴，vec3(0, 1, 0)）
 * */
void Camera::setView(glm::vec3 eye, glm::vec3 center, glm::vec3 up) {
    view_mat4_ = glm::lookAt(eye,center,up);
}

/*
 * 构建一个透视投影矩阵，模拟人眼或摄像机的视角（近大远小）
 * fov：垂直视野角度（Field of View, FOV），通常用弧度表示。
    aspect：视口的宽高比（width / height）。
    near：近裁剪平面距离（摄像机到最近可见平面的距离）。
    far：远裁剪平面距离（摄像机到最远可见平面的距离）
 * */
void Camera::setProjection(float fov, float aspect, float near, float far) {
    projection_mat4_ = glm::perspective(fov, aspect, near, far);
}

void Camera::Clear() const {
    glClearColor(clear_color_.r,clear_color_.g,clear_color_.b,clear_color_.a);
    glClear(clear_flag_);
}
