#include "GLApp.hpp"



GLApp::GLApp(const int width, const int height,  const std::string &name) : _width(width),_height(height),_name(name)
{
    init();
}

void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods){
    (void)mods;
    (void)scancode;

    WorldManager *worldManager = static_cast<WorldManager*>(glfwGetWindowUserPointer(window));

    Camera &camera = worldManager->getCamera();

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key == GLFW_KEY_Q && (action == GLFW_PRESS || action == GLFW_REPEAT))
        camera.moveFlags[0] = -.05;
    if (key == GLFW_KEY_Q && action == GLFW_RELEASE)
        camera.moveFlags[0] = 0;
    if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
        camera.moveFlags[0] = +.05;
    if (key == GLFW_KEY_D && action == GLFW_RELEASE)
        camera.moveFlags[0] = 0;

    if (key == GLFW_KEY_SPACE && (action == GLFW_PRESS || action == GLFW_REPEAT))
        camera.moveFlags[1] = +.05;
    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
        camera.moveFlags[1] = 0;
    if (key == GLFW_KEY_LEFT_SHIFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
        camera.moveFlags[1] = -.05;
    if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
        camera.moveFlags[1] = 0;

    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
        camera.moveFlags[2] = +.05;
    if (key == GLFW_KEY_W && action == GLFW_RELEASE)
        camera.moveFlags[2] = 0;
    if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
        camera.moveFlags[2] = -.05;
    if (key == GLFW_KEY_S && action == GLFW_RELEASE)
        camera.moveFlags[2] = 0;

    if (key == GLFW_KEY_T && action == GLFW_PRESS){
        worldManager->wireView = !worldManager->wireView;
        if (worldManager->wireView)
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        else
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }
}


void cursorCallBack(GLFWwindow* window, double xpos, double ypos){
    WorldManager *worldManager = static_cast<WorldManager*>(glfwGetWindowUserPointer(window));
    Camera &camera = worldManager->getCamera();
    camera.setNewCursorPosition(xpos, ypos);
    camera.updateRotation();
}

void GLApp::init(){
    if (!glfwInit())
        throw std::runtime_error("glfwInit failed");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(_width, _height, _name.c_str(), NULL, NULL);

    if (!_window)
        throw std::runtime_error("Window couldn't be oppened.");

    glfwMakeContextCurrent(_window);
    if (glfwGetCurrentContext() == nullptr)
        throw std::runtime_error("Failed to create OpenGL context");


    std::cout << "GL version: " << glGetString(GL_VERSION) << "\n";
    glEnable(GL_DEPTH_TEST);

    glfwSetKeyCallback(_window, keyCallBack);
    glfwSetCursorPosCallback(_window, cursorCallBack);

    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}


void GLApp::render()
{
double lastTime = 0.0;
int frameCount = 0;
double fps = 0.0;
    WorldManager worldManager;
    glfwSetWindowUserPointer(_window, &worldManager);
    // unsigned int i = 0;
            // worldManager.loadChunks();

    TextureArray textures({"textures/dirt.png", "textures/stone.png"});
    textures.bind(0);
    while (!glfwWindowShouldClose(_window)){

        glfwPollEvents();
        glClearColor(.2, .1, .2, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // worldManager.loadChunks();
        
//         // i++;

double currentTime = glfwGetTime();
frameCount++;

if (currentTime - lastTime >= 1.0) {
    fps = frameCount / (currentTime - lastTime);
    
    std::cout << "FPS: " << fps << std::endl;
    
    frameCount = 0;
    lastTime = currentTime;
}

        

        worldManager.draw();
        glfwSwapBuffers(_window);
    }

}

GLApp::~GLApp()
{
    if (_window != nullptr){
        glfwMakeContextCurrent(NULL);
        glfwDestroyWindow(_window);
    }
    glfwTerminate();
}
