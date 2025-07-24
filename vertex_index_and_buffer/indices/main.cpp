#include "VertexData.h"
#include "ShaderSource.h"
#include "Texture2D.h"

#include <iostream>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/transform2.hpp>
#include<glm/gtx/euler_angles.hpp>

#include <cstdlib>
#include <cstdio>



using namespace std;

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

GLFWwindow* window;
GLuint vertex_shader, fragment_shader, program;
GLint mvp_location, vpos_location, vcol_location,u_diffuse_texture_location,a_uv_location;;

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

/// 编译、链接Shader
void compile_shader()
{
    //创建顶点Shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    //指定Shader源码
    glShaderSource(vertex_shader, 1, &vertex_shader_text, nullptr);
    //编译Shader
    glCompileShader(vertex_shader);
    //获取编译结果
    GLint compile_status=GL_FALSE;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(vertex_shader, sizeof(message), nullptr, message);
        cout<<"compile vs error:"<<message<<endl;
    }

    //创建片段Shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    //指定Shader源码
    glShaderSource(fragment_shader, 1, &fragment_shader_text, nullptr);
    //编译Shader
    glCompileShader(fragment_shader);
    //获取编译结果
    compile_status=GL_FALSE;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLchar message[256];
        glGetShaderInfoLog(fragment_shader, sizeof(message), nullptr, message);
        cout<<"compile fs error:"<<message<<endl;
    }


    //创建GPU程序
    program = glCreateProgram();
    //附加Shader
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    //Link
    glLinkProgram(program);
    //获取编译结果
    GLint link_status=GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE)
    {
        GLchar message[256];
        glGetProgramInfoLog(program, sizeof(message), nullptr, message);
        cout<<"link error:"<<message<<endl;
    }
}
Texture2D* CreateTexture(std::string image_file_path)
{
    Texture2D* texture2d=Texture2D::LoadFromFile(image_file_path);
    return texture2d;
}
int main()
{
    VertexRemoveDumplicate();
    std::cout<<kVertexRemoveDumplicateVector.size()<<std::endl;
    init_opengl();
    auto texture2d = CreateTexture("C:\\Users\\TJR\\Desktop\\cpp-game-engine\\res\\images\\input_compressed.cpt");
    compile_shader();

    //获取shader属性ID
    mvp_location = glGetUniformLocation(program, "u_mvp");
    vpos_location = glGetAttribLocation(program, "a_pos");
    vcol_location = glGetAttribLocation(program, "a_color");
    a_uv_location = glGetAttribLocation(program, "a_uv");
    u_diffuse_texture_location= glGetUniformLocation(program, "u_diffuse_texture");

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glm::mat4 model,view, projection, mvp;

        //获取画面宽高
        glfwGetFramebufferSize(window, &width, &height);
        ratio = (float)width / (float) height;

        //设置渲染区域
        glViewport(0, 0, width, height);
        glClearColor(49.f/255,77.f/255,121.f/255,1.f);
        glEnable(GL_DEPTH_TEST); //绘制立方体需要添加
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        //坐标系变换
        glm::mat4 trans = glm::translate(glm::vec3(0,0,0)); //不移动顶点坐标;
        static float rotate_eulerAngle=0.f;
        rotate_eulerAngle+=0.01;
        glm::mat4 rotation = glm::eulerAngleYXZ(glm::radians(rotate_eulerAngle),
                                                glm::radians(rotate_eulerAngle),
                                                glm::radians(rotate_eulerAngle));
        glm::mat4 scale = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f)); //缩放;
        model = trans*scale*rotation;

        /*
         * 构建一个视图矩阵，模拟摄像机的位置
         * eye：摄像机在世界空间中的位置（vec3）。
            center：摄像机对准的目标点（vec3）。
            up：摄像机的“向上”方向（通常是世界空间的Y轴，vec3(0, 1, 0)）
         * */
        view = glm::lookAt(glm::vec3(0, 0, 10), glm::vec3(0, 0,0), glm::vec3(0, 1, 0));

        /*
         * 构建一个透视投影矩阵，模拟人眼或摄像机的视角（近大远小）
         * fov：垂直视野角度（Field of View, FOV），通常用弧度表示。
            aspect：视口的宽高比（width / height）。
            near：近裁剪平面距离（摄像机到最近可见平面的距离）。
            far：远裁剪平面距离（摄像机到最远可见平面的距离）
         * */
        projection=glm::perspective(glm::radians(45.f),ratio,1.f,1000.f);

        mvp=projection*view*model;

        //指定GPU程序(就是指定顶点着色器、片段着色器)
        glUseProgram(program);
        {
            //启用顶点Shader属性(a_pos)，指定与顶点坐标数据进行关联
            glEnableVertexAttribArray(vpos_location);
            glVertexAttribPointer(vpos_location, 3, GL_FLOAT,
                                  false, sizeof(Vertex),
                                  &kVertexRemoveDumplicateVector[0]);

            //启用顶点Shader属性(a_color)，指定与顶点颜色数据进行关联
            glEnableVertexAttribArray(vcol_location);
            glVertexAttribPointer(vcol_location, 3, GL_FLOAT,
                                  false, sizeof(Vertex),
                                  ((char*)&kVertexRemoveDumplicateVector[0])+sizeof(glm::vec3));

            //启用顶点Shader属性(a_uv)，指定与顶点UV数据进行关联
            glEnableVertexAttribArray(a_uv_location);
            glVertexAttribPointer(a_uv_location, 2, GL_FLOAT,
                                  false, sizeof(Vertex),
                                  ((char*)&kVertexRemoveDumplicateVector[0])+sizeof(glm::vec3)+sizeof(glm::vec4));
            //上传mvp矩阵
            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);

            //贴图设置
            //激活纹理单元0
            glActiveTexture(GL_TEXTURE0);
            //将加载的图片纹理句柄，绑定到纹理单元0的Texture2D上。
            glBindTexture(GL_TEXTURE_2D,texture2d->gl_texture_id_);
            //设置Shader程序从纹理单元0读取颜色数据
            glUniform1i(u_diffuse_texture_location,0);
            //void glDrawArrays(GLenum mode,GLint first,GLsizei count);
            glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_SHORT,
                           (float*)(&kVertexIndexVector[0]));
//            glDrawArrays(GL_TRIANGLES, 0, 6*6);//表示从第0个顶点开始画，总共画6个面，每个面6个顶点。
//            //上传顶点数据并进行绘制
//            glDrawArrays(GL_TRIANGLES, 0, 6*6);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

//    std::cout<<sizeof(glm::vec3)<<" "<<sizeof(glm::vec4 );
    exit(EXIT_SUCCESS);
}