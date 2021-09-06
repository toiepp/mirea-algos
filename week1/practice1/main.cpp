#include <bitset>
#include <iostream>

//#define TOP

#ifdef TOP
const int MAX = 8;
#else
const int MAX = 64;
#endif

void print(int *arr, int size) {
	for (int i = 0; i < size; ++i) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

void one_a() {
	std::cout << "Задание 1.а" << std::endl;
	unsigned char x1 = 255;
	unsigned char mask1 = 1;
	//     Сдвиг битов mask на 4 позиции влево, т.е. умножение его на 2^4 степень.
	//     Инверсия получившегося числа
	//     Операция И
	x1 = x1 & (~(mask1 << 4));
	std::cout << (int) x1 << std::endl;// резульатат верен (239)
	std::cout << std::bitset<sizeof(int) * 8>(mask1) << std::endl;
}

// Задание 1.б
void one_b() {
	std::cout << "Задание 1.б" << std::endl;

	unsigned char x = 255;
	unsigned int mask = 1;
	std::cout << "Before: ";
	std::cout << (int) x << ": \t";
	std::cout << std::bitset<sizeof(int) * 8>(x) << std::endl;

	x = x & (~(mask << 6));

	std::cout << "After: ";
	std::cout << (int) x << ": \t";
	std::cout << std::bitset<sizeof(int) * 8>(x) << std::endl;
}

// Задание 1.в
void one_c() {
	std::cout << "Задание 1.в" << std::endl;
	unsigned int x = 255;
	const int n = sizeof(int) * 8;
	// Создаем маску, битовый массив которой будет размером 32 бита,
	// где на 32-ом бите будет стоять единицы
	unsigned int mask = (1 << n - 1);
	std::cout << "Начальный вид маски: " << std::bitset<n>(mask) << std::endl;
	std::cout << "Результат: ";
	for (int i = 1; i <= n; ++i) {
		std::cout << ((x & mask) >> (n - i));
		mask = mask & 1;
	}
	std::cout << std::endl;
}

// Данный метод может сортировать массив от
void bit_sort() {
#ifdef TOP
	std::cout << "Задание 2.а" << std::endl;
#else
	std::cout << "Задание 2.б" << std::endl;
#endif
	// Создаю массив
	int size;
	std::cout << "Введите размер массива: ";
	std::cin >> size;
	int *arr = new int[size];
#ifdef TOP
	std::cout << "Введите массив (8, 0-7): ";
#else
	std::cout << "Введите массив (64, 0-63): ";
#endif
	for (int i = 0; i < size; ++i) {
		std::cin >> arr[i];
	}

	// заполняю битовый массив
	auto bitset = std::bitset<MAX>();
	for (int i = 0; i < size; ++i) {
		// ~(~bitset & ~mask)
		// Превращаем соотв. бит массива в 1
		int pos = MAX - arr[i] - 1;
		bitset.set(pos, true);
	}

	int null_count = 0;
	for (int i = 0; i < MAX; ++i) {
		if (bitset[MAX - i - 1])
			arr[i - null_count] = i;
		else
			null_count++;
	}
	print(arr, size);
}

#ifndef TOP
// Данная сортировка работает для массивов размером от 0 до 64
void bit_sort_with_chars() {
	std::cout << "Задание 2.в" << std::endl;
	// Создаю массив чисел
	int size;
	std::cout << "Введите размер массива: ";
	std::cin >> size;
	int *arr = new int[size];
	std::cout << "Введите массив (64, 0-63): ";
	for (int i = 0; i < size; ++i) {
		std::cin >> arr[i];
	}

	// Создаю битовый массив, равный 64 битам,
	// в котором все поля равны 0
	const int size_of_bit_set = 8; // размер битового массива в байтах
	auto *bitset = new unsigned char[8];
	for (int i = 0; i < size_of_bit_set; ++i) {
		bitset[i] = 0;
	}

	// Заполняю битовый массив
	for (int i = 0; i < size; ++i) {
		unsigned char mask = 1;
		// позиция в массиве bitset
		int pos_in_array = arr[i] / size_of_bit_set;
		// позиция в элемента массива bitset
		int pos_in_element = arr[i] % size_of_bit_set;
		bitset[pos_in_array] = ~(~bitset[pos_in_array] & ~(mask << pos_in_element));
	}

	// Печатаю битовый массив
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			std::cout << ((bitset[i] >> j) & 1);
		}
		std::cout << " ";
	}
	std::cout << std::endl;

	// Обхожу битовый массив
	int zero_count = 0;
	// Позиция элемента в отсортированном массиве
	int j = 0;
	for (int i = 0; i < size_of_bit_set * 8; ++i) {
		if (((bitset[i / 8] >> (i % 8)) & 1) == 1) {
			arr[j] = i;
			j++;
		} else {
			zero_count++;
		}
	}

	print(arr, size);
}
#endif

int main() {
	// Задание 1.а
	one_a();

	// Задание 1.а
	one_b();

	// Задание 1.в
	one_c();

//	bit_sort();
	bit_sort_with_chars();

//	unsigned char c = 0b10101010;
//	for (int i = 7; i >= 0; --i) {
//		std::cout << 8 - i - 1 << ": ";
//		std::cout << ((c >> i) & 1) << std::endl;
//	}
//	std::cout << std::endl;

	return 0;
}