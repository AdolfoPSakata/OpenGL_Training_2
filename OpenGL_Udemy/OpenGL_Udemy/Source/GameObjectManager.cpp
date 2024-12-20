#include <GameObjectManager.h>
//
//GameObjectManager::GameObjectManager()
//{
//}
//
//GameObjectManager::~GameObjectManager()
//{
//}
//
//void GameObjectManager::SetPosition(GameObject gameObject, glm::vec2 pos)
//{
//    gameObject.Position = pos;
//}
//
//void GameObjectManager::SetScale(GameObject gameObject, glm::vec2 size)
//{
//    gameObject.Size = size;
//}
//
//void GameObjectManager::SetColor(GameObject gameObject, glm::vec4 color)
//{
//    gameObject.Color = color;
//}
//
//void GameObjectManager::SetVelocity(GameObject gameObject, float velocity)
//{
//    gameObject.Velocity = velocity;
//}
//
////void GameObjectManager::SetTexture(player, textureName)
////{
////    gameObject.Texture = texture;
////}
//
//GameObject GameObjectManager::Instantiate(RenderManager* renderManager, GameObjectType type, 
//    glm::vec2 pos, glm::vec2 size, glm::vec4 color, float velocity, std::string textureName)
//{
//    if (type == PLAYER_OBJ)
//    {
//        Player player = Player(
//            glm::vec2(0.0f, -0.55f),
//            glm::vec2(0.1f, 0.1f),
//            renderManager->textureManager->GetTextureSlot(textureName),
//            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
//            1.0f);
//
//
//              return player;
//    }
//    if (type == ENEMY_OBJ)
//    {
//        Player player = Player(
//            glm::vec2(0.0f, 0.0f),
//            glm::vec2(0.1f, 0.1f),
//            renderManager->textureManager->GetTextureSlot("1.png"),
//            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
//            1.0f);
//        return player;
//    }
//
//    if (type == SHOT_OBJ)
//    {
//        Player player = Player(
//            glm::vec2(0.0f, -0.55f),
//            glm::vec2(0.1f, 0.1f),
//            renderManager->textureManager->GetTextureSlot("UVMap"),
//            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
//            1.0f);
//        return player;
//    }
//}