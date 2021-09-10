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
	void put(Account&);
	bool remove(Account&);
	bool find(Account&);
	void print();
	void rehash();
};


#endif//MIREA_ALGOS_HASHSET_H
