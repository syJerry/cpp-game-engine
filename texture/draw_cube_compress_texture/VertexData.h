//
// Created by TJR on 2025/7/12.
//

#ifndef CPP_GAME_ENGINE_VERTEXDATA_H
#define CPP_GAME_ENGINE_VERTEXDATA_H

#include <glm/glm.hpp>

static const glm::vec3 kPositions[36] = {
        //Front
        glm::vec3(-1.0f, -1.0f, 1.0f),
        glm::vec3(1.0f, -1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(-1.0f, -1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f),
        //back
        glm::vec3(1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f, 1.0f, -1.0f),
        glm::vec3(1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f, 1.0f, -1.0f),
        glm::vec3(1.0f, 1.0f, -1.0f),
        //left
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f, -1.0f, 1.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f),
        glm::vec3(-1.0f, 1.0f, -1.0f),
        //right
        glm::vec3(1.0f, -1.0f, 1.0f),
        glm::vec3(1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f, 1.0f, -1.0f),
        glm::vec3(1.0f, -1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, -1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        //up
        glm::vec3(-1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, -1.0f),
        glm::vec3(-1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, -1.0f),
        glm::vec3(-1.0f, 1.0f, -1.0f),
        //down
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f, -1.0f, 1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f, -1.0f, 1.0f),
        glm::vec3(-1.0f, -1.0f, 1.0f),
};
static const glm::vec4 kColors[36] = {
        //Front
        glm::vec4(1, 0, 0, 1),
        glm::vec4(1, 0, 0, 1),
        glm::vec4(1, 0, 0, 1),
        glm::vec4(1, 0, 0, 1),
        glm::vec4(1, 0, 0, 1),
        glm::vec4(1, 0, 0, 1),
        //back
        glm::vec4(1, 0, 0, 1),
        glm::vec4(1, 0, 0, 1),
        glm::vec4(1, 0, 0, 1),
        glm::vec4(1, 0, 0, 1),
        glm::vec4(1, 0, 0, 1),
        glm::vec4(1, 0, 0, 1),
        //left
        glm::vec4(0, 1, 0, 1),
        glm::vec4(0, 1, 0, 1),
        glm::vec4(0, 1, 0, 1),
        glm::vec4(0, 1, 0, 1),
        glm::vec4(0, 1, 0, 1),
        glm::vec4(0, 1, 0, 1),
        //right
        glm::vec4(0, 1, 0, 1),
        glm::vec4(0, 1, 0, 1),
        glm::vec4(0, 1, 0, 1),
        glm::vec4(0, 1, 0, 1),
        glm::vec4(0, 1, 0, 1),
        glm::vec4(0, 1, 0, 1),
        //up
        glm::vec4(0, 0, 1, 1),
        glm::vec4(0, 0, 1, 1),
        glm::vec4(0, 0, 1, 1),
        glm::vec4(0, 0, 1, 1),
        glm::vec4(0, 0, 1, 1),
        glm::vec4(0, 0, 1, 1),
        //down
        glm::vec4(0, 0, 1, 1),
        glm::vec4(0, 0, 1, 1),
        glm::vec4(0, 0, 1, 1),
        glm::vec4(0, 0, 1, 1),
        glm::vec4(0, 0, 1, 1),
        glm::vec4(0, 0, 1, 1),
};

static const glm::vec2 kUvs[36] =
        {
                //Front
                glm::vec2(0.0f, 0.0f),
                glm::vec2(1.0f, 0.0f),
                glm::vec2(1.0f, 1.0f),
                glm::vec2(0.0f, 0.0f),
                glm::vec2(1.0f, 1.0f),
                glm::vec2(0.0f, 1.0f),
                //back
                glm::vec2(0.0f, 0.0f),
                glm::vec2(1.0f, 0.0f),
                glm::vec2(1.0f, 1.0f),
                glm::vec2(0.0f, 0.0f),
                glm::vec2(1.0f, 1.0f),
                glm::vec2(0.0f, 1.0f),
                //left
                glm::vec2(0.0f, 0.0f),
                glm::vec2(1.0f, 0.0f),
                glm::vec2(1.0f, 1.0f),
                glm::vec2(0.0f, 0.0f),
                glm::vec2(1.0f, 1.0f),
                glm::vec2(0.0f, 1.0f),
                //right
                glm::vec2(0.0f, 0.0f),
                glm::vec2(1.0f, 0.0f),
                glm::vec2(1.0f, 1.0f),
                glm::vec2(0.0f, 0.0f),
                glm::vec2(1.0f, 1.0f),
                glm::vec2(0.0f, 1.0f),
                //up
                glm::vec2(0.0f, 0.0f),
                glm::vec2(1.0f, 0.0f),
                glm::vec2(1.0f, 1.0f),
                glm::vec2(0.0f, 0.0f),
                glm::vec2(1.0f, 1.0f),
                glm::vec2(0.0f, 1.0f),
                //down
                glm::vec2(0.0f, 0.0f),
                glm::vec2(1.0f, 0.0f),
                glm::vec2(1.0f, 1.0f),
                glm::vec2(0.0f, 0.0f),
                glm::vec2(1.0f, 1.0f),
                glm::vec2(0.0f, 1.0f),
        };
#endif //CPP_GAME_ENGINE_VERTEXDATA_H
