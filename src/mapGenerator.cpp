#include "mapGenerator.h"
#include <iostream>
#include <algorithm>

MapGenerator::MapGenerator(std::string name) : Module(name) {
}

MapGenerator::~MapGenerator() {

}

bool MapGenerator::LoadConfig(std::string config_file) 
{

    return true;
}

bool MapGenerator::Start() 
{   
    perlin.SetOctaveCount(6);
    perlin.SetFrequency(0.01);
    perlin.SetPersistence(0.86);
    perlin.SetLacunarity(0.14);
    perlin.SetSeed(0);
    perlin.SetNoiseQuality(noise::NoiseQuality::QUALITY_STD);

    GenerateChunk(0, 0);
    GenerateChunk(1, 0);
    GenerateChunk(0, 1);
    GenerateChunk(1, 1);

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


