#include <iostream>
#include <vector>
using namespace std;

struct Player {
    string name;
    int hp;
};

// 1) «читати гравц≥в
void readPlayers(vector<Player>& players, int n) {
    for (int i = 0; i < n; i++) {
        Player p;
        cout << "Player " << (i + 1) << " name: ";
        cin >> p.name;

        cout << "Player " << (i + 1) << " hp: ";
        cin >> p.hp;

        players.push_back(p);
    }
}

// 2) «астосувати шкоду до вс≥х
void applyDamage(vector<Player>& players, int damage) {
    for (int i = 0; i < (int)players.size(); i++) {
        players[i].hp = players[i].hp - damage;
    }
}

// 3) «найти ≥ндекс гравц€ з найб≥льшим hp
int findMaxHpIndex(const vector<Player>& players) {
    int maxIndex = 0;
    for (int i = 1; i < (int)players.size(); i++) {
        if (players[i].hp > players[maxIndex].hp) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

// 4) «найти ≥ндекс гравц€ з найменшим hp
int findMinHpIndex(const vector<Player>& players) {
    int minIndex = 0;
    for (int i = 1; i < (int)players.size(); i++) {
        if (players[i].hp < players[minIndex].hp) {
            minIndex = i;
        }
    }
    return minIndex;
}

// 5) ¬ивести мертвих гравц≥в
void printDeadPlayers(const vector<Player>& players) {
    bool found = false;

    for (int i = 0; i < (int)players.size(); i++) {
        if (players[i].hp <= 0) {
            cout << players[i].name << " is dead (hp = " << players[i].hp << ")\n";
            found = true;
        }
    }

    if (!found) {
        cout << "No dead players.\n";
    }
}

int main() {
    int n;
    cout << "Enter number of players: ";
    cin >> n;

    vector<Player> players;
    readPlayers(players, n);

    int damage;
    cout << "Enter damage (one digit): ";
    cin >> damage;

    applyDamage(players, damage);

    int q;
    cout << "Choose query:\n";
    cout << "1 - who has max hp\n";
    cout << "2 - who has min hp\n";
    cout << "3 - who is dead\n";
    cout << "Your choice: ";
    cin >> q;

    if (q == 1) {
        int idx = findMaxHpIndex(players);
        cout << "Max hp: " << players[idx].name << " (hp = " << players[idx].hp << ")\n";
    }
    else if (q == 2) {
        int idx = findMinHpIndex(players);
        cout << "Min hp: " << players[idx].name << " (hp = " << players[idx].hp << ")\n";
    }
    else if (q == 3) {
        printDeadPlayers(players);
    }
    else {
        cout << "Wrong query option.\n";
    }

    return 0;
}
