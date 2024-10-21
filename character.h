#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "inventory.h" // Include Inventory header

class Character {
protected:
    std::string name;
    int health;
    Inventory inventory; // Use Inventory class for managing items

public:
    Character(const std::string& name, int health);
    virtual ~Character() = default;
    void TakeDamage(int damage);
    void Heal(int amount);
    void PickUpItem(const Item& item);
    bool HasItem(const std::string& itemName) const;
    bool RemoveItemByName(const std::string& itemName);
    const std::vector<Item>& GetInventory() const;
    std::string GetName() const;
    int GetHealth() const;
};

#endif // CHARACTER_H




















