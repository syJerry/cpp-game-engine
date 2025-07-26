//
// Created by TJR on 2025/7/25.
//

#ifndef CPP_GAME_ENGINE_MESHRENDERER_H
#define CPP_GAME_ENGINE_MESHRENDERER_H

#include "Material.h"
#include "MeshFilter.h"

class MeshRenderer {
public:
    using MeshRenderer_ptr = std::shared_ptr<MeshRenderer>;

    void SetMaterial(Material::Material_ptr material) {
        material_=material;
    }
    void SetMeshFilter(MeshFilter::MeshFilter_ptr mesh_filter) {
        mesh_filter_=mesh_filter;
    }
    void SetMVP(glm::mat4 mvp) {
        mvp_=mvp;
    }

    void Render();
private:
    Material::Material_ptr material_;
    MeshFilter::MeshFilter_ptr mesh_filter_;
    glm::mat4 mvp_;

    GLuint vertex_array_object_;
    GLuint vertex_buffer_object_;
    GLuint element_buffer_object_;
};


#endif //CPP_GAME_ENGINE_MESHRENDERER_H
