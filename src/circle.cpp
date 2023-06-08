#include "../include/circle.hpp"

Circle::Circle(float radius, int triangles)
{   
    float total = 360.0f;

    //int triangles = 100;

    this->radius = radius;

    float degree = total / triangles; // 360 / 12 = 30

    float currentAngle = 0.0f;

    //float triangleVertices[3 + triangles * 3];
    float triangleVertices[5 + triangles * 5];

    triangleVertices[0] = 0.0f;
    triangleVertices[1] = 0.0f;
    triangleVertices[2] = 0.0f;
    triangleVertices[3] = 0.5f;
    triangleVertices[4] = 0.5f;


    // calculate new vertex
    for(int i = 0; i < triangles; i++) 
    {
        glm::vec3 newPoint;

        newPoint.x = radius * std::sin(glm::radians(currentAngle));
        newPoint.y = radius * std::cos(glm::radians(currentAngle));
        newPoint.z = 0;

        // triangleVertices[3 + 3 * i + 0] = newPoint.x;
        // triangleVertices[3 + 3 * i + 1] = newPoint.y;
        // triangleVertices[3 + 3 * i + 2] = newPoint.z;

        triangleVertices[5 + 5 * i + 0] = newPoint.x;
        triangleVertices[5 + 5 * i + 1] = newPoint.y;
        triangleVertices[5 + 5 * i + 2] = newPoint.z;
        triangleVertices[5 + 5 * i + 3] = (newPoint.x + 1.0f) / 2.0f;
        triangleVertices[5 + 5 * i + 4] = (newPoint.y + 1.0f) / 2.0f;

        currentAngle += degree;

        //printf("x: %f, y: %f\n", newPoint.x, newPoint.y);
    }
    
    int triangleIndices[triangles * 3];

    for(int i = 0; i < triangles; i++)
    {
        triangleIndices[i * 3 + 0] = 0;
        triangleIndices[i * 3 + 1] = i + 1;
        triangleIndices[i * 3 + 2] = i + 2;
        //printf("%d: %d, %d: %d, %d: %d\n", i * 3, 0, i * 3 + 1, i + 1, i * 3 + 2, i + 2);
    }

    triangleIndices[triangles * 3 - 1] = 1;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangleIndices), triangleIndices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

Circle::~Circle()
{

}

float Circle::getArea()
{
    return pi * std::pow(radius,2);
}

void Circle::bindVertexArray()
{
    glBindVertexArray(vao);
}