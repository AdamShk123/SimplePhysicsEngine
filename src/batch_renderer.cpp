#include "../include/batch_renderer.hpp"

BatchRenderer::BatchRenderer() 
{
    vertices = std::vector<float>();
}

BatchRenderer::~BatchRenderer()
{

}

void BatchRenderer::addVertices(float *vertices)
{
    for(int i = 0; i < 20; i++)
    {
        this->vertices.push_back(vertices[i]);
    }
}

void BatchRenderer::render()
{
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(float), this->vertices.data(), GL_DYNAMIC_DRAW);
    glDrawElements(GL_TRIANGLES, this->vertices.size() / 5 * 3 / 2, GL_UNSIGNED_INT, 0);
    this->vertices.clear();
}
