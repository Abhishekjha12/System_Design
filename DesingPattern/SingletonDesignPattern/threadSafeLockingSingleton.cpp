#include <iostream>
#include <mutex>
using namespace std;

class Singleton {
private:
    static Singleton* instance;
    static mutex mtx;   // ✅ correct type

    Singleton() {
        std::cout << "Singleton Constructor Called!" << std::endl;
     }

public:
    static Singleton* getInstance() {
        // ✅ lock the mutex before touching `instance`
        lock_guard<mutex> lock(mtx);
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
};

// ✅ Define static members
Singleton* Singleton::instance = nullptr;
mutex Singleton::mtx;

int main() {
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    std::cout << (s1 == s2) << std::endl; // prints 1 (true)
    return 0;
}
