// Local Headers
#include "Main.h"

// System Headers
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#include "Sprite.h"

#include <vector>

void render();
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);

bool keys[1024];

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Setup window
    auto window = glfwCreateWindow(mWidth, mHeight, "Tile Engine GL", nullptr, nullptr);
    if (window == nullptr)
    {
        fprintf(stderr, "Failed to create opengl context");
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, keyCallback);

    // Load open gl
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);

    Shader defaultShader("default.vert", "default.frag");

    std::vector<Sprite> tiles;
    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            Sprite sprite(glm::vec2(x * 0.96, y * 0.96), 0);
            tiles.push_back(sprite);
        }
    }

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        defaultShader.Use();
        for (int i = 0; i < tiles.size(); i ++)
        {
            Sprite sprite = tiles[i];
            glUniformMatrix4fv(glGetUniformLocation(defaultShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(sprite.GetModel()));
            sprite.Render();
        }
      

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

void render()
{
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (action == GLFW_PRESS)
    {
        keys[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        keys[key] = false;
    }
}