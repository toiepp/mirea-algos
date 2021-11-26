#include "Account.h"

unsigned Account::generate_id() {
	double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (9'999'999 - 1'000'000 + 1) + 1'000'000);
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

bool operator==(const Account &a1, const Account &a2) {
	return a1.id == a2.id &&
		   a1.name == a2.name &&
		   a1.address == a2.address;
}