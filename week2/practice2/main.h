#ifndef MIREA_ALGOS_MAIN_H
#define MIREA_ALGOS_MAIN_H

#include <iostream>
#include <string>

struct Account {
	Account* prev = nullptr;
	Account* next = nullptr;
	int id;
	std::string name;
	std::string address;

	int hash_code();
};

int main();

#endif//MIREA_ALGOS_MAIN_H
