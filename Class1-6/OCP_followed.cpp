#include<iostream>
#include<string>
#include<vector>

using namespace std;
//product class representing any item in ecommerce
class Product{
public:
    string name;
    double price;

    Product(string name, double price){
        this->name = name;
        this->price = price;
    }
};

//1 Shopping cart: Only responsible for cart related business logic
class shoppingCart{
private:
    vector<Product*>product;
public:
    void addProduct(Product*p){
        product.push_back(p);
    }
    const vector<Product*> &getProduct(){
        return product;
    }

    // calculates total price in cart
    double calculateTotal(){
        double total = 0;
        for(auto p: product){
            total += p->price;
        }
        return total;
    }
};

//2. shopping cart Printer : only responsible for printing invoices
class shoppingCartPrinter{
private:
    shoppingCart* cart;
public:
    shoppingCartPrinter(shoppingCart* cart){
        this->cart = cart;
    }
    void printInvoice(){
        cout<<"Shopping Cart Invoice:\n";
        for(auto p:cart->getProduct()){
            cout<<p->name<< " -$"<<p->price << endl;
        }
        cout<<"Total: $"<<cart->calculateTotal()<<endl;
    }
};

class Persistence{
private:
    shoppingCart* cart;
public:
    virtual void save(shoppingCart* cart) = 0;  //pure virtual function
};

class SQLPersistence: public Persistence{
public:
    void save(shoppingCart* cart) override{
        cout<<"Saving shopping cart to SQL DB..."<<endl;
    }
};

class MongoPersistence: public Persistence{
public:
    void save(shoppingCart* cart) override{
        cout<<"Saving shopping cart to MongoDB..."<<endl;
    }
};

class FilePersistence: public Persistence{
public:
    void save(shoppingCart* cart) override{
        cout<<"Saving shopping cart to file..."<<endl;
    }
};

int main(){
    shoppingCart* cart = new shoppingCart();
    cart->addProduct(new Product("Laptop",1500));
    cart->addProduct(new Product("Mouse",15));

    shoppingCartPrinter* printer = new shoppingCartPrinter(cart);
    printer->printInvoice();

    Persistence* db = new SQLPersistence();
    Persistence* mongo = new MongoPersistence();
    Persistence* file = new FilePersistence();

    db->save(cart); // save to SQL database
    mongo->save(cart); // save to MongoDB
    file->save(cart); // save to File
    return 0;
}