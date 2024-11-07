#include "player.h"

Player::Player(const std::string& name, int health) : Character(name, health), location(nullptr) {}

void Player::SetLocation(Room* room) {
    this->location = room;
}

Room* Player::GetLocation() const {
    return location;
}

























