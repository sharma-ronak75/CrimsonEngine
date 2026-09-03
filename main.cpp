#include "app.h"

GLFWwindow* window;

int main()
{

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 1);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwSwapInterval(1);
    
    // glfw window creation
    // --------------------
    window = glfwCreateWindow(1280, 720, Crimson::Window::title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // input.window = window;
    
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    // {
    //     std::cout << "Failed to initialize GLAD" << std::endl;
    //     return -1;
    // }

    glewExperimental = true;
    glewInit();
    
    // glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    Crimson::Renderer::_init();

    App app;
    // {
    Crimson::Input::window = window;
    app.Initialize();
    // Texture textureAtlas("res/atlas.png");
    // textureAtlas.Bind();

    // loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        std::chrono::system_clock::time_point current_time = std::chrono::system_clock::now();

        
        if(Crimson::Settings::wireframe_rendering) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        app.Update();
        app.Render();

        Crimson::Input::listen();

        app.tick ++;
        Crimson::Window::__tick ++;

        glfwSwapBuffers(window);

        app.deltaTime = ((std::chrono::duration<double>)(std::chrono::system_clock::now() - current_time)).count();

        // Set title

        std::string displayString;
        if(Crimson::Settings::show_debug_info)
        {
            displayString = Crimson::Window::title + " FPS - " + std::to_string(1.0 / app.deltaTime);
        }
        else
        {
            displayString = Crimson::Window::title;
        }

        glfwSetWindowTitle(Crimson::Input::window, displayString.c_str());

        // Set window size

        glm::ivec2 resolution;
        glfwGetWindowSize(Crimson::Input::window, &resolution.x, &resolution.y);
        glViewport(0, 0, resolution.x, resolution.y);
        
        Crimson::Window::aspect_ratio = (float)resolution.x / (float)resolution.y;
        Crimson::Window::aspect_ratio_inverse = (float)resolution.y / (float)resolution.x;

        // Mouse capture

        if(Crimson::Window::mouse_captured)
        {
            glfwSetInputMode(Crimson::Input::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else
        {
            glfwSetInputMode(Crimson::Input::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    app.Destruct();

    exit(0);
    
    // }

    // glfw: terminate, clearing all previously allocated GLFW resources.s
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}