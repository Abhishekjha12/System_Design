#include<iostream>
#include<vector>
using namespace std;
class Account{
public:
    virtual void deposit(double amount)=0;
    virtual void withdraw(double amount)=0;
};
class SavingAccount : public Account{
private:
    double balance;
public:
    SavingAccount(){
        balance = 0;
    }
    void deposit(double amount){
        balance += amount;
        cout<< "Deposited: "<< amount << "in Saving Account. New Balance: "<<balance <<endl;
    }
    void withdraw(double amount){
        if(balance >= amount){
            balance -= amount;
            cout<<"Withdrawn: "<<amount<<" from Saving Account. New Balanace: "<< balance << endl;
        }else{
            cout<<"Insufficient funds in Savings Account:\n";
        }
    }
};
class CurrentAccount : public Account{
private:
    double balance;
    void deposit(double amount){
        balance += amount;
        cout<< "Deposited: "<< amount << "in Saving Account. New Balance: "<<balance <<endl;
    }
    void withdraw(double amount){
        if(balance >= amount){
            balance -= amount;
            cout<<"Withdrawn: "<<amount<<" from Saving Account. New Balanace: "<< balance << endl;
        }else{
            cout<<"Insufficient funds in Savings Account:\n";
        }
    }
};
class FixedTermAccount : public Account{
private:
    double balance;
public:
    FixedTermAccount(){
        balance = 0;
    }
    void deposit(double amount){
        balance += amount;
        cout<<" Deposited: "<< amount <<" In Fixed Term Account. New Balance: "<< balance <<endl;
    }
    void withdraw(double amount){
        throw logic_error("withdrawal not allowed from Fixed Deposit Account type");
    }
};
class BankClient{
private:
    vector<Account*>accounts;
public:
    BankClient(vector<Account*>accounts){
        this->accounts = accounts;
    }
    void processTransaction(){
        for(Account* acc: accounts){
            acc->deposit(1000); // deposit allowe from all accounts

            //Assuming all accounts support withdrawl (LSP violation)
            try
            {
                acc->withdraw(500);
            }
            catch(const logic_error &e)
            {
                cout<<"Exception: "<<e.what()<<endl;
            }            
        }
    }
};
int main(){
    vector<Account*> accounts;
    accounts.push_back(new SavingAccount());
    accounts.push_back(new CurrentAccount());
    accounts.push_back(new FixedTermAccount());

    BankClient* client = new BankClient(accounts);
    client->processTransaction(); // throws exception when withdrawing from fixedTermAccount

    return 0;
}