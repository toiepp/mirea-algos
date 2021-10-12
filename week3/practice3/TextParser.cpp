#include "TextParser.h"

TextParser::TextParser(std::string &s) : sentence(s) {}

void TextParser::set_new(std::string &s) {
	this->sentence = s;
}

std::string TextParser::find_longest_with_same_edges() {
	std::string result;
	size_t max_length = 0;                   // Значение самой длинной строки с одинаковыми буквами по краям
	size_t flp = 0;                          // позиция первой буквы проверяемого слова
	size_t llp = sentence.find(' ', flp) - 1;// позиции последней буквы проверяемого слова
	while (llp != 18446744073709551614U) {
		if (sentence[flp] == sentence[llp]) {
			if (llp - flp + 1 > max_length) {
				max_length = llp - flp + 1;
				result = sentence.substr(flp, max_length);
			}
		}
		flp = llp + 2;
		llp = sentence.find(' ', flp) - 1;
	}
	if (sentence[flp] == sentence[sentence.length() - 1]) {
		if (sentence.length() - 1 - flp + 1 > max_length) {
			max_length = sentence.length() - 1 - flp + 1;
			result = sentence.substr(flp, max_length);
		}
	}
	return result;
}

size_t TextParser::find_last(const std::string &pat) {
	std::vector<int> pf(pat.length(), 0);
	// Префикс-функция
	for (int i = 2; i < pat.length(); ++i) {
		std::string prefix = pat.substr(0, i);
		int j = 1;
		for (; j < i; ++j) {
			std::string p_on_start = prefix.substr(0, j);
			if (p_on_start == prefix.substr(prefix.length() - j, i)) {
				pf[i - 1] = (int) p_on_start.length();
			}
		}
	}

	// индекс последнего вхождения образа
	size_t last = std::string::npos;
	for (int k = 0, i = 0; i < sentence.length(); ++i) {
		while ((k > 0) && (pat[k] != sentence[i])) {
			k = pf[k - 1];
		}

		k++;

		// если произошло полное совпадение образа
		if (k == pat.length()) {
			last = i - pat.length() + 1;
			std::cout << "(" << last << ") ";
		}
	}

	return last;
}
