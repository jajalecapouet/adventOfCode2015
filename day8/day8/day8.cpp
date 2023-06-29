// day8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>


int parseLinePartOne(const std::string& str) {
	int result = 0;
	std::string::size_type idx = 0;
	while (idx < str.size()) {
		++result;
		if (str[idx] == '\\') {
			if (str[idx + 1] == 'x')
				idx += 4;
			else
				idx += 2;
		}
		else
			++idx;
	}
	return result;
}

int parseLinePartTwo(const std::string& str) {
	int result = 4;
	std::string::size_type idx = 0;
	while (idx < str.size()) {
		char a = str[idx++];
		result += (a == '"' | a == '\\');
	}
	return result;
}

int main()
{
	std::ifstream input("./Input.txt");
	if (input.fail()) {
		std::cerr << "fail open Input.txt.\n";
		return 1;
	}
	int part = 1;
	std::cout << "which part ? (1 or 2)\n";
	std::cin >> part;
	std::string line;
	int allLine = 0;
	int allChar = 0;
	while (!input.eof()) {
		std::getline(input, line);
		std::string::size_type lineSize = line.size();
		if (part == 1) {
			allLine += lineSize;
			allChar += parseLinePartOne(line.substr(1, lineSize - 2));
		}
		else
			allLine += parseLinePartTwo(line.substr(1, lineSize - 2));
	}
	std::cout << "result : " << allLine - allChar << std::endl;
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
