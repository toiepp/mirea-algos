#include <bitset>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>

//#define TOP
//#define GENERATE
#define SIMPLE

#ifdef TOP
const int MAX = 8;// размер сортируемого массива
#else
const int MAX = 64;// размер сортируемого массива
#endif

const int COUNT = 10'000;

void print(int *arr, int size) {
	for (int i = 0; i < size; ++i) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

// Генерирует файл со случайными числами
// [0-9]{n}+    - n - кол-во
void generate_file() {
#ifndef SIMPLE
	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::ofstream out("../week1/practice1/numbers_input.txt");
	if (out.is_open()) {
		for (int i = 1; i < COUNT; i++) {
			out << 1'000'000 + mersenne() % 9'000'000 << " ";
			if (i % 10 == 0) {
				out << "\n";
			}
		}
	}
#else
	std::ofstream out("../week1/practice1/numbers_input.txt");
	if (out.is_open()) {
		int n = 0;
		for (int i = 9'999'998; i >= 1'000'000; --i) {
			out << i << " ";
			n++;
			if (n % 10 == 0 && i != 0) {
				out << "\n";
			}
		}
	}
#endif
	out.close();
}

void one_a() {
	std::cout << "Задание 1.а" << std::endl;
	unsigned char x = 255; // 8-разрядное двоичное число 11111111=255
	unsigned char mask = 1;// 1 = 00000001 - 8-ми разрядная маска
	/* Сдвиг битов mask на 4 позиции влево, т.е. умножение его на 2^4 степень.
	 * Таким образом единичный бит маски стоит на 5-ом месте (если считать справа),
	 * а за ним идут 4 нуля, т.е mask = 10000. Далее мы инвертируем маску ==> mask = 01111,
	 * чтобы после операции И (&) в x, там где стояли 1 они не превратились в нули, а на 5 позиции
	 * как раз будет нуль (даже если он и до этого там был). */
	x = x & (~(mask << 4));// должно получиться 239
	// Вывожу результат в консоль
	std::cout << (int) x << std::endl;// результат верен (239)
	// Вывожу то, как выглядит результат в двоичной системе
	std::cout << std::bitset<sizeof(unsigned char) * 8>(x) << std::endl;
}

// Задание 1.б
void one_b() {
	std::cout << "Задание 1.б" << std::endl;
	unsigned char x = 0;  // 8-разрядное двоичное число 00000000=0
	unsigned int mask = 1;// 1 = 00000001 - 8-ми разрядная маска
	std::cout << "Было: ";
	std::cout << (int) x << " ==> \t";                                  // 10-ичное представление числа
	std::cout << std::bitset<sizeof(unsigned char) * 8>(x) << std::endl;// 2-ичное представление числа

	x = x | (mask << 6);// превращаю бит на 7-ой позиции в 1

	std::cout << "Стало: ";
	std::cout << (int) x << " ==> \t";                                  // 10-ичное представление числа
	std::cout << std::bitset<sizeof(unsigned char) * 8>(x) << std::endl;// 2-ичное представление числа
	std::cout << std::endl;

	// Проверяю что оно не превращает 1 в 0
	unsigned char x2 = 255;// 8-разрядное двоичное число 11111111=255
	mask = 1;
	std::cout << "Было: ";
	std::cout << (int) x << " ==> \t";                                  // 10-ичное представление числа
	std::cout << std::bitset<sizeof(unsigned char) * 8>(x) << std::endl;// 2-ичное представление числа

	x2 = x2 | (mask << 6);// превращаю бит на 7-ой позиции в 1

	std::cout << "Стало: ";
	std::cout << (int) x2 << " ==> \t";                                  // 10-ичное представление числа
	std::cout << std::bitset<sizeof(unsigned char) * 8>(x2) << std::endl;// 2-ичное представление числа
}

// Задание 1.в
void one_c() {
	std::cout << "Задание 1.в" << std::endl;
	unsigned int x = 255;// 8-разрядное двоичное число 11111111=255
	// число, равно равное разрядной сетке в 32 бита
	const int n = sizeof(int) * 8;
	// Создаю маску, битовый массив которой будет размером 32 бита,
	// где на позиции 31 будет стоять единица
	unsigned int mask = (1 << (n - 1));
	std::cout << "Начальный вид маски:\t" << std::bitset<n>(mask) << std::endl;
	std::cout << "Результат:\t\t\t\t";
	// Прохожу циклом по каждому биту маски
	for (int i = 1; i <= n; ++i) {
		/* Делаем побитовую операцию И между числом x и маской, после
		 * чего сдвигаем получившийся результат вправо на кол-во позиций,
		 * равное позиции единицы в текущей маске */
		std::cout << ((x & mask) >> (n - i));
		// Сдвигаю единицу в битовом массиве на одну позицию назад
		mask = mask >> 1;
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
	for (int i = 0; i < size; ++i) { std::cin >> arr[i]; }

	// заполняю битовый массив
	// MAX равен 8 или 64
	// Создаю битовый массив соответствующего размера (8/64)
	// и изначально он равен 0
	auto bitset = std::bitset<MAX>(0);
	// В цикле прохожу по битовому массиву и устанавливаю
	// соответствующий бит в единицу
	for (int i = 0; i < size; ++i) {
		// Превращаем соответствующий бит массива в 1
		int pos = MAX - arr[i] - 1;
		bitset.set(pos, true);
	}

	// Сортирую массив на основе битового массива
	// кол-во нулей, которое встретилось,
	// чтобы учитывать сдвиг при обращении по индексу
	int shift = 0;
	for (int i = 0; i < MAX; ++i) {
		// если элемент равен 1, то берем его индекс
		if (bitset[MAX - i - 1]) arr[i - shift] = i;
		// если равен 0, то увеличиваем смещение
		else
			shift++;
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
	for (int i = 0; i < size; ++i) { std::cin >> arr[i]; }

	// Создаю битовый массив, равный 64 битам, в котором все поля равны 0
	const int size_of_bit_set_in_bytes = 8;// размер битового массива в байтах
	auto *bitset = new unsigned char[8];   // сам битовый массив на 64 бита
	// устанавливаю все значения битового массива в 0
	for (int i = 0; i < size_of_bit_set_in_bytes; ++i) { bitset[i] = 0; }

	// Заполняю битовый массив
	for (int i = 0; i < size; ++i) {
		// позиция в массиве bitset
		// обозначает в каком "байте" битового массива будет располагаться
		int pos_in_array = arr[i] / size_of_bit_set_in_bytes;
		// позиция в "байте" битового массива
		int pos_in_element = arr[i] % size_of_bit_set_in_bytes;
		// устанавливаю соответствующий бит битового массива в единицу
		bitset[pos_in_array] |= (1 << pos_in_element);
	}

	// Обхожу битовый массив.
	// Учитываю кол-во нулей в битовом массиве, чтобы
	// правильно находить нужный элемент
	int shift = 0;
	int j = 0;// Позиция элемента в отсортированном массиве
	for (int i = 0; i < size_of_bit_set_in_bytes * 8; ++i) {
		// Если соответствующий бит битового массива равен 1, то
		// устанавливаю индекс этого элемента в битовом массиве в
		// сортируемый массив
		int pos_in_array = i / 8;
		int pos_in_element = i % 8;
		if (((bitset[pos_in_array] >> pos_in_element) & 1) == 1) { arr[j++] = i; }
		// Если равен 0 увеличиваю смещение
		else {
			shift++;
		}
	}
	// Печатаю массив
	print(arr, size);
}
#endif

int quick_sort_file() {
	auto bitset = std::bitset<9'999'999>();                    // отсчет идет справа
	std::ifstream in("../week1/practice1/numbers_input.txt");  // для чтения файла
	std::ofstream out("../week1/practice1/numbers_output.txt");// для записи в файл
	if (in.is_open()) {
		int number;
		// Считываю из файла числа
		while (in >> number) {
			// Проверяю вдруг в файле есть дублирование чисел
			if (bitset.test(number)) {
				std::cout << "Присутствует повторение чисел: " << number << std::endl;
				// тогда закрываю потоки для работы с файлами
				in.close();
				out.close();
				// и указываю что сортровка не может быть произведена
				return 0;
			}
			// если все было нормально, то устанавливаю соответствующий
			// бит битового массива в единицу
			bitset.set(number, true);
		}

		// считаю сколько чисел было записано в выходной файл,
		// чтобы было удобно читать данный файл
		int count = 0;
		// Прохожусь по битовому массиву
		for (int i = 1'000'000; i < 9'999'999; ++i) {
			// если бит равен 1, то
			if (bitset.test(i) == 1) {
				// записываю соответствующее числа в файл
				out << i << " ";
				count++;
				// если выводится 10-й элемент по счету, то после него
				// идет перенос строки
				if (count % 10 == 0 && count != 0) {
					out << "\n";
				}
			} // иначе ничего не делаю
		}
		// Замеряю сколько использованной ОЗУ
		std::cout << "Кол-во использованной ОЗУ: ~" << sizeof(bitset) / 1024 << " КБ" << std::endl;
		in.close();
		out.close();
		return 1; // означает, что сортировка прошла успешно
	} else { // случай, если файл не открыт.
		std::cout << "Что-то не так с файлами!" << std::endl;
		in.close();
		out.close();
		return 0;
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
	//		bit_sort();

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
		std::cout << "Файл отсортирован за "
				  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
				  << " мс" << std::endl;
	} else {
		std::cout << "Файл не отсортирован. Ошибка!" << std::endl;
	}

	return 0;
}