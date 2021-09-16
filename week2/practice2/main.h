#ifndef MIREA_ALGOS_MAIN_H
#define MIREA_ALGOS_MAIN_H

#include <iostream>
#include <string>
#include "HashSet.h"

unsigned XorShift128();

struct Account {
	int id;
	std::string name;
	std::string address;

	Account();

	Account(int, std::string, std::string);

	unsigned hash_code() const;
};

int main();

#endif //MIREA_ALGOS_MAIN_H
