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
	// a b c a b d 	==> 0 0 0 1 2 0
	// a b				l = 2
	// a b c			l = 3
	// a b c a			l = 4
	// a b c a b		l = 5
	std::vector<int> pf(pat.length(), 0);
	std::string prefix;
	for (int i = 2; i < pat.length(); ++i) {
		int max = 0; // макс. длина одинаковых префикса и суффикса в префиксе
		prefix = pat.substr(0, i);
		int j = 1;
		for (; j < i; ++j) {
			std::string p_on_start = prefix.substr(0, j);
			std::string p_on_end = prefix.substr(prefix.length() - j, i);
			if (p_on_start == p_on_end) {
				if (p_on_start.length() > max) {
					max = (int) p_on_start.length();
				}
			}
		}
		pf[j - 1] = max;
	}
	return -1;
}
