// day10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

std::string algo(const std::string& str) {
	std::string result;
	result.reserve(2 * str.length()); //This is to not reallocate a lot of times the dynamic array of string for part 2
	char prevDigit = 0;
	int times = 0;
	for (const char& c : str) {
		if (prevDigit && c != prevDigit) {
			result += times + '0';
			times = 0;
			result += prevDigit;
			prevDigit = c;
		}
		if (!prevDigit)
			prevDigit = c;
		++times;
	}
	result += times + '0';
	result += prevDigit;
	return result;
}

int main()
{
	std::string input = "1321131112";
	std::string result;
	int part = 1;
	std::cout << "Which part ? (1 or 2)\n";
	std::cin >> part;
	if (part == 1) {
		for (int i = 0; i < 40; ++i)
			input = algo(input);
	}
	else {
		for (int i = 0; i < 50; ++i)
			input = algo(input);
	}
	std::cout << "result is " << input.length() << std::endl;
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
