#pragma warning(disable : 4996)

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Ingredient {
	char capacity;
	char durability;
	char flavor;
	char texture;
	char calories;
};

class Share {

	int _part;

	void _incr() {
		if (!finish) {
			if (spoons[2]) {
				++spoons[3];
				--spoons[2];
				if (spoons.back() == max)
					finish = true;
			}
			else {
				if (spoons[3]) {
					spoons[2] = spoons[3];
					spoons[3] = 0;
				}
				if (spoons[0]) {
					++spoons[1];
					--spoons[0];
				}
				else if (spoons[1]) {
					spoons[0] = spoons[1];
					spoons[1] = 0;
					++spoons[2];
					--spoons[1];
				}
			}
		}
		
	}


public:

	std::vector<char> spoons;
	const unsigned char max;
	bool finish;

	Share(short m, std::vector<unsigned char>::size_type size, int part) : _part(part), max(m), finish(false) {
		spoons.assign(size, 0);
		spoons[0] = max;
	}
	Share(const Share& other) : _part(other._part), spoons(other.spoons), max(other.max), finish(other.finish) {}

	Share& operator++() {
		_incr();
		return *this;
	}

	Share operator++(int) {
		Share temp(*this);
		++*this;
		return temp;
	}

	long result(const std::vector<Ingredient>& ing) const {
		long cap = 0;
		long dur = 0;
		long fla = 0;
		long tex = 0;
		long cal = 0;
		std::vector<char>::size_type idx = 0;
		for (std::vector<Ingredient>::const_iterator it = ing.begin(); it != ing.end(); ++it) {
			cap += spoons[idx] * it->capacity;
			dur += spoons[idx] * it->durability;
			fla += spoons[idx] * it->flavor;
			tex += spoons[idx] * it->texture;
			cal += spoons[idx++] * it->calories;
		}
		if (cap <= 0 | dur <= 0 | fla <= 0 | tex <= 0 | (_part != 1 & cal != 500))
			return 0;
		return cap * dur * fla * tex;
	}
};

std::ostream& operator<<(std::ostream& o, const Ingredient& i) {
	o << "capacity : " << (int)i.capacity << " | durability : " << (int)i.durability << " | flavor " << (int)i.flavor <<
		" | texture : " << (int)i.texture << " | calories : " << (int)i.calories;
	return o;
}

Ingredient parseLine(const std::string& line) {
	std::string::size_type idx = 0;
	std::string::size_type lenght = line.length();
	Ingredient pouet;
	uint64_t	i = 0;
	while (idx < lenght) {
		if (isdigit(line[idx]) || line[idx] == '-') {
			*((char*)&pouet + i++) = atoi(&line[idx]);
			while (isdigit(line[++idx]));
		}
		else
			++idx;
	}
	return pouet;
}

int main()
{
	std::ifstream input("./Input.txt");
	if (input.fail())
	{
		std::cerr << "couldn't read file ./Input.txt : " << strerror(errno) << std::endl;
		return errno;
	}
	std::string line;
	int part = 1;
	std::cout << "Which part ? (1 or 2)\n";
	std::cin >> part;
	std::vector<Ingredient> recipe;
	while (!input.eof()) {
		getline(input, line);
		recipe.push_back(parseLine(line));
	}
	Share pouet(100, recipe.size(), part);
	long max = 0;
	long newResult;
	while (!pouet.finish) {
		newResult = pouet.result(recipe);
		if (newResult > max)
			max = newResult;
		++pouet;
	}
	std::cout << "result is " << max << std::endl;
	return 0;
}

