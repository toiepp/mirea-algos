#include "main.h"

int main() {
	std::cout << "Вариант 13" << std::endl;
	std::cout << "Открытая адресация (Двойное хеширование)" << std::endl;

	HashSet set = HashSet();

	auto a1 = Account("Ivan", "Nagornaya");
	auto a2 = Account("fjabfk", "ajkbfhkalfb");
	auto a3 = Account("qegq", "tttrAAT");
	auto a4 = Account("gtwhwh", ";ajbv");
	auto a5 = Account("gqrhteshe", "khzabfl");
	auto a6 = Account("arlsdngsnl", "aya");
	auto a7 = Account("jfagvlarba", "ahrahr");
	auto a8 = Account("cdajrbflva", "ejgbvvlsk");
	auto a9 = Account("fejdnjdn", "fncbflfakfb");
	// Выскакивает ошибка в map out_of_range
	set.put(a1);
	set.print();
	std::cout << std::endl;
	set.put(a2);
	set.print();
	std::cout << std::endl;
	set.put(a3);
	set.print();
	std::cout << std::endl;
	set.put(a4);
	set.print();
	std::cout << std::endl;
	set.put(a5);
	set.print();
	std::cout << std::endl;
	set.put(a6);
	set.print();
	std::cout << std::endl;
	set.put(a7);
	set.print();
	std::cout << std::endl;
	set.put(a8);
	set.print();
	std::cout << std::endl;
	set.put(a9);
	set.print();
	std::cout << std::endl;

	return 0;
}
