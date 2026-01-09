#include<iostream>
#include<string>

using namespace std;

//Component Interface: defines a common interface for Mario and all power up decorators
class Character{
public:
    virtual string getAbilities() const = 0;
    virtual ~Character() {} // Virtual destructor
};

// Concrete Component : Basic Mario character with no power-ups
class mario : public Character{
public:
    string getAbilities() const override{
        return "Mario";
    }
};

// Abstract Decorator: CharacterDecorator "is-a" Character and "has-a" Character.
class CharacterDecorator : public Character{
protected:
    Character *character; //wrapped component
public:
    CharacterDecorator(Character* c){
        this->character = c;
    }
};

// Concrete Decorator : Height-Increasing Power-up
class HeightUp: public CharacterDecorator{
public:
    HeightUp(Character* c):CharacterDecorator(c){ }

    string getAbilities() const override{
        return character->getAbilities() + "With Height Up.";
    }
};

// Concrete Decorator : Gun Shooting Power-up
class Gun: public CharacterDecorator{
public:
    Gun(Character* c):CharacterDecorator(c){ }

    string getAbilities() const override{
        return character->getAbilities() + "With Gun.";
    }
};

// Concrete Decorator : Star Power-up(temporary ability)
class Star: public CharacterDecorator{
public:
    Star(Character* c):CharacterDecorator(c){ }

    string getAbilities() const override{
        return character->getAbilities() + "With Star Power (Limited Time).";
    }
};

int main(){
    //Create a basic Mario Character
    Character* Mario = new mario();
    cout<< "Basic Character:" << Mario->getAbilities()<<endl;

    //Decorator with height up
    Mario = new HeightUp(Mario);
    cout<<"After HeightUp: "<<Mario->getAbilities()<<endl;

    //Decorator Mario Further with Gun power
    Mario = new Gun(Mario);
    cout<<"After Gun up: "<<Mario->getAbilities()<<endl;

    //Decorator with Star Power-up
    Mario = new Star(Mario);
    cout<<"After HeightUp: "<<Mario->getAbilities()<<endl;

    delete Mario;

    return 0;
}