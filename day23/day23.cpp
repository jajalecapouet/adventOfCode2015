#pragma warning(disable : 4996)

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define HLF 0
#define TPL 1
#define INC 2
#define JMP 3
#define JIE 4
#define JIO 5

class Ins;

typedef std::vector<Ins> Program;

class Ins {

	int _type;
	unsigned int* _t;
	int _jmp;

public:

	Ins(const std::string& str, unsigned int* a, unsigned int* b) : _type(HLF), _t(nullptr), _jmp(0) {
		if (!str.compare(0, 3, "hlf")) {
			if (str[4] == 'a')
				_t = a;
			else
				_t = b;
		}
		else if (!str.compare(0, 3, "tpl")) {
			_type = TPL;
			if (str[4] == 'a')
				_t = a;
			else
				_t = b;
		}
		else if (!str.compare(0, 3, "inc")) {
			_type = INC;
			if (str[4] == 'a')
				_t = a;
			else
				_t = b;
		}
		else if (!str.compare(0, 3, "jmp")) {
			_type = JMP;
			if (str[4] == '+')
				_jmp = atoi(&str[5]);
			else
				_jmp = -atoi(&str[5]);
		}
		else if (!str.compare(0, 3, "jie")) {
			_type = JIE;
			if (str[4] == 'a')
				_t = a;
			else
				_t = b;
			if (str[7] == '+')
				_jmp = atoi(&str[8]);
			else
				_jmp = -atoi(&str[8]);
		}
		else if (!str.compare(0, 3, "jio")) {
			_type = JIO;
			if (str[4] == 'a')
				_t = a;
			else
				_t = b;
			if (str[7] == '+')
				_jmp = atoi(&str[8]);
			else
				_jmp = -atoi(&str[8]);
		}
	}

	void exe(Program& p, unsigned int idx) {
		int jump = 1;
		switch (_type) {
		case HLF:
			*_t >>= 1;
			break;
		case TPL:
			*_t *= 3;
			break;
		case INC:
			*_t += 1;
			break;
		case JMP:
			jump = _jmp;
			break;
		case JIE:
			if (!(*_t % 2))
				jump = _jmp;
			break;
		case JIO:
			if (*_t == 1)
				jump = _jmp;
			break;
		}
		jump += idx;
		if (jump < p.size())
			p[jump].exe(p, jump);
	}
};

void exe(Program& p) {
	p[0].exe(p, 0);
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
	unsigned int a = 0;
	if (part != 1)
		a = 1;
	unsigned int b = 0;
	Program pouet;
	while (!input.eof()) {
		getline(input, line);
		pouet.push_back(Ins(line, &a, &b));
	}
	exe(pouet);
	std::cout << "result is " << b << std::endl;

	return 0;
}