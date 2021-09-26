#include "main.h"

int main() {
	std::cout << "Вариант 13" << std::endl;
	std::cout << "Открытая адресация (Двойное хеширование)" << std::endl;

	HashSet set = HashSet();

	auto a1 = Account("Ivan", "Nagornaya");
	auto a2 = Account("Jack", "ajkbfhkalfb");
	auto a3 = Account("Olga", "tttrAAT");
	auto a4 = Account("Nick", ";ajbv");
	auto a5 = Account("Denis", "khzabfl");
	auto a6 = Account("Tayka", "aya");
	auto a7 = Account("Aboba", "ahrahr");
	auto a8 = Account("Michael", "ejgbvvlsk");
	auto a9 = Account("Frank", "fncbflfakfb");
	auto a10 = Account("Miles", "fncbflfakfb");
	auto a11 = Account("Neil", "fncbflfakfb");
	auto a12 = Account("Gabe", "fncbflfakfb");
	auto a13 = Account("Karen", "fncbflfakfb");

	set.put(a1);
	set.put(a2);
	set.put(a3);
	set.put(a4);
	set.put(a5);
	set.put(a6);
	set.put(a7);
	set.put(a8);
	set.put(a9);
	set.put(a10);
	set.put(a11);
	set.put(a12);
	set.put(a13);

	set.print();
	std::cout << std::endl;

	return 0;
}
