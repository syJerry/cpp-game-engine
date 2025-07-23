#include "MeshFilter.h"
#include "Shader.h"
#include "Texture2D.h"
#include <iostream>
#include <glad/glad.h>
//#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/transform2.hpp>
#include<glm/gtx/euler_angles.hpp>

#include <cstdlib>
#include <cstdio>


using namespace std;

static void error_callback(int err, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow *window;
GLint mvp_location, vpos_location, vcol_location, u_diffuse_texture_location, a_uv_location;
GLuint kVBO, kEBO, kVAO;
MeshFilter meshfilter;

/// 初始化OpenGL
void init_opengl() {
    cout << "init opengl" << endl;

    //设置错误回调
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //创建窗口
    window = glfwCreateWindow(960, 640, "Simple example", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(0);//开启 垂直同步（VSync），限制帧率与显示器刷新率同步
}


Texture2D *CreateTexture(std::string image_file_path) {
    Texture2D *texture2d = Texture2D::LoadFromFile(image_file_path);
    return texture2d;
}

void GeneratorVertexArrayObject() {
    glGenVertexArrays(1, &kVAO);
}

void GeneratorBufferObject() {
    //在GPU上创建缓冲区对象
    glGenBuffers(1, &kVBO);
    //将缓冲区对象指定为顶点缓冲区对象
    glBindBuffer(GL_ARRAY_BUFFER, kVBO);
    //上传顶点数据到缓冲区对象
    glBufferData(GL_ARRAY_BUFFER, meshfilter.mesh()->vertex_num_ * sizeof(Vertex),
                 meshfilter.mesh()->vertex_data_, GL_STATIC_DRAW);
    //在GPU上创建缓冲区对象
    glGenBuffers(1, &kEBO);
    //将缓冲区对象指定为顶点索引缓冲区对象
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO);
    //上传顶点索引数据到缓冲区对象
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 meshfilter.mesh()->vertex_index_num_ * sizeof(unsigned short),
                 meshfilter.mesh()->vertex_index_data_,
                 GL_STATIC_DRAW);

    glBindVertexArray(kVAO);

    //指定当前使用的VBO
    glBindBuffer(GL_ARRAY_BUFFER, kVBO);
    {
        //将Shader变量(a_pos)和顶点坐标VBO句柄进行关联，最后的0表示数据偏移量。
        glVertexAttribPointer(vpos_location, 3, GL_FLOAT, false, sizeof(Vertex), 0);
        //启用顶点Shader属性(a_color)，指定与顶点颜色数据进行关联
        glVertexAttribPointer(vcol_location, 4, GL_FLOAT, false, sizeof(Vertex), (void *) (sizeof(float) * 3));
        //将Shader变量(a_uv)和顶点UV坐标VBO句柄进行关联，最后的0表示数据偏移量。
        glVertexAttribPointer(a_uv_location, 2, GL_FLOAT, false, sizeof(Vertex), (void *) (sizeof(float) * (3 + 4)));

        glEnableVertexAttribArray(vpos_location);
        glEnableVertexAttribArray(vcol_location);
        glEnableVertexAttribArray(a_uv_location);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, kEBO);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

int main() {
    meshfilter.LoadMesh(R"(C:\Users\TJR\Desktop\cpp-game-engine\res\model\cube.mesh)");
    init_opengl();
    auto texture2d = CreateTexture(R"(C:\Users\TJR\Desktop\cpp-game-engine\res\image\input_compressed.cpt)");
    Shader shader;
    shader.Parse(R"(C:\Users\TJR\Desktop\cpp-game-engine\res\shader)","Unlit");
    //获取shader属性ID
    mvp_location = glGetUniformLocation(shader.getProgram(), "u_mvp");
    vpos_location = glGetAttribLocation(shader.getProgram(), "a_pos");
    vcol_location = glGetAttribLocation(shader.getProgram(), "a_color");
    a_uv_location = glGetAttribLocation(shader.getProgram(), "a_uv");
    u_diffuse_texture_location = glGetUniformLocation(shader.getProgram(), "u_diffuse_texture");

    GeneratorVertexArrayObject();
    GeneratorBufferObject();

    while (!glfwWindowShouldClose(window)) {
        float ratio;
        int width, height;
        glm::mat4 model, view, projection, mvp;

        //获取画面宽高
        glfwGetFramebufferSize(window, &width, &height);
        ratio = (float) width / (float) height;

        //设置渲染区域
        glViewport(0, 0, width, height);
        glClearColor(49.f / 255, 77.f / 255, 121.f / 255, 1.f);
        glEnable(GL_DEPTH_TEST); //绘制立方体需要添加
        glEnable(GL_CULL_FACE); ////开启背面剔除
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //坐标系变换
        glm::mat4 trans = glm::translate(glm::vec3(0, 0, 0)); //不移动顶点坐标;
        static float rotate_eulerAngle = 0.f;
        rotate_eulerAngle += 0.01;
        glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(rotate_eulerAngle),
                                                glm::radians(rotate_eulerAngle),
                                                glm::radians(rotate_eulerAngle));
        glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f)); //缩放;
        model = trans * scale * rotation;

        /*
         * 构建一个视图矩阵，模拟摄像机的位置
         * eye：摄像机在世界空间中的位置（vec3）。
            center：摄像机对准的目标点（vec3）。
            up：摄像机的“向上”方向（通常是世界空间的Y轴，vec3(0, 1, 0)）
         * */
        view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        /*
         * 构建一个透视投影矩阵，模拟人眼或摄像机的视角（近大远小）
         * fov：垂直视野角度（Field of View, FOV），通常用弧度表示。
            aspect：视口的宽高比（width / height）。
            near：近裁剪平面距离（摄像机到最近可见平面的距离）。
            far：远裁剪平面距离（摄像机到最远可见平面的距离）
         * */
        projection = glm::perspective(glm::radians(45.f), ratio, 1.f, 1000.f);

        mvp = projection * view * model;

        //指定GPU程序(就是指定顶点着色器、片段着色器)
        glUseProgram(shader.getProgram());
        {

            //上传mvp矩阵
            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);

            //贴图设置
            //激活纹理单元0
            glActiveTexture(GL_TEXTURE0);
            //将加载的图片纹理句柄，绑定到纹理单元0的Texture2D上。
            glBindTexture(GL_TEXTURE_2D, texture2d->gl_texture_id_);
            //设置Shader程序从纹理单元0读取颜色数据
            glUniform1i(u_diffuse_texture_location, 0);

            glBindVertexArray(kVAO);
            {
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);//使用顶点索引进行绘制，最后的0表示数据偏移量。
            }
            glBindVertexArray(0);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

//    std::cout<<sizeof(glm::vec3)<<" "<<sizeof(glm::vec4 );
    exit(EXIT_SUCCESS);
}