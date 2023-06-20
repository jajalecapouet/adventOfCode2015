// day1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>

int main()
{
	int part = 2;
	std::ifstream input("./Input.txt");
	if (input.fail()) {
		std::cerr << "couldn't open file\n";
		return 1;
	}
	std::string line;
	while (!input.eof())
	{
		std::getline(input, line);
	}
	int count = 0;
	if (part == 1) {
		for (std::string::const_iterator cit = line.begin(); cit != line.end(); ++cit) {
			if (*cit == ')')
				--count;
			else
				++count;
		}
		std::cout << count << std::endl;
	}
	else {
		int position = 0;
		for (std::string::const_iterator cit = line.begin(); cit != line.end(); ++cit) {
			if (count == -1)
			{
				std::cout << position << std::endl;
				return 0;
			}
			++position;
			if (*cit == ')')
				--count;
			else
				++count;
		}
	}
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
