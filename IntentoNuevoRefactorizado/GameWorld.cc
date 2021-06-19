#include "GameWorld.h"
#include "GameObject.h"
#include <algorithm>
#include "Player.h"
#include "Bullet.h"
#include "Obstacle.h"

GameWorld::GameWorld(SDL_Window *window) : window(window), removeObjects(), hasToRestart(false)
{
    Obstacle *obstacle = nullptr;

    obstacle = new Obstacle(250, 130, 100, 100);
    addGameObject(obstacle);
    obstacle = new Obstacle(420, 210, 24, 42);
    addGameObject(obstacle);
    obstacle = new Obstacle(325, 300, 35, 42);
    addGameObject(obstacle);
    obstacle = new Obstacle(25, 40, 50, 70);
    addGameObject(obstacle);
    obstacle = new Obstacle(500, 170, 100, 20);
    addGameObject(obstacle);
}

GameWorld::~GameWorld()
{
    window = nullptr;
    auto old = gameObjects;
    for (auto gO : old)
    {
        removeGameObject(gO);
    }
}

void GameWorld::render()
{
    auto gameObjects = this->gameObjects;

    
    for (GameObject *gameObject : gameObjects)
        gameObject->render(window);
    window->display();
}

void GameWorld::update(float deltaTime)
{

    checkCollisions();

    auto gameObjects = this->gameObjects;

    for (GameObject *gameObject : gameObjects)
        gameObject->update(deltaTime);


    if (hasToRestart)
    {
        hasToRestart = false;
        reset();
    }

    //Remove
    for (GameObject *gameObject : removeObjects)
    {
        removeGameObject(gameObject);
    }
    removeObjects.clear();
}

void GameWorld::handleEvent(sf::Event &event)
{
    auto gameObjects = this->gameObjects;

    for (GameObject *gameObject : gameObjects)
        gameObject->handleEvent(event);
}

void GameWorld::addGameObject(GameObject *gameObject)
{
    gameObjects.push_back(gameObject);
    gameObject->setGameWorld(this);
}

void GameWorld::removeGameObject(GameObject *gameObject)
{
    auto it = std::find(gameObjects.begin(), gameObjects.end(), gameObject);
    if (it == gameObjects.end())
        return;

    gameObjects.erase(it);
    delete gameObject;
}

void GameWorld::laterRemoveGameObject(GameObject *gameObject)
{
    auto it = std::find(removeObjects.begin(), removeObjects.end(), gameObject);
    if (it != removeObjects.end())
        return;
    removeObjects.push_back(gameObject);
}

const std::vector<GameObject *> &GameWorld::getGameObjects() const
{
    return gameObjects;
}

void GameWorld::copy(const GameWorld &GameWorld)
{
    // Delete all
    auto old = gameObjects;
    for (auto gO : old)
    {
        removeGameObject(gO);
    }

    for (auto gO : GameWorld.getGameObjects())
    {
        GameObject *gameObject = nullptr;
        if (gO->type == ObjectType::PLAYER)
        {
            Player* player = (Player*)gO;
            gameObject = new Player(player->index);
            Player* myPlayer = (Player*)gameObject;
            myPlayer->kills = player->kills;
            gameObject->xPosition = gO->xPosition;
            gameObject->yPosition = gO->yPosition;
            addGameObject(gameObject);
        }
        else if (gO->type == ObjectType::BULLET)
        {
            Bullet* bullet = (Bullet*)gO;
            gameObject = new Bullet(bullet->index);
            gameObject->xPosition = gO->xPosition;
            gameObject->yPosition = gO->yPosition;
            addGameObject(gameObject);
        }
        else if (gO->type == ObjectType::OBSTACLE)
        {
            gameObject = new Obstacle(gO->xPosition, gO->yPosition, gO->width, gO->height);
            addGameObject(gameObject);
        }
    }
}

void GameWorld::to_bin()
{
    int size = 0;
    for (GameObject *gameObject : gameObjects)
    {
        gameObject->to_bin();
        size += gameObject->size();
    }

    alloc_data(size + sizeof(size_t));

    char *pos = _data;
    size_t count = gameObjects.size();
    memcpy(pos, &count, sizeof(size_t));

    pos += sizeof(size_t);
    for (GameObject *gameObject : gameObjects)
    {
        memcpy(pos, gameObject->data(), gameObject->size());
        pos += gameObject->size();
    }
}

int GameWorld::from_bin(char *data)
{
    // Remove all
    auto old = gameObjects;
    for (auto gO : old)
    {
        removeGameObject(gO);
    }

    char *pos = data;
    size_t count = 0;
    memcpy(&count, pos, sizeof(size_t));

    pos += sizeof(size_t);
    while (count > 0)
    {
        ObjectType auxType;
        memcpy(&auxType, pos, sizeof(auxType));

        GameObject *gameObject = nullptr;
        if (auxType == ObjectType::PLAYER)
        {
            gameObject = new Player(-1);
            gameObject->from_bin(pos);
            pos += gameObject->size();
        }
        else if (auxType == ObjectType::BULLET)
        {
            gameObject = new Bullet();
            gameObject->from_bin(pos);
            pos += gameObject->size();
        }
        else if (auxType == ObjectType::OBSTACLE)
        {
            gameObject = new Obstacle();
            gameObject->from_bin(pos);
            pos += gameObject->size();
        }
        if (gameObject != nullptr)
            addGameObject(gameObject);

        count--;
    }

    return 0;
}

void GameWorld::setIndex(int index)
{
    GameWorldIndex = index;
}

int GameWorld::getIndex() const
{
    return GameWorldIndex;
}

void GameWorld::reset()
{
    for(GameObject* gameObject : gameObjects)
    {
        gameObject->reset();
    }
}

void GameWorld::restart()
{
    hasToRestart = true;
}

void GameWorld::checkCollisions()
{
    for (GameObject *gO : gameObjects)
    {
        for (GameObject *gO2 : gameObjects)
        {
            if (gO == gO2)
                continue;
            if (gO->checkCollision(gO2))
            {
                gO->onCollisionEnter(gO2);
            }
        }
    }
}