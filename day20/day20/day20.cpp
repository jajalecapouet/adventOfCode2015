// day20.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

long getResult(unsigned int h) {
    long result = 0;
    for (unsigned int i = 1; i <= h / 2; ++i) {
        if (!(h % i))
            result += 10 * i;
    }
    return result;
}

int main()
{
    int part = 1;
    std::cout << "Which part ? (1 or 2)";
    std::cin >> part;
    unsigned long result = 0;
    unsigned int house = 0;
    while (result < 36000000) {
        result = getResult(++house);
    }
    std::cout << "result is " << house << std::endl;
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
