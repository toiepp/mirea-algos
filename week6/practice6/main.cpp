#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

size_t LENGTH = 0;

typedef std::map<char, double> SP;

struct Tree {
	Tree *left = nullptr;
	Tree *right = nullptr;
	std::tuple<std::vector<char>, std::vector<double>> data;

	Tree(std::tuple<std::vector<char>, std::vector<double>> data)
		: data(data) {}
};

namespace util {
	void print_tuple(std::tuple<std::vector<char>, std::vector<double>> &t) {
		std::cout << "[ ";
		for (size_t i = 0; i < std::get<0>(t).size() - 1; ++i) {
			std::cout << "{" << std::get<0>(t).at(i) << " : " << std::get<1>(t).at(i) << "}, ";
		}
		std::cout << "{"
				  << std::get<0>(t).at(std::get<0>(t).size() - 1)
				  << " : "
				  << std::get<1>(t).at(std::get<0>(t).size() - 1)
				  << "}";
		std::cout << " ]" << std::endl;
	}
}// namespace util

/* Задания
 * 1.
Перводан, другодан,
На колоде барабан;
Свистель, коростель,
Пятерка, шестерка,
утюг.
 * 2.
0001000010101001101
 * 3.
comconcomconacom
 *
 * */

/*
 * LZ77, LZ78 https://neerc.ifmo.ru/wiki/index.php?title=%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D1%8B_LZ77_%D0%B8_LZ78
 * Код Шеннона https://neerc.ifmo.ru/wiki/index.php?title=%D0%9A%D0%BE%D0%B4_%D0%A8%D0%B5%D0%BD%D0%BD%D0%BE%D0%BD%D0%B0
 *
 * */

// flag = false -- decode
// flag = true -- encode
// Алгоритм Шеннона-Фано
/*
 * Кодовый алфавит: B = {0, 1}
 * 1. Определить вероятности встречи символов в тексте;
 * 2. Упорядочить символы исходного алфавита по невозрастанию вероятности встрети;
 * 3. Разделить последовательность на две группы, чтобы суммы вероятностей в обеих были равны;
 * 	  WARN ??? Если равенство не выполняется: влево - туда, где сумма меньше, вправо - туда, где больше
 * 4. Формуруем дерево: группе слева - 0, справа - 1;
 * 5. Продолжаем с шага 3, пока в каждой группе не будет по 1 символу
 * */
void shannon_fano(std::string &s, bool flag = false);

void build_prefix_tree(Tree *root);

double sum(std::vector<double> &prob);

// Алгоритм Лемпеля-Зива-Уэлча
void lz77();

void lz87();

int main() {
	setlocale(LC_ALL, "ru_RU.UTF-8");

	std::cout << "=== Практическая работа №6 ===" << std::endl;
	std::cout << "===       Вариант 19       ===" << std::endl;

	// WARN Работает некорректно с кириллицей, т.к. не UTF-8 помещается в char
	std::string default_str_ru = "Перводан, другодан,\n"
								 "На колоде барабан;\n"
								 "Свинистель, коростель,\n"
								 "Пятерка, шестерка,\n"
								 "утюг.";

	std::string default_str_en = "Do not go gentle into that good night,\n"
								 "Old age should burn and rave at close of day;\n"
								 "Rage, rage against the dying of the light.\n"
								 "Though wise men at their end know dark is right,\n"
								 "Because their words had forked no lightning they\n"
								 "Do not go gentle into that good night.\n"
								 "Rage, rage against the dying of the light.";
//
//	std::string default_str_en = "aaaaaaaaaabbbbaaabbbaaab";

	LENGTH = default_str_en.size();

	shannon_fano(default_str_en);

	return 0;
}

void shannon_fano(std::string &s, bool flag) {
	SP p;// отображение символа, к его вероятности
	for (size_t i = 0; i < s.size(); ++i) {
		p[s[i]] += (1 / (double) s.size());
	}

	std::vector<char> alphabet;
	std::vector<double> probability;

	for (auto &e : p) {
		alphabet.push_back(e.first);
		probability.push_back(e.second);
	}

	// сортирую массивы по невозрастанию вероятности
	for (size_t i = 1; i < alphabet.size(); ++i) {
		for (size_t j = 0; j < alphabet.size() - i; ++j) {
			if (probability.at(j) < probability.at(j + 1)) {
				double tmp = probability.at(j);
				probability[j] = probability.at(j + 1);
				probability[j + 1] = tmp;
				char tmpc = alphabet.at(j);
				alphabet[j] = alphabet.at(j + 1);
				alphabet[j + 1] = tmpc;
			}
		}
	}

	// Строю дерево
	Tree *root = new Tree(std::make_tuple(alphabet, probability));
	build_prefix_tree(root);

	return;
}

// ERR (неправильно работает построение префиксного дерева)
void build_prefix_tree(Tree *root) {
	// если размер оставшихся буква равен 1, то это дерево построено
	if (std::get<0>(root->data).size() == 1) return;
	// считаю размер левой части
	int size_of_left_side = 0;
	double accumulate = 0;
	double current_sum = sum(std::get<1>(root->data));
	if (std::get<1>(root->data).at(0) >= 0.5 || std::get<1>(root->data).size() == 2) {
		size_of_left_side = 1;
	} else {
		for (int i = 0; i < std::get<0>(root->data).size(); ++i) {
			accumulate += std::get<1>(root->data).at(i);
			if (accumulate >= current_sum / 2) {
				size_of_left_side = i;
				break;
			}
		}
	}
	printf("%d", size_of_left_side);

	root->left = new Tree(
			std::make_tuple(
					std::vector<char>(
							std::get<0>(root->data).begin(),
							std::get<0>(root->data).begin() + size_of_left_side),
					std::vector<double>(
							std::get<1>(root->data).begin(),
							std::get<1>(root->data).begin() + size_of_left_side)));

	root->right = new Tree(
			std::make_tuple(
					std::vector<char>(
							std::get<0>(root->data).begin() + size_of_left_side,
							std::get<0>(root->data).end()),
					std::vector<double>(
							std::get<1>(root->data).begin() + size_of_left_side,
							std::get<1>(root->data).end())));

	std::cout << std::endl << "=== === === ===" << std::endl;
	util::print_tuple(root->left->data);
	util::print_tuple(root->right->data);
	std::cout << std::endl << "=== === === ===" << std::endl;

	build_prefix_tree(root->left);
	build_prefix_tree(root->right);
}

double sum(std::vector<double> &prob) {
	return (double) std::accumulate(prob.begin(), prob.end(), 0.0);
}
