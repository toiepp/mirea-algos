#ifndef MIREA_ALGOS_HASHSET_H
#define MIREA_ALGOS_HASHSET_H

#include "Account.h"
#include "main.h"
#include "vector"
#include <map>

class HashSet {
private:
	int capacity = 13;
	int size = 0;
	double load_factor = 0.75;
	std::vector<Account *> arr = std::vector<Account *>(capacity, nullptr);

public:
	HashSet();
	HashSet(int initial_capacity);
	HashSet(int initial_capacity, double load_factor);
	// добавление метода в коллекцию
	void put(Account &);
	// удаление первого попавшегося элемента в коллекцию
	bool remove(Account &);
	// получение первого попавшегося элемента в коллекции
	// Поиск по ключу
	Account* find(const std::string&) const;
	// вывод коллекции в консоль
	void print() const;
	// перераспределение элементов коллекции после достижения заполнения 75%
	void rehash();

private:
	int h1(const Account &account) const;
	int h2(const Account &account) const;
};


#endif// MIREA_ALGOS_HASHSET_H
