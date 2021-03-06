#include "HashSet.h"

HashSet::HashSet() = default;

void HashSet::put(Account &account) {
	double check = (double) (load + 1) / (double) capacity;
	if (check >= load_factor) rehash();
	int x = h1(account);
	int y = h2(account);
	// ищу куда вставить элемент
	for (int i = 0; i < capacity; ++i) {
		if (arr.at(x).data == nullptr) {// нашел пустую ячейку
			load++;                     // увеличиваю загруженность
			arr.at(x).data = &account;  // вставляю элементв в набор
			return;                     // завершаю вставку
		} else {                        // произошла коллизия
			arr.at(x).collision = true; // указываю что произошла коллизия
			x = (x + y) % capacity;     // ищу следующую ячейку
		}
	}
}

Account *HashSet::find(const std::string &key) const {
	for (int i = 0; i < capacity; ++i) {      // прохожусь по всем ячейкам тадлицы
		if (arr.at(i).data != nullptr) {      // если ячейка не пустая
			if (arr.at(i).data->name == key) {// если ее ключ равен искомому
				return arr.at(i).data;        // возвращаю содержимое ячейки
			}
		}
	}
	return nullptr;
}

bool HashSet::find(Account &account) const {
	int x = h1(account);
	int y = h2(account);
	for (int i = 0; i < capacity; ++i) {     // прохожусь по хэштаблице
		if (arr.at(x).data != nullptr) {     // если нашел не пустую ячей
			if (*arr.at(x).data == account) {// если равно искомому элементу
				return true;                 // возвращаю значение
			} else {                         // если не равно искомому значению
				if (arr.at(x).collision) {   // если была коллизия
					x = (x + y) % capacity;  // продолжаю поиск
				} else {                     // если не было коллизии
					return false;            // возвразаю значение
				}
			}
		} else {                       // если ячейка была пустой
			if (arr.at(x).collision) { // если была коллизия
				x = (x + y) % capacity;// продолжаю поиск
			} else {                   // если не было коллизии
				return false;          // возвращаю значение
			}
		}
	}
	return false;
}

bool HashSet::remove(Account &account) {
	int x = h1(account);
	int y = h2(account);
	for (int i = 0; i < capacity; ++i) {     // обхожу хэш-таблицу
		if (arr.at(x).data != nullptr) {     // если найдена непустая ячейка
			if (*arr.at(x).data == account) {// если равна искомой
				arr[x].data = nullptr;       // удаляю содержимое
				load--;                      // уменьшаю загруженность таблицы
				return true;                 // возвращаю значение
			} else {                         // если ячейка не равна искомому значению
				if (arr.at(x).collision) {   // если была коллизия
					x = (x + y) % capacity;  // продолжаю поиск
				} else {                     // если коллизии не было
					return false;            // возвращаю значение
				}
			}
		} else {                       // если ячейка пуста
			if (arr.at(x).collision) { // но была коллизия
				x = (x + y) % capacity;// продолжаю поиск
			}
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
					  << ", " << ((arr.at(i).collision) ? 1 : 0)
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
	capacity = find_next_capacity();
	load = 0;
	std::vector<Node> new_arr = std::vector<Node>(capacity);
	for (auto &acc : arr) {       // прохожу по старой таблице
		if (acc.data != nullptr) {// если ячейка старой таблицы непуста
			int x = h1(*acc.data);
			int y = h2(*acc.data);
			for (int i = 0; i < capacity; ++i) {    // ищу куда вставить элемент в новой таблице
				if (new_arr.at(x).data == nullptr) {// если ячейка пуста
					load++;                         // увеличиваю загруженность нового массива
					new_arr[x].data = acc.data;     // вставляю в ячейку значение
					break;
				} else {                           // если ячейка была не пуста
					new_arr.at(x).collision = true;// указываю что была коллизия
					x = (x + y) % capacity;        // продолжаю поиск месте вставки
				}
			}
		}
	}
	arr.clear();
	arr.resize(new_arr.size());
	for (size_t i = 0; i < new_arr.size(); ++i) {
		arr[i] = new_arr.at(i);
	}
}

int HashSet::h1(const Account &account) const {
	return (int) (account.hash_code() % capacity);
}

int HashSet::h2(const Account &account) const {
	return (int) (1 + account.hash_code() % (capacity - 2));
}