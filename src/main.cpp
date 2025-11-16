#include "GLApp.hpp"
#include <iostream>

int main (){

    try {

        GLApp app(800, 800, "Vox");

        app.render();
    }catch (const std::exception &err){
        std::cerr << err.what() << std::endl;
    }
    return 0;
}