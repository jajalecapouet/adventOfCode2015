#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <deque>
#include <vector>

typedef std::map<std::string, std::set<std::string> > Comb;
typedef std::set<std::string> Mols;
typedef std::deque<std::pair<std::string, int>> Lilo;

void parseLine(const std::string& str, Comb& comb, int part) {
    std::string::size_type idx = 0;
    std::string mol;
    std::string replace;
    idx = str.find(' ');
    mol = str.substr(0, idx);
    idx = str.find(' ', idx + 1) + 1;
    replace = str.substr(idx);
    if (part == 1) {
        Comb::iterator it = comb.insert(std::make_pair(mol, Mols())).first;
        it->second.insert(replace);
    }
    else {
        Comb::iterator it = comb.insert(std::make_pair(replace, Mols())).first;
        it->second.insert(mol);
    }
}

bool containComb(std::string& str, std::string::size_type idx, const Comb& comb) {
    for (Comb::const_iterator cit = comb.begin(); cit != comb.end(); ++cit) {
        if (!str.compare(idx, cit->first.length(), cit->first)) {
            str.replace(idx, cit->first.length(), *(cit->second.begin()));
            return true;
        }
    }
    return false;
}

int reducedForm(std::string& str, const Comb& comb) {
    int count = 0;
    std::string beginMol;
    std::string endMol;
    std::string::size_type idx = 0;
    while (idx < str.size()) {
        if (containComb(str, idx, comb)) {
            ++count;
            idx = 0;
        }
        else
            ++idx;
    }
    return count;
}

bool isBeginOfOther(const std::string& str, const Comb& comb) {
    std::string::size_type idx;
    std::string debugStr;
    std::string debugCit;
    for (Comb::const_iterator cit = comb.begin(); cit != comb.end(); ++cit) {
        if (str != cit->first) {
            for (idx = str.size() - 1; idx > 0; --idx) {
                debugStr = str.substr(idx, str.size() - idx);
                debugCit = cit->first.substr(0, str.size() - idx);
                if (!str.compare(idx, str.size() - idx, cit->first, 0, str.size() - idx))
                    return true;
            }
        }
    }
    return false;
}

Comb reducedComb(const Comb& comb) {
    Comb c;
    for (Comb::const_iterator cit = comb.begin(); cit != comb.end(); ++cit) {
        if (!isBeginOfOther(cit->first, comb))
            c.insert(*cit);
    }
    return c;
}

Mols doTheThing(const std::string& str, const Comb& comb) {
    Mols mols;
    std::string mol;
    std::string beginMol;
    std::string endMol;
    std::string::size_type idx = 0;
    while (idx < str.size()) {
        for (Comb::const_iterator cit = comb.begin(); cit != comb.end(); ++cit) {
            if (!str.compare(idx, cit->first.length(), cit->first)) {
                beginMol = str.substr(0, idx);
                endMol = str.substr(idx + cit->first.length());
                for (Mols::const_iterator citM = cit->second.begin(); citM != cit->second.end(); ++citM) {
                    mol = beginMol;
                    mol += *citM;
                    mol += endMol;
                    mols.insert(mol);
                }
            }
        }
        ++idx;
    }
    return mols;
}

void dfs(const std::string& obj, const std::string& start, const Comb& comb, int depth, int& maxD) {
    if (depth >= maxD)
        return;
    if (start == obj) {
        std::cout << "new best way to do it : " << depth << std::endl;
        maxD = depth;
        return;
    }
    Mols resultThings = doTheThing(start, comb);
    for (std::string res : resultThings) {
        dfs(obj, res, comb, depth + 1, maxD);
    }
}

int bfs(const std::string& obj, const std::string& start, const Comb& comb) {
    //bfs was bad idea, tree is too big
    Lilo lilo;
    Mols resultThing;
    int depth;
    lilo.push_back(std::make_pair(start, 0));
    while (lilo.front().first.compare(obj)) {
        depth = lilo.front().second + 1;
        resultThing = doTheThing(lilo.front().first, comb);
        for (std::string str : resultThing) {
            lilo.push_back(std::make_pair(str, depth));
        }
        lilo.pop_front();
    }
    return lilo.front().second;
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
        if (mol.empty())
            isMol = true;
        else if (!isMol)
            parseLine(mol, comb, part);
    }
    if (part == 1)
        std::cout << "result is " << doTheThing(mol, comb).size() << std::endl;
    else {
        Comb reduceComb = reducedComb(comb);
        int depth = reducedForm(mol, reduceComb);
        int minD = 10000;
        dfs("e", mol, comb, depth, minD);
        std::cout << "result is " << minD << std::endl;
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
