#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <vector>

struct Symbol {
	size_t amount;
	std::string content;
	std::vector<bool> code;

	Symbol(size_t amount, std::string content, std::vector<bool> code)
		: amount(amount), content(content), code(code) {}

	Symbol(std::pair<char, size_t> s_to_a) : amount(s_to_a.second) {
		content = std::string(1, s_to_a.first);
	}
};

std::ostream &operator<<(std::ostream &out, const Symbol &symbol) {
	out << symbol.content << "(" << symbol.amount << ")\t=";
	for (size_t i = 0; i < symbol.code.size(); ++i) {
		out << std::setw(10)
			<< std::right << symbol.code.at(i);
	}
	return out;
}

Symbol operator+(Symbol &left, Symbol &right) {
	Symbol new_symbol(left.amount, left.content, left.code);
	new_symbol.amount += right.amount;
	new_symbol.content += right.content;
	return new_symbol;
}

std::vector<Symbol> create_alphabet(std::string &);

std::pair<Symbol, Symbol> get_two_min(std::vector<Symbol> &symbols);

void huffman(std::string &text, bool encode = true);

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

	std::string default_str_en_short = "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"
									   "ddddddddddddddddddddddddddddddddddddddd"
									   "aaaaaaaaaaaaaaaaaaaaaaaaaaa"
									   "eeeeeeeeeeee"
									   "ccccccccc";
	huffman(default_str_en_short);
	return 0;
}

void huffman(std::string &text, bool encode) {
	if (encode) {
		// получаю алфавит
		std::vector<Symbol> alphabet = create_alphabet(text);
		// Пока в алфавите не останется символ без пары
		// либо вообще не останется символов
		std::vector<Symbol> new_alphabet;
		while (alphabet.size() != 0 || alphabet.size() != 1) {
			std::pair<Symbol, Symbol> mins = get_two_min(alphabet);
			mins.second.code.push_back(1);
			mins.first.code.push_back(0);
			new_alphabet.push_back(mins.second + mins.first);
		}
	} else {
	}
}

std::vector<Symbol> create_alphabet(std::string &text) {
	std::map<char, size_t> symbol_to_amount;
	std::vector<Symbol> result;
	std::for_each(text.begin(), text.end(),
				  [&symbol_to_amount](const char &c) {
					  symbol_to_amount[c] += 1;
				  });
	std::for_each(symbol_to_amount.begin(), symbol_to_amount.end(),
				  [&result](const auto &p) {
					  Symbol symbol(p);
					  result.push_back(symbol);
				  });
	// сортирую алфавит по невозрастанию на основе кол-ва символов в алфавите
	std::sort(result.begin(), result.end(),
			  [&](Symbol const &left, Symbol const &right) {
				  return left.amount > right.amount;
			  });
	return result;
}

std::pair<Symbol, Symbol> get_two_min(std::vector<Symbol> &symbols) {
	std::vector<Symbol>::iterator min1 =
			std::min_element(symbols.begin(), symbols.end(),
							 [](const Symbol &s1, const Symbol &s2) {
								 return s1.amount < s2.amount;
							 });
	symbols.erase(min1, min1 + 1);
	std::vector<Symbol>::iterator min2 =
			std::min_element(symbols.begin(), symbols.end(),
							 [](Symbol &s1, Symbol &s2) {
								 return s1.amount < s2.amount;
							 });
	symbols.erase(min2, min2 + 1);
	return std::make_pair(*min2, *min1);
}
