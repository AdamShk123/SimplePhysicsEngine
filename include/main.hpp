#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

template<class T> 
struct Rect
{
    T x;
    T y;
    T w;
    T h;
};

struct Texture 
{
    unsigned int id;
    int width;
    int height;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
Texture loadTexture();

// settings
const unsigned int SCREEN_WIDTH = 1920;
const unsigned int SCREEN_HEIGHT = 1080;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
