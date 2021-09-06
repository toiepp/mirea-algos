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

void bit_sort() {
	std::cout << "Задание 2.а" << std::endl;
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
		if (bitset[MAX - i - 1]) arr[i - null_count] = i;
		else null_count++;
	}
	print(arr, size);
}

int main() {
	// Задание 1.а
	one_a();

	// Задание 1.а
	one_b();

	// Задание 1.в
	one_c();

	bit_sort();

	return 0;
}