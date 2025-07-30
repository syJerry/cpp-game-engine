//
// Created by TJR on 2025/7/30.
//

#ifndef CPP_GAME_ENGINE_CAMERA_H
#define CPP_GAME_ENGINE_CAMERA_H

#include "Component.h"
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

class Camera : public Component{
public:
    Camera():clear_color_(49.f/255,77.f/255,121.f/255,1.f),
            clear_flag_(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT) {
    }
    void setView(glm::vec3 eye,
                 glm::vec3 center,
                 glm::vec3 up);
    void setView(glm::mat4 view_mat4){view_mat4_ = view_mat4;}

    void setProjection(float fov,
                       float aspect,
                       float near,
                       float far);
    void setProjection(glm::mat4 projection_mat4){projection_mat4_ = projection_mat4;};

    glm::mat4 view_mat4() { return view_mat4_; }
    glm::mat4 projection_mat4() { return projection_mat4_; }

    /// 设置清屏颜色
    /// \param r
    /// \param g
    /// \param b
    /// \param a
    void set_clear_color(float r,float g,float b,float a){clear_color_=glm::vec4(r,g,b,a);}
    /// 设置刷帧清屏内容种类
    /// \param clear_flag
    void set_clear_flag(unsigned int clear_flag){clear_flag_=clear_flag;}

    void Clear() const;
private:
    glm::mat4 view_mat4_{};
    glm::mat4 projection_mat4_{};
    glm::vec4 clear_color_;//清屏颜色
    unsigned int clear_flag_;//刷新数据标志

};


#endif //CPP_GAME_ENGINE_CAMERA_H
