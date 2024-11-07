#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include "room.h"

class Player : public Character {
private:
    Room* location;

public:
    Player(const std::string& name, int health);
    void SetLocation(Room* room);
    Room* GetLocation() const;
};

#endif // PLAYER_H


























