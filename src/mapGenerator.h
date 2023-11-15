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
    int width = 200;
    int height = 200;
    double depth = 0.5;

    float heightMultiplier = 65.0f;
    float sizeOfTriangle = 3.0f;


    //Perlin values
    double frequency = 0.1;
    double lacunarity = 2.0;
    double persistence = 0.5;
    int octaves = 4;
    int seed = 0;


    std::vector<Vector3> vertices;
    std::vector<Triangle> triangles;
    std::vector<Chunk> chunks;
    noise::module::Perlin perlin;
};

#endif // MAPGENERATOR_H
