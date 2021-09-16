#ifndef MIREA_ALGOS_MAIN_H
#define MIREA_ALGOS_MAIN_H

#include <iostream>
#include <string>

unsigned XorShift128();

struct Account {
	Account* prev = nullptr;
	Account* next = nullptr;
	int id;
	std::string name;
	std::string address;

	Account();

	Account(int, std::string, std::string);

	unsigned hash_code() const;
};

int main();

#endif //MIREA_ALGOS_MAIN_H
