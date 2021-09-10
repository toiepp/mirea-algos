#include "HashSet.h"

HashSet::HashSet()
	: arr(new Account[16])
	, capacity(16)
	, load(0.75) { }

HashSet::HashSet(int capacity)
	: arr(new Account[capacity])
	, capacity(capacity)
	, load(0.75) { }

HashSet::HashSet(int capacity, double load)
	: HashSet(capacity) {
	this->capacity = capacity;
	this->load = load;
}

void HashSet::put(Account &account) {

}

bool HashSet::remove(Account &account) {
	return false;
}

bool HashSet::find(Account &account) {
	return false;
}

void HashSet::print() {

}
void HashSet::rehash() {
}
