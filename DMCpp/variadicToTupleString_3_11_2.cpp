//
// Created by zeph on 1/7/17.
//

#include <iostream>
#include "genericString_3_11_1.h"

template <typename T>
inline std::string to_tuple_string_aux(T t) {
    return to_string(t);
}

template <typename T, typename ...P>
inline std::string to_tuple_string_aux(T t, P ...p){
    return to_string(t) + ", " + to_tuple_string_aux(p...);
}

template <typename T, typename ...P>
inline std::string to_tuple_string(T t, P ...p){
    return to_string("(") + to_tuple_string_aux(t, p...) + ")";
}

int main(){
    using namespace std;
    cout << to_tuple_string(3) << endl;
    cout << to_tuple_string(3, "four") << endl;
    cout << to_tuple_string(3, "four", 5, 6.0, "seven") << endl;
    return 0;
}