#include "inventory.h"
#include <algorithm>

void Inventory::AddItem(const Item& item) {
    items.push_back(item);
}

bool Inventory::HasItem(const std::string& itemName) const {
    for (const auto& item : items) {
        if (item.GetName() == itemName) return true;
    }
    return false;
}

bool Inventory::RemoveItemByName(const std::string& itemName) {
    auto it = std::find_if(items.begin(), items.end(), [&itemName](const Item& item) {
        return item.GetName() == itemName;
        });

    if (it != items.end()) {
        items.erase(it);
        return true; // Item was found and removed
    }
    return false; // Item was not found
}

const std::vector<Item>& Inventory::GetItems() const {
    return items;
}
