#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H


#include "module.h"
#include "raylib.h"
#include "noise/noise.h"
#include <vector>


struct Triangle
{
    Vector3 a;
    Vector3 b;
    Vector3 c;
};

class MapGenerator : public Module {
public:
    MapGenerator(std::string name);
    virtual ~MapGenerator();
    virtual bool LoadConfig(std::string config_file) override;
    virtual bool Start() override;
    virtual bool Update(double delta_time) override;
    virtual void Cleanup() override;
    Vector3* GetVertices() { return vertices.data(); }
    int GetVerticesSize() { return vertices.size(); }

    Triangle GetTriangle(int index)
    {
        return Triangle{ vertices[index], vertices[index + 1], vertices[index + 2] };
    }

private:
    const int width = 30;
    const int height = 30;
    const double depth = 0.5;


    std::vector<Vector3> vertices;
    noise::module::Perlin perlin;
};

#endif // MAPGENERATOR_H
