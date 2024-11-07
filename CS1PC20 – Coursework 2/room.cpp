#include "room.h"
#include <algorithm>

Room::Room(const std::string& desc, bool locked, const std::string& unlockItemName)
    : description(desc), nextRoom(nullptr), prevRoom(nullptr), isLocked(locked), unlockItem(unlockItemName) {}

void Room::AddItem(const Item& item) {
    items.push_back(item);
}

void Room::RemoveItem(const Item& item) {
    auto it = std::find_if(items.begin(), items.end(),
        [&item](const Item& i) { return i.GetName() == item.GetName(); });
    if (it != items.end()) {
        items.erase(it);
    }
}

std::string Room::GetDescription() const {
    return description;
}

Item* Room::FindItemByName(const std::string& itemName) {
    auto it = std::find_if(items.begin(), items.end(),
        [&itemName](const Item& item) { return item.GetName() == itemName; });
    return it != items.end() ? &*it : nullptr;
}

std::vector<Item>& Room::GetItems() {
    return items;
}

Room* Room::GetNextRoom() const {
    return nextRoom;
}

void Room::SetNextRoom(Room* room) {
    nextRoom = room;
    if (room) {
        room->SetPrevRoom(this);
    }
}

Room* Room::GetPrevRoom() const {
    return prevRoom;
}

void Room::SetPrevRoom(Room* room) {
    prevRoom = room;
}

bool Room::IsLocked() const {
    return isLocked;
}

void Room::SetLocked(bool locked) {
    isLocked = locked;
}

std::string Room::GetUnlockItem() const {
    return unlockItem;
}

void Room::SetUnlockItem(const std::string& unlockItemName) {
    unlockItem = unlockItemName;
}





























