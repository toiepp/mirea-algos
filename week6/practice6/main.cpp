#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <numeric>
#include <vector>

namespace util {
	double sum(std::vector<double> &prob,
			   std::vector<double>::iterator &begin,
			   std::vector<double>::iterator &end) {
		return static_cast<double>(std::accumulate(begin, end, .0));
	}

	// метод нахождения кодов символов
	void find_codes(std::vector<std::tuple<char, std::string>> &codes,
					std::tuple<std::vector<char>, std::vector<double>> alph_prob,
					size_t start,
					size_t end) {
		// если длина вектора равна одному символу, то ничего делать не надо
		int break_condition = end - start;
		if (break_condition == 1) return;

		int size_of_right = 0; // длина правой стороны
		double accumulate = .0;// сумма вероятностей правой стороны

		// начало подсчета суммы участка, который надо разделить
		std::vector<double>::iterator start_of_current = std::get<1>(alph_prob).begin() + start;
		// конец подсчета суммы участка, который надо разделить
		std::vector<double>::iterator end_of_current = std::get<1>(alph_prob).begin() + end;
		double current_sum = sum(std::get<1>(alph_prob), start_of_current, end_of_current);

		// если первый элемент больше половины общей суммы или размер подгруппы равен 2
		if (*start_of_current >= (current_sum / 2) || std::distance(start_of_current, end_of_current) == 1) {
			// Расстояние между елементом, после первого элемента участка, до его конца
			size_of_right = std::distance(start_of_current + 1, end_of_current);
			// для левой половины у всех добавляю единицу
			std::get<1>(codes[start]) = "1" + std::get<1>(codes[start]);
			// для правой части добавляю единицу
			for (size_t i = start + 1; i < end; ++i) {
				std::get<1>(codes[i]) = "0" + std::get<1>(codes[i]);
			}
		} else {// если левый участок больше единицы
			// прохожусь по правой часте участка
			for (size_t i = end - 1; i >= start; --i) {
				accumulate += std::get<1>(alph_prob).at(i);
				if (accumulate >= current_sum / 2) {
					size_of_right = end - i; // WARN неправильно расчитывается
					std::get<1>(codes[i]) = "0" + std::get<1>(codes[i]);
					break;
				}
				std::get<1>(codes[i]) = "0" + std::get<1>(codes[i]);
			}
			// WARN что-то не так
			for (int i = start; i < end - size_of_right; ++i) {
				std::get<1>(codes[i]) = "1" + std::get<1>(codes[i]);
			}
		}

		size_t new_left_start = start;
		size_t new_left_end = end - size_of_right;
		find_codes(codes, alph_prob,
				   new_left_start, new_left_end);// передаю на обработку правую часть

		size_t new_right_start = new_left_end;
		size_t new_right_end = new_right_start + size_of_right;
		find_codes(codes, alph_prob,
				   new_right_start, new_right_end);// передаю на обработку левую часть
	}
}// namespace util


/*
 * LZ77, LZ78 https://neerc.ifmo.ru/wiki/index.php?title=%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D1%8B_LZ77_%D0%B8_LZ78
 * */

// flag = false -- decode
// flag = true -- encode
// Алгоритм Шеннона-Фано
void shannon_fano(std::string &s, bool flag = true);

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

		std::string default_str_en = "Do not go gentle into that good night,\n"
									 "Old age should burn and rave at close of day;\n"
									 "Rage, rage against the dying of the light.\n"
									 "Though wise men at their end know dark is right,\n"
									 "Because their words had forked no lightning they\n"
									 "Do not go gentle into that good night.\n"
									 "Rage, rage against the dying of the light.";

	shannon_fano(default_str_en);

	return 0;
}

void shannon_fano(std::string &s, bool flag) {
	if (flag) { // если надо закодировать строку
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

		// Таблица кодов построена
		// Кодирование строки
	}
	else { // если надо расшифровать строку

	}
}
