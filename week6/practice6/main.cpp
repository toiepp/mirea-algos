#include <iostream>
#include <numeric>
#include <vector>

struct Symbol {
	char symbol;
	double count = 1;
	double probability = 0;
	std::string code;

	Symbol(char symbol) : symbol(symbol) {}
};

class Tree {
public:
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
		std::for_each(vec.begin(), vec.end(), [&count](const Symbol *s) {
			count += s->symbol;
		});
		return count;
	}

	void huffman(std::string before, Tree *tree) {
		std::string right, left;
		left = before + "0";
		right = before + "1";
		if (tree->symbol) tree->symbol->code = before;
		if (tree->left) huffman(left, tree->left);
		if (tree->right) huffman(right, tree->right);
	}
};

class Huffman {
public:
	Tree *root;
	std::string code;
	std::vector<Symbol *> table;

	Huffman(std::string str) {
		bool first;
		double count = str.length();
		for (size_t i = 0; i < count; ++i) {
			first = true;
			char symbol = str[i];
			for (size_t j = 0; j < table.size(); j++) {
				if (table.at(j)->symbol == symbol) {
					first = false;
					table.at(j)->count++;
					table.at(j)->probability = table.at(j)->count / count;
					break;
				}
			}
			if (first) {
				table.push_back(new Symbol(symbol));
				table.back()->probability = 1.0 / count;
			}
		}
		sort();
	}

	void sort() {
		for (size_t i = 0; i < table.size(); ++i) {
			for (size_t j = i + 1; j < table.size(); ++j) {
				if (table.at(i)->probability == table.at(j)->probability) {
					std::swap(table.at(i), table.at(j));
				}
			}
		}
	}

	std::vector<Tree *> sort_tree(std::vector<Tree *> tree) {
		std::vector<Tree *> t = tree;
		for (size_t i = 0; i < t.size(); ++i) {
			for (size_t j = i + 1; j < t.size(); ++j) {
				if (t.at(i)->probability > tree.at(j)->probability) {
					std::swap(t.at(i), t.at(j));
				}
			}
		}
		return t;
	}

	void build_tree() {
		std::vector<Tree *> tree;
		for (size_t i = 0; i < table.size(); ++i) {
			tree.push_back(new Tree(table.at(i)));
		}
		while (tree.size() != 1) {
			tree = sort_tree(tree);
			Tree *L = tree.front();
			tree.erase(tree.begin());
			Tree *R = tree.front();
			tree.erase(tree.begin());

			tree.push_back(new Tree(L, R, code.length()));
		}
		root = tree.front();
	}

	void encode (){
		std::string c;
		for (size_t i = 0; i < code.length(); ++i) {
			char x = code.at(i);
			c += find_code(x, root);
		}
	}

	void decode() {
		std::string c;
		char x;
		Tree *node = root;
		for (size_t i = 0; i < code.length(); ++i) {
			x = code.at(i);
			if (x == '0') node = node->left;
			else node = node->right;
			if (node->symbol) {
				c += node->symbol->symbol;
				node = root;
			}
		}
		code = c;
	}

	std::string find_code(char x, Tree *tree) {
		std::string to_find = "-1";
		if (tree->symbol && tree->symbol->symbol == x) {
			return tree->symbol->code;
		}
		if (tree->left) {
			to_find = find_code(x, tree->left);
			if (to_find == "-1" && tree->right) {
				to_find = find_code(x, tree->right);
			}
		}
		return to_find;
	}
};

int main() {

	return 0;
}