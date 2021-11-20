#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

//struct Tree {
//	Tree *left = nullptr;
//	Tree *right = nullptr;
//	std::tuple<std::vector<char>, std::vector<double>> data;
//
//	Tree(std::tuple<std::vector<char>, std::vector<double>> data)
//		: data(data) {}
//};

namespace util {
	double sum(std::vector<double> &prob) {
		return static_cast<double>(std::accumulate(prob.begin(), prob.end(), .0));
	}

	// метод нахождения кодов символов
	void find_codes(std::vector<std::tuple<char, std::string>> &codes,
					std::tuple<std::vector<char>, std::vector<double>> alph_prob,
					size_t start,
					size_t end) {
		// если длина вектора равна одному символу, то ничего делать не надо
		if (std::get<0>(alph_prob).size() == 1) return;
		int size_of_right = 0;// длина правой стороны
		double accumulate = .0;
		double current_sum = sum(std::get<1>(alph_prob));
		// если первый элемент больше половины общей суммы или размер подгруппы равен 2
		if (std::get<1>(alph_prob).at(0) >= (current_sum / 2) || std::get<1>(alph_prob).size() == 2) {
			size_of_right = std::get<1>(alph_prob).size() - 1;
			// для левой половины у всех добавляю единицу
			std::get<1>(codes[0]) = "1" + std::get<1>(codes[0]);
			// для правой части добавляю единицу
			for (size_t i = 1; i < codes.size(); ++i) { // WARN поменять пределы циклов
				std::get<1>(codes[i]) = "0" + std::get<1>(codes[i]);
			}
		} else {
			for (size_t i = std::get<1>(alph_prob).size() - 1; i >= 0; --i) {
				accumulate += std::get<1>(alph_prob).at(i);
				if (accumulate >= current_sum / 2) {
					size_of_right = std::get<0>(alph_prob).size() - i;
					std::get<1>(codes[i]) = "0" + std::get<1>(codes[i]);
					break;
				} else {
					std::get<1>(codes[i]) = "0" + std::get<1>(codes[i]);
				}
			}
			for (int i = 0; i < std::get<1>(alph_prob).size() - size_of_right; ++i) {
				std::get<1>(codes[i]) = "1" + std::get<1>(codes[i]);
			}
		}
		// ERR работает только на первом цикле рекурсии так как основано не на ссылках
		// левые и правые подструктуры
		std::vector<std::tuple<char, std::string>> left(codes.begin(), codes.end() - size_of_right);
		std::vector<std::tuple<char, std::string>> right(codes.end() - size_of_right, codes.end());

		// новый алфавит, для новой подструктуры
		std::tuple<std::vector<char>, std::vector<double>> left_alph_prob;
		std::tuple<std::vector<char>, std::vector<double>> right_alph_prob;

		// подалфавит равен под массивам алфавила
		std::get<0>(left_alph_prob) = std::vector<char>(std::get<0>(alph_prob).begin(), std::get<0>(alph_prob).end() - size_of_right);
		std::get<1>(left_alph_prob) = std::vector<double>(std::get<1>(alph_prob).begin(), std::get<1>(alph_prob).end() - size_of_right);

		std::get<0>(right_alph_prob) = std::vector<char>(std::get<0>(alph_prob).end() - size_of_right, std::get<0>(alph_prob).end());
		std::get<1>(right_alph_prob) = std::vector<double>(std::get<1>(alph_prob).end() - size_of_right, std::get<1>(alph_prob).end());

		find_codes(left, left_alph_prob);
		find_codes(right, right_alph_prob);
	}
}


/*
 * LZ77, LZ78 https://neerc.ifmo.ru/wiki/index.php?title=%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D1%8B_LZ77_%D0%B8_LZ78
 * Код Шеннона https://neerc.ifmo.ru/wiki/index.php?title=%D0%9A%D0%BE%D0%B4_%D0%A8%D0%B5%D0%BD%D0%BD%D0%BE%D0%BD%D0%B0
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

// Алгоритм Лемпеля-Зива-Уэлча
void lz77();

void lz87();

int main() {
	std::cout << "=== Практическая работа №6 ===" << std::endl;
	std::cout << "===       Вариант 19       ===" << std::endl;

	// WARN Работает некорректно с кириллицей, т.к. не UTF-8 помещается в char
	std::string default_str_ru = "Перводан, другодан,\n"
								 "На колоде барабан;\n"
								 "Свинистель, коростель,\n"
								 "Пятерка, шестерка,\n"
								 "утюг.";

	//	std::string default_str_en = "Do not go gentle into that good night,\n"
	//								 "Old age should burn and rave at close of day;\n"
	//								 "Rage, rage against the dying of the light.\n"
	//								 "Though wise men at their end know dark is right,\n"
	//								 "Because their words had forked no lightning they\n"
	//								 "Do not go gentle into that good night.\n"
	//								 "Rage, rage against the dying of the light.";

	std::string default_str_en = "bbbbbbbbbbbbbbddddddddddddddddddddddddddddddddddddddeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeedddddddddddbbbbbbbbbbbbbbbbbbbbbbbbbaaaaaaaaaaaaaaaaaacccccccccccffffffffffffffffffffffffcccccccaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

	LENGTH = default_str_en.size();

	shannon_fano(default_str_en);

	return 0;
}

void shannon_fano(std::string &s, bool flag) {
	std::map<char, double> p;// отображение символа, к его вероятности
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

	// вектор кодов симполов
	std::vector<std::tuple<char, std::string>> codes(alphabet.size());
	for (size_t i = 0; i < alphabet.size(); ++i) {
		std::get<0>(codes.at(i)) = alphabet.at(i);
		std::get<1>(codes.at(i)) = "";
	}
	// передаю вектор функции, которая найдет коды
	util::find_codes(codes, std::make_tuple(alphabet, probability), 0, alphabet.size());

	return;
	// Строю дерево
	//	Tree *root = new Tree(std::make_tuple(alphabet, probability));
	//	build_prefix_tree(root);
}
