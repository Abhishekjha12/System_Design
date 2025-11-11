#include<iostream>
using namespace std;

// A preCondition must be satisfied before a method can be executed
// Sub classes can be weaken the precondition but cannot strenghthen it.

class User{
public:
    //Precondition: Password must be atleast 8 character long
    virtual void setPassword(string password){
        if(password.length() < 8){
            throw invalid_argument("Password must be more than of 8 characters long");
        }
        cout<< "Password set successfully"<<endl;
    }
};

class AdminUser: public User{
public:
    //Preconditon: Password must be at least 6 characters
    void setPassword(string password) override{
        if(password.length()<6){
            throw invalid_argument("Password must be at least 6 charcaters long");
        }
        cout<< "Password set Successfully"<<endl;
    }
};

int main(){
    User* user = new AdminUser();
    user->setPassword("Admin1"); // works fine: AdminUser allow shorter passwords
    

    return 0;
}