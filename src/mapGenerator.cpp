#include "mapGenerator.h"
#include "engine.h"
#include "render.h"
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
    sizeOfTriangle = j["triangleSize"].get<float>();
    seed = j["perlinSeed"].get<int>(); 
    chunkThreshold = j["chunkThreshold"].get<int>();
    bottomOfMap = j["bottomOfMap"].get<float>();

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

    return true;
}

void MapGenerator::UpdateChunksBasedOnCamera(Vector3 cameraPosition)
{
        int x = (int)(cameraPosition.x / (width * sizeOfTriangle));
        int y = (int)(cameraPosition.z / (height * sizeOfTriangle));

        if(x == savedX && y == savedY)
            return;

        std::cout << "x: " << x << " y: " << y << std::endl;

        for(int i = x - chunkThreshold; i <= x + chunkThreshold; ++i)
        {
            for(int j = y - chunkThreshold; j <= y + chunkThreshold; ++j)
            {
                bool chunkFound = false;
                for(auto chunk : chunks)
                {
                    if(chunk.x == i && chunk.y == j)
                    {
                        chunkFound = true;
                        break;
                    }
                }

                if(!chunkFound)
                {
                    GenerateChunk(i, j);
                }
            }
        }

        for(int p = 0; p < chunks.size(); p++)
        {
            if(chunks[p].x < x - chunkThreshold || chunks[p].x > x + chunkThreshold || chunks[p].y < y - chunkThreshold || chunks[p].y > y + chunkThreshold)
            {
                chunks.erase(chunks.begin() + p);
            }

        }
}

bool MapGenerator::Update(double delta_time) 
{
    UpdateChunksBasedOnCamera(engine->render->GetCamera()->position);
    savedX = (int)(engine->render->GetCamera()->position.x / (width * sizeOfTriangle));
    savedY = (int)(engine->render->GetCamera()->position.z / (height * sizeOfTriangle));
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
        
        float y_1_1 = heightMultiplier *(float)perlin.GetValue((double)(i + x), (double)(j + 1 + y), (double)depth);
        if(y_1_1 < bottomOfMap)
            y_1_1 = bottomOfMap;

        float y_1_2 = heightMultiplier *(float)perlin.GetValue((double)(i + 1 + x), (double)(j + y), (double)depth);
        if(y_1_2 < bottomOfMap)
            y_1_2 = bottomOfMap;

        float y_1_3 = heightMultiplier *(float)perlin.GetValue((double)(i + x), (double)(j + y), (double)depth);
        if(y_1_3 < bottomOfMap)
            y_1_3 = bottomOfMap;

        float y_2_1 = heightMultiplier *(float)perlin.GetValue((double)(i + 1 + x), (double)(j + y), (double)depth);
        if(y_2_1 < bottomOfMap)
            y_2_1 = bottomOfMap;

        float y_2_2 = heightMultiplier *(float)perlin.GetValue((double)(i + x), (double)(j + 1 + y), (double)depth);
        if(y_2_2 < bottomOfMap)
            y_2_2 = bottomOfMap;

        float y_2_3 = heightMultiplier *(float)perlin.GetValue((double)(i + 1 + x), (double)(j + 1 + y), (double)depth);
        if(y_2_3 < bottomOfMap)
            y_2_3 = bottomOfMap;

        

        // First triangle
        vertices.push_back(Vector3{sizeOfTriangle * (float)(i + x), y_1_1, sizeOfTriangle * float(j + 1 + y)});
        vertices.push_back(Vector3{sizeOfTriangle * (float)(i + 1 + x), y_1_2, sizeOfTriangle * (float)(j + y)});
        vertices.push_back(Vector3{sizeOfTriangle * (float)(i + x), y_1_3, sizeOfTriangle * (float)(j + y)});
    
        // Second triangle
        vertices.push_back(Vector3{sizeOfTriangle * (float)(i + 1 + x), y_2_1, sizeOfTriangle * (float)(j + y)});
        vertices.push_back(Vector3{sizeOfTriangle * (float)(i + x), y_2_2, sizeOfTriangle * float(j + 1 + y)});
        vertices.push_back(Vector3{sizeOfTriangle * (float)(i + 1 + x), y_2_3, sizeOfTriangle * float(j + 1 + y)});
        }
    }


    std::vector<Triangle> trianglesChunk;
    for (int i = 0; i < vertices.size(); i += 3) 
    {
        if(vertices[i].y == bottomOfMap && vertices[i + 1].y == bottomOfMap && vertices[i + 2].y == bottomOfMap)
        {
            Triangle triangle;
            triangle.a = vertices[i];
            triangle.b = vertices[i + 1];
            triangle.c = vertices[i + 2];
            triangle.color = Color{0, 102, 204, 255};

            trianglesChunk.push_back(triangle);
        }
        else
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
            triangle.color = Color{red, green, 0, 255};

            trianglesChunk.push_back(triangle);
        }
    
    }

    chunks.push_back(Chunk{x_index, y_index, trianglesChunk});

    vertices.clear();
}


