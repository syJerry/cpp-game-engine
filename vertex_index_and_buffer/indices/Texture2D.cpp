//
// Created by TJR on 2025/7/15.
//
#include "Texture2D.h"
#include <stb_image.h>
#include <iostream>
#include <fstream>
#include <cstdint>

Texture2D *Texture2D::LoadFromFile(std::string &image_file_path) {
    Texture2D *texture2d = new Texture2D();
//    StopWatch stopwatch;
//    stopwatch.start();
    //读取 cpt 压缩纹理文件
    std::ifstream input_file_stream(image_file_path, std::ios::in | std::ios::binary);
    TpcFileHead tcp_file_head;
    input_file_stream.read((char *) &tcp_file_head, sizeof(TpcFileHead));
    unsigned char *data = (unsigned char *) malloc(tcp_file_head.compress_size_);
    input_file_stream.read((char *) data, tcp_file_head.compress_size_);
    input_file_stream.close();
//    stopwatch.stop();
//    std::int64_t decompress_jpg_cost = stopwatch.milliseconds();
    texture2d->gl_texture_format_ = tcp_file_head.gl_texture_format_;
    texture2d->width_ = tcp_file_head.width_;
    texture2d->height_ = tcp_file_head.height_;
    //1. 通知显卡创建纹理对象，返回句柄;
    glGenTextures(1, &(texture2d->gl_texture_id_));
    //2. 将纹理绑定到特定纹理目标;
    glBindTexture(GL_TEXTURE_2D, texture2d->gl_texture_id_);
//    stopwatch.restart();
    {
        //3. 将压缩纹理数据上传到GPU;
        glCompressedTexImage2D(GL_TEXTURE_2D, 0,  texture2d->gl_texture_format_, texture2d->width_, texture2d->height_, 0, tcp_file_head.compress_size_, data);
    }
//    stopwatch.stop();
//    std::int64_t upload_cpt_cost = stopwatch.milliseconds();
    //4. 指定放大，缩小滤波方式，线性滤波，即放大缩小的插值方式;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    delete (data);
    return texture2d;
}
