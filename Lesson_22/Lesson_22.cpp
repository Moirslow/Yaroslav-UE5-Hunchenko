#include <iostream>
#include <string>
#include <array>
#include <algorithm>

// ---------- Stats ----------
struct Stats
{
    int str = 0;
    int intel = 0;
    int agi = 0;
};

Stats AddStats(const Stats& a, const Stats& b)
{
    return { a.str + b.str, a.intel + b.intel, a.agi + b.agi };
}

// ---------- Passive Item ----------
class PassiveItem
{
private:
    Stats bonus;
    std::string icon;

public:
    PassiveItem() : bonus{ 0,0,0 }, icon("None") {}
    PassiveItem(const Stats& b, const std::string& ic) : bonus(b), icon(ic) {}

    Stats GetBonus() const { return bonus; }
    std::string GetIcon() const { return icon; }
};

// ---------- Weapon ----------
class Weapon
{
private:
    int damage = 0;          // сила урону
    int cooldown = 0;        // кулдаун після атаки (сек)
    std::string icon;

    int lastAttackTime = -1000000; // коли били востаннє

public:
    Weapon() : damage(0), cooldown(0), icon("None") {}
    Weapon(int dmg, int cd, const std::string& ic) : damage(dmg), cooldown(cd), icon(ic) {}

    bool IsReady(int timeNow) const
    {
        return (timeNow - lastAttackTime) >= cooldown;
    }

    int RemainingCooldown(int timeNow) const
    {
        int remain = cooldown - (timeNow - lastAttackTime);
        return std::max(0, remain);
    }

    // повертає урон, або 0 якщо ще не готова
    int Use(int timeNow)
    {
        if (!IsReady(timeNow))
            return 0;

        lastAttackTime = timeNow;
        return damage;
    }

    std::string GetIcon() const { return icon; }
};

// ---------- Character ----------
class Character
{
private:
    int health = 100;

    Stats baseStats;
    Stats currentStats;

    bool hasWeapon = false;
    Weapon weapon;

    std::array<bool, 3> hasPassive = { false, false, false };
    std::array<PassiveItem, 3> passives;

public:
    Character(int hp, const Stats& s) : health(hp), baseStats(s)
    {
        RecalcStats();
    }

    void RecalcStats()
    {
        currentStats = baseStats;
        for (int i = 0; i < 3; i++)
        {
            if (hasPassive[i])
                currentStats = AddStats(currentStats, passives[i].GetBonus());
        }
    }

    void SetPassive(int slot, const PassiveItem& item)
    {
        if (slot < 0 || slot >= 3) return;
        passives[slot] = item;
        hasPassive[slot] = true;
        RecalcStats();
    }

    void PickupWeapon(const Weapon& newWeapon)
    {
        if (!hasWeapon)
        {
            std::cout << "PickupWeapon: no weapon -> equipped " << newWeapon.GetIcon() << "\n";
        }
        else
        {
            std::cout << "PickupWeapon: already had " << weapon.GetIcon()
                << " -> replaced with " << newWeapon.GetIcon() << "\n";
        }

        weapon = newWeapon;
        hasWeapon = true;
    }

    void UseWeapon(int timeNow)
    {
        if (!hasWeapon)
        {
            std::cout << "UseWeapon: no weapon, can't attack\n";
            return;
        }

        if (weapon.IsReady(timeNow))
        {
            int dmg = weapon.Use(timeNow);
            std::cout << "UseWeapon: attack! damage=" << dmg
                << " (icon: " << weapon.GetIcon() << ")\n";
        }
        else
        {
            std::cout << "UseWeapon: cooldown, remaining="
                << weapon.RemainingCooldown(timeNow) << " sec\n";
        }
    }

    void Print() const
    {
        std::cout << "Character:\n";
        std::cout << "  HP: " << health << "\n";
        std::cout << "  Base stats: STR=" << baseStats.str
            << " INT=" << baseStats.intel
            << " AGI=" << baseStats.agi << "\n";
        std::cout << "  Current stats: STR=" << currentStats.str
            << " INT=" << currentStats.intel
            << " AGI=" << currentStats.agi << "\n";

        std::cout << "  Weapon: " << (hasWeapon ? weapon.GetIcon() : "None") << "\n";
        std::cout << "  Passives:\n";
        for (int i = 0; i < 3; i++)
        {
            if (hasPassive[i])
                std::cout << "    slot " << i << ": " << passives[i].GetIcon() << "\n";
            else
                std::cout << "    slot " << i << ": empty\n";
        }
    }
};

int main()
{
    Character hero(120, Stats{ 10, 5, 7 });

    // пасивки змінюють характеристики
    hero.SetPassive(0, PassiveItem(Stats{ +2, 0, +1 }, "Ring"));
    hero.SetPassive(1, PassiveItem(Stats{ 0, +3, 0 }, "Amulet"));

    Weapon sword(25, 3, "Sword"); // damage=25, cooldown=3
    Weapon bow(15, 1, "Bow");     // damage=15, cooldown=1

    hero.Print();
    std::cout << "----------------\n";

    // підбір зброї коли немає
    hero.PickupWeapon(sword);

    // застосування зброї: готова / в кулдауні
    hero.UseWeapon(10);  // ready
    hero.UseWeapon(11);  // cooldown
    hero.UseWeapon(13);  // ready again

    std::cout << "----------------\n";

    // підбір зброї коли вже є
    hero.PickupWeapon(bow);

    hero.UseWeapon(100); // ready
    hero.UseWeapon(100); // cooldown (same time)
    hero.UseWeapon(101); // ready

    return 0;
}

