#include <iostream>
#include <bitset>

// Задание 1.б
void one_b() {
	std::cout << "Задание 1.б" << std::endl;

	unsigned char x = 255;
	unsigned int mask = 1;
	std::cout << "Before: ";
	std::cout << (int) x << ": \t";
	std::cout << std::bitset<sizeof(int) * 8> (x) << std::endl;

	x = x & (~ (mask << 6));
    
	std::cout << "After: ";
	std::cout << (int) x << ": \t";
	std::cout << std::bitset<sizeof(int) * 8> (x) << std::endl;
}

// Задание 1.в
void one_c() {
	std::cout << "Задание 1.в" << std::endl;
	unsigned int x = 255;
	const int n = sizeof(int) * 8;
	// Создаем маску, битовый массив которой будет размером 32 бита,
	// где на 32-ом бите будет стоять единицы
	unsigned int mask = (1 << n - 1);
	std::cout << "Начальный вид маски: " << std::bitset<n> (mask) << std::endl;
	std::cout << "Результат: ";
	for (int i = 0; i <= n; ++i) {
		std::cout << ((x & mask) >> (n - i));
		mask = mask & 1;
	}
	std::cout << std::endl;
}

void bit_sort(int *arr) {
	int* x = arr;
    
}

int main() {
	// Задание 1.а
	// unsigned char x1 = 255;
	// unsigned char mask1 = 1;
	// Сдвиг битов mask на 4 позиции влево, т.е. умножение его на 2^4 степень.
	// Инверсия получившегося числа
	// Операция И
	// x1 = x1 & (~(mask1 << 4));

	// std::cout << (int) x1 << std::endl; // резульатат верен (239)
	// std::cout << bitset<sizeof(int) * 8> (mask1) << std::endl;

	// Задание 1.а
	one_b();

	// Задание 1.в
	one_c();

	return 0;
}