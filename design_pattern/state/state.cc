#include <iostream>
#include <algorithm>
#include <cctype>
#include <functional>
#include <string>

class Statelike {
    public:
        virtual void writeName(StateContext context, string name) = 0;
};

class StateLowerCase : public Statelike {
    public:
        void writeName(const StateContext context, const string name) {
            transform(name.begin(), name.end(), name.begin(), ptr_fun<int, int>(tolower));
            cout << name << endl;

            context.setState(new StateMultipleUpperCase());
        }
};

class StateMultipleUpperCase : public Statelike {
    public:
        void writeName(const StateContext context, const string name) {
            transform(name.begin(), name.end(), name.begin(), ptr_fun<int, int>(touppper));
            cout << name << endl;

            if (++count > 1) {
                context.setState(new StateLowerCase());
            }
        }
    private:
        int count = 0;
};

class StateContext {
    public:
        StateContext() {
            setState(new StateLowerCase());
        }

        void writeName(const string name) {
            myState->writeName(this, name);
        }
    private:
        void setState(const Statelike* newState) {
            delete myState;
            myState = newState;
        }


        Statelike* myState;
};

class DemoOfClientState {
    public:
        static void Main() {
            const StateContext sc;

            sc.writeName("Monday");
            sc.writeName("Tuesday");
            sc.writeName("Wednesday");
            sc.writeName("Thursday");
            sc.writeName("Friday");
            sc.writeName("Saturday");
            sc.writeName("Sunday");
        }
};

int main() {
    DemoOfClientState::Main();
}
