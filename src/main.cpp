#include "GLApp.hpp"
#include <iostream>

int main (){

    try {

        GLApp app(1920, 1080, "Vox");

        app.render();
    }catch (const std::exception &err){
        std::cerr << err.what() << std::endl;
    }
    return 0;
}