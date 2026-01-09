#include<iostream>
using namespace std;
class Burger{
public:
    virtual void prepare()=0; // Pure virtual class
};

class BasicBurger : public Burger{
public:
    void prepare() override{
        cout<<"Preparing the Basic Burger with bun, patty and Ketchup!"<<endl;
    }
};

class StandardBurger : public Burger {
public:
    void prepare() override{
        cout<<"Preparing Standard Burger with bun, patty , cheese and lettuce!"<<endl;
    }
};

class PremiumBurger : public Burger{
public:
    void prepare() override{
        cout<<"Preparing Premimum Burger with the gourmet bun, premium patty , cheese and lettuce"<<endl;
    }
};

class BasicWheatBurger : public Burger{
public:
    void prepare() override{
        cout<<"Preparing Basic wheat Burger with bun, patty and ketchup!"<<endl;
    }
};

class StandardWheatBurger : public Burger{
public:
    void prepare() override{
        cout<<"Preparing Standard wheat Burger with bun, patty, cheese and lettuce!"<<endl;
    }
};

class PremiumWheatBurger : public Burger{
public:
    void prepare() override{
        cout<<"Preparing Premium wheat Burger with gourmet bun, premium patty, cheese and lettuce!"<<endl;
    }
};

class GarlicBread{
public:
    virtual void prepare() = 0;
};

class BasicGarlicBread : public GarlicBread {
public:
    void prepare() override{
        cout<<"Preparing Basic Garlic Bread with Butter and garlic!\n";
    }
};

class CheeseGarlicBread : public GarlicBread {
public:
    void prepare() override{
        cout<<"Preparing Cheese Garlic Bread with extra cheese and butter!\n";
    }
};

class BasicWheatGarlicBread : public GarlicBread {
public:
    void prepare() override{
        cout<<"Preparing Garlic Bread with wheat flour and butter!\n";
    }
};

class CheeseWheatGarlicBread : public GarlicBread {
public:
    void prepare() override{
        cout<<"Preparing Cheese Garlic Bread with wheat flour and butter!\n";
    }
};

//Factory and its connection

class MealFactory{
public:
    virtual Burger* createBurger(string &type)=0;
    virtual GarlicBread* createGarlicbread(string &type)=0;
};

class SinghBurger : public MealFactory{
public:
    Burger* createBurger(string &type) override{
        if(type == "basic"){
            return new BasicBurger();
        }
        else if(type=="standard"){
            return new StandardBurger();
        }
        else if(type=="premium"){
            return new PremiumBurger();
        }
        else{
            cout<<"Invalid Burger type!"<<endl;
            return nullptr;
        }
    }
    
    GarlicBread* createGarlicbread(string &type)override{
        if(type == "Basic"){
            return new BasicGarlicBread();
        }else if(type=="cheese"){
            return new CheeseGarlicBread();
        }
        else{
            cout<<"Invalid Garlic bread type!"<<endl;
            return nullptr;
        }
    }
};

class KingBurger : public MealFactory{
public:
    Burger* createBurger(string &type) override{
        if(type == "basic"){
            return new BasicWheatBurger();
        }
        else if(type == "Standard"){
            return new StandardWheatBurger();
        }
        else if(type=="premium"){
            return new PremiumWheatBurger();
        }
        else{
            cout<<"Invalid burger type!"<<endl;
            return nullptr;
        }
    }

    GarlicBread* createGarlicbread(string &type)override{
        if(type=="basic"){
            return new BasicWheatGarlicBread();
        }
        else if(type=="cheese"){
            return new CheeseGarlicBread();
        }
        else{
            cout<<"Invalid Garlic Bread Type!"<<endl;
            return nullptr;
        }
    }
};

int main(){
    string burgerType = "basic";
    string GarlicBreadType = "cheese";

    MealFactory* mealFactory = new KingBurger();

    Burger* burger = mealFactory->createBurger(burgerType);
    GarlicBread* garlicBread = mealFactory->createGarlicbread(GarlicBreadType);
    
    burger->prepare();
    garlicBread->prepare();

    return 0;
}
