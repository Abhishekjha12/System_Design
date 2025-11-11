#include<iostream>
using namespace std;
// Return type rule 
//subtype overriden method return type should be either identical
//or narrorwer then the parent method's return type
// c++ enforced this by covariance

class Animal{
    // some commom Animal method

};
class Dog: public Animal{

};
class Parent{
public:
    virtual Animal* getAnimal(){
        cout<<"Parent : Returning Animal instances"<<endl;
        return new Animal();
    }
};
class Child:public Parent{
public:
    Dog* getAnimal() override{  // here we can return both Dog and Animal class
         cout<<"Child : Returning Dog instance"<<endl;
        return new Dog();
    }
};
class Client{
private:
    Parent* p;
public:
    Client(Parent* p){
        this->p=p;
    }
    void takeAnimal(){
        p->getAnimal();
    }
};
int main(){
    Parent* parent = new Parent();
    Child* child = new Child();

    Client* client = new Client(parent);
    client->takeAnimal();

    return 0;
}