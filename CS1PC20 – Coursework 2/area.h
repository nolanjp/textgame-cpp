#ifndef AREA_H
#define AREA_H

#include "room.h"
#include <map>
#include <string>
#include <fstream>
#include <sstream>

class Area {
private:
    std::map<std::string, Room*> rooms;

public:
    Area();
    ~Area();
    void AddRoom(const std::string& name, Room* room);
    Room* GetRoom(const std::string& name) const;
    void LoadMapFromFile(const std::string& filename);
};

#endif // AREA_H


















