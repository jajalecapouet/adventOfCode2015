#include <iostream>
#include <vector>

typedef std::vector<unsigned int> Houses;

int main()
{
    int part = 1;
    unsigned int nbOfGift = 10;
    unsigned int houseNumber;
    unsigned int countOfDelivery;
    Houses houses(1000001, 0);

    std::cout << "Which part ? (1 or 2)\n";
    std::cin >> part;
    if (part != 1)
        ++nbOfGift;
    for (unsigned int elf = 1; elf < 1000001; ++elf) {
        houseNumber = elf;
        countOfDelivery = 0;
        while (houseNumber < 1000001 && (part == 1 || ++countOfDelivery <= 50)) {
            houses[houseNumber] += nbOfGift * elf;
            houseNumber += elf;
        }
    }
    for (unsigned int idx = 0; idx < houses.size(); ++idx) {
        if (houses[idx] >= 36000000) {
            std::cout << "result is " << idx << " => " << houses[idx] << std::endl;
            break;
        }
    }
    return 0;
}