#pragma warning(disable : 4996)

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Renne {

public :

	std::string name;
	unsigned int speed;
	unsigned int runTime;
	unsigned int restTime;
	unsigned int result;
	unsigned int dist;

	Renne() : speed(0), runTime(0), restTime(0), result(0), dist(0) {}
	Renne(const std::string& n, int sp, int run, int rest) : name(n), speed(sp), runTime(run), restTime(rest), result(0), dist(0) {}

	void parseLine(const std::string& str) {
		std::string::size_type idx = str.find(' ');
		name = str.substr(0, idx);
		while (!isdigit(str[++idx]));
		speed = atoi(&str[idx]);
		while (isdigit(str[++idx]));
		while (!isdigit(str[++idx]));
		runTime = atoi(&str[idx]);
		while (isdigit(str[++idx]));
		while (!isdigit(str[++idx]));
		restTime = atoi(&str[idx]);
	}

	void getResult() {
		unsigned int i = 0;
		unsigned int loop = runTime + restTime;
		unsigned int time = 2503;
		result = speed * ((time / loop) * runTime + std::min((time % loop), runTime));
	}

};

std::ostream& operator<<(std::ostream& o, const Renne& r) {
	o << r.name << " | sp : " << r.speed << " | runTime : " << r.runTime <<
		" | restTime : " << r.restTime << " | result : " << r.result;
	return o;
}

std::ostream& operator<<(std::ostream& o, const std::vector<Renne>& v) {
	for (Renne r : v) {
		o << r << std::endl;
	}
	return o;
}

int main(void) {
	std::ifstream input("./Input.txt");
	if (input.fail()) {
		std::cerr << "couldn't open file ./Input.txt -> " << errno << " : " << strerror(errno) << std::endl;;
		return errno;
	}
	std::string line;
	int part = 1;
	std::cout << "Which part ? (1 or 2)\n";
	std::cin >> part;
	std::vector<Renne> rennes;
	while (!input.eof()) {
		rennes.push_back(Renne());
		getline(input, line);
		rennes.back().parseLine(line);
		if (part == 1)
			rennes.back().getResult();
	}
	if (part == 1) {
		unsigned int max = 0;
		for (Renne r : rennes) {
			if (r.result > max)
				max = r.result;
		}
		std::cout << "result is " << max << std::endl;
	}
	else {
		int i = 0;
		int max;
		while (i < 2503) {
			max = 0;
			for (std::vector<Renne>::iterator r = rennes.begin(); r != rennes.end(); ++r) {
				if (i % (r->runTime + r->restTime) < r->runTime) {
					r->dist += r->speed;
				}
				if (r->dist >= max) {
					max = r->dist;
				}
			}
			for (std::vector<Renne>::iterator r = rennes.begin(); r != rennes.end(); ++r) {
				if (r->dist == max)
					r->result += 1;
			}
			++i;
		}
		max = 0;
		for (std::vector<Renne>::iterator r = rennes.begin(); r != rennes.end(); ++r) {
			if (r->result > max)
				max = r->result;
		}
		std::cout << "result is " << max << std::endl;
	}
	return 0;
}