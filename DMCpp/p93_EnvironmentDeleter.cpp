//
// Created by zeph on 11/23/16.
//

// I believe that we can create an environment deleter with a lambda.
// Is this true?

#include <iostream>

using namespace std;

class Dust2Dust {
public:
    const int id;
    Dust2Dust() : id{rand()} {
        cout << "D2D " << id << " just born\n";
    }
    void manualCleanup() const{
        cout << "Cleaning up " << id << "'s junk!\n";
    }
    ~Dust2Dust(){
        cout << "D2D " << id << " just died\n";
    }
};

struct D2D_deleter_memory_leak {
    void operator()(Dust2Dust* d2d) {
        d2d->manualCleanup();
    }
};

struct D2D_deleter_all_good {
    void operator()(Dust2Dust* d2d) {
        d2d->manualCleanup();
        delete d2d;
    }
};

int main(){
    srand((unsigned int)time(0));
    Dust2Dust d2d1;
    shared_ptr<Dust2Dust> d2d_sp1(new Dust2Dust());
    shared_ptr<Dust2Dust> d2d_sp2(new Dust2Dust(), D2D_deleter_memory_leak());
    shared_ptr<Dust2Dust> d2d_sp3(new Dust2Dust(), D2D_deleter_all_good());

    shared_ptr<Dust2Dust> d2d_lambda(new Dust2Dust(), [](Dust2Dust* d2d){
        d2d->manualCleanup();
        delete d2d;
        cout << "Yes, can define a deleter on the fly with a lambda!!!!\n";
    });

    cout << "Program done!\n";
    return 0;
}
