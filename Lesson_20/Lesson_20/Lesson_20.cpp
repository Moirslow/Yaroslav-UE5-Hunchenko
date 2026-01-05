// Lesson_20.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <iomanip>

struct Character {
    std::string name;
    int health = 0;
    int x = 0;
    int y = 0;

    // For report
    int healthBefore = 0;
    bool wasDamaged = false;
    double distanceToMeteor = 0.0;
};

double CalculateDistance(int x1, int y1, int x2, int y2) {
    long long dx = static_cast<long long>(x1) - x2;
    long long dy = static_cast<long long>(y1) - y2;
    return std::sqrt(static_cast<double>(dx * dx + dy * dy));
}

int ReadInt(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        int value;
        if (std::cin >> value) {
            return value;
        }
        std::cout << "Invalid input. Please enter an integer.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

Character ReadCharacter(int index) {
    Character c;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "\n--- Character #" << index << " ---\n";
    std::cout << "Name: ";
    std::getline(std::cin, c.name);

    while (c.name.empty()) {
        std::cout << "Name cannot be empty. Try again: ";
        std::getline(std::cin, c.name);
    }

    c.health = ReadInt("Health: ");
    c.x = ReadInt("Position X: ");
    c.y = ReadInt("Position Y: ");

    return c;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int characterCount = ReadInt("Enter number of characters: ");
    while (characterCount <= 0) {
        std::cout << "Number must be greater than zero.\n";
        characterCount = ReadInt("Enter number of characters: ");
    }

    std::vector<Character> characters;
    characters.reserve(characterCount);

    for (int i = 1; i <= characterCount; ++i) {
        characters.push_back(ReadCharacter(i));
    }

    std::cout << "\n--- Meteor Data ---\n";
    int meteorX = ReadInt("Meteor X: ");
    int meteorY = ReadInt("Meteor Y: ");

    int damage = ReadInt("Meteor damage: ");
    while (damage < 0) {
        std::cout << "Damage cannot be negative.\n";
        damage = ReadInt("Meteor damage: ");
    }

    int power = ReadInt("Meteor power: ");
    while (power < 0) {
        std::cout << "Power cannot be negative.\n";
        power = ReadInt("Meteor power: ");
    }

    const double damageRadius = 3.0 * static_cast<double>(power);

    bool hasDeadCharacters = false;
    std::vector<std::string> damagedCharacters;

    // Apply meteor damage
    for (auto& c : characters) {
        c.healthBefore = c.health;
        c.distanceToMeteor = CalculateDistance(c.x, c.y, meteorX, meteorY);

        if (c.distanceToMeteor <= damageRadius) {
            c.wasDamaged = true;
            c.health -= damage;
            damagedCharacters.push_back(c.name);
        }

        if (c.health <= 0) {
            hasDeadCharacters = true;
        }
    }

    // Output results
    std::cout << "\n============================\n";
    std::cout << "          RESULT\n";
    std::cout << "============================\n";
    std::cout << "Meteor position: (" << meteorX << ", " << meteorY << ")\n";
    std::cout << "Damage: " << damage << "\n";
    std::cout << "Power: " << power << "\n";
    std::cout << "Damage radius (3 * power): " << damageRadius << "\n\n";

    if (damagedCharacters.empty()) {
        std::cout << "No characters were damaged.\n\n";
    }
    else {
        std::cout << "Damaged characters:\n";
        for (const auto& name : damagedCharacters) {
            std::cout << "- " << name << "\n";
        }
        std::cout << "\n";
    }

    std::cout << "Dead characters after impact: "
        << (hasDeadCharacters ? "YES" : "NO") << "\n\n";

    // Detailed report
    std::cout << "Detailed report:\n";
    std::cout << std::left
        << std::setw(25) << "Name"
        << std::setw(12) << "HP (before)"
        << std::setw(12) << "HP (after)"
        << std::setw(14) << "Distance"
        << std::setw(12) << "Damaged"
        << "Status\n";

    std::cout << std::string(85, '-') << "\n";

    for (const auto& c : characters) {
        std::cout << std::left
            << std::setw(25) << c.name.substr(0, 24)
            << std::setw(12) << c.healthBefore
            << std::setw(12) << c.health
            << std::setw(14) << std::fixed << std::setprecision(2) << c.distanceToMeteor
            << std::setw(12) << (c.wasDamaged ? "YES" : "NO")
            << (c.health <= 0 ? "DEAD" : "ALIVE")
            << "\n";
    }

    return 0;
}

