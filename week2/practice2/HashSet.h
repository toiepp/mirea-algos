#ifndef MIREA_ALGOS_HASHSET_H
#define MIREA_ALGOS_HASHSET_H

#include "Account.h"
#include "main.h"
#include <vector>
#include <map>

class HashSet {
private:
	int init = 6;
	int capacity = 13;
	int load = 0; // кол-во элементов в массиве.
	double load_factor = 0.75;
	std::vector<Account *> arr = std::vector<Account *>(capacity, nullptr);

public:
	HashSet();
	HashSet(int initial_capacity);
	HashSet(int initial_capacity, double load_factor);
	// добавление метода в коллекцию
	void put(Account &);
	// Поиск по ключу
	Account *find(const std::string &) const;
	// Поиск по элементу
	bool find(Account &) const;
	// удаление первого попавшегося элемента в коллекцию
	bool remove(Account &);
	// вывод коллекции в консоль
	void print() const;

private:
	// Находит следующее (через 4) простое число и увеличивает до н1о
	int find_next_capacity();
	// перераспределение элементов коллекции после достижения заполнения 75%
	void rehash();
	int h1(const Account &account) const;
	int h2(const Account &account) const;
};


#endif// MIREA_ALGOS_HASHSET_H
