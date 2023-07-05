// day13.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>


//dfs tools
typedef std::map<std::string, std::pair<bool, int> > Visited;
typedef std::map<int, std::set<std::string>, std::greater<int> > Node;
typedef std::map<std::string, int> P;
typedef std::map<std::string, P> PreData;
typedef std::map<std::string, Node> Data;

class Sim {
	
	int _part;
	Data _data;
	PreData _predata;
	Visited _v;

	bool _allVisited(const Visited& v) {
		for (Visited::const_iterator cit = v.begin(); cit != v.end(); ++cit) {
			if (!cit->second.first)
				return false;
		}
		return true;
	}

	int _possibleMax(const Visited& v, const P& first) {
		int val = 0;
		for (Visited::const_iterator cit = v.begin(); cit != v.end(); ++cit) {
			if (!cit->second.first)
				val += cit->second.second;
		}
		int firstMax = -1000;
		for (P::const_iterator cit = first.begin(); cit != first.end(); ++cit) {
			if (v.find(cit->first) != v.end() & cit->second > firstMax)
				firstMax = cit->second;
		}
		if (firstMax == -1000)
			throw(std::invalid_argument("bad implementation\n"));
		return val + firstMax;
	}

public :

	Sim(int part) : _part(part) {}

	void parseLine(const std::string& str) {
		std::string nameLeft;
		std::string nameRight;
		int	happy;
		bool sign = false;
		std::string::size_type	idxS = 0;
		std::string::size_type	idxE = str.find(' ');
		if (idxE >= str.size() - 7)
			throw(std::invalid_argument("bad file format.\n"));
		nameLeft = str.substr(0, idxE);
		idxS = idxE + 7;
		if (str[idxS] == 'l')
			sign = true;
		else if (str[idxS] != 'g')
			throw(std::invalid_argument("bad file format.\n"));
		idxS += 5;
		happy = std::atoi(&str.c_str()[idxS]);
		if (sign)
			happy *= -1;
		idxS = str.find("to", idxS) + 3;
		if (idxS >= str.size() - 3)
			throw(std::invalid_argument("bad file format.\n"));
		idxE = str.find('.', idxS);
		nameRight = str.substr(idxS, idxE - idxS);

		std::pair<PreData::iterator, bool> insertRes = _predata.insert(std::make_pair(nameLeft, P()));
		std::pair<P::iterator, bool> insertResP = insertRes.first->second.insert(std::make_pair(nameRight, int()));
		insertResP.first->second += happy;
		std::pair<Visited::iterator, bool> insertResV = _v.insert(std::make_pair(nameLeft, std::make_pair(false, -1000)));
		if (!insertResP.second) {
			if (insertResP.first->second > insertResV.first->second.second)
				_v[nameLeft].second = insertResP.first->second;
		}
		insertRes = _predata.insert(std::make_pair(nameRight, P()));
		insertResP = insertRes.first->second.insert(std::make_pair(nameLeft, int()));
		insertResP.first->second += happy;
		insertResV = _v.insert(std::make_pair(nameRight, std::make_pair(false, -1000)));
		if (!insertResP.second) {
			if (insertResP.first->second > insertResV.first->second.second)
				_v[nameRight].second = insertResP.first->second;
		}
	}

	void endParsing() {
		if (_part != 1) {
			for (PreData::iterator it = _predata.begin(); it != _predata.end(); ++it) {
				it->second.insert(std::make_pair("Me", 0));
			}
			PreData::iterator inserted = _predata.insert(std::make_pair("Me", P())).first;
			for (Visited::const_iterator cit = _v.begin(); cit != _v.end(); ++cit) {
				inserted->second.insert(std::make_pair(cit->first, 0));
			}
			_v.insert(std::make_pair("Me", std::make_pair(false, 0)));
		}
		for (PreData::const_iterator it = _predata.begin(); it != _predata.end(); ++it) {
			Data::iterator itD = _data.insert(std::make_pair(it->first, Node())).first;
			for (P::const_iterator itP = it->second.begin(); itP != it->second.end(); ++itP) {
				Node::iterator itN = itD->second.insert(std::make_pair(itP->second, std::set<std::string>())).first;
				itN->second.insert(itP->first);
			}
		}
	}

	void _dfs(int score, int& bestScore, const Data& data, Visited& v, const Node& current, P& first, std::string justPlaced) {
		if (_allVisited(v)) {
			score += first.find(justPlaced)->second;
			if (score > bestScore)
				bestScore = score;
			return;
		}
		if (score + _possibleMax(v, first) - current.begin()->first <= bestScore) {
			return;
		}
		for (Node::const_iterator cit = current.begin(); cit != current.end(); ++cit) {
			for (std::set<std::string>::const_iterator cit2 = cit->second.begin(); cit2 != cit->second.end(); ++cit2) {
				Visited::iterator found = v.find(*cit2);
				if (!found->second.first) {

					found->second.first = true;
					score += cit->first;

					_dfs(score, bestScore, data, v, data.find(*cit2)->second, first, *cit2);

					score -= cit->first;
					found->second.first = false;
				}
			}
		}
	}

	int getResult() {
		int bestScore = 0;
		P first;
		Node init;
		first = _predata.begin()->second;
		init = _data.begin()->second;;
		_v.find(_data.begin()->first)->second.first = true;
		_dfs(0, bestScore, _data, _v, init, first, _predata.begin()->first);
		return bestScore;
	}
};

int main()
{
	std::ifstream input("./Input.txt");
	if (input.fail()) {
		std::cerr << "couldn't read file ./Input.txt";
		return 1;
	}
	std::string line;
	int part = 1;
	std::cout << "Which part ? (1 or 2)\n";
	std::cin >> part;
	Sim sim(part);
	while (!input.eof()) {
		getline(input, line);
		sim.parseLine(line);
	}
	sim.endParsing();

	std::cout << "Result is " << sim.getResult() << std::endl;
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
