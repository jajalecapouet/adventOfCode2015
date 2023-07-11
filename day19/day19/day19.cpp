#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>

typedef std::map<std::string, std::set<std::string> > Comb;
typedef std::set<std::string> Mols;


void parseLine(const std::string& str, Comb& comb) {
    std::string::size_type idx = 0;
    std::string mol;
    std::string replace;
    idx = str.find(' ');
    mol = str.substr(0, idx);
    idx = str.find(' ', idx + 1) + 1;
    replace = str.substr(idx);
    Comb::iterator it = comb.insert(std::make_pair(mol, Mols())).first;
    it->second.insert(replace);
}

int main()
{
    std::ifstream input("./Input.txt");
    if (input.fail()) {
        return 1;
    }

    std::string mol;
    std::cout << "Which part ? (1 or 2)\n";
    int part;
    std::cin >> part;
    Comb comb;
    Mols mols;
    bool isMol = false;
    while (!input.eof()) {
        getline(input, mol);
        if (!isMol) {
            if (mol.empty())
                isMol = true;
            else {
                parseLine(mol, comb);
            }
        }

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
