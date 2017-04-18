#include <map>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

class Player {
public:
    Player(string T) : TASK(T) {}
    void assignWeapon(string weapon) { this->weapon = weapon; }
    string getWeapon() { return weapon; }
    string getTASK() { return TASK; }
    virtual void mission() {}

private:
    const string TASK;
    string weapon;
};

class Terrorist : public Player {
public:
    Terrorist() : Player("PLANT A BOMB") {}

    virtual void mission() {
        cout << "Terrorist with weapon " << getWeapon() << "|" << " Task is " << getTASK();
    }
};

class CounterTerrorist : public Player {
public:
    CounterTerrorist() : Player("DIFFUSE BOMB") {}

    virtual void mission() {
        cout << "Counter Terrorist with weapon " << getWeapon() << "|" << " Task is " << getTASK();
    }
};

class PlayerFactory {
public:
    static Player& getPlayer(string type) {
        map<string, Player&>::iterator it = hm.find(type);
        if (it != hm.end())
            return reinterpret_cast<Player&>(*it);

        Player* p = nullptr;
        if (type == "Terrorist") {
            cout << "Terrorist Created";
            p = new Terrorist();
        } else if (type == "CounterTerrorist") {
            cout << "Counter Terrorist Created";
            p = new CounterTerrorist();
        } else {
            cout << "Unreachable code!";
            return reinterpret_cast<Player&>(*p);
        }

        hm.insert(pair<string, Player&>(type, reinterpret_cast<Player&>(*p)));
        return reinterpret_cast<Player&>(*p);
    }

private:
    static map<string, Player&> hm;
};

class CounterStrike {
public:
    static void Main() {
        for (int i = 0; i < 10; i++) {
            Player& p = PlayerFactory::getPlayer(getRandPlayerType());
            p.assignWeapon(getRandWeapon());
            p.mission();
        }
    }

    static string getRandPlayerType() {
        string playerType[] = {"Terrorist", "CounterTerrorist"};
        int randInt = rand() % 2;
        return playerType[randInt];
    }

    static string getRandWeapon() {
        string weapons[] = {"AK-47", "Maverick", "Gut Knife", "Desert Eagle"};
        int randInt = rand() % 4;
        return weapons[randInt];
    }
};

int main() {
    CounterStrike::Main();

    return 0;
}
