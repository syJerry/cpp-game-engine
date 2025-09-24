#include "MeshFilter.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "GameObject.h"
#include "Camera.h"
#include <iostream>
#include <glad/glad.h>
//#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <cstdlib>
#include <cstdio>


using namespace std;


#define CHECK(ptr) \
        if(ptr == nullptr) \
        { \
            std::cerr<<"Construct failed in "<<__LINE__<< std::endl; \
            exit(-1); \
        }           \


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
    glfwSwapInterval(1);//开启 垂直同步（VSync），限制帧率与显示器刷新率同步
}


int main() {
    init_opengl();
    auto go = std::make_shared<GameObject>("something");
    CHECK(go)
    auto go_camera = std::make_shared<GameObject>("go_camera");
    CHECK(go_camera)
    auto go_camera_2 = std::make_shared<GameObject>("go_camera_2");
    CHECK(go_camera_2)

    auto transform = std::dynamic_pointer_cast<Transform>(go->AddComponent("Transform"));
    CHECK(transform)
    auto meshfilter = std::dynamic_pointer_cast<MeshFilter>(go->AddComponent("MeshFilter"));
    CHECK(meshfilter)
    auto mesh_renderer = std::dynamic_pointer_cast<MeshRenderer>(go->AddComponent("MeshRenderer"));
    CHECK(mesh_renderer)
    auto material = std::dynamic_pointer_cast<Material>(go->AddComponent("Material"));
    CHECK(material)

    auto camera = std::dynamic_pointer_cast<Camera>(go_camera->AddComponent("Camera"));
    CHECK(camera)
    Camera::addCamera(camera);
    auto camera_2 = std::dynamic_pointer_cast<Camera>(go_camera_2->AddComponent("Camera"));
    CHECK(camera_2)
    Camera::addCamera(camera_2);
    camera_2->set_clear_flag(GL_DEPTH_BUFFER_BIT);

    meshfilter->LoadMesh(R"(C:\Users\TJR\Desktop\cpp-game-engine\res\model\Plane.008.mesh)");
    material->Parse("material/fish_soup.mat");
    while (!glfwWindowShouldClose(window)) {
        float ratio;
        int width, height;
        //获取画面宽高
        glfwGetFramebufferSize(window, &width, &height);
        ratio = (float) width / (float) height;
        //设置渲染区域
        glViewport(0, 0, width, height);
        glEnable(GL_DEPTH_TEST); //绘制立方体需要添加
        glEnable(GL_CULL_FACE); ////开启背面剔除
//        camera->Clear();

        camera->setView(glm::vec3(0, 10, 15),
                        glm::vec3(0, 0, 0),
                        glm::vec3(0, 1, 0));
        camera->setProjection(glm::radians(45.f), ratio, 1.f, 1000.f);
        camera_2->setView(glm::vec3(0, 10, 15),
                        glm::vec3(0, 0, 5),
                        glm::vec3(0, 1, 0));
        camera_2->setProjection(glm::radians(45.f), ratio, 1.f, 1000.f);
        static float rotate_eulerAngle = 0.f;
        rotate_eulerAngle += 1;
        glm::vec3 rotation{0, rotate_eulerAngle, 0};
        transform->set_rotation(rotation);
        transform->set_position(glm::vec3(0, 0, 0));
        transform->set_scale(glm::vec3(2.0f, 2.0f, 2.0f));
//        mesh_renderer->setProjection(camera->projection_mat4());
//        mesh_renderer->setView(camera->view_mat4());
//        mesh_renderer->Render();
        Camera::foreachCamera([&](){
            mesh_renderer->Render();
        });


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);
}