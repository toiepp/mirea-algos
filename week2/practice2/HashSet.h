#ifndef MIREA_ALGOS_HASHSET_H
#define MIREA_ALGOS_HASHSET_H

#include "main.h"

template<typename T>
class HashSet {
private:
	T *arr;
	int capacity;
	double load;
public:
	HashSet();
	HashSet(int);
	HashSet(int, double);
	// добавление метода в коллекцию
	void put(T&);
	// удаление первого попавшегося элемента в коллекцию
	bool remove(T&);
	// получение первого попавшегося элемента в коллекции
	T find(T&);
	// вывод коллекции в консоль
	void print();
	// перераспределение элементов коллекции после достижения заполнения 75%
	void rehash();
};


#endif//MIREA_ALGOS_HASHSET_H
