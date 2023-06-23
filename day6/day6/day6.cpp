// day6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

#define OFF 0
#define ON 1
#define TOGGLE 2

typedef std::pair<int, int> coord;
typedef std::vector<int> row;
typedef std::vector<row> grid;

class myGrid {
    
    grid _grid;
    int _part;

public :

    myGrid() : _grid(grid(1000, row(1000, -1))), _part(1) {}

    myGrid(int part) : _part(part) {
        if (_part == 1)
            _grid.insert(_grid.begin(), 1000, row(1000, -1));
        else
            _grid.insert(_grid.begin(), 1000, row(1000, 0));
    }

    ~myGrid() {}

    void newInstruction(int act, coord start, coord end) {
        for (grid::size_type y = start.second; y != end.second + 1; ++y) {
            for (row::size_type x = start.first; x != end.first + 1; ++x) {
                switch (act) {
                case OFF:
                    if (_part == 1)
                        _grid[y][x] = -1;
                    else if (_grid[y][x] > 0)
                        --_grid[y][x];
                    break;
                case ON:
                    if (_part == 1)
                        _grid[y][x] = 1;
                    else
                        ++_grid[y][x];
                    break;
                default:
                    if (_part == 1)
                        _grid[y][x] *= -1;
                    else
                        _grid[y][x] += 2;
                }
            }
        }
    }

    long lightsCount() {
        long count = 0;
        for (grid::const_iterator it = _grid.begin(); it != _grid.end(); ++it)
        {
            for (row::const_iterator it2 = it->begin(); it2 != it->end(); ++it2) {
                if (_part == 1 && *it2 == 1)
                    ++count;
                else if (_part != 1)
                    count += *it2;
            }
        }
        return count;
    }

};

void parseInput(const std::string& line, int& command, coord& start, coord& end) {
    std::string::size_type coma1 = line.find(',');
    std::string::size_type coma2 = line.find(',', coma1 + 1);
    std::string::size_type h = line.find("gh");
    if (!line.compare(0, 7, "turn on")) {
        start.first = std::stoi(line.substr(8));
        command = ON;
    }
    else if (!line.compare(0, 8, "turn off")) {
        start.first = std::stoi(line.substr(9));
        command = OFF;
    }
    else {
        start.first = std::stoi(line.substr(7));
        command = TOGGLE;
    }
    start.second = std::stoi(line.substr(coma1 + 1));
    end.first = std::stoi(line.substr(h + 2));
    end.second = std::stoi(line.substr(coma2 + 1));
}

int main()
{
    std::ifstream input("./Input.txt");
    if (input.fail())
    {
        std::cout << "couldn't read file.\n";
        return 1;
    }
    int part = 1;
    std::cout << "which part ? (1 or 2)\n";
    std::cin >> part;
    std::string line;
    int command = 0;
    coord start(0, 0);
    coord end(0, 0);
    myGrid pouet(part);
    while (!input.eof()) {
        std::getline(input, line);
        parseInput(line, command, start, end);
        pouet.newInstruction(command, start, end);
    }
    std::cout << pouet.lightsCount() << std::endl;
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
