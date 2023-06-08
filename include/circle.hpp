#ifndef SHAPE
    #include "shape.hpp"
#endif

class Circle : Shape
{
    private:
        float radius;

        const double pi = 3.14159265358979323846;

        std::vector<float> vertices;

    public:
        Circle(float radius = 1.0f, int triangles = 100);
        ~Circle();
        
        float getArea();
        void bindVertexArray();
};