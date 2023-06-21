// day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <set>
#include <utility>
#include <string>
#include <stdexcept>

typedef std::pair<int, int> coord;

std::ostream& operator<<(std::ostream& o, const coord& c) {
    o << c.first << '|' << c.second;
    return o;
}

coord& operator+=(coord& lhs, const coord& rhs) {
    lhs.first += rhs.first;
    lhs.second += rhs.second;
    return lhs;
}

int main()
{
    std::ifstream input("./Input.txt");
    if (input.fail()) {
        std::cerr << "couldn't read file\n";
        return 1;
    }
    int part = 1;
    std::cout << "which part ? (1 or 2)\n";
    std::cin >> part;
    char direction;
    coord location(0, 0);
    std::set<coord> visited;
    visited.insert(location);
    int result = 1;
    if (part == 1) {
    while (!input.eof()) {
        input.get(direction);
        switch (direction) {
        case '<':
            location += coord(-1, 0);
            break;
        case '>':
            location += coord(1, 0);
            break;
        case 'v':
            location += coord(0, 1);
            break;
        case '^':
            location += coord(0, -1);
            break;
        default:
            throw(std::invalid_argument("wrong file format\n"));
        }
        std::pair<std::set<coord>::iterator, bool> insertResult = visited.insert(location);
        if (insertResult.second)
            ++result;
    }
    std::cout << result << std::endl;
    }
    else {
        coord location2(0, 0);
        coord* loc = 0;
        int pouet = 0;
        while (!input.eof()) {
            ++pouet;
            if (pouet %= 2)
                loc = &location;
            else
                loc = &location2;
            input.get(direction);
            switch (direction) {
            case '<':
                *loc += coord(-1, 0);
                break;
            case '>':
                *loc += coord(1, 0);
                break;
            case 'v':
                *loc += coord(0, 1);
                break;
            case '^':
                *loc += coord(0, -1);
                break;
            default:
                throw(std::invalid_argument("wrong file format\n"));
            }
            std::pair<std::set<coord>::iterator, bool> insertResult = visited.insert(*loc);
            if (insertResult.second)
                ++result;
        }
        std::cout << result << std::endl;
    }
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
