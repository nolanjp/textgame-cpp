#include <iostream>
#include <limits>
#include "area.h"
#include "player.h"

// Forward declaration of StartGame function
void StartGame();

int main() {
    int menuChoice = 0;
    bool exitProgram = false;

    // Main menu loop
    while (!exitProgram) {
        // Displaying the main menu in bright cyan
        std::cout << "\033[96m+-------------------------------+\n";
        std::cout << "| Welcome to the Adventure Game |\n";
        std::cout << "+-------------------------------+\n";
        std::cout << "| 1. Start Game                 |\n";
        std::cout << "| 2. Quit Game                  |\n";
        std::cout << "+-------------------------------+\n";
        std::cout << "Enter your choice: \033[0m";
        std::cin >> menuChoice;

        // Handling the user's menu choice
        switch (menuChoice) {
            case 1:
                StartGame(); // Start the game
                break;
            case 2:
                std::cout << "Thank you for playing. Goodbye!\n";
                exitProgram = true; // Set flag to exit the program
                break;
            default:
                std::cout << "Invalid choice, please enter 1 or 2.\n";
                std::cin.clear(); // Clear error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard 'bad' character(s)
                break;
        }
    }

    return 0;
}

void StartGame() {
    // Initializing game components
    Area gameArea;
    gameArea.LoadMapFromFile("textgame-cpp/game_map.txt");

    Player player("Explorer", 100);

    // Setting up the treasure vault room
    Room* treasureVault = gameArea.GetRoom("Treasure Vault");
    if (treasureVault) {
        treasureVault->SetLocked(true);
        treasureVault->SetUnlockItem("Key");
    }

    // Setting up the initial room
    Room* currentRoom = gameArea.GetRoom("Healing Room");
    if (!currentRoom) {
        std::cerr << "Starting room not found." << std::endl;
        return; // Exit the function if the starting room is not found
    }
    player.SetLocation(currentRoom);

    // Variables for game logic
    Room* previousRoom = nullptr; // For tracking the previous room
    bool bossDefeated = false;
    bool gameRunning = true;
    std::string lastRoomDescription; // To avoid repeating the room description

    // Main game loop
    while (gameRunning) {
        // Updating and displaying the current room's description
        if (lastRoomDescription != currentRoom->GetDescription()) {
            std::cout << "\n\033[33mCurrent Location:\033[0m " << currentRoom->GetDescription() << std::endl;
            lastRoomDescription = currentRoom->GetDescription();
        }

        // Displaying items in the current room
        if (!currentRoom->GetItems().empty()) {
            std::cout << "Items in the room:" << std::endl;
            for (const Item& item : currentRoom->GetItems()) {
                std::cout << "- " << item.GetName() << std::endl;
            }
        }
        else {
            std::cout << "There are no items in this room." << std::endl;
        }

        // Displaying the options available to the player
        std::cout << "Options: " << std::endl;
        std::cout << "1. Look around" << std::endl;
        std::cout << "2. Pick up item" << std::endl;
        std::cout << "3. View Inventory" << std::endl;
        std::cout << "4. Move to the next room" << std::endl;
        std::cout << "5. Go back to the previous room" << std::endl; // New option to go back
        std::cout << "6. Quit" << std::endl;

        // Handling the player's choice
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer

        switch (choice) { // Cases for different actions (1-6)
            case 1:
                if (currentRoom->GetDescription().find("menacing figure") != std::string::npos && !bossDefeated) {
                    if (!player.HasItem("Sword")) {
                        std::cout << "\033[31mWarning: You don't have a sword. It might be tough to win without it. Continue? (yes/no)\033[0m" << std::endl;
                        std::string response;
                        std::getline(std::cin, response);
                        if (response == "no") {
                            continue; // Go back to the main menu if the player decides not to proceed.
                        }
                    }
                    std::cout << "\033[31mThe boss emerges from the shadows! Ready your weapon.\033[0m" << std::endl;
                    int bossHealth = 100;

                    while (player.GetHealth() > 0 && bossHealth > 0) {
                        std::cout << "\nChoose your action:" << std::endl;
                        std::cout << "\033[31m1. Attack\033[0m" << std::endl;
                        std::cout << "\033[32m2. Use Health Potion\033[0m" << std::endl;
                        std::cout << "Your choice: ";

                        int actionChoice;
                        std::cin >> actionChoice;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if (actionChoice == 1) {
                            int playerDamage = player.HasItem("Sword") ? 20 : 5;
                            bossHealth -= playerDamage;
                            std::cout << "You strike the boss, dealing " << playerDamage << " damage." << std::endl;
                        }
                        else if (actionChoice == 2 && player.HasItem("Health Potion")) {
                            player.Heal(100); // Full heal
                            player.RemoveItemByName("Health Potion"); // Remove the health potion after use
                            std::cout << "You used a Health Potion to restore your health to full." << std::endl;
                        }
                        else {
                            std::cout << "No Health Potions left." << std::endl;
                            continue; // Allow another action choice without the boss attacking
                        }

                        if (bossHealth > 0) {
                            player.TakeDamage(25);
                            std::cout << "The boss attacks you for 25 damage." << std::endl;
                        }

                        std::cout << "Player Health: [" << std::string(player.GetHealth() / 5, '=') << std::string(20 - player.GetHealth() / 5, ' ') << "] " << player.GetHealth() << " HP" << std::endl;
                        std::cout << "Boss Health: [" << std::string(bossHealth / 5, '=') << std::string(20 - bossHealth / 5, ' ') << "] " << bossHealth << " HP" << std::endl;
                    }

                    if (player.GetHealth() > 0) {
                        std::cout << "\nAs the dust settles, you stand victorious. The boss has been defeated!" << std::endl;
                        bossDefeated = true;
                        player.PickUpItem(Item("Key", "A shiny key dropped by the boss."));
                        std::cout << "The boss dropped a key. You pick it up." << std::endl;
                    }
                    else {
                        std::cout << "\033[31mOverwhelmed by the boss's might, you succumb to your injuries. Game Over.\033[0m" << std::endl;
                        gameRunning = false;
                    }
                }
                else if (currentRoom->GetDescription().find("large chest") != std::string::npos) {
                    // Room 4 NPC and riddle logic
                    std::cout << "As you approach the large chest, the air grows thick with anticipation.\n";
                    std::cout << "Beside the chest, a Statue stirs to life, its eyes glowing with an ethereal light.\n\n";

                    std::cout << "\033[33m'Brave soul, the Statue begins, its voice echoing around you,\033[0m\n";
                    std::cout << "\033[33m'Before you lay claim to what lies within, you must prove your worth.'\033[0m\n";
                    std::cout << "\033[33m'Face my challenge with courage, or opt for a lesser reward without a test of spirit.'\033[0m\n";
                    std::cout << "\033[33m'Will you attempt my riddle, or claim half now? (attempt/claim):'\033[0m ";
                    std::string choice;
                    std::getline(std::cin, choice);

                    if (choice == "attempt") {
                        std::cout << "\n\033[33m'Very well. Heed my words closely,'\033[0m\n";
                        std::cout << "\033[33m'I am born in fear, raised in truth, and I come to my own in deed.'\033[0m\n";
                        std::cout << "\033[33m'When a time comes that I'm called forth, I serve the cause of need.'\033[0m\n";
                        std::cout << "\033[33m'What am I?'\033[0m\n";
                        std::cout << "\033[33mYour answer:\033[0m ";

                        std::string riddleAnswer;
                        std::getline(std::cin, riddleAnswer);

                        if (riddleAnswer == "Courage" || riddleAnswer == "courage") {
                            std::cout << "\n\033[32m'Correct! Courage indeed shines brightest in the heart of the true,' the Statue nods approvingly.\033[0m\n";
                            std::cout << "\033[32m'You have shown wisdom and bravery, and thus, the full treasure is rightfully yours.'\033[0m\n";
                            std::cout << "\033[32mThe chest opens before you, revealing its bountiful contents.\033[0m\n";
                            player.PickUpItem(Item("Treasure", "A vast wealth of gold and jewels."));
                        }
                        else {
                            std::cout << "\n\033[31m'Alas, the essence sought was courage,' the Statue sighs with a tone of disappointment.\033[0m\n";
                            std::cout << "\033[31m'Remember, true valor lies not in always knowing the answers,'\033[0m\n";
                            std::cout << "\033[31m'but in facing the questions with the heart of a lion. Take this lesser treasure,'\033[0m\n";
                            std::cout << "\033[31m'as a token of the trials you've faced and the journey yet to come.'\033[0m\n";
                            player.PickUpItem(Item("Lesser Treasure", "Half the collection of gold and jewels."));
                        }
                    }
                    else if (choice == "claim") {
                        std::cout << "\n\033[32m'Prudence is a virtue, albeit a less adventurous one,' remarks the Statue.\033[0m\n";
                        std::cout << "\033[32m'It gestures toward a smaller coffer at its feet. 'This portion of the treasure is now yours,'\033[0m\n";
                        std::cout << "\033[32m'may it serve you well on the paths you choose to walk.'\033[0m\n";
                        player.PickUpItem(Item("Lesser Treasure", "Half the collection of gold and jewels."));
                    }
                    else {
                        std::cout << "\n\033[31m'Indecision bears its own consequences,' intones the Statue as it returns to stillness.\033[0m\n";
                        std::cout << "\033[31m'The moment passes, and no treasure is offered.'\033[0m\n";
                        // Optionally, you might allow the player another attempt or continue with the game.
                    }
                }
                else {
                    // Existing behavior for looking around in other rooms
                    std::cout << "You take a moment to look around the room. It's quiet... perhaps too quiet." << std::endl;
                }
                break;
                // Inside your case 2: Pick up item, add a check for the specific room and item
            case 2: { // Option 2: Pick up item
                std::cout << "Enter the name of the item you want to pick up: ";
                std::string itemName;
                std::getline(std::cin, itemName);

                // Check if the player is in the Armory and tries to pick up the Sword
                if (currentRoom->GetDescription().find("various weapons") != std::string::npos && itemName == "Sword") {
                    std::cout << "\nAn old bladesmith appears and says,\n";
                    std::cout << "\033[33mI will give you this sword if you can answer my question correctly.\033[0m\n";
                    std::cout << "\033[33mWhat is 6 x 9 + 6 + 9?\033[0m" << std::endl; // Math question appears on a new line
                    int answer;
                    std::cin >> answer;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline character after the input

                    if (answer == 69) {
                        std::cout << "\033[33mGood Job! The sword is yours, use it responsibly.\033[0m" << std::endl;
                        // The player answered correctly, so they receive the sword.
                        // This line adds the sword to the player's inventory
                        player.PickUpItem(Item("Sword", "A sharp and sturdy sword"));
                    }
                    else {
                        std::cout << "\n\033[31mThat is incorrect. You cannot take the sword.\033[0m" << std::endl;
                        // The player answered incorrectly. They do not receive the sword.
                        // Here, you break out of the case, so the sword isn't added to the inventory.
                        break;
                    }
                }
                else {
                    // This block handles picking up other items as normal.
                    Item* item = currentRoom->FindItemByName(itemName);
                    if (item) {
                        player.PickUpItem(*item); // Add the item to the player's inventory
                        currentRoom->RemoveItem(*item); // Remove the item from the room
                        std::cout << "You have picked up the item." << std::endl; // Confirm the item is picked up
                    }
                    else {
                        std::cout << "Item not found." << std::endl; // The item wasn't found in the room
                    }
                }
                break;
            }
            case 3: {
                std::cout << "Your Inventory:" << std::endl;
                const auto& items = player.GetInventory(); // Use GetInventory to access player's items
                if (items.empty()) {
                    std::cout << "Empty" << std::endl;
                }
                else {
                    for (const auto& item : items) {
                        std::cout << "- " << item.GetName() << std::endl;
                    }
                }
                break;
            }
            case 4: { // Move to the next room
                Room* nextRoom = currentRoom->GetNextRoom();
                if (nextRoom && nextRoom->IsLocked()) {
                    if (player.HasItem(nextRoom->GetUnlockItem())) {
                        std::cout << "Using the key, you unlock the door." << std::endl;
                        nextRoom->SetLocked(false);
                        currentRoom = nextRoom;
                        player.SetLocation(currentRoom);

                        // Check for treasure immediately after unlocking the room
                        if (player.HasItem("Treasure")) {
                            std::cout << "Congratulations! You have successfully claimed the treasure and completed your adventure. Tales of your bravery and cunning will be remembered for generations." << std::endl;
                            gameRunning = false; // Ends the game
                        }
                        else if (player.HasItem("Lesser Treasure")) {
                            std::cout << "Well done! Though you may not have claimed the full treasure, your adventure is a success. Your journey and the challenges you overcame will still be celebrated." << std::endl;
                            gameRunning = false; // Ends the game
                        }
                        else {
                            // This else block can be used if there's additional logic needed for unlocked rooms without treasure.
                            std::cout << "You unlock the room and step inside." << std::endl;
                        }
                    }
                    else {
                        std::cout << "The door is locked. You need the key to enter." << std::endl;
                    }
                }
                else if (nextRoom) {
                    currentRoom = nextRoom;
                    player.SetLocation(currentRoom);
                    std::cout << "You move to the next room." << std::endl;
                }
                else {
                    // Ending logic for when there's no next room and the player has the treasure
                    if (player.HasItem("Treasure")) {
                        std::cout << "\033[32mCongratulations! With the Treasure in hand, you've completed your grand adventure.\033[0m" << std::endl;
                        gameRunning = false; // Ends the game
                    }
                    else if (player.HasItem("Lesser Treasure")) {
                        std::cout << "\033[32mWell done! Though it's not the full treasure, the Lesser Treasure you've secured marks a successful end to your journey.\033[0m" << std::endl;
                        gameRunning = false; // Ends the game
                    }
                    else {
                        // If the player has neither form of treasure by the end, you might keep this message or adjust it based on your game's narrative.
                        std::cout << "It seems there's nowhere else to go, try looking around for a treasure." << std::endl;
                    }
                }
                break;
            }
            case 5: { // Go back to the previous room
                Room* prevRoom = currentRoom->GetPrevRoom();
                if (prevRoom) {
                    currentRoom = prevRoom;
                    player.SetLocation(currentRoom);
                    std::cout << "You go back to the previous room." << std::endl;
                }
                else {
                    std::cout << "You are at the starting room. There is no room to go back to." << std::endl;
                }
                break;
            }
            case 6:
                std::cout << "\033[31mYou choose to end your adventure, leaving the mysteries of the dungeon behind.\033[0m" << std::endl;
                gameRunning = false;
                break;
        }
    }
}

    
 




















