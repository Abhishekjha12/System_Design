#include<iostream>
using namespace std;

class BankAccount{
protected:
    double balance;
public:
    BankAccount(double b){
        if(b<0) throw invalid_argument("Balance can't be negative");
        balance = b;
    }
    virtual void withdraw(double amount){
        if(balance - amount < 0) throw runtime_error("Insufficient funds");
        balance -= amount;
        cout<<"Amount withdrawn. Remaning balance is "<< balance <<endl;
    }
};

//Brakes invariant: should not be allowed
class CheatAccount : public BankAccount{
public:
    CheatAccount(double b):BankAccount(b){}

    void withdraw(double amount) override{
        balance -= amount; //LSP break! Negative balance is now allowed
        cout<<"Amoutn withdrawn. Remaining balance is "<< balance <<endl;
    }
};

int main(){
    BankAccount*  bankAccount = new BankAccount(100);
    bankAccount->withdraw(100);
    bankAccount->withdraw(200); // returns error insufficient balance
}