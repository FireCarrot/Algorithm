#include <map>
#include <string>

class Player {
public:
    void assignWeapon(string weapon);
    void mission() = 0;

private:
    const string TASK;
    string weapon;
};

class Terrorist : public Player {
public:
    Terrorist() {
        TASK = "PLANT A BOMB";
    }

    void mission() {
        cout << "Terrorist with weapon " << weapon << "|" + " Task is " + TASK;
    }
};

class CounterTerrorist : public Player {
public:
    CounterTerrorist() {
        TASK = "DIFFUSE BOMB";
    }

    void mission() {
        cout << "Counter Terrorist with weapon " << weapon << "|" + " Task is " + TASK;
    }
};

class PlayerFactory {
public:
    static Player* getPlayer(string type) {
        Player* p = hm.find(type);
        if (p)
            return p;

        switch(type) {
        case "Terrorist":
            cout << "Terrorist Created";
            p = new Terrorist();
            break;
        case "CounterTerrorist":
            cout << "Counter Terrorist Created";
            p = new CounterTerrorist();
            break;
        default:
            cout << "Unreachable code!";
            return p;
        }

        hm.insert(make_pair(type, p));
        return p;
    }

private:
    static map<string, Player*> hm;
};

class CounterStrike {
public:
    CounterStrike() {
        playerType = {"Terrorist", "CounterTerrorist"};
        weapons = {"AK-47", "Maverick", "Gut Knife", "Desert Eagle"};
    }

    static void Main() {
        for (int i = 0; i < 10; i++) {
            Player* p = PlayerFactory.getPlayer(getRandPlayerType());
            if (!p)
                return;

            p->assignWeapon(getRandWeapon());
            p->mission();
        }
    }

    static string getRandPlayerType() {
        int randInt = rand() % playerType.size();
        return playerType[randInt];
    }

    static string getRandWeapon() {
        int randInt = ran() % weapons.size();
        return weapons[randInt];
    }

private:
    static vector<string> playerType;
    static vector<string> weapons;
};

int main() {
    CounterStrike cs;
    cs.Main();

    return 0;
}
