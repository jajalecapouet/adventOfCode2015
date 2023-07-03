// day12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <fstream>
#include <string>

bool isRed(const std::string& str, std::string::size_type idx) {
	return (!str.compare(idx, 3, "red"));
}

int parseLinePart2(const std::string& str, std::string::size_type& idx) {
	int psum = 0;
	bool ignore = false;
	std::string::size_type ignoreDepth = 0;
	while (idx < str.size()) {
		if (str[idx] == '}') {
			return psum;
		}
		else if (str[idx] == '{')
			psum += parseLinePart2(str, ++idx);
		else if (!ignore && isRed(str, idx)) {
			std::string::size_type depthScope = 1;
			while (depthScope) {
				++idx;
				if (str[idx] == '{')
					++depthScope;
				else if (str[idx] == '}')
					--depthScope;
			}
			return 0;
		}
		else if (str[idx] == '[') {
			++ignoreDepth;
			ignore = true;
		}
		else if (str[idx] == ']') {
			if (!ignore)
				throw(std::invalid_argument("bad parsing or bad file format.\n"));
			--ignoreDepth;
			if (!ignoreDepth)
				ignore = false;
		}
		else if ((isdigit(str[idx]) || str[idx] == '-')) {
			int bug = atoi(&str.c_str()[idx]);
			psum += bug;
			while (isdigit(str[idx + 1]))
				++idx;

		}
		++idx;
	}
	return psum;
}

int parseLine(const std::string& str) {
	int sum = 0;
	std::string::size_type idx = 0;
	while (idx < str.size()) {
		if ((isdigit(str[idx]) || str[idx] == '-')) {
			sum += atoi(&str.c_str()[idx]);
			while (isdigit(str[++idx]));
		}
		else
			++idx;
	}
	return sum;
}

int main()
{
	std::ifstream input("./Input.txt");
	if (input.fail()) {
		std::cerr << "couldn't open file ./Input.txt\n";
		return 1;
	}
	int part = 1;
	std::cout << "Which part ? (1 or 2)\n";
	std::cin >> part;
	std::string line;
	int sum = 0;
	while (!input.eof()) {
		std::getline(input, line);
		if (part == 1)
			sum += parseLine(line);
		else {
			std::string::size_type algoIdx = 0;
			sum = parseLinePart2(line, algoIdx);
		}
	}
	std::cout << "result is " << sum << std::endl;
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
