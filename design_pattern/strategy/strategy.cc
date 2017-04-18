#include <iostream>

using namespace std;

class KickBehavior {
    public:
        virtual void kick() = 0;
};

class LighteningKick : public KickBehavior {
    public:
        void kick() { cout << "Lightening Kick"; }
};

class TornadoKick : public KickBehavior {
    public:
        void kick() { cout << "Tornado Kick"; }
};

class JumpBehavior {
    public:
        virtual void jump() = 0;
};

class ShortJump : public JumpBehavior {
    public:
        void jump() { cout << "Short Jump"; }
};

class LongJump : public JumpBehavior {
    public:
        void jump() { cout << "Long Jump"; }
};

class Fighter {
    public:
        Fighter(KickBehavior* kick,
                JumpBehavior* jump)
            : kickBehavior(kick)
            , jumpBehavior(jump) {}

        void punch() { cout << "Default Punch"; }
        void roll() { cout << "Default Roll"; }
        void kick() { kickBehavior->kick(); }
        void jump() { jumpBehavior->jump(); }

        void setKickBehavior(KickBehavior* kick) {
            kickBehavior = kick;
        }

        void setJumpBehavior(JumpBehavior* jump) {
            jumpBehavior = jump;
        }

        virtual void display() = 0;

    private:
        KickBehavior* kickBehavior;
        JumpBehavior* jumpBehavior;
};


class Ken : public Fighter {
    public:
        Ken(KickBehavior* kick,
            JumpBehavior* jump) : Fighter(kick, jump) {}
        void display() { cout << "Ken"; }
};

class ChunLi : public Fighter {
    public:
        ChunLi(KickBehavior* kick,
               JumpBehavior* jump) : Fighter(kick, jump) {}
        void display() { cout << "ChuLi"; }
};

class StreetFighter {
    public:
        static void Main() {
            ShortJump shortJump;
            LongJump longJump;
            TornadoKick tornadoKick;

            Ken ken(&tornadoKick, &shortJump);
            ken.display();

            ken.punch();
            ken.kick();
            ken.jump();

            // Change behavior dynamically (algorithms are interchangeable)
            ken.setJumpBehavior(&longJump);
            ken.jump();
        }
};

int main() {
    StreetFighter::Main();
}
