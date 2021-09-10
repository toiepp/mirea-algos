#include "main.h"

int Account::hash_code() {
	return 42;
}

std::ostream& operator << (std::ostream &out, const Account& account) {
	out << "Account{ id=" << account.id << ", name=" << account.name << ", address=" << account.address << " }";
	return out;
}

std::istream& operator >> (std::istream &in, Account account) {
	in >> account.id >> account.name >> account.address;
	return in;
}

int main() {
	std::cout << "Вариант 13" << std::endl;
	return 0;
}