#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <string>
#include <map>

typedef std::map<int, int> Cont;

bool notEnoughtContainers(int liters, const Cont& c) {
	for (Cont::const_iterator cit = c.begin(); cit != c.end(); ++cit) {
		liters += cit->second;
		if (liters >= 150)
			return false;
	}
	return true;
}

int dfs(int liters, Cont cont, int depth, Cont& resultStock) {
	if (liters == 150) {
		std::pair<Cont::iterator, bool> insertResult = resultStock.insert(std::make_pair(depth, 0));
		insertResult.first->second += 1;
		return 1;
	}
	if (liters > 150 | cont.empty() | notEnoughtContainers(liters, cont))
		return 0;
	int score = 0;
	int litersTmp;
	Cont::iterator it = cont.begin();
	Cont::iterator tmp;
	while (it != cont.end()) {
		liters += it->second;
		litersTmp = it->second;
		tmp = it;
		++it;
		++depth;
		cont.erase(tmp);
		score += dfs(liters, cont, depth, resultStock);
		--depth;
		liters -= litersTmp;
	}
	return score;
}

int main() {
	std::ifstream input("./Input.txt");
	if (input.fail()) {
		std::cerr << "Couldn't open file ./Input.txt : " << strerror(errno) << std::endl;
		return errno;
	}
	std::string line;
	int part = 1;
	std::cout << "Which part ? (1 or 2)\n";
	std::cin >> part;
	Cont cont;
	int idx = 0;
	while (!input.eof()) {
		getline(input, line);
		cont.insert(std::make_pair(idx++, stoi(line)));
	}
	int result = 0;
	Cont resultStock;
	result = dfs(0, cont, 0, resultStock);
	if (part == 1)
		std::cout << "result is " << result << std::endl;
	else
		std::cout << "result is " << resultStock.begin()->second << std::endl;
	return 0;
}