#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include <string>
#include <utility>
#include "player.h"
#include "hunter.h"
#include "collectableitems.h"

class GameManager {
private:
    Player* jugador;
    std::vector<Hunter*> hunters;
    std::vector<CollectableItems*> items;
    std::vector<Hunter*> huntersTouchingPlayer;
    std::vector<std::vector<std::pair<float, float>>> hunterRoutes;
    std::vector<std::size_t> hunterRouteIndices;
    float huntersFreezeRemaining;

public:
    GameManager();
    ~GameManager();

    std::string processPlayerMovement(float dx, float dy);
    std::string checkCollisions();
    void updateHunters(float elapsedSeconds);
    bool allItemsCollected() const;
    float getHuntersFreezeRemaining() const;

    Player* getPlayer() const;
    const std::vector<Hunter*>& getHunters() const;
    const std::vector<CollectableItems*>& getItems() const;
};

#endif // GAMEMANAGER_H
