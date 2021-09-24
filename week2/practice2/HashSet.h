#ifndef MIREA_ALGOS_HASHSEAccount_H
#define MIREA_ALGOS_HASHSEAccount_H

#include "main.h"
#include "Account.h"
#include <map>

class HashSet {
private:
	Account *arr[16];
	int capacity = 16;
	int size = 0;
	double load_factor = 0.75;
	std::map<int, int> hash_codes_count = std::map<int, int>();
public:
	HashSet();
	HashSet(int initial_capacity);
	HashSet(int initial_capacity, double load_factor);
	// добавление метода в коллекцию
	void put(Account&);
	// удаление первого попавшегося элемента в коллекцию
	bool remove(Account&);
	// получение первого попавшегося элемента в коллекции
	bool find(Account&) const;
	// вывод коллекции в консоль
	void print() const;
	// перераспределение элементов коллекции после достижения заполнения 75%
	void rehash();
	int f(const Account& account) const;
	int g(const Account& account) const;
};


#endif//MIREA_ALGOS_HASHSEAccount_H
