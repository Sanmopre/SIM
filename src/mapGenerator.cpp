#include "mapGenerator.h"
#include "engine.h"
#include <iostream>
#include <algorithm>
#include <fstream>

MapGenerator::MapGenerator(std::string name) : Module(name) {
}

MapGenerator::~MapGenerator() {

}

bool MapGenerator::LoadConfig(std::string config_file) 
{
    std::ifstream file(config_file);
    json j;
    file >> j;

    // Get elements as integers
    height = j["chunkSize"].get<int>();
    width = j["chunkSize"].get<int>();


    octaves = j["perlinOctaves"].get<int>();
    frequency = j["perlinFrequency"].get<double>();
    lacunarity = j["perlinLacunarity"].get<double>();
    persistence = j["perlinPersistence"].get<double>();
    depth = j["depth"].get<double>();
    heightMultiplier = j["heightScale"].get<float>();
    seed = j["perlinSeed"].get<int>();

    return true;
}

bool MapGenerator::Start() 
{   
    perlin.SetOctaveCount(octaves);
    perlin.SetFrequency(frequency);
    perlin.SetPersistence(persistence);
    perlin.SetLacunarity(lacunarity);
    perlin.SetSeed(seed);
    perlin.SetNoiseQuality(noise::NoiseQuality::QUALITY_STD);

    GenerateChunk(0, 0);
    GenerateChunk(1, 0);
    GenerateChunk(0, 1);
    GenerateChunk(1, 1);
    GenerateChunk(2, 0);
    GenerateChunk(0, 2);
    GenerateChunk(2, 1);
    GenerateChunk(1, 2);
    GenerateChunk(2, 2);
    

    return true;
}

bool MapGenerator::Update(double delta_time) 
{
    return true;
}

void MapGenerator::Cleanup() 
{

}

void MapGenerator::DrawMap()
{
    for(int j = 0; j < chunks.size(); ++j)
        for (int i = 0; i < chunks[j].triangles.size(); ++i)
            DrawTriangle3D(chunks[j].triangles[i].a, chunks[j].triangles[i].b, chunks[j].triangles[i].c, chunks[j].triangles[i].color);
}

void MapGenerator::GenerateChunk(int x_index, int y_index)
{

    int x = x_index * width;
    int y = y_index * height;

    vertices.clear();
    for (int i = 1; i <= width; ++i) {
        for (int j = 1; j <= height; ++j) 
        {
        // First triangle
        vertices.push_back(Vector3{(float)(i + x), heightMultiplier *(float)perlin.GetValue((double)(i + x), (double)(j + 1 + y), (double)depth), float(j + 1 + y)});
        vertices.push_back(Vector3{float(i + 1 + x), heightMultiplier *(float)perlin.GetValue((double)(i + 1 + x), (double)(j + y), (double)depth), (float)(j + y)});
        vertices.push_back(Vector3{(float)(i + x), heightMultiplier *(float)perlin.GetValue((double)(i + x), (double)(j + y), (double)depth), (float)(j + y)});
    
        // Second triangle
        vertices.push_back(Vector3{float(i + 1 + x), heightMultiplier *(float)perlin.GetValue((double)(i + 1 + x), (double)(j + y), (double)depth), (float)(j + y)});
        vertices.push_back(Vector3{(float)(i + x), heightMultiplier *(float)perlin.GetValue((double)(i + x), (double)(j + 1 + y), (double)depth), float(j + 1 + y)});
        vertices.push_back(Vector3{(float)(i + 1 + x), heightMultiplier *(float)perlin.GetValue((double)(i + 1 + x), (double)(j + 1 + y), (double)depth), float(j + 1 + y)});
        }
    }


    std::vector<Triangle> trianglesChunk;
    for (int i = 0; i < vertices.size(); i += 3) 
    {
        float averageHeight = (((vertices[i].y/heightMultiplier + vertices[i + 1].y/heightMultiplier + vertices[i + 2].y/heightMultiplier) / 3.0f) + 1.0f) /2.0f;

        if(averageHeight > 1.0f)
            averageHeight = 1.0f;
        else if(averageHeight < 0.0f)
            averageHeight = 0.0f;

        Triangle triangle;
        triangle.a = vertices[i];
        triangle.b = vertices[i + 1];
        triangle.c = vertices[i + 2];

        unsigned char red = std::clamp(255 - static_cast<int>(averageHeight * 250.0f), 0, 255);
        unsigned char green = std::clamp(static_cast<int>(averageHeight * 250.0f), 0, 255);
        triangle.color = Color{red, green, 255, 255};

        trianglesChunk.push_back(triangle);
    
    }

    chunks.push_back(Chunk{x, y, trianglesChunk});

    vertices.clear();
}


