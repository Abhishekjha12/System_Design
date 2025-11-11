#include<iostream>
#include<string>
using namespace std;

// Base class
class Car {
public:
    virtual void startEngine()=0;
    virtual void shiftGear()=0;
    virtual void accelerate()=0;
    virtual void brake()=0;
    virtual void stopEngine()=0;
    virtual ~Car(){}
};

// Derived class
class sportCar: public Car {
private:
    string brand;
    string model;
    bool isEngineOn;
    int currentSpeed;
    int currentGear;
    string tyre;

public:
    sportCar(string b, string a) {
        brand = b;
        model = a;
        isEngineOn = false;
        currentSpeed = 0;
        currentGear = 0;
        tyre = "MRF";
    }

    // now since these private entities cant be changed but these values can be visible
    // and to perform this action we use getter and setter
    
    //getter and setter
    int getCurrentSpeed(){
        return this->currentSpeed;
    }
    string getTyre(){
        return this->tyre;
    }
    void setTyre(string tyre){
        //we can add validation too here using setters
        this->tyre=tyre;
    }
    void startEngine() {
        isEngineOn = true;
        cout << brand << " " << model << " : Engine starts with a roar!" << endl;
    }

    // This one satisfies the base class pure virtual method
    void shiftGear() {
        if(!isEngineOn) {
            cout << brand << " " << model << " : Engine is off! Cannot shift gear." << endl;
            return;
        }
        currentGear++;
        cout << brand << " " << model << " : Shifted to gear " << currentGear << endl;
    }

    // Overloaded version: lets you choose a gear
    void shiftGear(int gear) {
        if(!isEngineOn) {
            cout << brand << " " << model << " : Engine is off! Cannot shift gear." << endl;
            return;
        }
        currentGear = gear;
        cout << brand << " " << model << " : Shifted directly to gear " << currentGear << endl;
    }

    void accelerate() {
        if(isEngineOn && currentGear > 0) {
            currentSpeed += 20;
            cout << brand << " " << model << " : Accelerating to " << currentSpeed << " km/h" << endl;
        } else {
            cout << brand << " " << model << " : Cannot accelerate, check engine/gear." << endl;
        }
    }

    void brake() {
    if(currentSpeed > 0) {
        currentSpeed = 0; // immediate stop
        cout << brand << " " << model << " : Braking! Speed is now 0 km/h" << endl;
    } else {
        cout << brand << " " << model << " : Already stopped." << endl;
    }
}


    void stopEngine() {
        if(currentSpeed == 0 && isEngineOn) {
            isEngineOn = false;
            currentGear = 0;
            cout << brand << " " << model << " : Engine is turned off." << endl;
        } else if(currentSpeed > 0) {
            cout << brand << " " << model << " : Can't stop engine while moving!" << endl;
        } else {
            cout << brand << " " << model << " : Engine already off." << endl;
        }
    }
};

int main() {
    // Car* myCar = new sportCar("Ford","Mustang");
    // myCar->startEngine();
    // myCar->shiftGear();       // uses no-argument version
    // myCar->accelerate();
    // myCar->shiftGear();       // again increments gear
    // myCar->accelerate();
    // myCar->shiftGear();       // increments once more
    // myCar->brake();
    // myCar->stopEngine();

    
    // delete myCar;

    sportCar * mySportCar = new sportCar("Ford","Mustang");

    mySportCar->startEngine();
    mySportCar->shiftGear();
    mySportCar->accelerate();
    mySportCar->shiftGear();
    mySportCar->accelerate();
    mySportCar->brake();
    mySportCar->stopEngine();


    // mySportCar->currentSpeed = 500;
    // cout<<"Current speed of my car is Set to " <<mySportCar->currentSpeed<<endl;

    cout<<mySportCar->getCurrentSpeed();
    
    delete mySportCar;

    return 0;
}
