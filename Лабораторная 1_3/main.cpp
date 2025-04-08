#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class Entity {
protected:
    std::string name;
    int health;
    int attack;
    int defense;
    const int maxHealth = 100;

public:
    Entity(const std::string& n, int h, int a, int d)
            : name(n), health(h), attack(a), defense(d) {}

    virtual void attackTarget(Entity& target) {
        int damage = attack - target.getDefense();
        if (damage > 0) {
            target.takeDamage(damage);
            std::cout << name << " attacks " << target.getName() << " for " << damage << " damage!\n";
        } else {
            std::cout << name << " attacks " << target.getName() << ", but it has no effect!\n";
        }
    }

    virtual void displayInfo() const {
        std::cout << "Name: " << name << ", HP: " << health << "/" << maxHealth
                  << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }

    virtual void heal(int amount) {
        health += amount;
        if (health > maxHealth) health = maxHealth;
        std::cout << name << " heals for " << amount << " HP. Current HP: " << health << "/" << maxHealth << std::endl;
    }

    virtual void takeDamage(int amount) {
        if (amount > 0) {
            health -= amount;
            if (health < 0) health = 0;
        }
    }

    // Геттеры
    const std::string& getName() const { return name; }
    int getDefense() const { return defense; }
    int getHealth() const { return health; }
    int getAttack() const { return attack; }

    virtual ~Entity() {}
};

class Character : public Entity {
public:
    Character(const std::string& n, int h, int a, int d)
            : Entity(n, h, a, d) {}

    void attackTarget(Entity& target) override {
        int damage = attack - target.getDefense();
        if (damage > 0) {
            if (rand() % 100 < 20) {
                damage *= 2;
                std::cout << "Critical hit! ";
            }
            target.takeDamage(damage);
            std::cout << name << " attacks " << target.getName() << " for " << damage << " damage!\n";
        } else {
            std::cout << name << " attacks " << target.getName() << ", but it has no effect!\n";
        }
    }

    void displayInfo() const override {
        std::cout << "Character: " << name << ", HP: " << health << "/" << maxHealth
                  << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }

    void heal(int amount) override {
        int actualHeal = amount + static_cast<int>(amount * 0.25);
        health += actualHeal;
        if (health > maxHealth) health = maxHealth;
        std::cout << name << " heals for " << actualHeal << " HP (bonus +25%). Current HP: "
                  << health << "/" << maxHealth << std::endl;
    }
};

class Monster : public Entity {
public:
    Monster(const std::string& n, int h, int a, int d)
            : Entity(n, h, a, d) {}

    void attackTarget(Entity& target) override {
        int damage = attack - target.getDefense();
        if (damage > 0) {
            if (rand() % 100 < 30) {
                damage += 5;
                std::cout << "Poisonous attack! ";
            }
            target.takeDamage(damage);
            std::cout << name << " attacks " << target.getName() << " for " << damage << " damage!\n";
        } else {
            std::cout << name << " attacks " << target.getName() << ", but it has no effect!\n";
        }
    }

    void displayInfo() const override {
        std::cout << "Monster: " << name << ", HP: " << health << "/" << maxHealth
                  << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }
};

class Boss : public Monster {
public:
    Boss(const std::string& n, int h, int a, int d)
            : Monster(n, h, a, d) {}

    void attackTarget(Entity& target) override {
        int damage = attack - target.getDefense();
        if (damage > 0) {
            if (rand() % 100 < 40) {
                damage += 10;
                std::cout << "Fire attack! ";
            }
            target.takeDamage(damage);
            std::cout << name << " attacks " << target.getName() << " for " << damage << " damage!\n";
        } else {
            std::cout << name << " attacks " << target.getName() << ", but it has no effect!\n";
        }
    }

    void displayInfo() const override {
        std::cout << "BOSS: " << name << ", HP: " << health << "/" << maxHealth
                  << ", Attack: " << attack << ", Defense: " << defense << std::endl;
    }
};

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    Character hero("Hero", 100, 20, 10);
    Monster goblin("Goblin", 50, 15, 5);
    Monster dragon("Dragon", 150, 25, 20);
    Boss finalBoss("Dark Lord", 200, 30, 25);

    Entity* entities[] = { &hero, &goblin, &dragon, &finalBoss };

    std::cout << "=== All entities ===" << std::endl;
    for (auto entity : entities) {
        entity->displayInfo();
    }

    std::cout << "\n=== Battle starts ===" << std::endl;

    for (int i = 1; i < 4; i++) {
        entities[0]->attackTarget(*entities[i]);
    }

    for (int i = 1; i < 4; i++) {
        entities[i]->attackTarget(*entities[0]);
    }

    std::cout << "\n=== Healing ===" << std::endl;
    hero.heal(20);

    std::cout << "\n=== Boss special attack ===" << std::endl;
    finalBoss.attackTarget(hero);

    std::cout << "\n=== After battle ===" << std::endl;
    for (auto entity : entities) {
        entity->displayInfo();
    }

    std::cout << "\n=== Additional tests ===" << std::endl;
    hero.heal(50);
    goblin.takeDamage(10);
    goblin.displayInfo();
    goblin.takeDamage(100);
    goblin.displayInfo();

    return 0;
}
