#pragma warning(disable : 4996)

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>

typedef std::pair<int, int> ItemStat;
typedef std::pair<int, ItemStat> Item;
typedef std::map<Item, int> ShopStock;
typedef std::map<int, std::set<ItemStat>> ItemsCombinations;

std::ostream& operator<<(std::ostream& o, const ItemStat& i) {
	o << "(atk : " << i.first << " def : " << i.second << ')';
	return o;
}

std::ostream& operator<<(std::ostream& o, const Item& i) {
	o << "Price : " << i.first << " stats : " << i.second;
	return o;
}

std::ostream& operator<<(std::ostream& o, const std::set<ItemStat>& s) {
	for (const ItemStat& i : s) {
		o << i << ' ';
	}
	return o;
}

std::ostream& operator<<(std::ostream& o, const ItemsCombinations& i) {
	for (ItemsCombinations::const_iterator cit = i.begin(); cit != i.end(); ++cit) {
		o << "Price : " << cit->first << " possible stats : " << cit->second << std::endl;
	}
	return o;
}

ItemStat& operator+=(ItemStat& lhs, const ItemStat& rhs) {
	lhs.first += rhs.first;
	lhs.second += rhs.second;
	return lhs;
}

ItemStat operator+(const ItemStat& lhs, const ItemStat& rhs) {
	return ItemStat(lhs.first + rhs.first, lhs.second + rhs.second);
}

ItemStat& operator-=(ItemStat& lhs, const ItemStat& rhs) {
	lhs.first -= rhs.first;
	lhs.second -= rhs.second;
	return lhs;
}

ItemStat operator-(const ItemStat& lhs, const ItemStat& rhs) {
	return ItemStat(lhs.first - rhs.first, lhs.second - rhs.second);
}

struct CharStat {
	int pv;
	int dm;
	int ar;
};

class Shop {

public:

	ShopStock weapons;
	ShopStock armors;
	ShopStock rings;

	Shop() {
		weapons.insert(std::make_pair(Item(8, ItemStat(4, 0)), 1));
		weapons.insert(std::make_pair(Item(10, ItemStat(5, 0)), 1));
		weapons.insert(std::make_pair(Item(25, ItemStat(6, 0)), 1));
		weapons.insert(std::make_pair(Item(40, ItemStat(7, 0)), 1));
		weapons.insert(std::make_pair(Item(74, ItemStat(8, 0)), 1));
		armors.insert(std::make_pair(Item(0, ItemStat(0, 0)), 1));
		armors.insert(std::make_pair(Item(13, ItemStat(0, 1)), 1));
		armors.insert(std::make_pair(Item(31, ItemStat(0, 2)), 1));
		armors.insert(std::make_pair(Item(53, ItemStat(0, 3)), 1));
		armors.insert(std::make_pair(Item(75, ItemStat(0, 4)), 1));
		armors.insert(std::make_pair(Item(102, ItemStat(0, 5)), 1));
		rings.insert(std::make_pair(Item(0, ItemStat(0, 0)), 2));
		rings.insert(std::make_pair(Item(25, ItemStat(1, 0)), 1));
		rings.insert(std::make_pair(Item(50, ItemStat(2, 0)), 1));
		rings.insert(std::make_pair(Item(100, ItemStat(3, 0)), 1));
		rings.insert(std::make_pair(Item(20, ItemStat(0, 1)), 1));
		rings.insert(std::make_pair(Item(40, ItemStat(0, 2)), 1));
		rings.insert(std::make_pair(Item(80, ItemStat(0, 3)), 1));
	}

};

class Sim {

	int _part;
	CharStat _hero;
	CharStat _boss;
	Shop _shop;
	ItemsCombinations _ezSolver; // A not opti tool just to find rapidly the response

