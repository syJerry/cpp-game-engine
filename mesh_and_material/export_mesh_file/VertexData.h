//
// Created by TJR on 2025/7/12.
//

#ifndef CPP_GAME_ENGINE_VERTEXDATA_H
#define CPP_GAME_ENGINE_VERTEXDATA_H

#include <glm/glm.hpp>
#include <vector>
#include <fstream>

//顶点
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
static const Vertex kVertexs[36] ={
        //Front
        glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
        glm::vec3( 1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f),
        glm::vec3( 1.0f,  1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),

        glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
        glm::vec3( 1.0f,  1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),
        glm::vec3(-1.0f,  1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f),

        //back
        glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
        glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f),
        glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),

        glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),
        glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f),

        //left
        glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
        glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),

        glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),
        glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f),

        //right
        glm::vec3(1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
        glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),

        glm::vec3(1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f),

        //up
        glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),

        glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),
        glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f),

        //down
        glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
        glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 0.0f),
        glm::vec3(1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),

        glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 0.0f),
        glm::vec3(1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(1.0f, 1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f,1.0f,1.0f,1.0f),   glm::vec2(0.0f, 1.0f),
};

//去重的顶点Vector
static std::vector<Vertex> kVertexRemoveDumplicateVector;
//顶点索引Vector
static std::vector<unsigned short> kVertexIndexVector;

//顶点去重
static void VertexRemoveDumplicate(){
    for (int i = 0; i < 36; ++i) {
        const Vertex& vertex=kVertexs[i];
        //判断顶点是否存在
        int index=-1;
        for (int j = 0; j < kVertexRemoveDumplicateVector.size(); ++j) {
            if (vertex.pos_==kVertexRemoveDumplicateVector[j].pos_ && vertex.color_==kVertexRemoveDumplicateVector[j].color_ && vertex.uv_==kVertexRemoveDumplicateVector[j].uv_) {
                index=j;
                break;
            }
        }
        if(index<0){
            //没找到就将目标顶点加入kVertexRemoveDumplicateVector，并记录索引为kVertexRemoveDumplicateVector.size()。
            kVertexRemoveDumplicateVector.push_back(vertex);
            kVertexIndexVector.push_back(kVertexRemoveDumplicateVector.size()-1);
        }else{
            //找到了目标顶点，记录索引为kVertexRemoveDumplicateVector的位置。
            kVertexIndexVector.push_back(index);
        }
    }
}


static void ExportMesh(std::string save_path){
    std::ofstream output_file_stream(save_path,std::ios::out | std::ios::binary);
    MeshFileHead mesh_file_head{};
    mesh_file_head.type_[0]='m';
    mesh_file_head.type_[1]='e';
    mesh_file_head.type_[2]='s';
    mesh_file_head.type_[3]='h';
    mesh_file_head.vertex_num_=kVertexRemoveDumplicateVector.size();
    mesh_file_head.vertex_index_num_=kVertexIndexVector.size();
    //写入文件头
    output_file_stream.write((char*)&mesh_file_head, sizeof(mesh_file_head));
    //写入顶点数据
    output_file_stream.write((char*)&kVertexRemoveDumplicateVector[0],kVertexRemoveDumplicateVector.size()*sizeof(Vertex));
    //写入索引数据
    output_file_stream.write((char*)&kVertexIndexVector[0],kVertexIndexVector.size()*sizeof(unsigned short));
    output_file_stream.close();
}
#endif //CPP_GAME_ENGINE_VERTEXDATA_H
