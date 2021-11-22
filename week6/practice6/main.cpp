#include <iostream>
#include <vector>

#define task1

struct Symbol {
	char symbol;
	double count = 1;
	double porbability = 0;
	std::vector<bool> codes;

	Symbol(char symbol) : symbol(symbol) {}
};

#ifdef task1
class Tree {
	Tree *left = nullptr;
	Tree *right = nullptr;
	int count = 0;
	std::vector<Symbol*> table;
};
#else

#endif

int main() {

	return 0;
}