// #include<iostream>
// #include<vector>
// using namespace std;

// class Product{
// public:
//     string name;
//     double price;

//     Product(string name, double price){
//         this->name = name;
//         this->price = price;
//     }
// };

// class shoppingCart{
// private:
//     vector<Product*>products;

// public:
//     void addProduct(Product* p){
//         products.push_back(p);
//     }
//     const vector<Product*>&getProduct(){
//         return products;
//     }

//     //1.Calculate Total Price in cart
//     double calculateTotal(){
//         double total = 0;
//         for(auto p:products){
//             total += p->price;
//         }
//         return total;
//     }
//     //2. violating SRP - prints invoice (should be in a separate class)
//     void PrintInvoice(){
//         cout<<"Shopping Cart Invoice:\n";
//         for(auto p:products){
//             cout<<p->name << " - $"<<p->price<<endl;
//         }
//         cout<<"Total: $"<< calculateTotal()<<endl;
//     }

//     //3. Violating SRP - saves to DB (should be in separate class)
//     void saveToDatabase(){
//         cout<<"Saving shopping cart to database..."<<endl;
//     }
// };



// int main(){
//     shoppingCart * cart = new shoppingCart();

//     cart->addProduct(new Product("Laptop",15000));
//     cart->addProduct(new Product("Mouse",1500));

//     cart->PrintInvoice();
//     cart->saveToDatabase();
//     return 0;
// }


// ABOVE CODE IS BELOW NOW CONVERTED INTO SRP
#include <iostream>
#include <vector>
using namespace std;

// Product class
class Product {
public:
    string name;
    double price;

    Product(string name, double price) {
        this->name = name;
        this->price = price;
    }
};

// ShoppingCart: Responsible only for managing products
class ShoppingCart {
private:
    vector<Product*> products;

public:
    void addProduct(Product* p) {
        products.push_back(p);
    }

    const vector<Product*>& getProducts() {
        return products;
    }

    double calculateTotal() {
        double total = 0;
        for (auto p : products) {
            total += p->price;
        }
        return total;
    }
};

// InvoicePrinter: Responsible only for printing invoices
class InvoicePrinter {
public:
    void printInvoice(ShoppingCart& cart) {
        cout << "Shopping Cart Invoice:\n";
        for (auto p : cart.getProducts()) {
            cout << p->name << " - $" << p->price << endl;
        }
        cout << "Total: $" << cart.calculateTotal() << endl;
    }
};

// CartRepository: Responsible only for saving cart to database
class CartRepository {
public:
    void saveToDatabase(ShoppingCart& cart) {
        cout << "Saving shopping cart to database..." << endl;
        // Simulated DB save logic
    }
};

// ---- main ----
int main() {
    ShoppingCart cart;
    cart.addProduct(new Product("Laptop", 15000));
    cart.addProduct(new Product("Mouse", 1500));

    InvoicePrinter printer;
    printer.printInvoice(cart);

    CartRepository repo;
    repo.saveToDatabase(cart);

    return 0;
}
