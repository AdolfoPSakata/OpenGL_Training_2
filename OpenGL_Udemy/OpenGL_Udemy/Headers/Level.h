#pragma once
#include <vector>
//#include <GameObject.h>
#include <Definitions.h>

class GameLevel
{
public:
    GameLevel() { }

    //std::vector<GameObject> Enemies;
    void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
    void Draw(Renderer& renderer);
    bool IsCompleted();

private:
    void init(std::vector<std::vector<unsigned int>> enemyData);
};