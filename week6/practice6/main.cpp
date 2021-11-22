#include <iostream>
#include <vector>
#include <numeric>

struct Symbol {
	char symbol;
	double count = 1;
	double probability = 0;
	std::string code;

	Symbol(char symbol) : symbol(symbol) {}
};

class Tree {
	Tree *left = nullptr;
	Tree *right = nullptr;
	Symbol *symbol = nullptr;
	int count = 0;
	double probability = 0;
	std::vector<Symbol *> table;

	Tree(Tree *left, Tree *right, double count)
		: left(left), right(right) {
		probability = left->probability + right->probability;
	}

	Tree(Symbol *symbol) : symbol(symbol), probability(symbol->probability) {}

	Tree(std::vector<Symbol *> vec) : table(vec), count(counts(vec)) {
		if (vec.size() > 1) {
			std::vector<std::vector<Symbol *>> two = two_vector(vec, this->count);
		}
	}

	std::vector<std::vector<Symbol *>> two_vector(std::vector<Symbol *> vec, int count) {
		int c = 0;
		int before;
		bool f = true;
		std::vector<std::vector<Symbol *>> two;
		std::vector<Symbol *> first;
		std::vector<Symbol *> second;
		for (size_t i = 0; i < vec.size(); ++i) {
			before = c;
			c += vec.at(i)->count;
			if (std::abs(count - before * 2) > std::abs(count - c * 2)) {
				first.push_back(vec.at(i));
			} else {
				second.push_back(vec.at(i));
			}
		}
		two.push_back(first);
		two.push_back(second);
		return two;
	}

	int counts(std::vector<Symbol *> vec) {
		int count = 0;
		std::for_each(vec.begin(), vec.end(), [&count](const Symbol *s){
			count += s->symbol;
		});
		return count;
	}

	void build_huffman_tree(std::string before, Tree* tree) {
		std::string right, left;
		left = before + "0";
		right = before + "1";
		if (tree->symbol) tree->symbol->code = before;
		if (tree->left) build_huffman_tree(left, tree->left);
		if (tree->right) build_huffman_tree(right, tree->right);
	}
};


int main() {

	return 0;
}