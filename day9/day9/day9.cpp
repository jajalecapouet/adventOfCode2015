// day9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>

typedef std::map<std::string, bool> Visited;
typedef std::map<unsigned int, std::set<std::string> > Node;
typedef std::map<std::string, Node> Nodes;

typedef std::map<unsigned int, std::set<std::string>, std::greater<unsigned int> > LNode;
typedef std::map<std::string, LNode> LNodes;
typedef std::map<std::string, std::pair<bool, unsigned int> > LVisited;

class Sim {

	int _part;
	Nodes _n;
	LNodes _ln;
	Visited _v;
	LVisited _lv;

	bool _allVisited(const Visited& v) {
		for (Visited::const_iterator cit = v.begin(); cit != v.end(); ++cit) {
			if (!cit->second)
				return false;
		}
		return true;
	}

	bool _allLVisited(const LVisited& v) {
		for (LVisited::const_iterator cit = v.begin(); cit != v.end(); ++cit) {
			if (!cit->second.first)
				return false;
		}
		return true;
	}

	unsigned int _possibleMax(const LVisited& v) {
		unsigned int val = 0;
		for (LVisited::const_iterator cit = v.begin(); cit != v.end(); ++cit) {
			if (!cit->second.first)
				val += cit->second.second;
		}
		return val;
	}

public :


	Sim(int part) : _part(part) {}

	void parseLine(const std::string& str) {
		std::string strNode1;
		std::string strNode2;
		int dist = 0;
		std::string::size_type idxStart = 0;
		std::string::size_type idxEnd = str.find(' ');
		strNode1 = str.substr(idxStart, idxEnd - idxStart);
		idxStart = str.find(' ', ++idxEnd) + 1;
		idxEnd = str.find(' ', idxStart);
		strNode2 = str.substr(idxStart, idxEnd - idxStart);
		idxStart = str.find('=') + 2;
		dist = std::stoi(str.substr(idxStart));

		if (_part == 1) {
			std::pair<Nodes::iterator, bool> insertRes = _n.insert(std::make_pair(strNode1, Node()));
			std::pair<Node::iterator, bool> insertRes2 = insertRes.first->second.insert(std::make_pair(dist, std::set<std::string>()));
			insertRes2.first->second.insert(strNode2);
			if (insertRes.second)
				_v[strNode1] = false;
			insertRes = _n.insert(std::make_pair(strNode2, Node()));
			insertRes2 = insertRes.first->second.insert(std::make_pair(dist, std::set<std::string>()));
			insertRes2.first->second.insert(strNode1);
			if (insertRes.second)
				_v[strNode2] = false;
		}
		else {
			std::pair<LNodes::iterator, bool> insertRes = _ln.insert(std::make_pair(strNode1, LNode()));
			std::pair<LNode::iterator, bool> insertRes2 = insertRes.first->second.insert(std::make_pair(dist, std::set<std::string>()));
			insertRes2.first->second.insert(strNode2);
			_lv[strNode1].first = false;
			if (dist > _lv[strNode1].second)
				_lv[strNode1].second = dist;
			insertRes = _ln.insert(std::make_pair(strNode2, LNode()));
			insertRes2 = insertRes.first->second.insert(std::make_pair(dist, std::set<std::string>()));
			insertRes2.first->second.insert(strNode1);
			_lv[strNode2].first = false;
			if (dist > _lv[strNode2].second)
				_lv[strNode2].second = dist;
		}
	}

	void _dfs(unsigned int score, unsigned int& bestScore, const Node& node, Visited& v, const Nodes& data) {
		if (_allVisited(v)) {
			bestScore = score;
			return;
		}
		for (Node::const_iterator cit = node.begin(); cit != node.end(); ++cit) {
			if (score + cit->first >= bestScore)
				return;
			for (std::set<std::string>::const_iterator cit2 = cit->second.begin(); cit2 != cit->second.end(); ++cit2) {
				Visited::iterator found = v.find(*cit2);
				if (!found->second) {
					found->second = true;
					score += cit->first;
					_dfs(score, bestScore, data.find(*cit2)->second, v, data);
					found->second = false;
					score -= cit->first;
				}
			}
		}
	}
	
	void _dfs2(unsigned int score, unsigned int& bestScore, const LNode& node, LVisited& v, const LNodes& data) {
		if (_allLVisited(v)) {
			bestScore = score;
			return;
		}
		if (score + _possibleMax(v) - node.begin()->first <= bestScore)
			return;
		for (Node::const_iterator cit = node.begin(); cit != node.end(); ++cit) {
			for (std::set<std::string>::const_iterator cit2 = cit->second.begin(); cit2 != cit->second.end(); ++cit2) {
				LVisited::iterator found = v.find(*cit2);
				if (!found->second.first) {
					found->second.first = true;
					score += cit->first;
					_dfs2(score, bestScore, data.find(*cit2)->second, v, data);
					found->second.first = false;
					score -= cit->first;
				}
			}
		}
	}

	unsigned int startSim() {
		if (_part == 1) {
			unsigned int bestScore = ~0;
			Node init;
			Visited visitedCpy = _v;
			init.insert(std::make_pair(0, std::set<std::string>()));
			for (Visited::const_iterator cit = _v.begin(); cit != _v.end(); ++cit) {
				init.begin()->second.insert(cit->first);
			}
			_dfs(0, bestScore, init, visitedCpy, _n);
			return bestScore;
		}
		else {
			unsigned int bestScore = 0;
			LNode init;
			LVisited visitedCpy = _lv;
			init.insert(std::make_pair(0, std::set<std::string>()));
			for (LVisited::const_iterator cit = _lv.begin(); cit != _lv.end(); ++cit) {
				init.begin()->second.insert(cit->first);
			}
			_dfs2(0, bestScore, init, visitedCpy, _ln);
			return bestScore;
		}
	}

};

int main()
{
	std::ifstream input("./Input.txt");
	if (input.fail()) {
		std::cerr << "couldn't open file ./Input.txt\n";
		return 1;
	}
	std::string line;
	int part = 1;
	std::cout << "which part ? (1 or 2)\n";
	std::cin >> part;
	Sim sim(part);
	while (!input.eof()) {
		std::getline(input, line);
		sim.parseLine(line);
	}
	std::cout << "result = " << sim.startSim() << std::endl;
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
