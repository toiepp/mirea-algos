#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

std::vector<std::pair<char, std::string>> CODES;
std::pair<std::vector<char>, std::vector<double>> AP;

namespace util {
	void print_codes() {
		std::for_each(CODES.begin(), CODES.end(), [](const auto &t) {
			std::cout << ((t.first == '\n') ? '@' : t.first) << " = " << std::setw(10) << std::right << t.second << std::endl;
		});
	}

	void print_AP() {
		for (int i = 0; i < AP.first.size(); ++i) {
			std::cout << AP.first.at(i) << " ~ " << AP.second.at(i) << std::endl;
		}
	}

	std::string get_code(const char &symbol) {
		return std::find_if(CODES.begin(), CODES.end(),
							[&symbol](const std::pair<char, std::string> &pair) {
								return symbol == pair.first;
							})
				->second;
	}

	std::vector<std::pair<char, std::string>>::iterator get_symbol(const std::string &code) {
		return std::find_if(CODES.begin(), CODES.end(),
							[&code](const std::pair<char, std::string> &pair) {
								return code == pair.second;
							});
	}

	double sum(const std::vector<double>::iterator begin,
			   const std::vector<double>::iterator end) {
		return static_cast<double>(std::accumulate(begin, end, .0));
	}

	// метод нахождения кодов символов
	void find_codes(std::vector<std::pair<char, std::string>> &codes,
					std::pair<std::vector<char>, std::vector<double>> alph_prob,
					size_t start,
					size_t end) {
		// если длина вектора равна одному символу, то ничего делать не надо
		int break_condition = end - start;
		if (break_condition == 1) return;

		int size_of_right = 0;// длина правой стороны

		// начало подсчета суммы участка, который надо разделить
		std::vector<double>::iterator start_of_current = alph_prob.second.begin() + start;
		// конец подсчета суммы участка, который надо разделить
		std::vector<double>::iterator end_of_current = alph_prob.second.begin() + end;
		double current_sum = sum(start_of_current, end_of_current);

		// если первый элемент больше половины общей суммы или размер подгруппы равен 2
		if (*start_of_current >= (current_sum / 2) || std::distance(start_of_current, end_of_current) == 1) {
			// Расстояние между елементом, после первого элемента участка, до его конца
			size_of_right = static_cast<int>(std::distance(start_of_current + 1, end_of_current));
			// для левой половины у всех добавляю единицу
			codes[start].second = codes[start].second.append("0");
			// для правой части добавляю единицу
			for (size_t i = start + 1; i < end; ++i) {
				codes[i].second = codes[i].second.append("1");
			}
		} else {// если левый участок больше единицы
			// прохожусь по правой часте участка
			double accumulate = .0;// сумма вероятностей правой стороны
			for (size_t i = end - 1; i >= start; --i) {
				accumulate += alph_prob.second.at(i);// текущая сумма правой части
				if (accumulate >= current_sum / 2) {
					// если разница между частями после прибавления последнего элемента больше чем до
					size_of_right = end - i - 1;
					// сумма правой части до прибавления
					double before = std::accumulate(end_of_current - size_of_right, end_of_current, 0.0);
					// сумма правой части после прибавления
					double after = accumulate;
					if (std::abs(current_sum / 2 - before) >= std::abs(current_sum / 2 - after)) {
						codes.at(i).second = codes.at(i).second.append("1");
						size_of_right++;
					}
					break;
				}
				codes[i].second = codes[i].second.append("1");
			}
			for (size_t i = start; i < end - size_of_right; ++i) {
				codes[i].second = codes[i].second.append("0");
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
	std::cout << std::endl;

	std::string default_str_ru = "Перводан, другодан,\n"
								 "На колоде барабан;\n"
								 "Свинистель, коростель,\n"
								 "Пятерка, шестерка,\n"
								 "утюг.";

	std::string default_str_en_long = "Do not go gentle into that good night,\n"
									  "Old age should burn and rave at close of day;\n"
									  "Rage, rage against the dying of the light.\n"
									  "Though wise men at their end know dark is right,\n"
									  "Because their words had forked no lightning they\n"
									  "Do not go gentle into that good night.";

	std::string default_str_en_short = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
									   "bbbbbbbbbbbbbbbbbb"
									   "cccccccccccccccccc"
									   "dddddddddddd"
									   "eeeeeeeee"
									   "fffffff";

	default_str_en_short = "aaabbc";

	std::cout << "Изначально: " << default_str_en_long << std::endl;
	shannon_fano(default_str_en_long);
	util::print_codes();
	util::print_AP();
	std::cout << "Закодировано:\t" << default_str_en_long << std::endl;
	shannon_fano(default_str_en_long, false);
	std::cout << "Раскодировано:\t" << default_str_en_long << std::endl
			  << std::endl;
	CODES.clear();

	std::cout << "Изначально: " << default_str_en_short << std::endl;
	shannon_fano(default_str_en_short);
	util::print_codes();
	util::print_AP();
	std::cout << "Закодировано:\t" << default_str_en_short << std::endl;
	shannon_fano(default_str_en_short, false);
	std::cout << "Раскодировано:\t" << default_str_en_short << std::endl
			  << std::endl;
	CODES.clear();

	return 0;
}

void shannon_fano(std::string &string, bool flag) {
	if (flag) {                  // если надо закодировать строку
		std::map<char, double> p;// отображение символа, к его вероятности
		for (size_t i = 0; i < string.size(); ++i) {
			p[string[i]] += (1 / (double) string.size());
		}

		std::vector<char> alphabet;
		std::vector<double> probability;

		for (auto &e : p) {
			alphabet.push_back(e.first);
			probability.push_back(e.second);
		}

		//		 сортирую массивы по невозрастанию вероятности
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
		CODES = std::vector<std::pair<char, std::string>>(alphabet.size());
		for (size_t i = 0; i < alphabet.size(); ++i) {
			std::get<0>(CODES.at(i)) = alphabet.at(i);
			std::get<1>(CODES.at(i)) = "";
		}
		// передаю вектор функции, которая найдет коды
		AP = std::make_pair(alphabet, probability);
		util::find_codes(CODES, std::make_pair(alphabet, probability), 0, alphabet.size());

		// Кодирование строки
		std::string result;
		for (const char &c : string) {
			result += util::get_code(c);
		}
		string = result;
	} else {
		// размер минимально возможного кода
		/* 1. Получить первый код последовательности,
		 * 	  равный минимально возможному коду
		 * 2. Проверить, есть ли он в таблице кодов
		 * 	  1. Если есть, то заменить код на символ
		 * 	  2. Если нет, добавить к коду следующий символ строки*/
		// результат декодирования строки
		std::string result;
		// длина минимально возможного кода
		size_t min = CODES.at(0).second.length();
		// 111101101000010000100010
		for (int i = 0; i < string.size(); ) {
			// получаю минимально возможный код
			std::string code = string.substr(i, min);
			// получаю символ по его коду или итератор end(), если такого кода нет
			std::vector<std::pair<char, std::string>>::iterator symbol = util::get_symbol(code);
			// пока соотв. код не нашелся
			while (symbol == CODES.end()) {
				// добавляю к код следующий символ
				code += string.substr(i + min, 1);
				min += 1;
				// получаю символ по коду
				symbol = util::get_symbol(code);
			}
			result += symbol->first;
			min = CODES.at(0).second.length();
			i += code.length();
		}
		string = result;
	}
}
