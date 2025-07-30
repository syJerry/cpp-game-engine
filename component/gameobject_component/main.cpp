#include "MeshFilter.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "GameObject.h"
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
    auto go=std::make_shared<GameObject>("something");
    if(go == nullptr)
    {
        std::cerr<<"Construct GameObject failed!"<<std::endl;
        exit(-1);
    }
    auto transform=std::dynamic_pointer_cast<Transform>(go->AddComponent("Transform"));
    if(go == nullptr)
    {
        std::cerr<<"Construct transform failed!"<<std::endl;
        exit(-1);
    }
    auto meshfilter=std::dynamic_pointer_cast<MeshFilter>(go->AddComponent("MeshFilter"));
    if(meshfilter == nullptr)
    {
        std::cerr<<"Construct meshfilter failed!"<<std::endl;
        exit(-1);
    }
    auto mesh_renderer=std::dynamic_pointer_cast<MeshRenderer>(go->AddComponent("MeshRenderer"));
    if(mesh_renderer == nullptr)
    {
        std::cerr<<"Construct mesh_renderer failed!"<<std::endl;
        exit(-1);
    }

    auto material=std::dynamic_pointer_cast<Material>(go->AddComponent("Material"));
    if(material == nullptr)
    {
        std::cerr<<"Construct material failed!"<<std::endl;
        exit(-1);
    }
    meshfilter->LoadMesh(R"(C:\Users\TJR\Desktop\cpp-game-engine\res\model\Plane.008.mesh)");
    material->Parse("material/fish_soup.mat");


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


        /*
         * 构建一个视图矩阵，模拟摄像机的位置
         * eye：摄像机在世界空间中的位置（vec3）。
            center：摄像机对准的目标点（vec3）。
            up：摄像机的“向上”方向（通常是世界空间的Y轴，vec3(0, 1, 0)）
         * */
        view = glm::lookAt(glm::vec3(0, 10, 15), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        /*
         * 构建一个透视投影矩阵，模拟人眼或摄像机的视角（近大远小）
         * fov：垂直视野角度（Field of View, FOV），通常用弧度表示。
            aspect：视口的宽高比（width / height）。
            near：近裁剪平面距离（摄像机到最近可见平面的距离）。
            far：远裁剪平面距离（摄像机到最远可见平面的距离）
         * */
        projection = glm::perspective(glm::radians(45.f), ratio, 1.f, 1000.f);
        static float rotate_eulerAngle = 0.f;
        rotate_eulerAngle += 0.01;
        glm::vec3 rotation{0,rotate_eulerAngle,0};
        transform->set_rotation(rotation);
        transform->set_position(glm::vec3(0,0,0));
        transform->set_scale(glm::vec3(2.0f, 2.0f, 2.0f));
        mesh_renderer->setProjection(projection);
        mesh_renderer->setView(view);
        mesh_renderer->Render();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

//    std::cout<<sizeof(glm::vec3)<<" "<<sizeof(glm::vec4 );
    exit(EXIT_SUCCESS);
}