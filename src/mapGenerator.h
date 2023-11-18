#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H


#include "module.h"
#include "raylib.h"
#include "noise/noise.h"
#include "thridParty/FastNoiseLite.h"
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
    std::vector<Vector3> treesPositions;
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
    void UpdateChunksBasedOnCamera(Vector3 cameraPosition);
    void DrawMap();
    void DrawTree(Vector3 position, int treeType = 1);
    
private:
    int width = 200;
    int height = 200;
    double depth = 0.5;

    float heightMultiplier = 65.0f;
    float sizeOfTriangle = 3.0f;
    float bottomOfMap = 1.0f;
    int oceanColorVariation = 5;


    //Perlin values
    double frequency = 0.1;
    double lacunarity = 2.0;
    double persistence = 0.5;
    int octaves = 4;
    int seed = 0;

    int chunkThreshold = 8;

    //Random values to make sure the map is generated correctly at the start
    int savedX = 3129;
    int savedY = 8954;


    FastNoiseLite m_noise;

    std::vector<Vector3> vertices;
    std::vector<Triangle> triangles;
    std::vector<Chunk> chunks;
    noise::module::Perlin perlin;


    Model treeModel;
    int treeDensity = 5;
};

#endif // MAPGENERATOR_H
