//
// Created by zeph on 11/24/16.
//

#include <iostream>

using namespace std;

class MoveVsCopyCtor
{
public:
    MoveVsCopyCtor() = default;
    MoveVsCopyCtor& operator=(const MoveVsCopyCtor&) = default;
    MoveVsCopyCtor& operator=(MoveVsCopyCtor&&) = default;
    ~MoveVsCopyCtor() = default;

    MoveVsCopyCtor(const MoveVsCopyCtor& x) : id(x.id){
        cout << "Copied from " << x.id << endl;
    }
    MoveVsCopyCtor(MoveVsCopyCtor&& x) : id(move(x.id)){
        cout << "Moved from " << x.id << endl;
        x.id = -1;
        cout << "Now it is " << x.id << endl;
    }
    friend ostream& operator<<(ostream& o, const MoveVsCopyCtor& x);
private:
    int id{rand()};
};

ostream& operator<<(ostream& o, const MoveVsCopyCtor& x){
    o << "I am " << x.id << endl;
    return o;
}

int main(){
    srand((unsigned int)time(0));
    MoveVsCopyCtor a, b, c, d, e;
    cout << a << b << c << d << e;

    cout << endl << "MoveVsCopyCtor x(b);" << endl;
    MoveVsCopyCtor x(b);
    cout << x << b;

    cout << endl << "MoveVsCopyCtor y(move(b);" << endl;
    MoveVsCopyCtor y(move(b));
    cout << y << b;

    return 0;
}
