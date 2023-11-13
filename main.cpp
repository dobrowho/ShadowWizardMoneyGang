#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#ifdef __linux__
#include <X11/Xlib.h>
#endif

//clasa pentru consumabile
class Consumable
{
private:
    std::string name;
    std::string description;
    int attack;
    int speed;
    int health;
    int armor;
    int price;
public:
    Consumable() = default;
    explicit Consumable(std::string& _name);
    Consumable(const std::string& _name, const std::string& _description,
               int _attack, int _speed, int _health, int _armor, int _price)
    {
        name = _name;
        description = _description;
        attack = _attack;
        speed = _speed;
        health = _health;
        armor = _armor;
        price = _price;

        std::cout << "Constructor pentru consumabil.\n";
    }
    friend std::ostream& operator<<(std::ostream& os, const Consumable& consumable)
    {
        os << "Name: " << consumable.name << "\n";
        os << "Description: " << consumable.description << "\n";
        os << "Attack: " << consumable.attack << "\n";
        os << "Speed: " << consumable.speed << "\n";
        os << "Health: " << consumable.health << "\n";
        os << "Armor: " << consumable.armor << "\n";
        os << "Price: " << consumable.price << "\n";

        return os;
    }
    int getAttack() const {return attack;}
    int getSpeed() const {return speed;}
    int getPrice() const {return price;}
    const std::string& getName() const {return name;}

};

Consumable::Consumable(std::string &_name) : name{_name = "Potiune"}
{
    std::cout << "CI pentru consumabil.\n";
}

//clasa pentru arme
class Weapon
{
private:
    std::string name;
    std::string rarity;
    std::string description;
    int attack;
    int speed;
    int price;
public:
    Weapon() = default;
    explicit Weapon(std::string& _name);
    Weapon(const std::string& _name, const std::string& _description,
               int _attack, int _speed, int _price)
    {
        name = _name;
        description = _description;
        attack = _attack;
        speed = _speed;
        price = _price;

        std::cout << "Constructor pentru arma.\n";
    }
    Weapon(const Weapon& other) : name{other.name}, rarity{other.rarity},
                                  description{other.description}, attack{other.attack}, speed{other.speed}, price{other.price}
    {
        std::cout << "CC pentru arma.\n";
    }
    Weapon& operator=(const Weapon& other)
    {
        name = other.name;
        rarity = other.rarity;
        description = other.description;
        attack = other.attack;
        speed = other.speed;
        price = other.price;
        std::cout << "operator= copiere arma.\n";

        return *this;
    }
    ~Weapon()
    {
        std::cout << "Destructor arma.\n";
    }
    friend std::ostream& operator<<(std::ostream& os, const Weapon& weapon)
    {
        os << "Name: " << weapon.name << "\n";
        os << "Rarity: " << weapon.rarity << "\n";
        os << "Description: " << weapon.description << "\n";
        os << "Attack: " << weapon.attack << "\n";
        os << "Speed: " << weapon.speed << "\n";
        os << "Price: " << weapon.price << "\n";

        return os;
    }
    int getPrice() const {return price;}
    const std::string& getName() const {return name;}
    void upgrade(const Consumable& consumable)
    {
        attack += consumable.getAttack();
        speed += consumable.getSpeed();
    }

};

Weapon::Weapon(std::string &_name) : name{_name = "Sword"}
{
    std::cout << "CI pentru arma.\n";
}

//clasa pentru personajul principal
class MC
{
private:
    std::string name;
    int attack;
    int speed;
    int health;
    int armor;
    int money;
    std::vector<Weapon> weapons;
    std::vector<Consumable> consumables;
public:
    explicit MC(std::string& _name) : name{_name}
    {
        std::cout << "CI pentru MC.\n";
    }
    MC(const std::string& _name = "Wizard", int _attack = 5, int _speed = 5, int _health = 10, int _armor = 10, int _money = 100)
    {
        name = _name;
        attack = _attack;
        speed = _speed;
        armor = _armor;
        health = _health;
        money = _money;

        std::cout << "Construcor pentru mc.\n";
    }
    friend std::ostream& operator<<(std::ostream& os, const MC& mc)
    {
        os << "Personajul principal este:\n";
        os << "Name: " << mc.name << "\n";
        os << "Attack: " << mc.attack << "\n";
        os << "Speed: " << mc.speed << "\n";
        os << "Health: " << mc.health << "\n";
        os << "Armor: " << mc.armor << "\n" << "\n";

        return os;
    }
    const std::string& getName() const {return name;}
    void buy(const Weapon& weapon)
    {
        if(money >= weapon.getPrice())
        {
            money -= weapon.getPrice();
            weapons.push_back(weapon);
            std::cout << weapon.getName() << " optained!\n";
        }
        else
        {
            std::cout << "Bani insuficienti pentru a cumpara " << weapon.getName() << "!" << "\n";
        }
    }
    void buy(const Consumable& consumable)
    {
        if(money >= consumable.getPrice())
        {
            money -= consumable.getPrice();
            consumables.push_back(consumable);
            std::cout << consumable.getName() << " optained!\n";
        }
        else
        {
            std::cout << "Bani insuficienti pentru a cumpara " << consumable.getName() << "!" << "\n";
        }
    }
    void upgrade(const Consumable& consumable)
    {
        attack += consumable.getAttack();
        speed += consumable.getSpeed();
    }

};

//clasa pentru inamici
class Enemy
{
private:
    std::string name;
    int attack;
    int speed;
    int health;
    Weapon weapon;
    Consumable consumable;
public:
    explicit Enemy(std::string& _name) : name{_name}
    {
        std::cout << "CI pentru enemy.\n";
    }
    Enemy(const std::string& _name = "Orc", int _attack = 2, int _speed = 2, int _health = 5, const Weapon& _weapon = Weapon(), const Consumable& _consumable = Consumable())
    {
        name = _name;
        attack = _attack;
        speed = _speed;
        health = _health;
        weapon = _weapon;
        consumable = _consumable;
    }
    friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy)
    {
        os << "Name: " << enemy.name << "\n";
        os << "Attack: " << enemy.attack << "\n";
        os << "Speed: " << enemy.speed << "\n";
        os << "Health: " << enemy.health << "\n";

        return os;
    }
    const std::string& getName() const {return name;}
};

//clasa pentru caractere
class Characters
{
private:
    MC mc;
    std::vector<Enemy> enemies;
public:
    void addEnemies(int number, const Enemy& enemy)
    {
        while(number--)
        enemies.push_back(enemy);
    }
    MC& getMC() {return mc;}
    void getEnemies() const
    {
        std::cout << "Enemies:" << "\n";
        for(const auto& enem : enemies)
            std::cout << enem.getName() << "\n";
        std::cout << "\n";
    }
};

int main() {
    Characters characters;

    std::cout << characters.getMC();
    characters.addEnemies(5, Enemy());

    characters.getEnemies();

    return 0;
}
