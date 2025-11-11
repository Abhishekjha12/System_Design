#include<iostream>
#include<string>
using namespace std;

class Car {
protected:
    string brand;
    string model;
    bool isEngineOn;
    int currentSpeed;

public:
    Car(string b,string a) {
        this->brand = b;
        this->model = a;
        isEngineOn = false;
        currentSpeed = 0;
    }

    void startEngine() {
        isEngineOn = true;
        cout << brand << " " << model << " : Engine starts with a roar!" << endl;
    }

    void stopEngine() {
        isEngineOn = false;
        currentSpeed = 0;
        cout << brand << " " << model << " : Engine is turned off." << endl;
    }

    virtual void accelerate() = 0; // Abstract Method for Dynamic Polymorphism
    virtual void brake() = 0;      // Abstract Method for Dynamic Polymorphism
    virtual ~Car(){}               // Virtual Destructor
};

// ---------------- Manual Car ----------------
class ManualCar : public Car {
private:
    int currentGear; // specific to manual car
public:
    ManualCar(string b,string a): Car(b,a) {
        currentGear = 0;
    }

    // specialised method for manual car
    void shiftGear(int gear) {
        currentGear = gear;
        cout << brand << " " << model << " : Shifted to gear " << currentGear << endl;
    }

    void accelerate() {
        if(!isEngineOn) {
            cout << brand << " " << model << " : Cannot accelerate, engine is off." << endl;
            return;
        }
        currentSpeed += 20;
        cout << brand << " " << model << " : Accelerating to " << currentSpeed << " km/h" << endl;
    }

    // overriding brake - dynamic polymorphism
    void brake() {
        currentSpeed -= 20;
        if(currentSpeed < 0) currentSpeed = 0;
        cout << brand << " " << model << " : Braking! Speed is now " << currentSpeed << " km/h" << endl;
    }
};

// ---------------- Electric Car ----------------
class ElectricCar : public Car {
private:
    int batteryLevel;
public:
    ElectricCar(string b,string a): Car(b,a) {
        batteryLevel = 100;
    }

    // override accelerate
    void accelerate() {
        if(!isEngineOn) {
            cout << brand << " " << model << " : Cannot accelerate, engine is off." << endl;
            return;
        }
        if(batteryLevel <= 0) {
            cout << brand << " " << model << " : Battery empty! Cannot accelerate." << endl;
            return;
        }
        currentSpeed += 30;  // EV accelerates faster ⚡
        batteryLevel -= 10;
        cout << brand << " " << model << " : Accelerating to " << currentSpeed 
             << " km/h. Battery at " << batteryLevel << "%" << endl;
    }

    // override brake
    void brake() {
        currentSpeed -= 30;
        if(currentSpeed < 0) currentSpeed = 0;
        cout << brand << " " << model << " : Braking! Speed is now " 
             << currentSpeed << " km/h" << endl;
    }

    // specialised feature for electric car
    void chargeBattery() {
        batteryLevel = 100;
        cout << brand << " " <<  model << " : Battery is fully charged" << endl;
    }
};

// ---------------- Main ----------------
int main() {
    ManualCar *myManualCar = new ManualCar("Suzuki","WagonR");
    myManualCar->startEngine();
    myManualCar->shiftGear(1);
    myManualCar->accelerate();
    myManualCar->brake();
    myManualCar->stopEngine();
    delete myManualCar;

    cout << "--------------------" << endl;
     
    ElectricCar *myEV = new ElectricCar("Tesla","Model 3");
    myEV->startEngine();
    myEV->accelerate();
    myEV->brake();
    myEV->stopEngine();
    myEV->chargeBattery();
    delete myEV;

    return 0;
}
