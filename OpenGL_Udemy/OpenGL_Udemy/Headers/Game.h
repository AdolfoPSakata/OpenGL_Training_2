#pragma once
#include <Definitions.h>
#include <vector>
#include <Enemy.h>
#include <RenderManager.h>
#include <GameObjectManager.h>
#include <UIManager.h>
#include <TextRenderer.h>

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN,
    GAME_LOSE,
};

class Game
{
public:
    Game();
    ~Game();

    static GameState State;
    static Player player;
    static float cooldown;
    static float deltaTime;
    static float MAX_COOLDOWN;
    static RenderManager* renderManager; 
    static UIManager* uiManager; 
    static TextRenderer* test;
    //static GameObjectManager* objectManager;
    void Init();
    void CreateCallbacks(GLFWwindow* window);
    int Update(float deltaTime);
    const int MAX_ENEMY = 30;
    int enemyCount = 0;
    std::vector<Enemy> enemyVector;
    static void ProcessInput(GLFWwindow* window, int key, int code, int action, int mode);
    bool CheckCollision(GameObject& shot, GameObject& enemy);
    //void Render();
    void EndGameCheck();
};