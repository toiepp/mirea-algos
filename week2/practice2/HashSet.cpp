#include "HashSet.h"

HashSet::HashSet() = default;

HashSet::HashSet(int initial_capacity) : capacity(initial_capacity) {}

HashSet::HashSet(int initial_capacity, double load_factor) : HashSet(initial_capacity) {
	this->load_factor = load_factor;
}

void HashSet::put(Account &account) {
	// Проверить заполнение массива, если надо перераспределить массив
	// WARN По-моему неправильно работает определение заполнения списка
	if (((double) (100 * (size + 1)) / capacity) > this->load_factor) {
		rehash();
	}
	// Получаю позицию, в которую должен вставиться элемент
	int pos = f(account);
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
		pos = g(account); // WARN какая-то хуйня
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
		}
	}
}

void HashSet::rehash() {
}

int HashSet::f(const Account &account) const {
	int hash_code = abs(((int) account.hash_code()));
	return hash_code % this->capacity;
}

int HashSet::g(const Account &account) const {
	/*
	 * k - ключ поиска (хэшкод элемента)
	 * i - счетчик (кол-во элементов с одинаковым хэшкодом)
	 * N - вместимость структуры данных
	 * */
	int init_pos = f(account);                   // изначальная позиция элемента
	int i = shifts.at((int) account.hash_code());// кол-во элементов с таким же хэш кодом
	int k = (int) account.hash_code();           // хэш код элемента
	return (int) (init_pos + i * (1 + k % (capacity - 2)));
}