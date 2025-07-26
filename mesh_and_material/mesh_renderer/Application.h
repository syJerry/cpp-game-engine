//
// Created by TJR on 2025/7/24.
//

#ifndef CPP_GAME_ENGINE_APPLICATION_H
#define CPP_GAME_ENGINE_APPLICATION_H


#include <string>

class Application {
public:
    static std::string data_path(){return path;}
private:
    static std::string path;
};


#endif //CPP_GAME_ENGINE_APPLICATION_H
