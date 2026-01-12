// Lesson_21.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>

class Character {
private:
    std::string name;
    int health;
    int x;
    int y;
    int speed;

public:
    Character(const std::string& name_, int health_, int x_, int y_, int speed_)
        : name(name_), health(health_), x(x_), y(y_), speed(speed_) {
    }

    void Move(int dirX, int dirY) {
        x += dirX * speed;
        y += dirY * speed;
    }

    int GetX() const { return x; }
    int GetY() const { return y; }
    const std::string& GetName() const { return name; }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<Character> characters;
    characters.reserve(n);

    for (int i = 0; i < n; i++) {
        std::string name;
        int health, x, y, speed;
        std::cin >> name >> health >> x >> y >> speed;

        characters.emplace_back(name, health, x, y, speed);
    }

    int commandsCount;
    std::cin >> commandsCount;

    for (int i = 0; i < commandsCount; i++) {
        int index, dx, dy;
        std::cin >> index >> dx >> dy;

        index--; // convert from 1-based to 0-based

        if (index >= 0 && index < n) {
            characters[index].Move(dx, dy);
        }
    }

    // Output final positions
    for (int i = 0; i < n; i++) {
        std::cout << characters[i].GetName()
            << " position: (" << characters[i].GetX()
            << ", " << characters[i].GetY() << ")\n";
    }

    return 0;
}

