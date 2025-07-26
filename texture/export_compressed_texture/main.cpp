#include "Texture2D.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow* window;
/// 初始化OpenGL
void init_opengl()
{
    cout<<"init opengl"<<endl;

    //设置错误回调
    glfwSetErrorCallback(nullptr);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    //创建窗口
    window = glfwCreateWindow(960, 640, "Simple example", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(0);//开启 垂直同步（VSync），限制帧率与显示器刷新率同步


}
int main()
{
    init_opengl();
    //从GPU中，将显存中保存的压缩好的纹理数据，下载到内存，并保存到硬盘。
    std::string src_image_file_path("C:\\Users\\TJR\\Desktop\\cpp-game-engine\\res\\images\\Diffuse_FishSoup_Pot_1.jpg");
    std::string cpt_file_path("C:\\Users\\TJR\\Desktop\\cpp-game-engine\\res\\images\\Diffuse_FishSoup_Pot_1.cpt");
    Texture2D::CompressImageFile(src_image_file_path,cpt_file_path);

    return 0;
}