	bool _herosWin() {
		int herosDmg = _hero.dm - _boss.ar;
		int bossDmg = _boss.dm - _hero.ar;
		if (herosDmg <= 0)
			return false;
		if (bossDmg <= 0)
			return true;
		int bossTurnsToDie = _boss.pv / (herosDmg);
		if (_boss.pv % (herosDmg))
			++bossTurnsToDie;
		int herosTurnsToDie = _hero.pv / (bossDmg);
		if (_hero.pv % (bossDmg))
			++herosTurnsToDie;
		return bossTurnsToDie <= herosTurnsToDie;
	}

	int _getResultPart1() {
		for (ItemsCombinations::const_iterator cit = _ezSolver.begin(); cit != _ezSolver.end(); ++cit) {
			for (std::set<ItemStat>::const_iterator cit2 = cit->second.begin(); cit2 != cit->second.end(); ++cit2) {
				_hero.dm = cit2->first;
				_hero.ar = cit2->second;
				if (_herosWin()) {
					return cit->first;
				}
			}
		}
		std::cout << "This boss is unbeatable.\n";
		return -1;
	}

	int _getResultPart2() {
		for (ItemsCombinations::const_reverse_iterator cit = _ezSolver.rbegin(); cit != _ezSolver.rend(); ++cit) {
			for (std::set<ItemStat>::const_iterator cit2 = cit->second.begin(); cit2 != cit->second.end(); ++cit2) {
				_hero.dm = cit2->first;
				_hero.ar = cit2->second;
				if (!_herosWin()) {
					return cit->first;
				}
			}
		}
		std::cout << "This hero is unbeatable.\n";
		return -1;
	}

public:

	Sim(std::ifstream& input, int part) : _part(part), _hero({100, 0, 0}), _boss({0, 0, 0})
	{
		std::string line;
		std::string::size_type idx;
		uint64_t ptrIdx = 0;
		while (!input.eof()) {
			getline(input, line);
			idx = 0;
			while (!isdigit(line[idx]))
				idx++;
			*(((int*)&_boss) + ptrIdx++) = atoi(&line[idx]);
		}
	}

	void doEzSolver() {
		ShopStock& w = _shop.weapons;
		ShopStock& a = _shop.armors;
		ShopStock& r = _shop.rings;
		ItemStat currentStat(0, 0);
		int moneySpend = 0;
		ItemsCombinations::iterator itInsert;
		for (ShopStock::iterator itW = w.begin(); itW != w.end(); ++itW) {
			moneySpend += itW->first.first;
			currentStat += itW->first.second;
			for (ShopStock::iterator itA = a.begin(); itA != a.end(); ++itA) {
				moneySpend += itA->first.first;
				currentStat += itA->first.second;
				for (ShopStock::iterator itR1 = r.begin(); itR1 != r.end(); ++itR1) {
					moneySpend += itR1->first.first;
					currentStat += itR1->first.second;
					--itR1->second;
					for (ShopStock::iterator itR2 = r.begin(); itR2 != r.end(); ++itR2) {
						if (itR2->second) {
							moneySpend += itR2->first.first;
							currentStat += itR2->first.second;
							itInsert = _ezSolver.insert(std::make_pair(moneySpend, std::set<ItemStat>())).first;
							itInsert->second.insert(currentStat);
							moneySpend -= itR2->first.first;
							currentStat -= itR2->first.second;
						}
					}
					moneySpend -= itR1->first.first;
					currentStat -= itR1->first.second;
					++itR1->second;
				}
				moneySpend -= itA->first.first;
				currentStat -= itA->first.second;
			}
			moneySpend -= itW->first.first;
			currentStat -= itW->first.second;
		}
		std::cout << _ezSolver << std::endl;
	}

	int getResult() {
		if (_part == 1)
			return _getResultPart1();
		else
			return _getResultPart2();
	}


};

int main() {
	std::ifstream input("./Input.txt");
	if (input.fail()) {
		std::cerr << "Couldn't open file ./Input.txt : " << strerror(errno) << std::endl;
		return errno;
	}
	int part = 1;
	std::cout << "Which part ? (1 or 2)\n";
	std::cin >> part;
	Sim sim(input, part);
	sim.doEzSolver();
	std::cout << "result is " << sim.getResult() << std::endl;
	return(0);
}
