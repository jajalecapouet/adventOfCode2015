#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

typedef std::pair<int, int> Coord;
typedef std::vector<bool> Row;
typedef std::vector<Row> Grid;

std::ostream& operator<<(std::ostream& o, const Row& r) {
	for (bool b : r) {
		if (b)
			o << '#';
		else
			o << '.';
	}
	return o;
}

std::ostream& operator<<(std::ostream& o, const Grid& g) {
	for (Row r : g) {
		o << r << std::endl;
	}
	return o;
}

class Sim {

	Grid _grid;
	int _part;

	int _checkAround(int x, int y) {
		int neigh = 0;
		for (int j = -1; j < 2; ++j) {
			if (y + j >= 0 & y + j < _grid.size()) {
				for (int i = -1; i < 2; ++i) {
					if (x + i >= 0 & !(i == 0 & j == 0) & x + i < _grid[y + j].size()) {
						if (_grid[y + j][x + i])
							++neigh;
					}
				}
			}

		}
		return neigh;
	}

	void _incr() {
		Grid nextGrid(_grid);
		for (int j = 0; j < _grid.size(); ++j) {
			for (int i = 0; i < _grid[j].size(); ++i) {
				int neigh = _checkAround(i, j);
				if (_part == 1 || (!(i == 0 && j == 0) && !(i == 0 && j == _grid.size() - 1)
					&& !(i == _grid[j].size() - 1 && j == 0) && !(i == _grid[j].size() - 1 && j == _grid.size() - 1))) {
					if (_grid[j][i]) {
						if (neigh < 2 | neigh > 3)
							nextGrid[j][i] = false;
					}
					else {
						if (neigh == 3)
							nextGrid[j][i] = true;
					}
				}
			}
		}
		_grid = nextGrid;
		//std::cout << _grid << std::endl;
	}

public :

	Sim() : _part(1) {
		_grid.reserve(100);
	}

	Sim(const Grid& g, int part) : _grid(g), _part(part) {
		if (_part != 1) {
			_grid[0][0] = true;
			_grid[0][99] = true;
			_grid[99][0] = true;
			_grid[99][99] = true;
		}
	}

	Sim(const Sim& o) : _grid(o._grid), _part(o._part) {}

	Sim& operator++() {
		_incr();
		return *this;
	}

	Sim operator++(int) {
		Sim tmp(*this);
		++*this;
		return tmp;
	}

	const Grid& getGrid() const {
		return _grid;
	}

	int countLights() const {
		int result = 0;
		for (Row r : _grid) {
			for (bool b : r) {
				if (b)
					++result;
			}
		}
		return result;
	}

};

int main()
{
	std::ifstream input("./Input.txt");
	if (input.fail()) {
		std::cerr << "Couldn't open file ./Input.txt : " << strerror(errno) << std::endl;
		return errno;
	}
	std::string line;
	int part = 1;
	std::cout << "Which part ? (1 or 2)\n";
	std::cin >> part;
	Grid grid;
	grid.reserve(100);
	Row row;
	row.reserve(100);
	while (!input.eof()) {
		row.clear();
		getline(input, line);
		for (char c : line) {
			if (c == '.')
				row.push_back(false);
			else
				row.push_back(true);
		}
		grid.push_back(row);
	}
	Sim sim(grid, part);
	for (int i = 0; i < 100; ++i)
		++sim;
	std::cout << "result is " << sim.countLights() << std::endl;
	return 0;
}
