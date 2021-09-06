#include <bitset>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>

//#define TOP
#define GENERATE

#ifdef TOP
const int MAX = 8;
#else
const int MAX = 64;
#endif

const int COUNT = 150'000;

void print(int *arr, int size) {
	for (int i = 0; i < size; ++i) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

// Генерирует файл
void generate_file() {
	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::ofstream out("../week1/practice1/numbers_input.txt");
	if (out.is_open()) {
		// Пока размер файла не равен 1 MB
		for (int i = 1; i < COUNT; i++) {
			out << 1'000'000 + mersenne() % 1'000'000 << " ";
			if (i % 10 == 0) {
				out << "\n";
			}
		}
	}
	out.close();
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
	const int size_of_bit_set = 8;// размер битового массива в байтах
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

int quick_sort_file() {
	auto bitset = std::bitset<9'999'999>();                    // отсчет идет справа
	std::ifstream in("../week1/practice1/numbers_input.txt");  // для чтения файла
	std::ofstream out("../week1/practice1/numbers_output.txt");// для записи в файл
	int number;
	if (in.is_open()) {
		// Читаю файл с числами и заполняю битовый массив
		while (in >> number) {
			if (bitset.test(number)) {
				std::cout << "Присутсвует повторение чисел: " << number << std::endl;
				in.close();
				out.close();
				return 0;
			}
			bitset.set(number, true);
		}
		int count = 0;
		for (int i = 1'000'000; i < 9'999'999; ++i) {
			if (bitset.test(i) == 1) {
				out << i << " ";
				count++;
				if (count % 10 == 0 && count != 0) {
					out << "\n";
				}
			}
		}
		in.close();
		out.close();
		return 1;
	} else {
		std::cout << "Что-то не так с файлами!" << std::endl;
		return 0;
		in.close();
		out.close();
	}
}


int main() {
	// Задание 1.а
	//	one_a();

	// Задание 1.а
	//	one_b();

	// Задание 1.в
	//	one_c();

	// Задание 2.а, 2.б
	//	bit_sort();

	// Задание 2.в
	//	bit_sort_with_chars();

	// Задание 3.а
#ifdef GENERATE
	auto s = std::chrono::high_resolution_clock::now();
	generate_file();
	auto e = std::chrono::high_resolution_clock::now();
	std::cout << "Файл сгенерирован за " << std::chrono::duration_cast<std::chrono::milliseconds>(e - s).count() << " мс" << std::endl;
#endif

	auto start = std::chrono::high_resolution_clock::now();
	int res = quick_sort_file();
	auto end = std::chrono::high_resolution_clock::now();
	if (res) {
		std::cout << "Файл отсортирован за " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " мс" << std::endl;
	} else {
		std::cout << "Файл не отсортирован. Ошибка!" << std::endl;
	}


	return 0;
}