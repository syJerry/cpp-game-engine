//
// Created by TJR on 2025/7/25.
//

#ifndef CPP_GAME_ENGINE_MESHRENDERER_H
#define CPP_GAME_ENGINE_MESHRENDERER_H


#include "Material.h"
#include "MeshFilter.h"
#include "Component.h"
#include "Transform.h"
#include <utility>


class MeshRenderer : public Component {
public:
    using MeshRenderer_ptr = std::shared_ptr<MeshRenderer>;

    void setView(glm::mat4 view){view_ = view;}
    void setProjection(glm::mat4 projection){projection_ = projection;}


    void Render();

private:
//    Material::Material_ptr material_;
//    MeshFilter::MeshFilter_ptr mesh_filter_;
//    glm::mat4 mvp_;
    glm::mat4  view_, projection_, mvp_;
    GLuint vertex_array_object_{};
    GLuint vertex_buffer_object_{};
    GLuint element_buffer_object_{};
};


#endif //CPP_GAME_ENGINE_MESHRENDERER_H
