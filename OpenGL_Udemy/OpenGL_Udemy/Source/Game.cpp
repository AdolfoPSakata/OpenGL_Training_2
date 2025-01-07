#include "Game.h"


RenderManager* Game::renderManager;
UIManager* Game::uiManager;
TextRenderer* Game::test;
//GameObjectManager* Game::objectManager;

GameState Game::State;
Player Game::player;
float Game::deltaTime;
std::vector<Enemy> enemyVector = {};
float Game::cooldown = 1.5f;
float Game::MAX_COOLDOWN = 1.5f;

Game::Game()
{
    Game::deltaTime = 0.01f;
    Game::renderManager = new RenderManager();
}
Game::~Game() {}

void Game::Init()
{
    Game::test->Init();
    Game::renderManager->Init();
    Game::uiManager->Init();

    Game::player = Player(
        glm::vec2(0.0f,-0.55f),
        glm::vec2(0.1f, 0.1f),
        Game::renderManager->textureManager->GetTextureSlot("Tank.png"),
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        1.0f);

    float xPos = -0.7f;
    float yPos = 0.4f;
    for (int i = 0; i < MAX_ENEMY; i++)
    {
        Enemy enemy = Enemy(
            glm::vec2(xPos, yPos),
            glm::vec2(0.08f, 0.08f),
            Game::renderManager->textureManager->GetTextureSlot("Alien.png"),
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            1.0f);
        enemyVector.push_back(enemy);
        
        xPos += 0.12f;
        if (xPos >= 0.5f)
        {
            xPos = -0.7f;
            yPos -= 0.12f;
        }
    }

    Game::CreateCallbacks(Game::renderManager->window);
    Game::Update(deltaTime);
}

void Game::ProcessInput(GLFWwindow* window, int key, int code, int action, int mode)
{
    if (Game::State == GAME_ACTIVE)
    {
        float velocity = Game::player.Velocity * Game::deltaTime;
        if (key == GLFW_KEY_A)
        {
            if (Game::player.Position.x > -0.75f)
                Game::player.Position.x -= velocity;
        }
        if (key == GLFW_KEY_D)
        {
            if (Game::player.Position.x < 0.65f)
                Game::player.Position.x += velocity;
        }
        if (key == GLFW_KEY_SPACE && Game::cooldown > Game::MAX_COOLDOWN)
        {
             Game::player.Shoot();
             Game::cooldown = 0;
        }
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void Game::CreateCallbacks(GLFWwindow* window)
{
    glfwSetKeyCallback(window, ProcessInput);
}

bool Game::CheckCollision(GameObject& shot, GameObject& enemy)
{
    bool collisionX = shot.Position.x + enemy.Size.x >= enemy.Position.x &&
        enemy.Position.x + enemy.Size.x >= shot.Position.x;
    bool collisionY = shot.Position.y + shot.Size.y >= enemy.Position.y &&
        enemy.Position.y + enemy.Size.y >= shot.Position.y;
    return collisionX && collisionY;
}

void Game::EndGameCheck()
{
    if (enemyVector.size() <= 0)
    {
        std::cout << "----------------- WIN -------------------" << std::endl;
        return;
    }

    for (int i = 0; i < enemyVector.size(); i++)
    {
        if (enemyVector[i].Position.y <= -0.5f)
        {
            std::cout << "----------------- LOSE -------------------" << std::endl;
            return;
        }
    }
}

int Game::Update(float deltaTime)
{
    Game::State = GAME_ACTIVE;

    while (!glfwWindowShouldClose(renderManager->window))
    {
        renderManager->StartDraw();

        Game::cooldown += deltaTime;

        glm::mat4 Model = glm::translate(glm::mat4(1.0f), glm::vec3(Game::player.Position.x, Game::player.Position.y, 0));
        Model = glm::scale(Model, glm::vec3(Game::player.Size.x, Game::player.Size.y, 1));
        glm::mat4 MVP = renderManager->m_Projection * Model;

        Game::player.OnRender(renderManager->uniformManager, renderManager->rendererObject,
            renderManager->textureManager, MVP);
        
        Game::player.Draw(renderManager->renderer, renderManager->rendererObject);

        Game::uiManager->DrawElements(renderManager, MVP);

        bool hasColision = false;
        for (int i = 0; i < enemyVector.size(); i++)
        {
            for (int j = 0; j < Game::player.projectileVector.size(); j++)
            {
                if (Game::player.projectileVector[j].Destroyed || enemyVector[i].Destroyed)
                    continue;

                bool hasColision = CheckCollision(Game::player.projectileVector[j], enemyVector[i]);
                if (hasColision)
                {
                    Game::player.projectileVector[j].OnHit();
                    Game::player.projectileVector[j].~Projectile();
                    enemyVector[i].OnHit();
                    Enemy* currentEnemy = &enemyVector[i];
                    enemyVector.erase(enemyVector.begin() + i);
                    currentEnemy->~Enemy();
                    break;
                }
            }
            if (hasColision)
            {
                hasColision = false;
                break;
            }
        }

        for (int i = 0; i < Game::player.projectileVector.size(); i++)
        {
            if (!Game::player.projectileVector[i].Destroyed)
            {
                glm::mat4 Model3 = glm::translate(glm::mat4(1.0f), 
                    glm::vec3(Game::player.projectileVector[i].Position.x, Game::player.projectileVector[i].Position.y, 0));
                
                Model3 = glm::scale(Model3, glm::vec3(player.projectileVector[i].Size.x, player.projectileVector[i].Size.y, 1));
                glm::mat4 MVP3 = renderManager->m_Projection * Model3;

                Game::player.projectileVector[i].OnRender(renderManager->uniformManager, renderManager->rendererObject,
                    renderManager->textureManager, MVP3);
                
                Game::player.projectileVector[i].Draw(renderManager->renderer, renderManager->rendererObject);
                
                Game::player.projectileVector[i].Move();
            }
            else
            {
                Projectile* currentProjectile = &Game::player.projectileVector[i];
                Game::player.projectileVector.erase(Game::player.projectileVector.begin() + i);
                currentProjectile->~Projectile();
            }
        }
        
        for (int i = 0; i < enemyVector.size(); i++)
        {
            if (!enemyVector[i].Destroyed)
            {
                glm::mat4 Model2 = glm::translate(glm::mat4(1.0f), glm::vec3(enemyVector[i].Position.x, enemyVector[i].Position.y, 0));
                Model2 = glm::scale(Model2, glm::vec3(enemyVector[i].Size.x, enemyVector[i].Size.y, 1));
                glm::mat4 MVP2 = renderManager->m_Projection * Model2;
        
                enemyVector[i].OnRender(renderManager->uniformManager, renderManager->rendererObject,
                    renderManager->textureManager, MVP2);
                
                enemyVector[i].Draw(renderManager->renderer, renderManager->rendererObject);
           
                enemyVector[i].Move(deltaTime);
            }
        }
        //test->RenderText(renderManager->uniformManager, renderManager->rendererObject, "ASFSDFIOHSDOISJDH", renderManager->renderer, 1,1,1, glm::vec3(1,1,1));
        renderManager->DrawEnd();
        EndGameCheck();
    }

    glfwTerminate();
    return 0;
}