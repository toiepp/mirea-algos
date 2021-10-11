#include "HashSet.h"

HashSet::HashSet() = default;

void HashSet::put(Account &account) {
	double check = (double) (load + 1) / (double) capacity;
	if (check >= load_factor) rehash();
	int x = h1(account);
	int y = h2(account);
	for (int i = 0; i < capacity; ++i) {
		if (arr.at(x).data == nullptr) {
			load++;
			arr[x].data = &account;
			return;
		}
		x = (x + y) % capacity;
	}
}

Account *HashSet::find(const std::string &key) const {
	for (int i = 0; i < capacity; ++i) {
		if (arr.at(i).data != nullptr) {
			if (arr.at(i).data->name == key) { return arr.at(i).data; }
		}
	}
	return nullptr;
}

bool HashSet::find(Account &account) const {
	int x = h1(account);
	int y = h2(account);
	for (int i = 0; i < capacity; ++i) {
		if (arr.at(x).data != nullptr) {
			if (*arr.at(x).data == account) {
				return true;
			}
		} else {
			return false;
		}
		x = (x + y) % capacity;
	}
	return false;
}

bool HashSet::remove(Account &account) {
	int x = h1(account);
	int y = h2(account);
	for (int i = 0; i < capacity; ++i) {
		if (arr.at(x).data != nullptr) {
			if (*arr.at(x).data == account) {
				arr[x].data = nullptr;
				load--;
				return true;
			} else {
				x = (x + y) % capacity;
			}
		} else {
			x = (x + y) % capacity;
		}
	}
	return false;
}

void HashSet::print() const {
	for (int i = 0; i < capacity; ++i) {
		if (arr.at(i).data != nullptr) {
			std::cout << "("
					  << i << ", "
					  << (*arr.at(i).data).hash_code()
					  << "):\t" << (*arr.at(i).data) << std::endl;
		} else {
			std::cout << "(" << i << ", ___):" << std::endl;
		}
	}
}

int HashSet::find_next_capacity() {
	init += 4;
	int n = init;
	int size = n;
	std::vector<int> primes = std::vector<int>(n);
	std::vector<int> nums = std::vector<int>(size);

	for (int i = 0; i < size; i++) nums[i] = i;

	primes[0] = 2;
	int i = 0;

	while (i < n) {
		int p = primes[i++];// запоминаем текущее простое число

		for (int j = p * 2; j < size; j += p) {
			nums[j] = 0;// обнуляем все кратные ему числа в массиве
		}

		while (nums[p + 1] == 0) p++;

		if (p + 1 >= size) {
			std::vector<int> tmp = std::vector<int>(size * 2);

			for (int k = 0; k < size; k++)
				tmp[k] = nums[k];

			size *= 2;
			nums = tmp;

			for (int j = size / 2; j < size; j++) nums[j] = j;
			i = 0;
		} else {
			primes[i] = p + 1;
		}
	}

	return primes.at(n - 1);
}

void HashSet::rehash() {
	/* Создать новый массив, который будет простого размера и почти в 2 раза больше
	 * Умеличить capacity
	 * Сохранить элементы из старого массива и перенести их в новый*/
	capacity = find_next_capacity();
	load = 0;
	std::vector<Node> new_arr = std::vector<Node>(capacity);
	// Прохожусь по старому массиву и переношу их в новый
	for (auto &acc : arr) {
		if (acc.data != nullptr) {
			int x = h1(*acc.data);
			int y = h2(*acc.data);
			for (int i = 0; i < capacity; ++i) {
				if (new_arr.at(x).data == nullptr) {
					load++;
					new_arr[x].data = acc.data;
					break;
				}
				x = (x + y) % capacity;
			}
		}
	}
	arr.clear();
	for (const auto& el : new_arr) {
		arr.push_back(el);
	}
}

int HashSet::h1(const Account &account) const {
	return (int) (account.hash_code() % capacity);
}

int HashSet::h2(const Account &account) const {
	return (int) (1 + account.hash_code() % (capacity - 2));
}