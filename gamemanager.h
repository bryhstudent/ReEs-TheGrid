#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include <string>
#include "player.h"
#include "hunter.h"
#include "commonhunter.h"
#include "elitehunter.h"
#include "collectableitems.h"
#include "frag.h"
#include "pem.h"

using namespace std;

class GameManager {
private:
    Player* jugador;
    vector<Hunter*> hunters;
    vector<CollectableItems*> items;

public:
    GameManager();
    ~GameManager();

    string processPlayerMovement(float dx, float dy);
    string checkCollisions();

    // Getters para que MainWindow / UI lea el estado
    Player* getPlayer() const;
    const vector<Hunter*>& getHunters() const;
    const vector<CollectableItems*>& getItems() const;
};

#endif // GAMEMANAGER_H
