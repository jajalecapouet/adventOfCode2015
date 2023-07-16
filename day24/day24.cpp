#pragma warning(disable : 4996)

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

typedef std::vector<int> Pack;
typedef std::set<int> Choosen;

int sumCh(const Choosen& ch) {
	int res = 0;
	for (int i : ch)
		res += i;
	return res;
}

unsigned long long getQuantum(const Choosen& ch) {
	unsigned long long res = 1;
	for (int i : ch)
		res *= (unsigned long long) i;
	return res;
}

bool osefDfs(const Pack& rest, int start, int current, int goal) {
	if (goal == current)
		return true;
	while (start < rest.size()) {
		if (current + rest[start] <= goal) {
			current += rest[start];
			if (osefDfs(rest, start + 1, current, goal))
				return true;
			current -= rest[start];
		}
		++start;
	}
	return false;
}

bool restIsGood(const Pack& p, const Choosen& ch, int goal) {
	Pack rest;
	for (int i : p) {
		if (ch.find(i) == ch.end())
			rest.push_back(i);
	}
	return osefDfs(rest, 0, 0, goal);
}

void dfs(Choosen::size_type& bS, unsigned long long& bQ, Choosen& ch, const Pack& p, int start, int goal) {
	if (ch.size() > bS)
		return;
	if (sumCh(ch) == goal && restIsGood(p, ch, goal)) {
		unsigned long long newQ = getQuantum(ch);
		if (ch.size() == bS) {
			if (newQ < bQ)
				bQ = newQ;
		}
		else {
			bS = ch.size();
			bQ = newQ;
		}
	}
	while (start >= 0) {
		if (p[start] + sumCh(ch) <= goal) {
			ch.insert(p[start]);
			dfs(bS, bQ, ch, p, start - 1, goal);
			ch.erase(p[start]);
		}
		--start;
	}
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
	std::vector<int> p;
	int total = 0;
	int packageWeigh;
	while (!input.eof()) {
		getline(input, line);
		packageWeigh = stoi(line);
		total += packageWeigh;
		p.push_back(packageWeigh);
	}
	if (part == 1)
		total /= 3;
	else
		total /= 4;
	Choosen ch;
	Choosen::size_type bestSize = 28;
	unsigned long long bestQuantum = 0;
	dfs(bestSize, bestQuantum, ch, p, p.size() - 1, total);
	std::cout << "result is " << bestQuantum << std::endl;
	return 0;
}