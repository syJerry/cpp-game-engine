#include "MeshFilter.h"
#include "Material.h"
#include "MeshRenderer.h"
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







int main() {
    init_opengl();
    MeshFilter::MeshFilter_ptr meshfilter = std::make_shared<MeshFilter>();
    meshfilter->LoadMesh(R"(C:\Users\TJR\Desktop\cpp-game-engine\res\model\cube.mesh)");
    Material::Material_ptr material = std::make_shared<Material>();
    material->Parse("material/cude.mat");
    MeshRenderer::MeshRenderer_ptr mesh_renderer = std::make_shared<MeshRenderer>();
    mesh_renderer->SetMeshFilter(meshfilter);
    mesh_renderer->SetMaterial(material);


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

        mesh_renderer->SetMVP(mvp);
        mesh_renderer->Render();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

//    std::cout<<sizeof(glm::vec3)<<" "<<sizeof(glm::vec4 );
    exit(EXIT_SUCCESS);
}