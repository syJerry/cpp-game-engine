//
// Created by TJR on 2025/7/23.
//

#ifndef CPP_GAME_ENGINE_MESHFILTER_H
#define CPP_GAME_ENGINE_MESHFILTER_H


#include <glm/glm.hpp>
#include <string>

struct  Vertex
{
    glm::vec3 pos_;
    glm::vec4 color_;
    glm::vec2 uv_;
};

struct MeshFileHead{
    char type_[4];
    int vertex_num_;//顶点个数
    int vertex_index_num_;//索引个数
};

//Mesh数据
struct Mesh{
    unsigned short vertex_num_;//顶点个数
    unsigned short vertex_index_num_;//索引个数
    Vertex* vertex_data_;//顶点数据
    unsigned short* vertex_index_data_;//顶点索引数据
};

class MeshFilter {
public:
    MeshFilter() = default;
    ~MeshFilter();
    void LoadMesh(std::string mesh_file_path);
    Mesh* mesh(){return mesh_;};//Mesh对象
private:
    Mesh* mesh_;
};


#endif //CPP_GAME_ENGINE_MESHFILTER_H
