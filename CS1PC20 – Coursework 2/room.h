#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "item.h"

class Room {
private:
    std::string description;
    std::vector<Item> items;
    Room* nextRoom;
    Room* prevRoom;
    bool isLocked;
    std::string unlockItem;

public:
    Room(const std::string& desc, bool locked = false, const std::string& unlockItemName = "");
    void AddItem(const Item& item);
    void RemoveItem(const Item& item);
    std::string GetDescription() const;
    Item* FindItemByName(const std::string& itemName);
    std::vector<Item>& GetItems();
    Room* GetNextRoom() const;
    void SetNextRoom(Room* nextRoom);
    Room* GetPrevRoom() const;
    void SetPrevRoom(Room* prevRoom);
    bool IsLocked() const;
    void SetLocked(bool locked);
    std::string GetUnlockItem() const;
    void SetUnlockItem(const std::string& unlockItemName);
};

#endif // ROOM_H


























