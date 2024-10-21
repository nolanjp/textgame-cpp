#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "item.h"

class Inventory {
private:
    std::vector<Item> items;

public:
    void AddItem(const Item& item);
    bool HasItem(const std::string& itemName) const;
    bool RemoveItemByName(const std::string& itemName);
    const std::vector<Item>& GetItems() const;
};

#endif // INVENTORY_H


