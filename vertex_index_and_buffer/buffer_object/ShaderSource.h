//
// Created by TJR on 2025/7/12.
//

#ifndef CPP_GAME_ENGINE_SHADERSOURCE_H
#define CPP_GAME_ENGINE_SHADERSOURCE_H

//顶点着色器代码
static const char* vertex_shader_text =R"(
            #version 110
            uniform mat4 u_mvp;
            attribute  vec3 a_pos;
            attribute  vec4 a_color;
            attribute  vec2 a_uv;
            varying vec4 v_color;
            varying vec2 v_uv;
            void main()
            {
                gl_Position = u_mvp * vec4(a_pos, 1.0);
                v_color = a_color;
                v_uv = a_uv;
            }
        )";

//片段着色器代码
static const char* fragment_shader_text = R"(
            #version 110
            uniform sampler2D u_diffuse_texture;
            varying vec4 v_color;
            varying vec2 v_uv;
            void main()
            {
                gl_FragColor = texture2D(u_diffuse_texture,v_uv);
            }
        )";

#endif //CPP_GAME_ENGINE_SHADERSOURCE_H
