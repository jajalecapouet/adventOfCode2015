// Day7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <set>

typedef struct Content {
	std::string lhs;
	unsigned short lhsVal;
	std::string rhs;
	unsigned short rhsVal;
	std::string operand;
	bool valueFind;
	unsigned short value;
};

typedef std::map<std::string, Content> Entries;

bool isDigit(char c) {
	return (c >= '0' && c <= '9');
}

void resetMap(Entries& ent) {
	for (Entries::iterator it = ent.begin(); it != ent.end(); ++it) {
		it->second.value = 0;
		it->second.valueFind = false;
	}
}

void parseLine(const std::string &line, Entries& entries) {
	int count = 1;
	bool endParse = false;
	std::string key;
	Content content = { "", 0, "", 0, "", false, 0 };
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

unsigned short getValueRecursive(Content& cont, Entries& ent) {
	std::string op = cont.operand;
	if (cont.valueFind)
		return cont.value;
	cont.valueFind = true;
	if (cont.lhs.empty() && cont.rhs.empty()) {
		if (op == "EQUAL")
			cont.value = cont.lhsVal;
		else if (op == "NOT")
			cont.value = ~cont.lhsVal;
		else if (op == "AND")
			cont.value = cont.lhsVal & cont.rhsVal;
		else if (op == "OR")
			cont.value = cont.lhsVal | cont.rhsVal;
		else if (op == "RSHIFT")
			cont.value = cont.lhsVal >> cont.rhsVal;
		else if (op == "LSHIFT")
			cont.value = cont.lhsVal << cont.rhsVal;
		return cont.value;
	}
	if (cont.lhs.empty()) {
		if (op == "AND")
			cont.value = cont.lhsVal & getValueRecursive(ent.find(cont.rhs)->second, ent);
		else if (op == "OR")
			cont.value = cont.lhsVal | getValueRecursive(ent.find(cont.rhs)->second, ent);
		else if (op == "RSHIFT")
			cont.value = cont.lhsVal >> getValueRecursive(ent.find(cont.rhs)->second, ent);
		else if (op == "LSHIFT")
			cont.value = cont.lhsVal << getValueRecursive(ent.find(cont.rhs)->second, ent);
		return cont.value;
	}
	if (cont.rhs.empty()) {
		if (op == "EQUAL")
			cont.value = getValueRecursive(ent.find(cont.lhs)->second, ent);
		else if (op == "NOT")
			cont.value = ~getValueRecursive(ent.find(cont.lhs)->second, ent);
		else if (op == "AND")
			cont.value = getValueRecursive(ent.find(cont.lhs)->second, ent) & cont.rhsVal;
		else if (op == "OR")
			cont.value = getValueRecursive(ent.find(cont.lhs)->second, ent) | cont.rhsVal;
		else if (op == "RSHIFT")
		{
			if (cont.rhsVal >= 16)
				cont.value = 0;
			else
				cont.value = getValueRecursive(ent.find(cont.lhs)->second, ent) >> cont.rhsVal;
		}
		else if (op == "LSHIFT")
		{
			if (cont.lhsVal >= 16)
				cont.value = 0;
			else
				cont.value = getValueRecursive(ent.find(cont.lhs)->second, ent) << cont.rhsVal;
		}
		return cont.value;
	}
	if (op == "AND")
		cont.value = getValueRecursive(ent.find(cont.lhs)->second, ent) & getValueRecursive(ent.find(cont.rhs)->second, ent);
	else if (op == "OR")
		cont.value = getValueRecursive(ent.find(cont.lhs)->second, ent) | getValueRecursive(ent.find(cont.rhs)->second, ent);
	else if (op == "RSHIFT")
		cont.value = getValueRecursive(ent.find(cont.lhs)->second, ent) >> getValueRecursive(ent.find(cont.rhs)->second, ent);
	else if (op == "LSHIFT")
		cont.value = getValueRecursive(ent.find(cont.lhs)->second, ent) << getValueRecursive(ent.find(cont.rhs)->second, ent);
	return cont.value;
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
	unsigned short a = getValueRecursive(entries.find("a")->second, entries);
	if (part != 1) {
		resetMap(entries);
		entries.find("b")->second.lhsVal = a;
		a = getValueRecursive(entries.find("a")->second, entries);
	}
	std::cout << "Result is " << a << std::endl;
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
