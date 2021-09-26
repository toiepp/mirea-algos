#include "Account.h"

unsigned Account::generate_id() {
	std::random_device rd;
	std::mt19937 gen(rd());
	return gen() % 10'000'000;
}

Account::Account(std::string name, std::string address)
	: id(generate_id()), name(std::move(name)), address(std::move(address)) {}

unsigned Account::hash_code() const {
	return this->id;
}

std::ostream &operator<<(std::ostream &out, const Account &account) {
	out << "{ id=" << account.id << ", name=" << account.name << ", address=" << account.address << " }";
	return out;
}

std::istream &operator>>(std::istream &in, Account account) {
	in >> account.id >> account.name >> account.address;
	return in;
}