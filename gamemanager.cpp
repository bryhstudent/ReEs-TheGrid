#include "gamemanager.h"
#include "commonhunter.h"
#include "elitehunter.h"
#include "frag.h"
#include "pem.h"
#include <algorithm>
#include <cmath>
using namespace std;

GameManager::GameManager() {
    huntersFreezeRemaining = 0.0f;
    jugador = new Player(2.0f, 3.0f);
    hunters.push_back(new CommonHunter(1.0f, 1.0f));
    hunters.push_back(new EliteHunter(5.0f, 5.0f));
    hunters.push_back(new CommonHunter(14.0f, 1.0f));
    hunters.push_back(new CommonHunter(1.0f, 10.0f));
    hunters.push_back(new EliteHunter(15.0f, 8.0f));
    hunters.push_back(new CommonHunter(10.0f, 11.0f));
    for (auto hunter : hunters) {
        hunter->setWidth(0.65f);
        hunter->setHeight(0.65f);
    }

    hunterRoutes = {
        {{6.0f, 1.0f}, {6.0f, 6.0f}, {1.0f, 6.0f}, {1.0f, 1.0f}},
        {{9.0f, 5.0f}, {9.0f, 9.0f}, {5.0f, 9.0f}, {5.0f, 5.0f}},
        {{18.0f, 1.0f}, {18.0f, 4.0f}, {14.0f, 4.0f}, {14.0f, 1.0f}},
        {{5.0f, 10.0f}, {5.0f, 12.0f}, {1.0f, 12.0f}, {1.0f, 10.0f}},
        {{18.0f, 8.0f}, {18.0f, 11.0f}, {15.0f, 11.0f}, {15.0f, 8.0f}},
        {{13.0f, 11.0f}, {13.0f, 7.0f}, {10.0f, 7.0f}, {10.0f, 11.0f}}
    };
    hunterRouteIndices = {0, 0, 0, 0, 0, 0};

    items.push_back(new Frag(2.0f, 1.8f));
    items.push_back(new Frag(3.8f, 2.0f));
    items.push_back(new Frag(6.0f, 2.4f));
    items.push_back(new Frag(8.0f, 2.0f));
    items.push_back(new Frag(10.0f, 3.0f));
    items.push_back(new Frag(13.0f, 2.0f));
    items.push_back(new Frag(16.0f, 3.0f));
    items.push_back(new Frag(17.0f, 6.0f));
    items.push_back(new Frag(14.0f, 8.5f));
    items.push_back(new Frag(11.0f, 10.0f));
    items.push_back(new Frag(8.0f, 11.0f));
    items.push_back(new Frag(4.0f, 10.0f));
    items.push_back(new Frag(2.0f, 7.0f));
    items.push_back(new Frag(6.0f, 7.5f));
    items.push_back(new Frag(1.0f, 4.5f));
    items.push_back(new Frag(4.5f, 4.0f));
    items.push_back(new Frag(7.0f, 5.0f));
    items.push_back(new Frag(11.0f, 5.0f));
    items.push_back(new Frag(15.0f, 5.0f));
    items.push_back(new Frag(18.0f, 9.5f));
    items.push_back(new Frag(16.5f, 11.5f));
    items.push_back(new Frag(12.0f, 12.0f));
    items.push_back(new Frag(7.0f, 12.0f));
    items.push_back(new Frag(3.0f, 12.0f));
    items.push_back(new PEM(5.0f, 1.5f));
    items.push_back(new PEM(12.0f, 2.5f));
    items.push_back(new PEM(9.0f, 8.0f));
    items.push_back(new PEM(17.0f, 12.0f));
}

