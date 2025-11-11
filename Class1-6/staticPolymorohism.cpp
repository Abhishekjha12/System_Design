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
        brand = b;
        model = a;
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

    // compile-time polymorphism via overloading
    void accelerate() {
        if(!isEngineOn) {
            cout << brand << " " << model << " : Cannot accelerate, engine is off." << endl;
            return;
        }
        currentSpeed += 20;
        cout << brand << " " << model << " : Accelerating to " << currentSpeed << " km/h" << endl;
    }

    void brake() {
        currentSpeed -= 20;
        if(currentSpeed < 0) currentSpeed = 0;
        cout << brand << " " << model << " : Braking! Speed is now " << currentSpeed << " km/h" << endl;
    }
};

// ---------------- ManualCar ----------------
class ManualCar : public Car {
public:
    using Car::accelerate;
private:
    int currentGear;
public:
    ManualCar(string b,string a): Car(b,a) {
        currentGear = 0;
    }

    // specialised method
    void shiftGear(int gear) {
        currentGear = gear;
        cout << brand << " " << model << " : Shifted to gear " << currentGear << endl;
    }

    // overload accelerate (static polymorphism)
    void accelerate(int boost) {
        if(!isEngineOn) {
            cout << brand << " " << model << " : Cannot accelerate, engine is off." << endl;
            return;
        }
        currentSpeed += boost;
        cout << brand << " " << model << " : Accelerating with boost to " << currentSpeed << " km/h" << endl;
    }
};

// ---------------- ElectricCar ----------------
class ElectricCar : public Car {
private:
    int batteryLevel;
public:
    ElectricCar(string b,string a): Car(b,a) {
        batteryLevel = 100;
    }

    // overload accelerate (different behavior for EV)
    void accelerate(double factor) {
        if(!isEngineOn) {
            cout << brand << " " << model << " : Cannot accelerate, engine is off." << endl;
            return;
        }
        if(batteryLevel <= 0) {
            cout << brand << " " << model << " : Battery empty! Cannot accelerate." << endl;
            return;
        }
        currentSpeed += (int)(30 * factor);
        batteryLevel -= 10;
        cout << brand << " " << model << " : Accelerating to " << currentSpeed 
             << " km/h. Battery at " << batteryLevel << "%" << endl;
    }

    void chargeBattery() {
        batteryLevel = 100;
        cout << brand << " " << model << " : Battery is fully charged" << endl;
    }
};

// ---------------- Main ----------------
int main() {
    ManualCar myManual("Suzuki","WagonR");
    myManual.startEngine();
    myManual.shiftGear(1);
    myManual.accelerate();      // base class accelerate()
    myManual.accelerate(40);    // overloaded accelerate()
    myManual.brake();
    myManual.stopEngine();

    cout << "--------------------" << endl;

    ElectricCar myEV("Tesla","Model 3");
    myEV.startEngine();
    myEV.accelerate(1.5);       // overloaded accelerate() for EV
    myEV.brake();
    myEV.stopEngine();
    myEV.chargeBattery();

    return 0;
}
