// Day7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

#define LEAF 0
#define AND 1
#define OR 2
#define LSHIFT 3
#define RSHIFT 4
#define NOT 5
#define EQUAL 6

typedef struct Content {
	std::string lhs;
	int lhsVal;
	std::string rhs;
	int rhsVal;
	std::string operand;
};

typedef struct Node {
	int operand;
	Node* rhs;
	Node* lhs;
	int val;
};

typedef std::map<std::string, Content> Entries;

class LittleTree {

	int _part;
	Node* _first;

	Node* _newNode(const std::string& operand) {
		Node* newOne = new Node();
		newOne->lhs = nullptr;
		newOne->rhs = nullptr;
		newOne->val = 0;
		if (operand == "AND")
			newOne->operand = AND;
		else if (operand == "OR")
			newOne->operand = OR;
		else if (operand == "LSHIFT")
			newOne->operand = LSHIFT;
		else if (operand == "RSHIFT")
			newOne->operand = RSHIFT;
		else if (operand == "EQUAL")
			newOne->operand = EQUAL;
		else if (operand == "NOT")
			newOne->operand = NOT;
		return newOne;
	}

	Node* _newNode(int val) {
		Node* leaf = new Node();
		leaf->lhs = nullptr;
		leaf->rhs = nullptr;
		leaf->val = val;
		leaf->operand = LEAF;
		return leaf;
	}

	void _recuBuildTree(Node* current, const Entries& entries, const Content& needs) {
		std::string lhs = needs.lhs;
		std::string rhs = needs.rhs;
		if (!lhs.empty()) {
			Content CLhs = entries.find(lhs)->second;
			current->lhs = _newNode(CLhs.operand);
			_recuBuildTree(current->lhs, entries, CLhs);
		}
		else
			current->lhs = _newNode(needs.lhsVal);
		if (needs.operand != "EQUAL" && needs.operand != "NOT") {
			if (!rhs.empty()) {
				Content CRhs = entries.find(rhs)->second;
				current->rhs = _newNode(CRhs.operand);
				_recuBuildTree(current->rhs, entries, CRhs);
			}
			else
				current->rhs = _newNode(needs.rhsVal);
		}
	}

	void _recuBurnTree(Node* fiouf) {
		_recuBurnTree(fiouf->lhs);
		_recuBurnTree(fiouf->rhs);
		free(fiouf);
		fiouf = nullptr;
	}

	void _burnTree() {
		_recuBurnTree(_first->lhs);
		_recuBurnTree(_first->rhs);
		free(_first);
		_first = nullptr;
	}

	int _letRecuResultPartOne(Node* current) {
		switch (current->operand) {
		case LEAF:
			return current->val;
		case EQUAL:
			return _letRecuResultPartOne(current->lhs);
		case NOT:
			return ~_letRecuResultPartOne(current->lhs);
		case OR:
			return (_letRecuResultPartOne(current->lhs) | _letRecuResultPartOne(current->rhs));
		case AND:
			return (_letRecuResultPartOne(current->lhs) & _letRecuResultPartOne(current->rhs));
		case LSHIFT:
			return (_letRecuResultPartOne(current->lhs) << _letRecuResultPartOne(current->rhs));
		case RSHIFT:
			return (_letRecuResultPartOne(current->lhs) >> _letRecuResultPartOne(current->lhs));
		}
	}

public :

	LittleTree(int part, const Entries& entries) : _part(part), _first(nullptr) {
		if (part == 1) {
			Content start = entries.find("a")->second;
			_first = _newNode(start.operand);
			_recuBuildTree(_first, entries, start);
		}
		else {

		}
	}

	int gemmeResult() {
		if (_part == 1) {
			return (_letRecuResultPartOne(_first));
		}
		else {

		}
	}

};

bool isDigit(char c) {
	return (c >= '0' && c <= '9');
}

void parseLine(const std::string &line, Entries& entries) {
	int count = 1;
	bool endParse = false;
	std::string key;
	Content content = { "", 0, "", 0, "" };
	std::string::size_type idxStart = 0;
	std::string::size_type idxEnd = line.find(' ');
	if (idxEnd == std::string::npos)
		idxEnd = line.size();

	while (idxStart < line.size()) {
		std::string bout = line.substr(idxStart, idxEnd - idxStart);
		{
			if (endParse)
				key = bout;
			else if (!bout.compare("->")) {
				endParse = true;
				if (content.operand.empty())
					content.operand = "EQUAL";
			}
			else if (isDigit(bout[0])) {
				if (count <= 2)
					content.lhsVal = stoi(bout);
				else
					content.rhsVal = stoi(bout);
			}
			else if (isupper(bout[0]))
				content.operand = bout;
			else if (count <= 2)
				content.lhs = bout;
			else
				content.rhs = bout;
		}
		idxStart = ++idxEnd;
		idxEnd = line.find(' ', idxEnd);
		if (idxEnd == std::string::npos)
			idxEnd = line.size();
		++count;
	}
	entries.insert(std::make_pair(key, content));
}

int main()
{
	std::ifstream input("./Input.txt");
	if (input.fail()) {
		std::cout << "file error\n";
		return 1;
	}
	std::string line;
	int part;
	std::cout << "1 or 2 ?\n";
	std::cin >> part;
	Entries entries;
	while (!input.eof()) {
		std::getline(input, line);
		parseLine(line, entries);
	}
	LittleTree poney(part, entries);
	std::cout << "result : " << poney.gemmeResult() << std::endl;
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
