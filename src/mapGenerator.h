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
    Color color;
};

struct Chunk
{
    int x;
    int y;
    std::vector<Triangle> triangles;
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
    void GenerateChunk(int x_index, int y_index);
    void DrawMap();
    
private:
    const int width = 200;
    const int height = 200;
    const double depth = 0.5;
    const float heightMultiplier = 65.0f;

    std::vector<Vector3> vertices;
    std::vector<Triangle> triangles;
    std::vector<Chunk> chunks;
    noise::module::Perlin perlin;
};

#endif // MAPGENERATOR_H
