#include "GameWorld.h"
#include "GameObject.h"

GameWorld::GameWorld()
{

}

GameWorld::~GameWorld()
{
    /*window = nullptr;
    auto old = gameObjects;
    for (auto gO : old)
    {
        removeGameObject(gO);
    }*/
}

void GameWorld::render()
{
    for (auto go : gameObjects)
    {

        go->render();
    }
}

void GameWorld::update(float deltaTime)
{
    for (auto go : gameObjects)
    {

        go->update(deltaTime);
    }
}

void GameWorld::to_bin()
{
    //primero cogemos el tamaño para saber que tamaño de data vamos a necesitar
    size_t size = 0;
    for (GameObject *gameObject : gameObjects)
    {
        gameObject->to_bin();
        size += gameObject->size();
    }

    alloc_data(size + sizeof(size_t));

    char *tmp = _data;
    size_t count = gameObjects.size();
    memcpy(tmp, &count, sizeof(size_t));
    tmp += sizeof(size_t);

    for (GameObject *gameObject : gameObjects)
    {
        memcpy(tmp, gameObject->data(), gameObject->size());
        tmp += gameObject->size();
    }

    
}

int GameWorld::from_bin(char *data)
{
    //
    
    auto old = gameObjects;
    for (auto gO : old)
    {
        removeGameObject(gO);
    }

    char *tmp = data;
    size_t count = 0;
    memcpy(&count, tmp, sizeof(size_t));

    tmp += sizeof(size_t);

    while (count > 0)
    {
        ObjectType auxType;
        memcpy(&auxType, tmp, sizeof(auxType));

        GameObject *gameObject = nullptr;
        if (auxType == ObjectType::PLAYER)
        {
         //   gameObject = new Player();
            gameObject->from_bin(tmp);
            tmp += gameObject->size();
        }
        else if (auxType == ObjectType::BULLET)
        {
            //gameObject = new Bullet();
            gameObject->from_bin(tmp);
            tmp += gameObject->size();
        }
        else if (auxType == ObjectType::OBSTACLE)
        {
           // gameObject = new Obstacle();
            gameObject->from_bin(tmp);
            tmp += gameObject->size();
        }
        if (gameObject != nullptr)
            addNewGameObject(gameObject);

        count--;
    }

    return 0;
}

std::vector<GameObject *> GameWorld::getWorldGameObjects()
{
    return gameObjects;
}

std::vector<GameObject *> GameWorld::getRemoveWorldGameObjects()
{
    return removeObjects;
}

//metodo para añadir un nuevo gameObject a la lista
void GameWorld::addNewGameObject(GameObject *gO)
{
    gameObjects.push_back(gO);
    
   // gO->setWorld(this);
}

//metodo para eliminar el objeto que queremos de la lista
void GameWorld::removeGameObject(GameObject *gO)
{
  /*  auto it = std::find(gameObjects.begin(), gameObjects.end(), gO);
    if (it == gameObjects.end())
        return;

    gameObjects.erase(it);
    delete gO;*/
}
