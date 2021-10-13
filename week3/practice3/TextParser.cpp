#include "TextParser.h"

size_t C = 0;
size_t M = 0;
size_t F = 0;

TextParser::TextParser(std::string &s) : sentence(s) {}

void TextParser::set_new(std::string &s) {
	this->sentence = s;
}

std::string TextParser::find_longest_with_same_edges() {
	std::string result;
	// Значение самой длинной строки с одинаковыми буквами по краям
	size_t max_length = 0;
	// позиция первой буквы проверяемого слова
	size_t flp = 0;
	// позиции последней буквы проверяемого слова
	size_t llp = sentence.find(' ', flp) - 1;

	while (llp != 18446744073709551614U) {
		C++;
		if (sentence[flp] == sentence[llp]) {
			M++;
			if (llp - flp + 1 > max_length) {
				F++;
				max_length = llp - flp + 1;
				result = sentence.substr(flp, max_length);
			}
		}
		flp = llp + 2;
		llp = sentence.find(' ', flp) - 1;
	}
	if (sentence[flp] == sentence[sentence.length() - 1]) {
		M++;
		if (sentence.length() - 1 - flp + 1 > max_length) {
			F++;
			max_length = sentence.length() - 1 - flp + 1;
			result = sentence.substr(flp, max_length);
		}
	}
	std::cout << "(С=" << C << ", M=" << M << ", F=" << F << ") ";
	C = M = F = 0;
	return result;
}

// f(k) = k - π(k) + 1 - формула расчета сдвига образца
size_t TextParser::find_last(const std::string &pat) {
	std::vector<int> pf(pat.length(), 0);
	// Префикс-функция
	for (int i = 2; i < pat.length(); ++i) {
		std::string prefix = pat.substr(0, i);
		for (int j = 1; j < i; ++j) {
			std::string p_on_start = prefix.substr(0, j);
			if (p_on_start == prefix.substr(prefix.length() - j, i)) {
				pf[i - 1] = (int) p_on_start.length();
			}
		}
	}

	size_t last = std::string::npos;
	int k = 0;
	for (int i = 0; i < sentence.length(); ++i) {
		while (k && (pat[k] != sentence[i])) {
			k = pf.at(k - 1);
		}

		if (++k == pat.length()) last = i - pat.length() + 1;
	}

	return last;
}
