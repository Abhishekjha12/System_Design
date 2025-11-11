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

//3 shopping cart storage
class ShoppingCartStorage{
private:
    shoppingCart* cart;
public:
    ShoppingCartStorage(shoppingCart* cart){
        this->cart = cart;
    }
    void saveToSQLDatabase(){
        cout<<"Saving shopping cart to SQL DB..."<<endl;
    }
    void saveToMongooseDatabase(){
        cout<<"Saving shopping cart to Mongo DB..."<<endl;
    }

    void saveToFile(){
        cout<<"saving shopping cart to File..."<<endl;
    }
};


int main(){
    shoppingCart* cart = new shoppingCart();

    cart->addProduct(new Product("Laptop",1500));
    cart->addProduct(new Product("Mouse",15));

    shoppingCartPrinter* printer = new shoppingCartPrinter(cart);
    printer->printInvoice();

    ShoppingCartStorage* db = new ShoppingCartStorage(cart);
    db->saveToSQLDatabase();

    return 0;
}