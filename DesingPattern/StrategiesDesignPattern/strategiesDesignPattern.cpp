#include<iostream>
using namespace std;

//Strategy Interface for walk
class WalkableRobot{
public:
    virtual void walk()=0;
    virtual ~WalkableRobot(){}
};

class NormwalWalk : public WalkableRobot{
public:
    void walk() override{
        cout<<"Walking Normally..."<<endl;
    }
};

class NoWalk : public WalkableRobot{
public:
    void walk() override{
        cout<<"Cannot walk..."<<endl;
    }
};


//Stratey Interface for talking robot
class TalkableRobot{
public:
    virtual void talk()=0;
    virtual ~TalkableRobot(){}
};

// Concrete Strategies for Talking Robot
class NormalTalk : public TalkableRobot{
public:
    void talk() override{
        cout<<"Talking Normally..."<<endl;
    }
};

class NoTalk:public TalkableRobot{
public:
    void talk() override{
        cout<<"Cannot talk"<<endl;
    }
};

class FlyableRobot{
public:
    virtual void fly()=0;
    virtual ~FlyableRobot(){}
};

//Strategies for flying robot
class normalfly :  public FlyableRobot{
public:
    void fly()override{
        cout<<"Can Fly"<<endl;
    }
};

class nonflyble : public FlyableRobot{
public:
    void fly()override{
        cout<<"Cannot fly"<<endl;
    }
};

class Robot{
protected:
    WalkableRobot* WalkBehaviour;
    TalkableRobot* talkBehaviour;
    FlyableRobot* flyBehaviour;

public:
    Robot(WalkableRobot* w, TalkableRobot* t,FlyableRobot* f){
        this->WalkBehaviour = w;
        this->talkBehaviour = t;
        this->flyBehaviour = f;
    }

    void walk(){
        WalkBehaviour->walk();
    }

    void talk(){
        talkBehaviour->talk();
    }

    void fly(){
        flyBehaviour->fly();
    }

    virtual void projection()=0; // Abstract method for subclasses
};


// Concrete Robot type
class CompanionRobot: public Robot{
public:
    CompanionRobot(WalkableRobot* w,TalkableRobot* t,FlyableRobot* f) : Robot(w,t,f){}

    void projection() override{
        cout<<"Displaying friendly companion feature..."<<endl;
    }
};

class workerRobot : public Robot{
public:
    workerRobot(WalkableRobot* w,TalkableRobot* t,FlyableRobot* f) : Robot(w,t,f){}

    void projection(){
        cout<<"Displaying worker efficiency stats..."<<endl;
    }
};

int main(){
    Robot* robot1 = new CompanionRobot(new NormwalWalk(),new NormalTalk(),new normalfly());
    robot1->walk();
    robot1->talk();
    robot1->fly();
    robot1->projection();

    cout<< "___________________"<<endl<<endl;

    Robot* robot2 = new workerRobot(new NoWalk(),new NoTalk(), new normalfly());
    robot2->walk();
    robot2->talk();
    robot2->fly();

    robot2->projection();

    return 0;
}