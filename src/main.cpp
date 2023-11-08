#include "../include/main.hpp"

float *getVertices(Texture *texture, Rect<float> *screen, Rect<float> *sprite)
{
    float a,b,c,d;
    a = (screen->x - (float)SCREEN_WIDTH/2) / ((float)SCREEN_WIDTH/2);
    b = (screen->y - (float)SCREEN_HEIGHT/2) / ((float)SCREEN_HEIGHT/2) * -1;
    c = (screen->x + screen->w - (float)SCREEN_WIDTH/2) / ((float)SCREEN_WIDTH/2);
    d = (screen->y + screen->h - (float)SCREEN_HEIGHT/2) / ((float)SCREEN_HEIGHT/2) * -1;

    float e,f,g,h;
    e = (sprite->x) / ((float)texture->width);
    f = 1.0f - (sprite->y) / ((float)texture->height);
    g = (sprite->x + sprite->w) / ((float)texture->width);
    h = 1.0f - (sprite->y + sprite->h) / ((float)texture->height);

    float *vertices = new float[30] {
        a, b, 0.0f, e, f,
        c, b, 0.0f, g, f,
        a, d, 0.0f, e, h,
        c, d, 0.0f, g, h,
    };

    return vertices;
};

void loadTexture(std::string path, bool rgba, Texture *texture)
{
    unsigned int id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;

    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        if(rgba)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("Failed to load texture\n");
    }

    stbi_image_free(data);
    
    texture->id = id;
    texture->width = width;
    texture->height = height;
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader ourShader("shaders/vertex.glsl", "shaders/fragment.glsl");

    std::vector<float> buffer = std::vector<float>(); 

    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3,
        4, 5, 6,
        5, 6, 7
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    stbi_set_flip_vertically_on_load(true);

    Texture t1, t2;

    loadTexture("resources/container.jpg", false, &t1);
    loadTexture("resources/link.png", true, &t2);

    Rect<float> screen = {0, 0, (float)t1.width, (float)t1.height};
    Rect<float> sprite = {0,0, (float)t1.width, (float)t1.height};

    screen.w = (float)SCREEN_WIDTH * 2;
    screen.h = (float)SCREEN_HEIGHT * 2;
    float *v1 = getVertices(&t1, &screen, &sprite);
    float sprite_size = 32.0f; 
    screen = {(float)SCREEN_WIDTH / 2 - sprite_size / 2, (float)SCREEN_HEIGHT / 2 - sprite_size / 2, sprite_size, sprite_size};
    sprite = {8, 5, sprite_size, sprite_size};
    
    float *v2 = getVertices(&t2, &screen, &sprite);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, t1.id);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, t2.id);

    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    BatchRenderer batchRenderer = BatchRenderer();
    float player_x = (float)SCREEN_WIDTH / 2 - sprite_size / 2;
    float player_y = (float)SCREEN_HEIGHT / 2 - sprite_size / 2;
    float velocity_in_pixels = 30.0f;
    float velocity_x_in_screen_coordinates = velocity_in_pixels / SCREEN_WIDTH * 2;
    float velocity_y_in_screen_coordinates = velocity_in_pixels / SCREEN_HEIGHT * 2;

    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 player = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // processInput(window);
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }
        
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            player_x += velocity_in_pixels;
            transform = glm::translate(transform, glm::vec3(-velocity_x_in_screen_coordinates, 0.0f, 0.0f));
        }
        
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            player_x -= velocity_in_pixels;
            transform = glm::translate(transform, glm::vec3(velocity_x_in_screen_coordinates, 0.0, 0.0f)); 
            
            for(int i = 0; i < 4; i++)
            {
                for(int x = 0; x < 4; x++)
                {
                    printf("(%f)", player[i][x]);
                }
                printf("\n");
            }
            printf("\n");
            printf("x: %f\n", player_x);
        }
        glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // create transformations

        // get matrix's uniform location and set matrix
        ourShader.use();
        ourShader.setMat4("transform", transform);
        ourShader.setMat4("player", player);
        ourShader.setInt("num", 0);

        batchRenderer.addVertices(v1);
        batchRenderer.render();

        ourShader.setInt("num", 1);
        batchRenderer.addVertices(v2);
        batchRenderer.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
