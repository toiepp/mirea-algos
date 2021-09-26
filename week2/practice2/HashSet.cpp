#include "HashSet.h"

HashSet::HashSet() = default;

HashSet::HashSet(int initial_capacity) : capacity(initial_capacity) {}

HashSet::HashSet(int initial_capacity, double load_factor) : HashSet(initial_capacity) {
	this->load_factor = load_factor;
}

void HashSet::put(Account &account) {
	int x = h1(account);
	int y = h2(account);
	for (int i = 0; i < capacity; ++i) {
		if (arr.at(x) == nullptr) {
			arr[x] = &account;
			return;
		}
		x = (x + y) % capacity;
	}
	rehash();
}

Account* HashSet::find(const std::string& key) const {
	for (int i = 0; i < capacity; ++i) {
		if (arr.at(i) != nullptr) {
			if (arr.at(i)->name == key) { return arr.at(i); }
		}
	}
	return nullptr;
}

bool HashSet::remove(Account &account) {
	return false;
}

void HashSet::print() const {
	for (int i = 0; i < capacity; ++i) {
		if (arr.at(i) != nullptr) {
			std::cout << "("
					  << i << ", "
					  << (*arr.at(i)).hash_code()
					  << "):\t" << (*arr.at(i)) << std::endl;
		} else {
			std::cout << "(" << i << ", ___):" << std::endl;
		}
	}
}

void HashSet::rehash() {
}

// k mod N
int HashSet::h1(const Account &account) const {
	return (int) (account.hash_code() % capacity);
}

// 1 + k mod (N - 2)
int HashSet::h2(const Account &account) const {
	return (int) (1 + account.hash_code() % (capacity - 2));
}