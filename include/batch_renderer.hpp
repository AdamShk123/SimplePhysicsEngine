#include <vector>
#include <glad/glad.h>

class BatchRenderer 
{
private:
    std::vector<float> vertices;
public:
    BatchRenderer();
    ~BatchRenderer();
    void addVertices(float * vertices);
    void render();
};
