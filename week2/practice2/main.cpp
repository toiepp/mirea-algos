#include "main.h"

int main() {
	std::cout << "Вариант 13" << std::endl;
	std::cout << "Открытая адресация (Двойное хеширование)" << std::endl;

	HashSet set = HashSet();

	auto a1 = Account("John", "faggfdsahj");
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
	auto a14 = Account("Ron", "asssssgahaed");
	auto a15 = Account("Lily", "ttjhsgsgjsgjgjDD");
	auto a16 = Account("Rick", "adgagdadgadgad");
	auto a17 = Account("Matt", "ddlkhjghbdhjklgfhbdahjlk");
	auto a18 = Account("Vanessa", "dgsag");
	auto a19 = Account("Barry", "vrvrvrjrtds");
	auto a20 = Account("Paul", "dfadafdasfdf");
	auto a21 = Account("Brick", "kjhddfjkhdsaklj");
	auto a22 = Account("Von", "dwghfjahsgbd");
	auto a23 = Account("Michael", "adhgfhafha");
	auto a24 = Account("Lisa", "fsfs");
	auto a25 = Account("Mark", "dlngflaksfj");

	// TODO Тестирую вставку и перераспределение после переполнения массива
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
	// Перехэширование
	set.put(a11);
	set.put(a12);
	set.put(a13);
	set.put(a14);
	set.put(a15);
	set.put(a16);
	set.put(a17);
	set.put(a18);
	set.put(a19);
	set.put(a20);
	set.put(a21);
	set.put(a22);
	set.put(a23);
	// перехэширование
	set.put(a24);
	set.put(a25);

	set.print();
	std::cout << std::endl
			  << std::endl;

	std::cout << "Проверка нахождения элементов в множестве" << std::endl;
	std::cout << set.find("John") << ": " << *set.find("John") << std::endl;
	std::cout << set.find("Jack") << ": " << *set.find("Jack") << std::endl;
	std::cout << set.find("Miles") << ": " << *set.find("Miles") << std::endl;

	std::string find_me;
	std::cout << "Введите имя для поиска: ";
	std::cin >> find_me;
	if (!set.find(find_me)) {
		std::cout << find_me << " doesn't exist" << std::endl;
	} else {
		std::cout << find_me << " exists" << *set.find(find_me) << std::endl;
	}
	std::cout << std::endl;

	std::cout << set.find(a1) << ": " << a1 << std::endl;
	std::cout << set.find(a2) << ": " << a2 << std::endl;
	std::cout << set.find(a3) << ": " << a3 << std::endl;
	std::cout << set.find(a4) << ": " << a4 << std::endl;
	std::cout << set.find(a5) << ": " << a5 << std::endl;
	std::cout << set.find(a6) << ": " << a6 << std::endl;
	std::cout << set.find(a7) << ": " << a7 << std::endl;
	std::cout << set.find(a8) << ": " << a8 << std::endl;
	std::cout << set.find(a9) << ": " << a9 << std::endl;
	std::cout << set.find(a10) << ": " << a10 << std::endl;
	std::cout << set.find(a11) << ": " << a11 << std::endl;
	std::cout << set.find(a12) << ": " << a12 << std::endl;
	std::cout << set.find(a13) << ": " << a13 << std::endl;

	auto no = Account(find_me, "London");
	std::cout << set.find(no) << ": " << no << std::endl;
	std::cout << std::endl;

	std::cout << set.remove(a1) << std::endl;
	std::cout << set.remove(a12) << std::endl;
	std::cout << set.remove(a8) << std::endl;
	std::cout << set.remove(a13) << std::endl;
	std::cout << set.remove(a1) << std::endl;
	std::cout << set.remove(a8) << std::endl;
	std::cout << set.remove(a12) << std::endl;
	std::cout << set.remove(a13) << std::endl;
	std::cout << std::endl << std::endl;

	std::cout << "Множество после удаления" << std::endl;
	set.print();
	std::cout << std::endl;
	return 0;
}
