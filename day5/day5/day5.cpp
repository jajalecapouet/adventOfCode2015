// day5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class niceStringChecker {
	
	typedef std::pair<char, char> Pair;
	typedef std::map<Pair, std::string::size_type> Pairs;

	std::vector<std::string> _exceptions;
	const char _vowels[5] = { 'a', 'e', 'i', 'o', 'u' };
	const int _part;

	bool _isVowels(char c) {
		for (int i = 0; i < 5; ++i) {
			if (c == _vowels[i])
				return true;
		}
		return false;
	}

	bool _isException(char a, char b) {
		for (std::vector<std::string>::const_iterator it = _exceptions.begin(); it != _exceptions.end(); ++it) {
			if (a == it->at(0) && b == it->at(1))
				return true;
		}
		return false;
	}

	int _isNicePartOne(const std::string& str) {
		bool twice = false;
		int vowelsCount = 0;
		char previous = 0;
		for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
			if (vowelsCount < 3 && _isVowels(*it))
				++vowelsCount;
			if (!twice && *it == previous)
				twice = true;
			else if (_isException(previous, *it)) {
				return 0;
			}
			previous = *it;
		}
		if (twice && vowelsCount == 3)
			return 1;
		return 0;
	}

	int _isNicePartTwo(const std::string& str) {
		bool between = false;
		bool pairOk = false;
		char previous = 0;
		char prePrevious = 0;
		Pairs pairs;
		std::string::size_type pos = 0;
		for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
			if (!between && prePrevious == *it)
				between = true;
			if (!pairOk) {
				std::pair<Pairs::iterator, bool> insertResult = pairs.insert(std::make_pair(std::make_pair(previous, *it), pos));
				if (!insertResult.second) {
					if (insertResult.first->second <= pos - 2)
						pairOk = true;
				}
				++pos;
			}
			if (pairOk && between)
				return 1;
			prePrevious = previous;
			previous = *it;
		}
		return 0;
	}

public :

	niceStringChecker() : _part(1) {
		_exceptions.insert(_exceptions.end(), {"ab", "cd", "pq", "xy"});
	}

	niceStringChecker(int part) : _part(part) {
		if (part == 1)
			_exceptions.insert(_exceptions.end(), { "ab", "cd", "pq", "xy" });
	}

	~niceStringChecker() {}

	int isNice(const std::string& str) {
		if (_part == 1)
			return _isNicePartOne(str);
		return _isNicePartTwo(str);
	}

};

int main()
{
	std::ifstream input("./Input.txt");
	if (input.fail())
	{
		std::cerr << "couldn't read file.\n";
		return 1;
	}
	int part = 1;
	std::cout << "which part ? (1 or 2)\n";
	std::cin >> part;
	std::string line;
	niceStringChecker tool(2);
	int count = 0;
	while (!input.eof()) {
		std::getline(input, line);
		count += tool.isNice(line);
	}
	std::cout << count << std::endl;
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
