#define SHAPE

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shape
{
    private:

    public:
        unsigned int vao;
        unsigned int vbo;
        unsigned int ebo;

        virtual float getArea(); // returns area of shape
        virtual void bindVertexArray();
};



