#ifndef MIREA_ALGOS_ACCOUNT_H
#define MIREA_ALGOS_ACCOUNT_H

#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <utility>

class Account {
	// WARN Переделать алгоритм генерации уникального id
	static unsigned generate_id();

public:
	unsigned id;
	std::string name;
	std::string address;

	Account(std::string, std::string);

	unsigned hash_code() const;
};

std::ostream &operator<<(std::ostream &out, const Account &account);
std::istream &operator>>(std::istream &in, Account account);

#endif//MIREA_ALGOS_ACCOUNT_H
