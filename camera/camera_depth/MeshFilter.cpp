//
// Created by TJR on 2025/7/23.
//

#include "MeshFilter.h"

#include <fstream>
#include <iostream>
#include <rttr/registration>
#include <rttr/registration>

RTTR_REGISTRATION//注册反射
{
    rttr::registration::class_<MeshFilter>("MeshFilter")
            .constructor<>()(rttr::policy::ctor::as_std_shared_ptr)
            .property("mesh", &MeshFilter::mesh, static_cast<void(MeshFilter::*)(MeshFilter::Mesh::Mesh_ptr)>(nullptr));
}

void MeshFilter::LoadMesh(const std::string& mesh_file_path) {
//读取 Mesh文件头
    std::ifstream input_file_stream(mesh_file_path, std::ios::in | std::ios::binary);
    MeshFileHead mesh_file_head{};
    input_file_stream.read((char *) &mesh_file_head, sizeof(mesh_file_head));
    //读取顶点数据
    auto *vertex_data = (unsigned char *) malloc(mesh_file_head.vertex_num_ * sizeof(Vertex));
    input_file_stream.read((char *) vertex_data, mesh_file_head.vertex_num_ * sizeof(Vertex));
    //读取顶点索引数据
    auto *vertex_index_data = (unsigned short *) malloc(
            mesh_file_head.vertex_index_num_ * sizeof(unsigned short));
    input_file_stream.read((char *) vertex_index_data, mesh_file_head.vertex_index_num_ * sizeof(unsigned short));
    input_file_stream.close();
    mesh_ = std::make_shared<Mesh>();
    mesh_->vertex_num_ = mesh_file_head.vertex_num_;
    mesh_->vertex_index_num_ = mesh_file_head.vertex_index_num_;
    mesh_->vertex_data_ = (Vertex *) vertex_data;
    mesh_->vertex_index_data_ = vertex_index_data;
    std::cout << " vectorx_num_:" << mesh_file_head.vertex_num_ <<
              " vertex_index_num_:" << mesh_file_head.vertex_index_num_ << std::endl;
}


