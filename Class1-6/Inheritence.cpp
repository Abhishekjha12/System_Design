#include<iostream>
#include<string>
using namespace std;

class Car{
protected:
    string brand;
    string model;
    bool isEngineOn;
    int currentSpeed;

public:
    Car(string b,string a){
        this->brand=b;
        this->model=a;
        isEngineOn = false;
        currentSpeed = 0;
    }

     void startEngine() {
        isEngineOn = true;
        cout << brand << " " << model << " : Engine starts with a roar!" << endl;
    }

    void stopEngine() {
        isEngineOn = false;
        currentSpeed=0;
        cout<< brand << " " << model << " : Emgine is turned off."<<endl;
    }

    void accelerate(){
         if(!isEngineOn){
            cout<< brand << " " << model << " :Cannot accelerate Engine is off"<<endl;
            return;
         }
         currentSpeed += 20;
         cout<< brand << " " << model << " Accelerating to "<<currentSpeed<<"km/h"<<endl;
    }
    void brake(){
        currentSpeed -= 20;
        if(currentSpeed < 0) currentSpeed = 0;
        cout<< brand << " " << model << " : Braking! Speed is now" << currentSpeed << " km/h"<<endl; 
    }
    virtual ~Car(){}

};

class ManualCar : public Car{
private:
    int currentGear; // specific to manual car
public:
    ManualCar(string b,string a): Car(b,a){
        currentGear= 0;
    }

    //specialised method for manual car
    void shiftGear(int gear){
        currentGear = gear;
        cout<< brand << " " << model << " : Shifted to gear "<< currentGear <<endl;
    }
};
class ElectricCar : public Car{
private:
    int batteryLevel;
public:
    ElectricCar(string b,string a): Car(b,a){
        batteryLevel = 100;
    }
    //specialised feature for electric car
    void chargeBattery(){
        batteryLevel = 100;
        cout<< brand << " " <<  model << " : Battery is fully charged"<<endl;
    }
};
int main(){
    ManualCar *myManualCar = new ManualCar("Suzuki","wagonR");
    myManualCar->startEngine();
    myManualCar->shiftGear(1);
    myManualCar->accelerate();
    myManualCar->brake();
    myManualCar->stopEngine();
    delete myManualCar;

    cout << "--------------------"<<endl;
     
    ElectricCar *myEV = new ElectricCar("Tesla","Model 3");
    myEV->startEngine();
    myEV->accelerate();
    myEV->brake();
    myEV->stopEngine();
    myEV->chargeBattery();
    delete myEV;
    return 0;
}