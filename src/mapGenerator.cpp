#include "mapGenerator.h"
#include <iostream>

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
    perlin.SetOctaveCount(1);
    perlin.SetFrequency(0.1);
    perlin.SetPersistence(0.1);
    perlin.SetLacunarity(0.1);
    perlin.SetSeed(0);
    perlin.SetNoiseQuality(noise::NoiseQuality::QUALITY_STD);

    float multiplier = 6.0f;

    vertices.clear();
    for (int i = 1; i <= width; ++i) {
        for (int j = 1; j <= height; ++j) 
        {
        // First triangle
        vertices.push_back(Vector3{(float)i, multiplier * (float)perlin.GetValue((double)i, (double)j, (double)depth), (float)j});
        vertices.push_back(Vector3{float(i + 1), multiplier * (float)perlin.GetValue((double)(i + 1), (double)j, (double)depth), (float)j});
        vertices.push_back(Vector3{(float)i, multiplier * (float)perlin.GetValue((double)i, (double)(j + 1), (double)depth), float(j + 1)});

        // Second triangle
        vertices.push_back(Vector3{float(i + 1), multiplier * (float)perlin.GetValue((double)(i + 1), (double)j, (double)depth), (float)j});
        vertices.push_back(Vector3{(float)i, multiplier * (float)perlin.GetValue((double)i, (double)(j + 1), (double)depth), float(j + 1)});
        vertices.push_back(Vector3{(float)(i + 1), multiplier * (float)perlin.GetValue((double)(i + 1), (double)(j + 1), (double)depth), float(j + 1)});
        }
    }
    

    return true;
}

bool MapGenerator::Update(double delta_time) 
{
    return true;
}

void MapGenerator::Cleanup() 
{

}



