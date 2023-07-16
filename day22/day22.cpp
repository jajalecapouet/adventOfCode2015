#pragma warning(disable : 4996)

#include <iostream>
#include <fstream>
#include <string>

struct Boss {
	int pv;
	int dm;
};

struct Wizard {
	int pv;
	int ar;
	int mana;
};

struct Effects {
	int poi;
	int rec;
	int shi;
};

class Sim {

	int _part;
	Effects _eff;
	Wizard _wiz;
	Boss _boss;
	int _manaSpend;

	void _missile() {
		_wiz.mana -= 53;
		_manaSpend += 53;
		_boss.pv -= 4;
	}

	void _reverseMissile() {
		_wiz.mana += 53;
		_manaSpend -= 53;
		_boss.pv += 4;
	}

	void _drain() {
		_wiz.mana -= 73;
		_manaSpend += 73;
		_boss.pv -= 2;
		_wiz.pv += 2;
	}

	void _reverseDrain() {
		_wiz.mana += 73;
		_manaSpend -= 73;
		_boss.pv += 2;
		_wiz.pv -= 2;
	}

	void _shield() {
		_wiz.mana -= 113;
		_manaSpend += 113;
		_eff.shi = 6;
	}

	void _reverseShield() {
		_wiz.mana += 113;
		_manaSpend -= 113;
		_eff.shi = 0;
	}

	void _poison() {
		_wiz.mana -= 173;
		_manaSpend += 173;
		_eff.poi = 6;
	}

	void _reversePoison() {
		_wiz.mana += 173;
		_manaSpend -= 173;
		_eff.poi = 0;
	}

	void _recharge() {
		_wiz.mana -= 229;
		_manaSpend += 229;
		_eff.rec = 5;
	}

	void _reverseRecharge() {
		_wiz.mana += 229;
		_manaSpend -= 229;
		_eff.rec = 0;
	}

	int _applyEffects(bool playerTurn) {
		int prevEffect = 0;
		_wiz.ar = 0;
		if (_eff.shi) {
			_wiz.ar = 7;
			--_eff.shi;
			prevEffect |= 1;
		}
		if (_eff.poi) {
			--_eff.poi;
			_boss.pv -= 3;
			prevEffect |= 2;
		}
		if (_eff.rec) {
			--_eff.rec;
			_wiz.mana += 101;
			prevEffect |= 4;
		}
		if (_part != 1 && playerTurn)
			--_wiz.pv;
		return prevEffect;
	}

	void _reverseApplyEffects(int prevEffect, bool playerTurn) {
		if (prevEffect & 1) {
			++_eff.shi;
		}
		if (prevEffect & 2) {
			++_eff.poi;
			_boss.pv += 3;
		}
		if (prevEffect & 4) {
			++_eff.rec;
			_wiz.mana -= 101;
		}
		if (_part != 1 && playerTurn)
			++_wiz.pv;
	}

	std::pair<bool, int> _bossHit() {
		int dmgDealt = _boss.dm - _wiz.ar;
		if (dmgDealt <= 0)
			dmgDealt = 1;
		_wiz.pv -= dmgDealt;
		return std::make_pair(_wiz.pv < 1, dmgDealt);
	}

	void _reverseBossHit(int dmg) {
		_wiz.pv += dmg;
	}

	void _dfs(int &best, bool playerTurn) {
		static int loop = 0;
		++loop;
		if (_manaSpend >= best)
			return;
		int resEffects = _applyEffects(playerTurn);
		if (_wiz.pv <= 0);
		else if (_boss.pv <= 0) {
			best = _manaSpend;
			std::cout <<"at loop " << loop << "(after effects) new best : " << best << std::endl;
		}
		else if (playerTurn) {
			_missile();
			if (_wiz.mana >= 0) {
				if (_boss.pv > 0)
					_dfs(best, !playerTurn);
				else if (_manaSpend < best) {
					best = _manaSpend;
					std::cout << "at loop " << loop << "(after missile) new best : " << best << std::endl;
				}
			}
			_reverseMissile();
			_drain();
			if (_wiz.mana >= 0) {
				if (_boss.pv > 0)
					_dfs(best, !playerTurn);
				else if (_manaSpend < best) {
					best = _manaSpend;
					std::cout << "at loop " << loop << "(after drain) new best : " << best << std::endl;
				}
			}
			_reverseDrain();
			if (!_eff.shi) {
				_shield();
				if (_wiz.mana >= 0)
					_dfs(best, !playerTurn);
				_reverseShield();
			}
			if (!_eff.poi) {
				_poison();
				if (_wiz.mana >= 0)
					_dfs(best, !playerTurn);
				_reversePoison();
			}
			if (!_eff.rec) {
				_recharge();
				if (_wiz.mana >= 0)
					_dfs(best, !playerTurn);
				_reverseRecharge();
			}
		}
		else {
			std::pair<bool, int> hitResult = _bossHit();
			if (!hitResult.first)
				_dfs(best, !playerTurn);
			_reverseBossHit(hitResult.second);
		}
		_reverseApplyEffects(resEffects, playerTurn);
	}

public:

	Sim(std::ifstream& input, int part) : _part(part), _eff({ 0, 0, 0 }), _wiz({ 50, 0, 500 }), _boss({ 0, 0 }), _manaSpend(0) {
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

	int fight() {
		int minManaSpend = 10000;
		_dfs(minManaSpend, true);
		return minManaSpend;
	}
};

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
	Sim sim(input, part);
	std::cout << "result is " << sim.fight() << std::endl;
	return (0);
}