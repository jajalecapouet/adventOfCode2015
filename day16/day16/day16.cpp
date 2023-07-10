#pragma warning(disable : 4996)

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

struct Sue {
	int sueIdx;
	int children;
	int cats;
	int samoyeds;
	int pomeranians;
	int akitas;
	int vizslas;
	int goldfish;
	int trees;
	int cars;
	int perfumes;
};

Sue parseLine(const std::string& str, const std::string compounds[]) {
	Sue toReturn = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	if (str.empty())
		return toReturn;
	std::string::size_type idx = 4;
	toReturn.sueIdx = atoi(&str[idx]);
	idx = str.find(':') + 2;
	uint64_t i;
	while (idx != std::string::npos) {
		i = 0;
		while (i < 10) {
			if (!str.compare(idx, compounds[i].size(), compounds[i])) {
				idx += compounds[i].size() + 2;
				*((int*)&toReturn + i + 1) = atoi(&str[idx]);
				break;
			}
			i++;
		}
		idx = str.find(',', idx);
		if (idx != std::string::npos)
			idx += 2;
	}
	return toReturn;
}

bool isGoodSue(const Sue& sue, int part) {
	if (part == 1) {
		if ((sue.children >= 0 & sue.children != 3) |
			(sue.cats >= 0 & sue.cats != 7) |
			(sue.samoyeds >= 0 & sue.samoyeds != 2) |
			(sue.pomeranians >= 0 & sue.pomeranians != 3) |
			(sue.akitas >= 0 & sue.akitas != 0) |
			(sue.vizslas >= 0 & sue.vizslas != 0) |
			(sue.goldfish >= 0 & sue.goldfish != 5) |
			(sue.trees >= 0 & sue.trees != 3) |
			(sue.cars >= 0 & sue.cars != 2) |
			(sue.perfumes >= 0 & sue.perfumes != 1) |
			sue.sueIdx == -1)
			return false;
	}
	else {
		if ((sue.children >= 0 & sue.children != 3) |
			(sue.cats >= 0 & sue.cats <= 7) |
			(sue.samoyeds >= 0 & sue.samoyeds != 2) |
			(sue.pomeranians >= 0 & sue.pomeranians >= 3) |
			(sue.akitas >= 0 & sue.akitas != 0) |
			(sue.vizslas >= 0 & sue.vizslas != 0) |
			(sue.goldfish >= 0 & sue.goldfish >= 5) |
			(sue.trees >= 0 & sue.trees <= 3) |
			(sue.cars >= 0 & sue.cars != 2) |
			(sue.perfumes >= 0 & sue.perfumes != 1) |
			sue.sueIdx == -1)
			return false;
	}
	return true;
}

int main() {
	std::ifstream input("./Input.txt");
	if (input.fail()) {
		std::cerr << "Couldn't open file ./Input.txt : " << strerror(errno) << std::endl;
		return errno;
	}
	std::string line;
	int part = 1;
	std::cout << "Wich part ? (1 or 2)\n";
	std::cin >> part;
	std::string compounds[] = { "children", "cats", "samoyeds", "pomeranians", "akitas", "vizslas", "goldfish", "trees", "cars", "perfumes" };
	int suesIdx = 0;
	while (!input.eof() & !isGoodSue(parseLine(line, compounds), part)) {
		getline(input, line);
		++suesIdx;
	}
	std::cout << "Good Sue is " << suesIdx << std::endl;
	return 0;
}