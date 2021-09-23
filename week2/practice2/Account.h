#ifndef MIREA_ALGOS_ACCOUNT_H
#define MIREA_ALGOS_ACCOUNT_H

#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <utility>

class Account {
	// WARN
	static unsigned generate_id();

public:
	unsigned id;
	std::string name;
	std::string address;

	Account();

	Account(std::string, std::string);

	unsigned hash_code() const;
};

#endif//MIREA_ALGOS_ACCOUNT_H