void GameManager::updateHunters(float elapsedSeconds) {
    if (elapsedSeconds <= 0.0f) return;
    if (huntersFreezeRemaining > 0.0f) {
        huntersFreezeRemaining = std::max(0.0f, huntersFreezeRemaining - elapsedSeconds);
        return;
    }
    for (size_t i = 0; i < hunters.size(); ++i) {
        if (i >= hunterRoutes.size() || hunterRoutes[i].empty()) continue;

        Hunter *hunter = hunters[i];
        EliteHunter *elite = dynamic_cast<EliteHunter*>(hunter);
        const float playerCenterX = jugador->getPosX() + jugador->getWidth() / 2.0f;
        const float playerCenterY = jugador->getPosY() + jugador->getHeight() / 2.0f;
        const bool pursuing = elite && elite->drawRadius(playerCenterX, playerCenterY);

        if (pursuing) {
            const float hunterCenterX = hunter->getPosX() + hunter->getWidth() / 2.0f;
            const float hunterCenterY = hunter->getPosY() + hunter->getHeight() / 2.0f;
            const float dx = playerCenterX - hunterCenterX;
            const float dy = playerCenterY - hunterCenterY;
            const float distance = std::sqrt(dx * dx + dy * dy);
            if (distance > 0.0f) {
                const float step = std::min(distance, hunter->getVelocity() * elapsedSeconds);
                const float velocity = hunter->getVelocity();
                if (velocity > 0.0f) {
                    hunter->move((dx / distance) * step / velocity,
                                 (dy / distance) * step / velocity);
                }
                if (hunter->intersects(*jugador)) {
                    if (std::abs(dx) >= std::abs(dy)) {
                        hunter->setPosY(jugador->getPosY());
                        hunter->setPosX(dx > 0.0f
                                            ? jugador->getPosX() - hunter->getWidth()
                                            : jugador->getPosX() + jugador->getWidth());
                    } else {
                        hunter->setPosX(jugador->getPosX());
                        hunter->setPosY(dy > 0.0f
                                            ? jugador->getPosY() - hunter->getHeight()
                                            : jugador->getPosY() + jugador->getHeight());
                    }
                }
            }
            continue;
        }

        const auto& target = hunterRoutes[i][hunterRouteIndices[i]];
        const float dx = target.first - hunter->getPosX();
        const float dy = target.second - hunter->getPosY();
        const float distance = std::sqrt(dx * dx + dy * dy);
        if (distance < 0.03f) {
            hunter->setPosX(target.first);
            hunter->setPosY(target.second);
            hunterRouteIndices[i] = (hunterRouteIndices[i] + 1) % hunterRoutes[i].size();
            continue;
        }

        const float step = std::min(distance, hunter->getVelocity() * elapsedSeconds);
        const float velocity = hunter->getVelocity();
        if (velocity > 0.0f) {
            hunter->move((dx / distance) * step / velocity,
                         (dy / distance) * step / velocity);
            if (hunter->intersects(*jugador)) {
                if (std::abs(dx) >= std::abs(dy)) {
                    hunter->setPosY(jugador->getPosY());
                    hunter->setPosX(dx > 0.0f
                                        ? jugador->getPosX() - hunter->getWidth()
                                        : jugador->getPosX() + jugador->getWidth());
                } else {
                    hunter->setPosX(jugador->getPosX());
                    hunter->setPosY(dy > 0.0f
                                        ? jugador->getPosY() - hunter->getHeight()
                                        : jugador->getPosY() + jugador->getHeight());
                }
            }
        }
    }
}

GameManager::~GameManager() {
    delete jugador;
    for (auto h : hunters) delete h;
    for (auto i : items) delete i;
}

string GameManager::processPlayerMovement(float dx, float dy) {
    const float oldX = jugador->getPosX();
    const float oldY = jugador->getPosY();
    const float moveX = dx * jugador->getVelocity();
    const float moveY = dy * jugador->getVelocity();

    if (moveX != 0.0f) {
        jugador->setPosX(oldX + moveX);
        for (auto hunter : hunters) {
            if (jugador->intersects(*hunter)) {
                jugador->setPosX(moveX > 0.0f ? hunter->getPosX() - jugador->getWidth()
                                               : hunter->getPosX() + hunter->getWidth());
                break;
            }
        }
    }

    if (moveY != 0.0f) {
        jugador->setPosY(oldY + moveY);
        for (auto hunter : hunters) {
            if (jugador->intersects(*hunter)) {
                jugador->setPosY(moveY > 0.0f ? hunter->getPosY() - jugador->getHeight()
                                               : hunter->getPosY() + hunter->getHeight());
                break;
            }
        }
    }
    string log = "Pos: (" + to_string(jugador->getPosX()) + ", " + to_string(jugador->getPosY()) + ")";
    return log;
}

string GameManager::checkCollisions() {
    string events = "";
    vector<Hunter*> currentlyTouching;
    for (auto hunter : hunters) {
        if (hunter->touches(*jugador)) {
            currentlyTouching.push_back(hunter);
            bool wasTouching = find(huntersTouchingPlayer.begin(), huntersTouchingPlayer.end(), hunter)
                               != huntersTouchingPlayer.end();
            if (!wasTouching) {
                hunter->attack(*jugador);
                events += "Atacado! Vidas: " + to_string(jugador->getRemainingLifes()) + " ";
            }
        }
    }
    for (auto item : items) {
        if (!item->getIsCollected() && item->intersects(*jugador)) {
            item->collectItem(*jugador);
            if (dynamic_cast<PEM*>(item)) {
                huntersFreezeRemaining = 5.0f;
            }
            events += "Item recolectado! Puntos: " + to_string(jugador->getScore()) + " ";
        }
    }
    huntersTouchingPlayer = currentlyTouching;
    return events;
}

bool GameManager::allItemsCollected() const {
    for (auto item : items) {
        if (!item->getIsCollected()) return false;
    }
    return true;
}

float GameManager::getHuntersFreezeRemaining() const {
    return huntersFreezeRemaining;
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
