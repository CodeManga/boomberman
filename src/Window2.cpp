#include "Window.hpp"
#include "MainMenu.hpp"
#include "Sound.hpp"

//Error checking         :Cradebe
static void error_callback(int error, const char* description)
{
    (void)error;
    fputs(description, stderr);
}

Window::Window(){
    latestHeight = HEIGHT;
    latestWidth = WIDTH;
    _width  = WIDTH;
    _window = nullptr;
    _fullWindow = nullptr;
    _height  = HEIGHT;
    _sound = new Sound();
    _keyEvents = new WindowKeyEvents();
}
Window::~Window(){
    // delete graphics;
    // delete _sound;
    // delete _keyEvents;
}


//Initiates Screen  :Cradebe
void Window::initiateSystemsFullscreen()
{
    printf("test\n");

    glfwSetErrorCallback(error_callback);


    // Initialise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor()/*monitor*/);
       _fullWindow = glfwCreateWindow(/*mode->width, mode->height*/2048, 1536/*512, 396*//*1024, 768*/, "Bomberman", NULL, NULL);//to create new window

   glfwSetWindowMonitor(_fullWindow, glfwGetPrimaryMonitor()/*monitor*/, 0, 0, 2048, 1536, mode->refreshRate);
    if (!_fullWindow)
    {
        terminateSystems();
    }

    glfwMakeContextCurrent(_fullWindow);
    // // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(_fullWindow, GLFW_STICKY_KEYS, GL_TRUE);

    // // Dark green background
    glClearColor(0.0f, 0.3f, 0.0f, 0.0f);
}


void Window::switchToLarge(GLFWwindow* win , int wantedWidth, int wantedHeight)
{
    if (wantedHeight != latestHeight && wantedWidth !=  latestWidth)
    {
        glfwSetWindowSize(win, wantedWidth, wantedHeight);
        latestHeight = wantedHeight;
        latestWidth = wantedWidth;
    }

}

void Window::switchToMedium(GLFWwindow* win , int wantedWidth, int wantedHeight)
{
    if (wantedHeight != latestHeight && wantedWidth !=  latestWidth)
    {
        glfwSetWindowSize(win, wantedWidth, wantedHeight);
        latestHeight = wantedHeight;
        latestWidth = wantedWidth;
    }
}

void Window::switchToWindowed(GLFWwindow* win)
{
    if (HEIGHT != latestHeight && WIDTH !=  latestWidth)
    {
        glfwSetWindowSize(win, WIDTH, HEIGHT);
        latestHeight = HEIGHT;
        latestWidth = WIDTH;
    }

}

void Window::switchToFull(GLFWwindow* win)
{
    (void)win;
}

void Window::initiateSystemsWindowed()
{

    glfwSetErrorCallback(error_callback);

    // Initialise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(1060, 750, "Bomberman", NULL, NULL);//to create new window

    if (!_window)
    {
        terminateSystems();
    }

    glfwMakeContextCurrent(_window);
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark green background
    glClearColor(0.0f, 0.3f, 0.0f, 0.0f);
}

void Window::setGraphics(Graphics g)
{
    this->graphics = &g;
}

//Terminates initialised system
void Window::terminateSystems()
{
    fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
    getchar();
    glfwTerminate();
    exit(EXIT_FAILURE);
}

bool Window::initializeGlew()
{
    glewExperimental = true; // Needed for core profile

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return false;
    }
    else
        return true;
}

void Window::changeWindowSize()
{
    if (_fullWindow)
    {
        initiateSystemsWindowed();
        glfwDestroyWindow(_fullWindow);
        _fullWindow = nullptr;
    }
    else if (_window)
    {
        initiateSystemsFullscreen();
        glfwDestroyWindow(_window);
        _window = nullptr;
    }
}

Sound* Window::getSound()
{
    return (_sound);
}

GLFWwindow* Window::getWindow()
{
    if (!_window)
        return _fullWindow;
    return _window;
}

WindowKeyEvents* Window::getEvents()
{
    return (_keyEvents);
}
