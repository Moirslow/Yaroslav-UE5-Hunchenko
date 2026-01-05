// Lesson_19.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <map>

int main() {
    int N;
    std::cin >> N;

    std::vector<std::string> commands(N);
    for (int i = 0; i < N; i++) {
        std::cin >> commands[i];
    }

    int x, y;
    std::cin >> x >> y;

    std::map<std::string, std::pair<int, int>> moves = {
        {"right",    { 1,  0}},
        {"left",     {-1,  0}},
        {"forward",  { 0,  1}},
        {"backward", { 0, -1}}
    };

    for (const auto& cmd : commands) {
        auto it = moves.find(cmd);
        if (it != moves.end()) {
            x += it->second.first;
            y += it->second.second;
        }
    }

    std::cout << x << " " << y << "\n";
    return 0;
}

