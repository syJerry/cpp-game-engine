//
// Created by TJR on 2025/7/23.
//

#ifndef CPP_GAME_ENGINE_MESHFILTER_H
#define CPP_GAME_ENGINE_MESHFILTER_H


#include <glm/glm.hpp>
#include <string>
#include <memory>


class MeshFilter {
public:
    struct Vertex {
        glm::vec3 pos_;
        glm::vec4 color_;
        glm::vec2 uv_;
    };

    struct MeshFileHead {
        char type_[4];
        int vertex_num_;//顶点个数
        int vertex_index_num_;//索引个数
    };
    //Mesh数据
    struct Mesh {
        using Mesh_ptr = std::shared_ptr<Mesh>;
        unsigned short vertex_num_;//顶点个数
        unsigned short vertex_index_num_;//索引个数
        Vertex *vertex_data_;//顶点数据
        unsigned short *vertex_index_data_;//顶点索引数据
    };

public:
    using MeshFilter_ptr = std::shared_ptr<MeshFilter>;

    MeshFilter() = default;

    void LoadMesh(std::string mesh_file_path);

    Mesh::Mesh_ptr mesh() { return mesh_; };//Mesh对象
private:
    Mesh::Mesh_ptr mesh_;
};


#endif //CPP_GAME_ENGINE_MESHFILTER_H
