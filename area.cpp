#include "area.h"
#include <iostream>

Area::Area() {}

Area::~Area() {
    for (auto& pair : rooms) {
        delete pair.second;
    }
}

void Area::AddRoom(const std::string& name, Room* room) {
    rooms[name] = room;
}

Room* Area::GetRoom(const std::string& name) const {
    auto it = rooms.find(name);
    if (it != rooms.end()) {
        return it->second;
    }
    return nullptr;
}

void Area::LoadMapFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }
    std::map<std::string, std::string> nextRoomMappings; // Store next room names temporarily
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string roomName, description, itemName, nextRoomName;
        std::getline(iss, roomName, '|');
        std::getline(iss, description, '|');
        std::getline(iss, itemName, '|');
        std::getline(iss, nextRoomName, '|');

        Room* room;
        if (rooms.find(roomName) == rooms.end()) {
            room = new Room(description);
            rooms[roomName] = room;
        }
        else {
            room = rooms[roomName];
        }

        if (!itemName.empty() && itemName != "null") {
            room->AddItem(Item(itemName, "It looks important."));
        }

        // Save the next room name for later linking
        if (!nextRoomName.empty() && nextRoomName != "null") {
            nextRoomMappings[roomName] = nextRoomName;
        }
    }

    // Link rooms after all have been created
    for (const auto& pair : nextRoomMappings) {
        const auto& currentRoomName = pair.first;
        const auto& nextRoomName = pair.second;
        if (rooms.find(nextRoomName) != rooms.end()) {
            rooms[currentRoomName]->SetNextRoom(rooms[nextRoomName]);
        }
    }
}



















