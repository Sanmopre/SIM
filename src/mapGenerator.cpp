#include "mapGenerator.h"
#include "engine.h"
#include "render.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>

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

    //treeModel = LoadModel(j["treeModel"].get<std::string>().c_str());

    treeDensity = j["treeDensity"].get<int>();

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

    m_noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    m_noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    m_noise.SetFractalOctaves(octaves);
    m_noise.SetFractalLacunarity(lacunarity);
    m_noise.SetFractalGain(persistence);
    m_noise.SetFrequency(frequency);
    m_noise.SetSeed(seed);

    return true;
}

void MapGenerator::UpdateChunksBasedOnCamera(Vector3 cameraPosition)
{
        int x = (int)(cameraPosition.x / (width * sizeOfTriangle));
        int y = (int)(cameraPosition.z / (height * sizeOfTriangle));

        if(x == savedX && y == savedY)
            return;

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
    {
        for (int i = 0; i < chunks[j].triangles.size(); ++i)
        {
            DrawTriangle3D(chunks[j].triangles[i].a, chunks[j].triangles[i].b, chunks[j].triangles[i].c, chunks[j].triangles[i].color);
        }

        for (int i = 0; i < chunks[j].treesPositions.size(); ++i)
        {
            DrawTree(chunks[j].treesPositions[i]);
        } 
    }

}

void MapGenerator::GenerateChunk(int x_index, int y_index)
{

    int x = x_index * width;
    int y = y_index * height;

    vertices.clear();
    for (int i = 1; i <= width; ++i) {
        for (int j = 1; j <= height; ++j) 
        {


        float y_1_1 = heightMultiplier *(float)m_noise.GetNoise((double)(i + x), (double)(j + 1 + y), (double)depth);
        if(y_1_1 < bottomOfMap)
            y_1_1 = bottomOfMap;

        float y_1_2 = heightMultiplier *(float)m_noise.GetNoise((double)(i + 1 + x), (double)(j + y), (double)depth);
        if(y_1_2 < bottomOfMap)
            y_1_2 = bottomOfMap;

        float y_1_3 = heightMultiplier *(float)m_noise.GetNoise((double)(i + x), (double)(j + y), (double)depth);
        if(y_1_3 < bottomOfMap)
            y_1_3 = bottomOfMap;

        float y_2_1 = heightMultiplier *(float)m_noise.GetNoise((double)(i + 1 + x), (double)(j + y), (double)depth);
        if(y_2_1 < bottomOfMap)
            y_2_1 = bottomOfMap;

        float y_2_2 = heightMultiplier *(float)m_noise.GetNoise((double)(i + x), (double)(j + 1 + y), (double)depth);
        if(y_2_2 < bottomOfMap)
            y_2_2 = bottomOfMap;

        float y_2_3 = heightMultiplier *(float)m_noise.GetNoise((double)(i + 1 + x), (double)(j + 1 + y), (double)depth);
        if(y_2_3 < bottomOfMap)
            y_2_3 = bottomOfMap;
            

        /*
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
        */
        

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
    std::vector<Vector3> treesPositions;
    for (int i = 0; i < vertices.size(); i += 3) 
    {
        if(vertices[i].y == bottomOfMap && vertices[i + 1].y == bottomOfMap && vertices[i + 2].y == bottomOfMap)
        {
            //Ocean triangles
            Triangle triangle;
            triangle.a = vertices[i];
            triangle.b = vertices[i + 1];
            triangle.c = vertices[i + 2];

            int randomSign = rand() % 2 == 0 ? -1 : 1;
            triangle.color = Color{0, 102, static_cast<unsigned char>(204 + static_cast<int>(oceanColorVariation * randomSign)), 255};

            trianglesChunk.push_back(triangle);
        }
        else
        {
            //Land triangles
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


            //Trees
            std::random_device rd; // obtain a random number from hardware
            std::mt19937 gen(rd()); // seed the generator
            std::uniform_int_distribution<> distr(0, 1000); // define the range
            if(distr(gen) < treeDensity)
            {
                Vector3 treePosition;
                treePosition.x = (vertices[i].x + vertices[i + 1].x + vertices[i + 2].x) / 3.0f;
                treePosition.y = (vertices[i].y + vertices[i + 1].y + vertices[i + 2].y) / 3.0f;
                treePosition.z = (vertices[i].z + vertices[i + 1].z + vertices[i + 2].z) / 3.0f;
                treesPositions.push_back(treePosition);
            }
        }
    
    }

    chunks.push_back(Chunk{x_index, y_index, trianglesChunk, treesPositions});

    vertices.clear();
}

void MapGenerator::DrawTree(Vector3 position, int treeType)
{
    switch (treeType)
    {
    case 1:
        DrawCube(Vector3{position .x + 0.0f, position.y + 0.5f, position.z + 0.0f}, 0.25, 1, 0.25,Color{ 102, 51, 0, 255 } );
        DrawCube(Vector3{position .x + 0.0f, position.y + 0.8f, position.z + 0.0f}, 1.0f, 0.6, 1.0f, Color{ 0, 104, 0, 255 });
        break;
    case 2:
        DrawCube(position, 0.25, 1, 0.25,Color{ 102, 51, 0, 255 } );
        DrawCube(Vector3{position .x + 0.0f, position.y + 1.0f, position.z + 0.0f}, 1.0f, 0.6, 1.0f, Color{ 0, 104, 0, 255 });
        break;
    case 3:
        DrawCube(position, 0.25, 1, 0.25,Color{ 102, 51, 0, 255 } );
        DrawCube(Vector3{position .x + 0.0f, position.y + 1.0f, position.z + 0.0f}, 1.0f, 0.6, 1.0f, Color{ 0, 104, 0, 255 });
        break;
    case 4:
        DrawCube(position, 0.25, 1, 0.25,Color{ 102, 51, 0, 255 } );
        DrawCube(Vector3{position .x + 0.0f, position.y + 1.0f, position.z + 0.0f}, 1.0f, 0.6, 1.0f, Color{ 0, 104, 0, 255 });
        break;
    case 5:
        DrawCube(position, 0.25, 1, 0.25,Color{ 102, 51, 0, 255 } );
        DrawCube(Vector3{position .x + 0.0f, position.y + 1.0f, position.z + 0.0f}, 1.0f, 0.6, 1.0f, Color{ 0, 104, 0, 255 });
        break;
    default:
        break;
    }

}


