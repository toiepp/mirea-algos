#include "HashSet.h"

HashSet::HashSet() {
	for (int i = 0; i < capacity; ++i) {
		arr[i] = nullptr;
	}
}

HashSet::HashSet(int initial_capacity)
	: capacity(initial_capacity) { }

HashSet::HashSet(int initial_capacity, double load_factor)
	: HashSet(initial_capacity) {
	this->load_factor = load_factor;
}

void HashSet::put(Account &account) {
}

bool HashSet::remove(Account &account) {
	return false;
}

bool HashSet::find(Account &account) const {
	for (int i = 0; i < capacity; ++i) {
		if (arr[i] && arr[i] == account) return true;
	}
	return false;
}

void HashSet::print() const {
	for (int i = 0; i < capacity; ++i) {
		if (arr[i] != nullptr) std::cout << arr[i] << std::endl;
	}
}

void HashSet::rehash() {

}

int HashSet::with_shift(unsigned hash) const {
	
}