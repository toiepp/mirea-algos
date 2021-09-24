#include "HashSet.h"

HashSet::HashSet() {
	for (int i = 0; i < capacity; ++i) {
		arr[i] = nullptr;
	}
}

HashSet::HashSet(int initial_capacity)
	: capacity(initial_capacity) {}

HashSet::HashSet(int initial_capacity, double load_factor)
	: HashSet(initial_capacity) {
	this->load_factor = load_factor;
}

void HashSet::put(Account &account) {
	// Проверить заполнение массива
	// Если заполнение массива станет больше допустимой нормы,
	// то нежно провести перераспределение элементов
	if (((double) (100 * size) / capacity) > this->load_factor) {
		rehash();
	}
	// Проверяю заполнена ли ячейка в массиве с полученным хэшкодом
	int pos = f(account);
	// Если заполнена, то получаю новую позицию нового элемента
	if (arr[pos] != nullptr) {
		// добавить в map кол-во хэщей
		pos = g(account);
	}
}

bool HashSet::remove(Account &account) {
	return false;
}

bool HashSet::find(Account &account) const {
	return false;
}

void HashSet::print() const {
}

void HashSet::rehash() {
}

int HashSet::f(const Account &account) const {
	return static_cast<int>(account.hash_code()) % this->capacity;
}

int HashSet::g(const Account &account) const {
	return static_cast<int>((f(account) + hash_codes_count.at((int) account.hash_code()) * (1 + account.hash_code() % (capacity - 2))));
}