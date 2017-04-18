#include <memory>
#include <iostream>
#include <list>

using namespace std;

class Observer {
    public:
        virtual void update(int runs, int wickets, float overs) = 0;
};

class Subject {
    public:
        virtual void registerObserver(Observer* o) = 0;
        virtual void unregisterObserver(Observer* o) = 0;
        virtual void notifyObservers() = 0;
};

class CricketData : public Subject {
    public:
        void registerObserver(Observer* o) {
            observerList.push_back(o);
        }

        void unregisterObserver(Observer* o) {
            observerList.remove(o);
        }

        void notifyObservers() {
            for (auto it : observerList)
                it->update(runs, wickets, overs);
        }

        void dataChanged() {
            runs = getLatestRuns();
            wickets = getLatestWickets();
            overs = getLatestOvers();

            notifyObservers();
        }

    private:
        int runs;
        int wickets;
        float overs;
        list<Observer*> observerList;

        int getLatestRuns() { return 90; }
        int getLatestWickets() { return 2; }
        float getLatestOvers() { return (float)10.2; }
};

class AverageScoreDisplay : public Observer {
    public:
        void update(int runs, int wickets, float overs) {
            runRate = (float)runs/overs;
            predictedScore = (int)(runRate * 50);
            display();
        }

    private:
        void display() {
            cout << endl
                 << "Average Score Display: \n"
                 << "Run Rate: " << runRate
                 << endl
                 << "PredictedScore: "
                 << predictedScore;
        }

        float runRate;
        int predictedScore;
};

class CurrentScoreDisplay : public Observer {
    public:
        void update(int runs, int wickets, float overs) {
            this->runs = runs;
            this->wickets = wickets;
            this->overs = overs;
            display();
        }

        void display() {
            cout << endl
                 << "Current Score Display:"
                 << endl << "Runs: " << runs
                 << endl << "Wickets: " << wickets
                 << endl << "Overs: " << overs;
        }

    private:
        float overs;
        int runs, wickets;
};

class Test {
    public:
        static void Main() {
            auto averageScoreDisplay = new AverageScoreDisplay;
            auto currentScoreDisplay = new CurrentScoreDisplay;

            CricketData cricketData;

            cricketData.registerObserver(averageScoreDisplay);
            cricketData.registerObserver(currentScoreDisplay);

            cricketData.dataChanged();

            cricketData.unregisterObserver(averageScoreDisplay);

            cricketData.dataChanged();

            delete averageScoreDisplay;
            delete currentScoreDisplay;
        }
};

int main() {
    Test::Main();
}
