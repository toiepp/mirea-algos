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

}
