//
// Created by zeph on 11/14/16.
//
#include <iostream>
#include <fstream>
int main()
{
    const std::string FILENAME("1_10_1_RESULT.txt");
    std::cout << "What's your age?" << std::endl << "> ";
    bool success= false;
    do {
        try{
            int age;
            std::cin >> age;
            std::cout << std::endl << "So your age is " << age;
            std::cout << std::endl << "Saving this information in " << FILENAME << std::endl;
            std::ofstream fout;
            fout.open(FILENAME);
            fout << age;
            success = true;
        } catch (int e) {
            std::cout << "Woops: " << e << std::endl;
        }
    } while(!success);

    return 0;
}