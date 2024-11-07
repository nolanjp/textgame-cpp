#include "character.h"

Character::Character(const std::string& name, int health) : name(name), health(health) {}

void Character::TakeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

void Character::Heal(int amount) {
    health += amount;
    if (health > 100) health = 100;
}

void Character::PickUpItem(const Item& item) {
    inventory.AddItem(item);
}

bool Character::HasItem(const std::string& itemName) const {
    return inventory.HasItem(itemName);
}

bool Character::RemoveItemByName(const std::string& itemName) {
    return inventory.RemoveItemByName(itemName);
}

const std::vector<Item>& Character::GetInventory() const {
    return inventory.GetItems();
}

std::string Character::GetName() const {
    return name;
}

int Character::GetHealth() const {
    return health;
}











