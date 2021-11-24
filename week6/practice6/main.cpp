#include <cmath>
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

	std::vector<std::vector<Symbol *>> two_vector(std::vector<Symbol *> vec, int counted) {
		int c = 0;
		int before;
		bool f = true;
		std::vector<std::vector<Symbol *>> two;
		std::vector<Symbol *> first;
		std::vector<Symbol *> second;
		for (size_t i = 0; i < vec.size(); ++i) {
			before = c;
			c += vec.at(i)->count;
			if (std::abs(counted - before * 2) > std::abs(counted - c * 2)) {
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
		int counted = 0;
		std::for_each(vec.begin(), vec.end(), [&counted](const Symbol *s) {
			counted += s->symbol;
		});
		return count;
	}

	void huffman(Tree *tree, std::string before = "") {
		std::string r, l;
		l = before + "0";
		r = before + "1";
		if (tree->symbol) tree->symbol->code = before;
		if (tree->left) huffman(tree->left, l);
		if (tree->right) huffman(tree->right, r);
	}
};

class Huffman {
public:
	Tree *root;
	std::string code;
	std::vector<Symbol *> table;

	Huffman(std::string s) : code(s) {
		add_table(code);
		build_tree();
		root->huffman(root);
		for (auto t : table) {
			std::cout << t->symbol << " " << t->count << " " << t->probability << " " << t->code << std::endl;
		}
		encode();
	}

	void add_table(std::string str) {
		bool first;
		double count = str.length();
		for (size_t i = 0; i < count; ++i) {
			first = true;
			char symbol = str.at(i);
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
				if (table.at(i)->probability > table.at(j)->probability) {
					std::swap(table.at(i), table.at(j));
				}
			}
		}
	}

	std::vector<Tree *> sort_tree(std::vector<Tree *> tree) {
		std::vector<Tree *> sorted = tree;
		for (size_t i = 0; i < sorted.size(); ++i) {
			for (size_t j = i + 1; j < sorted.size(); ++j) {
				if (sorted.at(i)->probability > tree.at(j)->probability) {
					std::swap(sorted.at(i), sorted.at(j));
				}
			}
		}
		return sorted;
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

	void encode() {
		std::string c;
		for (size_t i = 0; i < code.length(); ++i) {
			c += find_code(code.at(i), root);
		}
	}

	void decode() {
		std::string c;
		char x;
		Tree *node = root;
		for (size_t i = 0; i < code.length(); ++i) {
			x = code.at(i);
			if (x == '0') node = node->left;
			else
				node = node->right;
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

	void compression() {
		double before_size = code.length() * 8;
		encode();
		double after_size = code.length();
		decode();
		std::cout << "Коэффциент сжатия " << after_size * 100 / before_size << "%" << std::endl;
	}

	void despertion() {
		double a = average();
		std::cout << "Дисперсия: "
				  << std::pow(a, 2) / (double(table.size())) - std::pow((a / (double) table.size()), 2) << std::endl;
	}

	int average() {
		double c = 0;
		for (size_t i = 0; i < table.size(); ++i) {
			c += table.at(i)->code.length();
		}
		return c / ((double) table.size());
	}
};

int main() {
	std::string str = "aaabbc";
	Huffman huffman(str);
	std::cout << huffman.code << std::endl;
	huffman.encode();
	std::cout << huffman.code << std::endl;
	huffman.compression();
	std::cout << huffman.average() << std::endl;
	huffman.despertion();
	return 0;
}