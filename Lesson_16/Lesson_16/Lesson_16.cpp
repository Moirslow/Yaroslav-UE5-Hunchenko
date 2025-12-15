// Lesson_16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>


int main()
{
    std::string name;            // character name
    int health;                  // health points
    int classChoice;             // class choice (number)
    std::string characterClass;  // class name

    std::cout << "Character Creation\n\n";

    std::cout << "Enter character name: ";
    std::cin >> name;

    std::cout << "Enter health points: ";
    std::cin >> health;

    std::cout << "Choose class (enter number):\n";
    std::cout << "1 - Spellhowler\n";
    std::cout << "2 - Gladiator\n";
    std::cout << "3 - Bladedancer\n";
    std::cout << "Your choice: ";
    std::cin >> classChoice;

    if (classChoice == 1)
    {
        characterClass = "Spellhowler";
    }
    else if (classChoice == 2)
    {
        characterClass = "Gladiator";
    }
    else if (classChoice == 3)
    {
        characterClass = "Bladedancer";
    }
    else
    {
        std::cout << "Invalid class choice. Default class set to Gladiator.\n";
        characterClass = "Gladiator";
    }

    std::cout << "\nCharacter created!\n";
    std::cout << "Name: " << name << "\n";
    std::cout << "Health: " << health << "\n";
    std::cout << "Class: " << characterClass << "\n";

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
