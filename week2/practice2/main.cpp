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
	auto a6 = Account("Tamika", "aya");
	auto a7 = Account("Victor", "ahrahr");
	auto a8 = Account("Michael", "ejgbvvlsk");
	auto a9 = Account("Frank", "rrretrshjtsj");
	auto a10 = Account("Miles", "fncbflfakfb");
	auto a11 = Account("Neil", "gjsj");
	auto a12 = Account("Gabe", "fncbflfsjjhsyjsakfb");
	auto a13 = Account("Karen", "srjsrjhsrjs");

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

	std::cout << set.find("Ivan") << ": " << *set.find("Ivan") << std::endl;
	std::cout << set.find("Jack") << ": " << *set.find("Jack") << std::endl;
	std::cout << set.find("Miles") << ": " << *set.find("Miles") << std::endl;

	std::string find_me;
	std::cout << "Введите имя для поиска: ";
	std::cin >> find_me;
	if (!set.find(find_me)) {
		std::cout << find_me << " doesn't exist" << std::endl;
	} else {
		std::cout << find_me << " exists" << std::endl;
	}
	std::cout << std::endl;

	std::cout << a1 << ": " << set.find(a1) << std::endl;
	std::cout << a2 << ": " << set.find(a2) << std::endl;
	std::cout << a3 << ": " << set.find(a3) << std::endl;
	std::cout << a4 << ": " << set.find(a4) << std::endl;
	std::cout << a5 << ": " << set.find(a5) << std::endl;
	std::cout << a6 << ": " << set.find(a6) << std::endl;
	std::cout << a7 << ": " << set.find(a7) << std::endl;
	std::cout << a8 << ": " << set.find(a8) << std::endl;
	std::cout << a9 << ": " << set.find(a9) << std::endl;
	std::cout << a10 << ": " << set.find(a10) << std::endl;
	std::cout << a11 << ": " << set.find(a11) << std::endl;
	std::cout << a12 << ": " << set.find(a12) << std::endl;
	std::cout << a13 << ": " << set.find(a13) << std::endl;

	auto no = Account(find_me, "London");
	std::cout << no << ": " << set.find(no) << std::endl;
	return 0;
}
