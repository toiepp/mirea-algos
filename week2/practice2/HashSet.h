#ifndef MIREA_ALGOS_HASHSET_H
#define MIREA_ALGOS_HASHSET_H

#include "main.h"

class HashSet {
private:
	Account *arr;
	int capacity;
	double load;
public:
	HashSet();
	HashSet(int);
	HashSet(int, double);
	// добавление метода в коллекцию
	void put(Account&);
	// удаление первого попавшегося элемента в коллекцию
	bool remove(Account&);
	// получение первого попавшегося элемента в коллекции
	Account find(Account&);
	// вывод коллекции в консоль
	void print();
	// перераспределение элементов коллекции после достижения заполнения 75%
	void rehash();
};


#endif//MIREA_ALGOS_HASHSET_H
