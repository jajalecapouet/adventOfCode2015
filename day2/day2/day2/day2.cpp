// day2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

int paperNeed(const std::string &dim) {
    int l = std::stoi(dim);
    std::string::size_type x = dim.find('x');
    int w = std::stoi(dim.substr(x + 1));
    x = dim.find('x', x + 1);
    int h = std::stoi(dim.substr(x + 1));
    return (2 * (l * w) + 2 * (l * h) + 2 * (w * h) + std::min({ l * w, l * h, w * h }));
}

int ribbonNeed(const char *dim) {
    int l = std::atoi(dim);
    int idx = 0;
    while (dim[idx] != 'x')
        ++idx;
    int w = std::atoi(&dim[++idx]);
    while (dim[idx] != 'x')
        ++idx;
    int h = std::atoi(&dim[++idx]);
    int minPerimeter = 0;
    if (h >= l && h >= w)
        minPerimeter = 2 * (l + w);
    else if (l >= w)
        minPerimeter = 2 * (h + w);
    else
        minPerimeter = 2 * (h + l);
    return ((l * w * h) + minPerimeter);
}

int main()
{
    std::ifstream input("./Input.txt");
    if (input.fail())
    {
        std::cerr << "couldn't open file\n";
        return 1;
    }
    std::string line;
    int part = 1;
    std::cout << "which part ? (1 or 2)\n";
    std::cin >> part;
    int totalOfPaper = 0;
    long totalOfRibbon = 0;
    while (!input.eof())
    {
        std::getline(input, line);
        if (part == 1)
        {
            totalOfPaper += paperNeed(line);
        }
        else
        {
            totalOfRibbon += ribbonNeed(line.c_str());
        }
    }
    if (part == 1)
        std::cout << "totalOfPaper : " << totalOfPaper << std::endl;
    else
        std::cout << "totalOfRibbon : " << totalOfRibbon << std::endl;
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
