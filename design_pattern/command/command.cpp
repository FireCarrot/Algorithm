#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Command {
public:
    virtual void execute() = 0;
};

class Light {
public:
    void on() {
        cout << "Light is on" << endl;
    }

    void off() {
        cout << "Light is off" << endl;
    }
};

class LightOnCommand : public Command {
public:
    LightOnCommand(unique_ptr<Light> light) : light(std::move(light)) {}
    virtual ~LightOnCommand() {
        cout << "~LightOnCommand: " << light.get() << endl;
    }
    void execute() { light->on(); }
private:
    unique_ptr<Light> light;
};

class LightOffCommand : public Command {
public:
    LightOffCommand(unique_ptr<Light> light) : light(std::move(light)) {}
    virtual ~LightOffCommand() {
        cout << "~LightOffCommand: " << light.get() << endl;
    }
    void execute() { light->off(); }
private:
    unique_ptr<Light> light;
};

class Stereo {
public:
    void on() {
        cout << "Stereo is on" << endl;
    }

    void off() {
        cout << "Stereo is off" << endl;
    }

    void setRadio() {
        cout << "Stereo is set for Radio" << endl;
    }

    void setVolume(int volume) {
        cout << "Stereo volume set to " << volume << endl;
    }
};

class StereoOffCommand : public Command {
public:
    StereoOffCommand(unique_ptr<Stereo> s) : stereo(std::move(s)) {}
    virtual ~StereoOffCommand() {
        cout << "StereoOffCommand: " << stereo.get() << endl;
    }
    void execute() { stereo->off(); }
private:
    unique_ptr<Stereo> stereo;
};

class StereoOnWithRadioCommand : public Command {
public:
    StereoOnWithRadioCommand(unique_ptr<Stereo> s) : stereo(std::move(s)) {}
    virtual ~StereoOnWithRadioCommand() {
        cout << "~StereoOnWithRadioCommand: " << stereo.get() << endl;
    }
    void execute() {
        stereo->on();
        stereo->setRadio();
        stereo->setVolume(12);
    }
private:
    unique_ptr<Stereo> stereo;
};

class SimpleRemoteControl {
public:
    SimpleRemoteControl() {}
    ~SimpleRemoteControl() {
        for (auto it = slots.begin(); it != slots.end(); it++) {
            cout << "~SimpleRemoteControl: " << (*it).get() << endl;
            (*it).reset();
        }
    }
    void setCommand(unique_ptr<Command> command) {
        slots.push_back(std::move(command));
    }

    void buttonWasPressed() {
        slots.back()->execute();
    }
private:
    vector<unique_ptr<Command>> slots;
};

class RemoteControlTest {
public:
    void Main() {
        unique_ptr<SimpleRemoteControl> remote = make_unique<SimpleRemoteControl>();
        unique_ptr<Light> light = make_unique<Light>();
        unique_ptr<Stereo> stereo = make_unique<Stereo>();

        unique_ptr<Command> lightOnCmd = make_unique<LightOnCommand>(move(light));
        remote->setCommand(move(lightOnCmd));
        remote->buttonWasPressed();
        unique_ptr<Command> stereoOnWithRadioCmd = make_unique<StereoOnWithRadioCommand>(move(stereo));
        remote->setCommand(move(stereoOnWithRadioCmd));
        remote->buttonWasPressed();
        remote.reset();
    }
};

int main() {
    RemoteControlTest test;
    test.Main();
}
