// day11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

class Password {

	void _recuIncr(std::string::size_type idx) {
		char& c = pass[idx];
		if (c == 'z') {
			c = 'a';
			_recuIncr(idx - 1);
		}
		else if (c == 'h' | c == 'n' | c == 'k') {
			c += 2;
		}
		else
			c += 1;
	}

	bool _threeStraight() const {
		std::string::size_type idx = 2;
		while (idx < pass.size()) {
			if (pass[idx - 2] + 1 == pass[idx - 1] & pass[idx - 1] + 1 == pass[idx])
				return true;
			++idx;
		}
		return false;
	}

	bool _twoPairs() const {
		std::string::size_type idx = 0;
		std::string::size_type idxPair = std::string::npos;
		char prev = 0;
		for (char c : pass) {
			if (!prev)
				;
			else if (prev == c) {
				if (idxPair != std::string::npos & idx >= idxPair + 2)
					return true;
				if (idxPair == std::string::npos)
					idxPair = idx;
			}
			++idx;
			prev = c;
		}
		return false;
	}

public :

	std::string pass;

	Password(const std::string &str) : pass(str) {}

	bool ok() const {
		return (_threeStraight() & _twoPairs());
	}

	std::string& operator++() {
		_recuIncr(pass.length() - 1);
		return (pass);
	}

	std::string operator++(int) {
		std::string tmp = pass;
		_recuIncr(pass.length() - 1);
		return (tmp);
	}

};

std::ostream& operator<<(std::ostream& o, const Password& p) {
	o << p.pass;
	return o;
}

int main()
{
	Password pass("cqjxjnds");
	int part = 1;
	std::cout << "Which part ? (1 or 2)\n";
	std::cin >> part;
	++pass;
	while (!pass.ok()) {
		++pass;
	}
	if (part != 1) {
		++pass;
		while (!pass.ok())
			++pass;
	}
	std::cout << "new pass is " << pass << std::endl;
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
