#include "gamemanager.h"

using namespace std;

GameManager::GameManager() {
    jugador = new Player(2.0f, 3.0f);
    hunters.push_back(new CommonHunter(1.0f, 1.0f));
    hunters.push_back(new EliteHunter(5.0f, 5.0f));
    items.push_back(new Frag(2.0f, 2.0f));
    items.push_back(new PEM(3.0f, 3.0f));
}

GameManager::~GameManager() {
    delete jugador;
    for (auto h : hunters) delete h;
    for (auto i : items) delete i;
}

string GameManager::processPlayerMovement(float dx, float dy) {
    jugador->move(dx, dy);
    string log = "Pos: (" + to_string(jugador->getPosX()) + ", " + to_string(jugador->getPosY()) + ")";
    string collisionEvent = checkCollisions();
    if (!collisionEvent.empty()) {
        log += " | " + collisionEvent;
    }
    return log;
}

string GameManager::checkCollisions() {
    string events = "";
    for (auto hunter : hunters) {
        if (hunter->getPosX() == jugador->getPosX() && hunter->getPosY() == jugador->getPosY()) {
            hunter->attack(*jugador);
            events += "Atacado! Vidas: " + to_string(jugador->getRemainingLifes()) + " ";
        }
    }
    for (auto item : items) {
        if (!item->getIsCollected() && item->getPosX() == jugador->getPosX() && item->getPosY() == jugador->getPosY()) {
            item->collectItem(*jugador);
            events += "Item recolectado! Puntos: " + to_string(jugador->getScore()) + " ";
        }
    }
    return events;
}

Player* GameManager::getPlayer() const {
    return jugador;
}

const vector<Hunter*>& GameManager::getHunters() const {
    return hunters;
}

const vector<CollectableItems*>& GameManager::getItems() const {
    return items;
}
