#include "main.h"

#include <utility>

unsigned xor_shift_128() {
	struct seed_t {
		unsigned x = 1000;// начальные значения могут быть любыми
		unsigned z = 4561;
		unsigned y = 1235;
		unsigned w = 76843;
	};
	static seed_t s;
	unsigned t = s.x ^ (s.x << 11);
	s.x = s.y;
	s.y = s.z;
	s.z = s.w;
	s.w = (s.w ^ (s.w >> 19)) ^ (t ^ (t >> 8));
	return s.w % 10000000;
}

std::ostream &operator<<(std::ostream &out, const Account &account) {
	out << "Account{ id=" << account.id << ", name=" << account.name << ", address=" << account.address << " }";
	return out;
}

std::istream &operator>>(std::istream &in, Account account) {
	in >> account.id >> account.name >> account.address;
	return in;
}

Account::Account() {}

Account::Account(int id, std::string name, std::string address)
	: id((int) xor_shift_128()), name(std::move(name)), address(std::move(address)) {}

unsigned Account::hash_code() const {
	return id + std::hash<std::string>()(name) + std::hash<std::string>()(address);
}

int main() {
	std::cout << "Вариант 13" << std::endl;
	std::cout << "Открытая адресация (Двойное хеширование)" << std::endl;

	return 0;
}
