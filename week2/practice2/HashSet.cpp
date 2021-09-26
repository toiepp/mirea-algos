#include "HashSet.h"

HashSet::HashSet() = default;

HashSet::HashSet(int initial_capacity) : capacity(initial_capacity) {}

HashSet::HashSet(int initial_capacity, double load_factor) : HashSet(initial_capacity) {
	this->load_factor = load_factor;
}

void HashSet::put(Account &account) {
	int pos = f(account);
	if (arr.at(pos) == &account) return; // дублирующий ключ
	// Проверить заполнение массива, если надо перераспределить массив
	if (((double) (100 * (size + 1)) / capacity) > this->load_factor) {
		rehash();
	}
	// Получаю позицию, в которую должен вставиться элемент
	// Если ячейка не занята, то кладу в нее элемент.
	// И добавляю по данному ключу счетчик
	if (arr.at(pos) == nullptr) {
		arr[pos] = &account;
		shifts.insert(std::pair<int, int>(pos, 1));
		return;
	}
	// Проверяю заполнена ли ячейка в массиве с полученным хэшкодом
	// Если ячейка занята, то получаю новую позицию нового элемента
	if (arr.at(pos) != nullptr) {
		// Получаю новую позицию элемента в таблице
		shifts.at(pos)++;
		pos = g(account, shifts.at(pos));
		arr[pos] = &account;
		// Увеличиваю счетчик по данному хэш-коду
	}
}

bool HashSet::remove(Account &account) {
	return false;
}

bool HashSet::find(Account &account) const {
	return false;
}

void HashSet::print() const {
	for (int i = 0; i < capacity; ++i) {
		if (arr.at(i) != nullptr) {
			std::cout << "(" << i << ", " << (*arr.at(i)).hash_code() << "): " << (*arr.at(i)) << std::endl;
		} else {
			std::cout << "(" << i << ", ___):" << std::endl;
		}
	}
}

void HashSet::rehash() {
}

int HashSet::h(const Account &account, int &i) const {
	return (f(account) + i * g(account));
}

// k mod N
int HashSet::f(const Account &account) const {
	int hash_code = (int) account.hash_code();
	return abs((hash_code % this->capacity));
}

// 1 + k mod (N - 2)
int HashSet::g(const Account &account) const {
//	return (int) (account.hash_code() % capacity + i * (1 + account.hash_code() % (capacity - 2)));
	return (int) (1 + account.hash_code() % (capacity - 2));
}