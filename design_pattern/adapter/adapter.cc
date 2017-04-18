#include <iostream>

using namespace std;

class Bird {
    public:
        virtual void fly() = 0;
        virtual void makeSound() = 0;
};

class Sparrow : public Bird {
    public:
        void fly() {
            cout << "Flying";
        }
        void makeSound() {
            cout << "Chirp Chirp";
        }
};

class ToyDuck {
    public:
       virtual void squeak() = 0;
};

class PlasticToyDuck : public ToyDuck {
    public:
        void squeak() {
            cout << "Squeak";
        }
};

class BirdAdapter : public ToyDuck {
    public:
        BirdAdapter(Bird* toy) : toyBird(toy) {}
        void squeak() { toyBird->makeSound(); }

    private:
        Bird* toyBird;
};

class Test {
    public:
        static void Main() {
            Sparrow* sparrow = new Sparrow();
            PlasticToyDuck* toyDuck = new PlasticToyDuck();

            ToyDuck* birdAdapter = new BirdAdapter(sparrow);

            cout << "Sparrow...";
            sparrow->fly();
            sparrow->makeSound();

            cout << "ToyDuck...";
            toyDuck->squeak();

            cout << "BirdAdapter...";
            birdAdapter->squeak();
        }
};

int main() {
    Test::Main();
}
